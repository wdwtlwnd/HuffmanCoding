//Written by Frans-Lukas Lövenvald <franslukas@gmail.com>
//May be used in the course Datastrukturer och Algoritmer (C) at Umeå University.
//Usage exept those listed above requires permission by the author.

#include <stdbool.h>
#include "table.h"
#include "tree_3cell.h"
#include "bitset.h"
#include "dlist.h"

typedef struct{
    char character;
    int numOccurences;
} charElement;

typedef struct{
    char character;
    bool leftOrRight;
} treeNode;

typedef struct{
    binary_tree *subTree;
    int value;
} subTree;


/*
// Purpose: Read a file and create an array with all of the characters. 
// Parameters: char* fileName - The name of the file being read.
// Returns: A list with all the characters read. 
*/
dlist* readFile(char* fileName);

/*
//  Purpose: compare function for the table data type.
//  Parameters: KEY key1 - pointer to the first value to compare.
               KEY key2 - pointer to the second value to compare.
    Returns: if val1 equals val2 it returns 0, otherwise it returns 1.
*/
int compareFunction(KEY key1, KEY key2);

/*
// Purpose: Analyse the number of occurences of characters from string chars.
// Paramters: char* dlist - A list with the characters to analyse.
// Returns: An charElement array with the number of occurences of every character.
*/
charElement *frequencyAnalasys(dlist* chars);

/*
// Purpose: Create a huffman tree with the analysed characters from the array aChars. 
// Parameters: charElement* aChars - An array with the analysed charaters based on frequency.
// Returns: A huffman tree. 
*/
binary_tree createHuffmanTree(charElement *aChars);

    
/*
// Purpose: Write chars to the textfile filename.
*/
void writeOutputFile(dlist* chars, char *filename);

/*
// Purpose: Decode the array with the help of the huffmantree huffmanTree.
// Parameters: dlist *chars - A list with the characters to decode. Written in unreadable compressed bit format.
               binary_tree huffmanTree - the huffman tree used to decode the list.
// Returns: A list with the decoded characters.
*/
dlist* decodeChars(dlist* chars, binary_tree *huffmanTree);

/*
// Purpose: Create a string with the compressed characters from the huffman table and the string chars.
// Parameters: dlist *chars - A list with the characters to compress.
               binary_tree huffmanTable - The table which shows what characters have what bit value 
                                   ex a = 0, b = 100, c = 110, ... = 1111...
// Returns: An array with the compressed characters in bitformat.
*/
char* compressChars(char* chars, binary_tree *huffmanTree);

/*
// Purpose: Create a table where each character (key) has a bit value to use for compression.
// Parameters: dlist *chars - A list with the characters to use in the tree.
               binary_tree huffmanTree - the huffman tree used to create the table with.
// Returns: An array to use for compressing strings.
*/
charElement *createHuffmanArray(dlist* chars, binary_tree *huffmanTree);

/*
// Purpose: Sort the keys and values from the analysed character array into an array to make for easier tree creation.
// Parameters: charElement *aChars - An array with the analysed charaters based on frequency.
*/
void reverseSortArray(charElement *aChars);

/*
// Purpose: Get the bit at position n of character data.
// Parameters: int n - position of the bit to get of a char of one byte.
               char data - the character to get the bit from.
// Returns: The value of the bit at position n.
*/
bool getNthBit(int n, char data);


/*
//  Purpose: Change the bit at position n of character data to bool val.
//  Parameters: int n - position of the bit to change at character data.
               char data - the character to change the bit at.
               bool val - the value to change the bit at position n to.
//  Comment: Written with the help of user Jeremy Ruten on stackoverflow:
            http://stackoverflow.com/a/47990.
*/
void setNthBit(int n, char* data, bool val);

