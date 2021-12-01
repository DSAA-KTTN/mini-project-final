#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
//
#define NUM_CHAR 256
//
typedef struct{
	char completeText[256];
} data;
//
typedef struct trieNode {
	bool terminal;
	struct trieNode *children[NUM_CHAR];
} trieNode;
//----------------------------------------------------
trieNode *createNode();
bool trieInsert(trieNode **root, char *signedtext);
bool searchTrie(trieNode *root, char *signedtext);
void printTrieRec(trieNode *node, unsigned char *prefix, int length, data *array, int j);
void printTrie(trieNode *root);
void autocomplete(trieNode *node, char *prefix, data *array);
bool deletestr(trieNode **root, char* signedtext);
//----------------------------------------------------
