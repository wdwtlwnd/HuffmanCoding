#include <stdio.h>
#include "huffman.h"
#include <string.h>
#include "dlist.h"

#define CHARSETSIZE 256

/*
// Purpose: Read a file and create an array with all of the characters. 
// Parameters: char* fileName - The name of the file being read.
// Returns: A list with all the characters read. 
*/
dlist* readFile(char* fileName){
    FILE *fp;
    printf("test\n");
    fp = fopen(fileName, "r");
    
    dlist *chars = dlist_empty();
    dlist_setMemHandler(chars, free);
    dlist_position pos = dlist_first(chars);
    char ch;

    if(fp == NULL){
        printf("Can't read file\n");
        dlist_free(chars);
        exit(0);
    }
    while((ch = fgetc(fp)) != EOF){
        char *charToSave = malloc(sizeof(char));
        *charToSave = ch;
        pos = dlist_insert(chars, pos, (int*)charToSave);
    }

    fclose(fp);
    return chars;
}

/*
//  Purpose: compare function for the table data type.
//  Parameters: KEY key1 - pointer to the first value to compare.
               KEY key2 - pointer to the second value to compare.
    Returns: if val1 equals val2 it returns 0, otherwise it returns 1.
*/
int compareFunction(KEY key1, KEY key2){
    if(key1 != NULL && key2 != NULL){
        return (*(int*) key1) != (*(int*)key2);
    } else{
        return 1;
    }
}

/*
// Purpose: Analyse the number of occurences of characters from string chars.
// Paramters: char* dlist - A list with the characters to analyze.
// Returns: An charElement array with the number of occurences of every character.
*/
charElement *frequencyAnalasys(dlist* chars){
    charElement *analysedSymbols = malloc(sizeof(charElement) * CHARSETSIZE);

    //add every character from charset of one byte to the array
    for(int i = 0; i < CHARSETSIZE; i++){
        analysedSymbols[i].character = i;
        analysedSymbols[i].numOccurences = 0;
    }

    //increment every character found in string to use as freqvency text.
    dlist_position pos = dlist_first(chars);
    while(!dlist_isEnd(chars, pos)){
        char *charToIncrease = ((char *)dlist_inspect(chars, pos));
        analysedSymbols[*charToIncrease].numOccurences++;
        pos = dlist_next(chars, pos);
    }
    for(int i = 0; i < CHARSETSIZE; i++){
        printf("%c = %d\n", analysedSymbols[i].character, analysedSymbols[i].numOccurences);
    }
    return analysedSymbols;
}

/*
// Purpose: Create a huffman tree with the analysed characters from the array aChars. 
// Parameters: charElement *aChars - An array with the analysed charaters based on frequency.
// Returns: A huffman tree. 
*/
binary_tree *createHuffmanTree(charElement *aChars){
    binary_tree *huffTree = binaryTree_create();
    binaryTree_setMemHandler(huffTree, free);
    reverseSortArray(aChars);
    int *size = malloc(sizeof(int));
    *size = CHARSETSIZE;

    //keep creating trees with two children out of the analysed character array.
    while(*size > 0){
        charElement *elementToAdd = malloc(sizeof(charElement));
        elementToAdd->tree = binaryTree_create();
        binaryTree_setMemHandler(elementToAdd->tree, free);
        binaryTree_pos pos = binaryTree_root(elementToAdd->tree);
        binaryTree_pos left = binaryTree_insertLeft(elementToAdd->tree, pos);
        binaryTree_pos right = binaryTree_insertRight(elementToAdd->tree, pos);
        charElement *leftChild = malloc(sizeof(charElement));
        charElement *rightChild = malloc(sizeof(charElement));
        *leftChild = aChars[*size - 1];
        *rightChild = aChars[*size - 2];
        elementToAdd->numOccurences = leftChild->numOccurences + rightChild->numOccurences;
        binaryTree_setLabel(elementToAdd->tree, leftChild, left);
        binaryTree_setLabel(elementToAdd->tree, rightChild, right);
        *size -= 1;
        insertElement(aChars, size, elementToAdd);
        /*printf("\n\n");
        for(int i = 0; i < *size; i++){
            printf("%d=%d,", i, aChars[i].numOccurences);
        }
        printf("\n\n");*/
    }
    printf("%d=%d,", 0, aChars[0].numOccurences);
    free(size);
    return aChars[0].tree;
};

/*
// Purpose: Add element to array and sort it afterwards.
// Parameters: charElement *chars - A list with the characters to compress.
               int *size - size of the array
               charElement *element - the element to insert into the array.
*/
void insertElement(charElement *aChars, int *size, charElement *element){
    // search for where to insert element.
    for(int i = *size - 1; i >= 0; i--){
        if(aChars[i].numOccurences >= element->numOccurences || i == 0){
            //move all values to make space for inserted element.
            for(int j = *size; j > i; j--){
                aChars[j] = aChars[j-1];
            }
            aChars[i] = *element;
            break;
        }
    }
}

/*
// Purpose: Sort the keys and values from the analysed character table into an array to make for easier tree creation.
// Parameters: Table aChars - A table with the analysed charaters based on frequency.
// Returns: A charElement array sorted by the number of occurences of every character from largest to smallest.
*/
void reverseSortArray(charElement *aChars){
    //bubble sort the array
    for(int i = 0; i < CHARSETSIZE - 1; i++){
        for(int j = 0; j < CHARSETSIZE - i - 1; j++){
            if(aChars[j].numOccurences < aChars[j + 1].numOccurences){
                charElement swap = aChars[j];
                aChars[j] = aChars[j+1];
                aChars[j+1] = swap;
            }

        }
    }
}

    
/*
// Purpose: Write chars to the textfile filename.
*/
void writeOutputFile(dlist *chars, char *filename);

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
char* compressChars(dlist* chars, binary_tree *huffmanTable);

/*
// Purpose: Create a table where each character (key) has a bit value to use for compression.
// Parameters: dlist *chars - A list with the characters to use in the tree.
               binary_tree huffmanTree - the huffman tree used to create the table with.
// Returns: A table to use for compressing strings.
*/
Table createHuffmanTable(dlist* chars, binary_tree *huffmanTree);

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

/*
//  Purpose: 
//  Parameters: 
*/
int main(int argc, char *argv[]){
    printf("%s\n", argv[1]);
    printf("hello\n");
    if(argc < 2){
        printf("Too few arguments!\n");
        return 1;
    }
    if(strcmp(argv[1], "-encode") == 0){
        dlist *chars = readFile("testFile.txt");
        printf("working so far...\n");
        charElement *analysedSymbols = frequencyAnalasys(chars);
        binary_tree *tree = createHuffmanTree(analysedSymbols);
        
        dlist_free(chars);
        free(analysedSymbols);
        printf("program works!\n");



    } else{
        printf("nooo\n");
    }
}