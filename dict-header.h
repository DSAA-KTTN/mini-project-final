#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"btree.h"
#include"dict-autocomplete.h"
//----------------------------------------------------------
BTA *dictOpen(BTA *root, char *dict);
int readFile(BTA *root,trieNode **node, int dsize);
int dictInsert(BTA *root,trieNode **node, int dsize, char *engWord, char* vietWord);
void dictUpdate(BTA *root,  int dsize, int *rsize, char* engWord, char* vietWord);
void dictDeleteNode(BTA *root, int dsize, int *rsize, char *engWord);
void dictPrint(BTA *root, int dsize, int *rsize);
void dictDeleteAll(BTA *root, int dsize, int *rsize);
