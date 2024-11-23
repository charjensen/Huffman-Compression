#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

Huffnode* createFreqTable(char* fileName);
Huffnode* createHuffmanTree(Huffnode* leafNodes);
void encodeFile(char* fileName, Huffnode* leafNodes);
void decodeFile(char* fileName, Huffnode* treeRoot);