#include <stdint.h>
#include "mydb.h"

#define BTREE_KEY_CNT 3
#define BTREE_KEY_LEN 128
#define BTREE_VAL_LEN 4092
#define BTREE_CHLD_CNT (BTREE_KEY_CNT+1)

struct BTreeNode {
	size_t   page;
	size_t   parentPage;
	uint32_t nKeys;
	int	 leaf;
	size_t *chld;
	char   *keys;
	size_t *vals;//Указатель на страницу, в которой храняться данные
};

int insert_key(struct BTreeNode* head,char* key);
struct BTreeNode* search_key(struct BTreeNode* node,char* key,int& num,const struct DB* db);
int delete_key(struct BTreeNode* head,char* key);


