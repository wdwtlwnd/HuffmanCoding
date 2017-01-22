#include <stdio.h>
#include "bitset.h"
#include <stdbool.h>


bool getBit(int n, char data){
    return (data >> n) & 1;
}
void setBit(int n, char *data, bool val){
    //Changing the nth bit of data to val, from user Jeremy Ruten on stackoverflow:
    // http://stackoverflow.com/a/47990
    *data ^= (-val ^ *data) & (1 << n);
}
int main(){
    printf("hello, world!\n");
    //bitset *test = bitset_empty();
    char testChar = 'b';
    char changeChar = 'a';
    for(int i = 0; i <= 8; i++){
        printf("%d", getBit(i, testChar));
        setBit(i, &changeChar, getBit(i, testChar));
    }
    printf("\n");
    for(int i = 0; i <= 8; i++){
        printf("%d", getBit(i, changeChar));
    }
    printf("\n%c\n", changeChar);
}

