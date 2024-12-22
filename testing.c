#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void modify(char* new,char* old){
    strcpy(old, new);
}
int main(){
    char first[5]; 
    char second[6];
    strcpy(first, "vlad");
    strcpy(second, "cmptn");
    printf("%as\n",first);

    modify(second, first);
    printf("%s",first);
    return 0;
}