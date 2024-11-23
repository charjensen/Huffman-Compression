#include "hcompress.h"

int main(int argc, char *argv[]) {

  // Check the make sure the input parameters are correct

   if (argc != 3) {
      printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);

    exit(1);

  }

  // Create the frequency table by reading the generic file

  Huffnode* leafNodes = createFreqTable("decind.txt");

  // Create the huffman tree from the frequency table

  Huffnode* treeRoot = createHuffmanTree(leafNodes);

  // encode

  if (strcmp(argv[1], "-e") == 0) {

    // Pass the leafNodes since it will process bottom up

    encodeFile(argv[2], leafNodes);

  } else { // decode

    // Pass the tree root since it will process top down

    decodeFile(argv[2], treeRoot);

  }

  return 0;

}

Huffnode* createFreqTable(char* fileName) {
	
	// Create new file and create new array of Huffnodes
	FILE* f = fopen(fileName, "r");
	
	Huffnode* h = (Huffnode*)malloc( 128 * sizeof(Huffnode) );
	
	// Fill in the array with ASCII codes 0 - 127 and set each frequency to 0
	for (int i = 0; i < 128; i++) {
		
		h[i].let = i;
		h[i].value = 0;
		
	}
	
	// Create a char that will store each character of the file as it is read
	char c;
	
	// Read in each character and up the frequency for each instance found.
	while ( (c = fgetc(f)) != -1 ) {
	
		h[(int) c].value++;
		
	}

return h;

}

Huffnode* createHuffmanTree(Huffnode* leafNodes) {
	
	//Make a new linked list
	LinkedList* linkedNodes = llCreate();
	
	//Add all the leaf nodes into the linked list
	for (int i = 0; i < 128; i++) {
		
		llAdd(&linkedNodes, &leafNodes[i]);
		
	}
	
	// Builds the tree
	while (linkedNodes->next != NULL) {
		//While there is more than one node in the linked list
		
		//Make a parent node in the heap
		Huffnode* parent = (Huffnode*)malloc(1 * sizeof(Huffnode));
		//Remove the first two nodes of the linkedList and return them,
		//Save those nodes into a left and right node
		Huffnode* left = removeFirst(&linkedNodes);
		Huffnode* right = removeFirst(&linkedNodes);
		//Assign the parent's left and right child to the returned removed nodes
		parent->lc = left;
		parent->rc = right;
		//Assign the children's parent to the parent
		left->parent = parent;
		right->parent = parent;
		//Add up the frequencies of the children and assign that to the parents frequency
		parent->value = left->value + right->value;
		
		//Add our new parent back into the linked list
		llAdd(&linkedNodes, parent);
		
	}
	
	//Remove the last node of the linked list (the entire tree) and return that
	return removeFirst(&linkedNodes);
	
}

void encodeFile(char* fileName, Huffnode* leafNodes) {
	
	//Open an existing file from user input to read
	FILE* r = fopen(fileName, "r");
	
	//Make sure file exists
	if (r == NULL) {
		printf("Fatal Error: Please enter a file that exists\n");
		exit(1);
	}
	
	//Create space for the new string name of the .huf file
	//Will always be the original file name + ".huf"
	char* newFile = (char*)malloc( strlen(fileName) * (sizeof(char)));
	sprintf(newFile, "%s", fileName);
	newFile[strlen(fileName) - 4] = '.';
	newFile[strlen(fileName) - 3] = 'h';
	newFile[strlen(fileName) - 2] = 'u';
	newFile[strlen(fileName) - 1] = 'f';
	newFile[strlen(fileName)] = '\0';
	
	//Create the new file with the new name
	FILE* w = fopen(newFile, "w");
	
	//Make space for the encoded character
	unsigned char code = (unsigned char) 0;
	// Create a char that will store each character of the file as it is read
	char c;
	
	//Create int var that will keep track of how many bytes have been written to the encoded character
	int codeMax = 0;
	
	//Create new huffnode pointer that points to the array based on the character read in from the file
	Huffnode* p;
	
	//Create a buffer for the code in an int array
	int temp[16];
	
	//While we read in each character of the file,
	while( ( c = fgetc(r) ) != -1 ) {
		
		//Create var that keeps track of how big the array we write to is
		int j = 0;
		
		//Get the leafnode from the scanned in character
		p = &leafNodes[(int) c];
		
		//Determine whether to write a 1 or 0 to the respective index of the array while we walk up the tree
		while (p->parent != NULL) {
			//If the current node is a right child we write a 1
			if ( (p == p->parent->rc) ) {

				temp[j] = 1;
				j++;
				
			}
			//Otherwise we right a 0 if it is a left node
			else {
				
				temp[j] = 0;
				j++;
				
			}
			
		//Walk up the tree each iteration
		p = p->parent;
		
		}
		
		//Write the encoded character
		for (int k = j-1; k >= 0; k--) {
			
			code = code << 1;
		
			if (temp[k] == 1) {
				
				code = code | 1;
				
			}
			
			codeMax++;
			
			//Wrtie the character after writing 8 bits
			//Reset the counter and clear the encoded character
			 if (codeMax == 8) {
				 
				codeMax = 0;
				fprintf(w, "%c", code);
				code = (unsigned char) 0;
				
			 }
			
		}
		
		
		
	}
	
	//Close both files
	fclose(r);
	fclose(w);
	
}

void decodeFile(char* fileName, Huffnode* treeRoot) {
	
	//Open file to read
	FILE* r = fopen(fileName, "r");
	
	//Make sure files exists
	if (r == NULL) {
		printf("Fatal Error: Please enter a file that exists\n");
		exit(1);
	}
	
	//Create new name for .dec file
	char* newFile = (char*)malloc((strlen(fileName) + 5) * (sizeof(char)));
	
	sprintf(newFile, "%s", fileName);
	newFile[strlen(fileName)] = '.';
	newFile[strlen(fileName) + 1] = 'd';
	newFile[strlen(fileName) + 2] = 'e';
	newFile[strlen(fileName) + 3] = 'c';
	newFile[strlen(fileName) + 4] = '\0';
	
	//Start writing to new file
	FILE* w = fopen(newFile, "w");
	
	//Char that scans in each character of file
	unsigned char c;
	
	//Start at root of tree
	Huffnode* p = treeRoot;
	
	//Until we get to the end of the file
	while ( !(feof(r)) ) {
	
		//Read in new character
		c = fgetc(r);
		
		//Create a bitset of 10000000
		unsigned char d = (unsigned char) 128;
		
		//For each bit
		for(int i = 0; i < 8; i++)
		{
		
			//Compare the current characters binary code to our bitset
			//If we get a 1 then walk down the right child
			//Else we are walking down the left child
			//When we find a leafnode we write that character to the file
			if( (c & d) > 0)
			{
				if(p->rc != NULL)
				{	
					p = p->rc;
				 } 			
			} else {
				if(p->lc != NULL)
				{
					p = p->lc;
				} 
			}
			
			d = d >> 1;
			
			if (p->rc == NULL && p ->lc == NULL) {
					fprintf(w, "%c", p->let);
					p = treeRoot;
				}
			
		}

	}
	
	//Removes faulty r that is encoded into an EOF
	fseek(w, -1, SEEK_END);
	fprintf(w, "%c", ' ');
	
	//Close the file
	fclose(r);
	fclose(w);
	
}