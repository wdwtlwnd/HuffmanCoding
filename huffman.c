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
    
    /*pos = dlist_first(chars);
    while(!dlist_isEnd(chars, pos)){
        ch = *(char*)dlist_inspect(chars, pos);
        printf("%c", ch);
        pos = dlist_next(chars, pos);
    }*/
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
// Returns: A table with the key being the character analyzed and the value being the number of occurences. 
*/
Table *frequencyAnalasys(dlist* chars){
    /*Table *analyzedSymbols = table_create(compareFunction);
    table_setKeyMemHandler(analyzedSymbols, free);
    table_setValueMemHandler(analyzedSymbols, free);
    */
    charElement *analyzedSymbols = malloc(sizeof(charElement) * CHARSETSIZE);


    //add every character from charset of one byte to table
    for(int i = 0; i < CHARSETSIZE; i++){
        analyzedSymbols[i].character = i;
        analyzedSymbols[i].numOccurences = 0;
/*
        int* valToInsert = calloc(0,sizeof(int));
        int* keyToInsert = malloc(sizeof(int));
        *keyToInsert = i;
        table_insert(analyzedSymbols, keyToInsert, valToInsert);*/
    }

    //increment every character found in string to use as freqvency text.
    dlist_position pos = dlist_first(chars);
    while(!dlist_isEnd(chars, pos)){
        char *charToIncrease = ((char *)dlist_inspect(chars, pos));
        int *val = table_lookup(analyzedSymbols, charToIncrease);
        if(val != NULL){
            *val = *val + 1;
        }
        else{
            printf("fail");
        }
        pos = dlist_next(chars, pos);
    }
    /*
    for(int i = 0; i < CHARSETSIZE; i++){
        printf("char %c = %d\n", i, *(int*) table_lookup(analyzedSymbols, &i));
    }
    char ch;
    pos = dlist_first(chars);
    while(!dlist_isEnd(chars, pos)){
        ch = *(char*)dlist_inspect(chars, pos);
        printf("%c", ch);
        pos = dlist_next(chars, pos);
    }*/

    return analyzedSymbols;
}

/*
// Purpose: Create a huffman tree with the analyzed characters from the array aChars. 
// Parameters: Table aChars - A table with the analyzed charaters based on frequency.
// Returns: A huffman tree. 
*/
binary_tree createHuffmanTree(Table *aChars){
    /*binary_tree huffTree = binaryTree_create();
    binaryTree_setMemHandler(huffTree, free);
*/

};

/*
// Purpose: Sort the keys and values from the analyzed character table into an array to make for easier tree creation.
// Parameters: Table aChars - A table with the analyzed charaters based on frequency.
// Returns: A charElement array sorted by the number of occurences of every character from smallest to largest.
*/
charElement* createSortedAnalyzedArray(Table *aChars){
    charElement *chars = malloc(sizeof(charElement) * 256);
    while(!table_isEmpty(aChars)){
        for(int i = 0; i < 256; i++){
            int *smallestValue = table_lookup(aChars, &i);
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
char* compressChars(char* chars, Table *huffmanTable);

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
        Table *analyzedSymbols = frequencyAnalasys(chars);
        //binary_tree huffTree = createHuffmanTree(analyzedSymbols);
        



        dlist_free(chars);
        table_free(analyzedSymbols);
        printf("program works!\n");



    } else{
        printf("nooo\n");
    }
}