#include"dict-header.h"
#include "dict-soundex.h"
#include <string.h>
//----------------------------------------------------------
//----------------------------------------------------------
BTA *dictOpen(BTA *root, char *dict)
{
	root = btopn(dict, 0, 0);
	if (root == NULL)
		root = btcrt(dict, 0, 0);	
	return root;
}
//----------------------------------------------------------
// Read from file
int readFile(BTA *root,trieNode **node, int dsize){
	char path[256],engWord[256], vietWord[256];
	strcpy(path, "vnedict.txt");
	FILE *fi = fopen(path, "r");
	if(fi==NULL) return 0;
	while(1)
	{
		fscanf(fi, "%[^':']: %[^'\n']\n", engWord, vietWord);
		trieInsert(node,engWord);
		btins(root, engWord, vietWord, dsize);
		if(feof(fi)) break;
	}
	fclose(fi);
	return 1;
}
//----------------------------------------------------------
// Insert
int dictInsert(BTA *root,trieNode **node, int dsize, char* engWord, char* vietWord)
{	
	// Insert du lieu
	if (btins(root, engWord, vietWord, dsize) == 0){
		trieInsert(node,engWord);
		return 1;}
	else
		return 0;
	
}
//------------------------------------------------------------
void dictUpdate(BTA *root, int dsize, int *rsize, char* engWord, char* vietWord)
{
	(btupd(root, engWord, vietWord, dsize) == 0);
}
//------------------------------------------------------------
//----------------------------------------------------------
void dictDeleteNode(BTA *root, int dsize, int *rsize, char* engWord)
{
	init();
	btpos(root, 1);
	btdel(root, engWord); // Xoa tu trong tu dien
}
//----------------------------------------------------------
void dictPrint(BTA *root, int dsize, int *rsize)
{	
	FILE *ptr=fopen("vnedict-copy.txt","w+");
	// Check tu dien co dang trong hay khong
	char engWord[256], vietWord[256];
	btpos(root, 1);
	if (btseln(root, engWord, vietWord, dsize, rsize) != 0)
	{return;}
	btpos(root, 1);
	
	// Duyet va in toan bo tu dien
	while (btseln(root, engWord, vietWord, dsize, rsize) == 0)
		fprintf(ptr,"%s: %s\n", engWord, vietWord);
	fclose(ptr);
}
//----------------------------------------------------------
void dictDeleteAll(BTA *root, int dsize, int *rsize)
{
	if(rsize==NULL) return;
	int check;
	// Check tu dien co dang trong hay khong
	char engWord[256], vietWord[256];
	btpos(root, 1);
	if (btseln(root, engWord, vietWord, dsize, rsize) != 0)
	{
		return;
	}
	btpos(root, 1);

	// Duyet va xoa toan bo tu dien
	while (btseln(root, engWord, vietWord, dsize, rsize) == 0)
		check = btdel(root, engWord);
	return;
}
//----------------------------------------------------------
//----------------------------------------------------------
