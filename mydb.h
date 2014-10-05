#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
/* check `man dbopen` */
struct DBT {
     void  *data;
     size_t size;
};

struct DB{
    /* Public API */
    /* Returns 0 on OK, -1 on Error */
    int (*close)(const struct DB *db);
    int (*del)  (const struct DB *db, const struct DBT *key);
    /* Returns data into *data */
    /* e.g.
     * struct DB db = dbopen(...);
     * struct DBT key = {
     *     .data = "hello"
     *     .size = 6
     * }
     * struct DBT d = {
     *     .data = ""
     *     .size = 0
     * }
     * db.get(db, *key, *d);
     * // d.data now stores data with length d.size
     * // d.data is (c/m)alloc'ed inside BTree
     * // Caller must free d.data
     * */
    struct BTreeNode* head;
    size_t head_offset; 

    FILE* fd;
    int (*get)  (const struct DB *db, struct DBT *key, struct DBT *data);
    int (*put)  (const struct DB *db, struct DBT *key, const struct DBT *data);
    /* int (*sync)(const struct DB *db); */
    /* Private API */
    /* ... */
}; /* Need for supporting multiple backends (HASH/BTREE) */

struct DBC {
        /* Maximum on-disk file size */
        /* 512MB by default */
        size_t db_size;
        /* Maximum chunk (node/data chunk) size */
        /* 4KB by default */
        size_t chunk_size;
        /* Maximum memory size */
        /* 16MB by default */
        /* size_t mem_size; */
};

struct DB *dbcreate(const char *file, const struct DBC conf);
struct DB *dbopen  (const char *file); /*struct DB *dbclose(struct DB* base);*/

int db_close(struct DB *db);
int db_del(const struct DB *, void *, size_t);
int db_get(const struct DB *, void *, size_t, void **, size_t *);
int db_put(const struct DB *, void *, size_t, void * , size_t  );

