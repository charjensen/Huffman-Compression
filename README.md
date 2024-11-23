# Huffman Compression and Decompression

## Overview

This project implements Huffman Compression and Decompression. Huffman coding is a lossless data compression algorithm. It assigns variable-length codes to input characters, with shorter codes assigned to more frequently occurring characters.

## Files

- `hcompress.c`: Contains the main function for compressing and decompressing files.
- `linkedlist.c`: Implements a linked list used for creating the Huffman tree.

## Usage

### Compress a File

To compress a file, use the `-e` flag followed by the filename:
hcompress -e filename


This will create a compressed file with the `.huf` extension.

### Decompress a File

To decompress a file, use the `-d` flag followed by the compressed filename:
hcompress -d filename.huf


This will create a decompressed file with the `.dec` extension.

## Implementation Details

### Frequency Table

The function `createFreqTable` reads a file and creates a frequency table of characters.

### Huffman Tree

The function `createHuffmanTree` takes the frequency table and creates a Huffman tree.

### Encoding

The function `encodeFile` reads the input file and creates a compressed file using the Huffman tree.

### Decoding

The function `decodeFile` reads the compressed file and decodes it back to the original file using the Huffman tree.

## Linked List

The `linkedlist.c` file provides functionality to create a linked list, add nodes in order, display the list, and remove nodes from the list.
