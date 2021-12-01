#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dict-autocomplete.h"
//------------------------------------------------------------------
trieNode *createNode() {
	trieNode *newNode = malloc(sizeof *newNode);

	for (int i = 0; i < NUM_CHAR; i++)
	{
		newNode->children[i] = NULL;
	}
	newNode->terminal = false;
	return newNode; 
}
//------------------------------------------------------------------
bool trieInsert(trieNode **root, char *signedtext)
{
	if (*root == NULL) {
		*root = createNode();
	}

	unsigned char *text = (unsigned char *)signedtext;
	trieNode *tmp = *root;
	int length = strlen(signedtext);

	for (int i = 0; i < length; i++)
	{
		if (tmp->children[text[i]] == NULL) {
			//create a new node
			tmp->children[text[i]] = createNode();
		}
		tmp = tmp->children[text[i]];
	}
	if (tmp->terminal) {
		return false;
	}
	else {
		tmp->terminal = true;
		return true;
	}
}
//-------------------------------------------------------------------
bool searchTrie(trieNode *root, char *signedtext)
{
	unsigned char *text = (unsigned char *)signedtext;
	int length = strlen(signedtext);
	trieNode *tmp = root;

	for (int i = 0; i < length; i++) 
	{
		if (tmp->children[text[i]] == NULL) {
			return false;
		}
		tmp = tmp->children[text[i]];
	}
	return tmp->terminal;
}
//-------------------------------------------------------------------
void printTrieRec(trieNode *node, unsigned char *prefix, int length, data *array, int j)
{
	unsigned char newPrefix[length+2];
	memcpy(newPrefix, prefix, length);
	newPrefix[length+1] = 0;

	if (node->terminal) {
		strcpy(array[j].completeText, (const char *)prefix);
	}
	for (int i = 0; i < NUM_CHAR; i++) {
		if (node->children[i] != NULL)
		{
			newPrefix[length] = i;
			printTrieRec(node->children[i], newPrefix, length+1, array, j++);
		}
	}
}
//-------------------------------------------------------------------
void printTrie(trieNode *root)
{
	if (root == NULL) {
		printf("Empty!\n");
		return;
	}
	data array[256];
	printTrieRec(root, NULL, 0, array, 0);
}
//-------------------------------------------------------------------
void autocomplete(trieNode *node, char *prefix, data *array)
{
	unsigned char *newPrefix = (unsigned char *)prefix;
	int length = strlen(prefix);
	trieNode *tmp = node;
	int i = 0;
	for ( ; i < length; i++)
	{
		if (tmp->children[newPrefix[i]] == NULL)
			return;
		tmp = tmp->children[newPrefix[i]];
	
	}
		printTrieRec(tmp, newPrefix, length, array, 0);
	
}
bool node_has_children(trieNode *node) {
    if (node == NULL) return false;
    for (int i=0; i < 256; i++) {
         if (node->children[i] != NULL) {
             //there's at least one child
             return true;
		 }
	}
    return false;
}
trieNode* deletestr_rec(trieNode *node, unsigned char *text, bool *deleted){
    if (node == NULL) return node;
    if (*text == '\0'){
        if (node->terminal) {
            node->terminal = false;
            *deleted = true;
            if (node_has_children(node) == false){
                free(node);
                node = NULL;
			}
		}
        return node;
		}
    node->children[text[0]] = deletestr_rec(node->children[text[0]], text+1, deleted);
	if (*deleted && node_has_children(node) == false &&
     node->terminal == false){
           free(node);
           node = NULL;
	 }
    return node;
}
bool deletestr(trieNode** root, char *signedtext) {
    unsigned char *text = (unsigned char *)signedtext;
    bool result = false;
    if (*root == NULL) return false;
    *root = deletestr_rec(*root, text, &result);
    return result;
}