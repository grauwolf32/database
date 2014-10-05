#include <string.h>
#include "mydb.h"

int insert_key(struct BTreeNode* head,char* key)
{
	struct BTreeNode* r = head;
 	if(head->nKeys == 2*BTREE_KEY_CNT - 1)
	{
	 struct BTreeNode* s = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
	 head = s;
	 s->leaf = 0;
	 s->page = 0;
	 s->parentPage = 0;
	 s->chld[0] = r;
	 split_child(s,0);// split_child(s,1)
	 insert_nonfull(s,key);
	}
	else insert_nonfull(r,k);
}

struct BTreeNode* search_key(struct BTreeNode* node,char* key,int& num,const struct DB* db)
{
 int i = 0;
 while(i < node->nKeys)i++;
 if(i < node->nKeys && compare(key,node->keys,i)){num = i;return node;}
 else if(node->leaf)return NULL;
 else {struct BTreeNode* c_i = disk_read(node->chld[i].page);return search_key(c_i,key,num,db);}
}

//Для сравнения ключей используем strcmp

BTreeNode* disc_read(const struct DB* db,int page)
{
	long int addr = db->head_offset+page*sizeof(struct BTreeNode));
	BTreeNode* res = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
	fseek(db->fd,addr,SEEK_SET);
	fread(res,sizeof(BTreeNode),1,db->fd);
	return res;
}

