# huffman_algo

# Huffman File Compression Utility
This program implements a file compression algorithm based on Huffman coding. It reads in a text file and generates a compressed binary output file using a Huffman tree. The compressed file can be decompressed back to the original file using the same program.

# Team Members
Zhanbolot Bakytbek uulu
# Course Information

This project is developed as part of the Programming Language 2 course at Ala-Too International University.

# Requirements
1. C++ compiler
2. Input file to be compressed

# Usage
To compile the program:
`g++ huffman.cpp -o huffman`

To run the program:

`./huffman input.txt output.bin`
where input.txt is the input file to be compressed, and output.bin is the compressed binary output file.

To decompress the file:

`./huffman output.bin decompressed.txt`
where output.bin is the compressed binary file, and decompressed.txt is the decompressed text file.

# Implementation Details
The program first builds a frequency table for the characters in the input file. It then uses the frequency table to build a Huffman tree, which is used to generate codes for each character. The codes are then used to compress the input file into a binary output file.

To compress the input file, the program reads in each character and looks up its code in the code table. It concatenates the codes into a single bitstream and writes out the bitstream as bytes to the output file. If the bitstream does not have enough bits to form a complete byte, the program pads the bitstream with zeros to fill up the last byte.

To decompress the binary output file, the program reads in each byte and converts it to a bitstream. It then traverses the Huffman tree, starting from the root, and follows the code for each bit in the bitstream to determine the corresponding character. The characters are then written out to the decompressed output file.
