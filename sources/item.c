#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "utils.h"

struct _item{
    int key;
    char *name;
    int relevance;
    char *URL;
    char **keywords;
    int num_kw;
};

ITEM *item_create(int key, char *name, int relevance, char *URL, char **keywords) {
    ITEM *item;
    item = (ITEM *) malloc(sizeof(ITEM));
    
    if (item){
        item->key = key;
        item->name = strPart(name, NULL, NULL);
        item->relevance = relevance;
        item->URL = strPart(URL, NULL, NULL);
        for(int i = 0; keywords[i] == TRUE; i++) item->keywords[i] = strPart(keywords[i], NULL, NULL);
        item->num_kw = 0;
    }
    return item;
}

boolean item_delete(ITEM **item) {
    if (!item)
        return FALSE;

    free(*item->name); *item->name = NULL;
    free(*item->URL); *item->URL = NULL;
    for(int i = 0; keywords[i] == TRUE; i++){
        free(*item->keywords[i]);
        *item->keywords[i] = NULL;
    }
    free(*item); *item = NULL;

    return TRUE;
}

void item_print(ITEM *item) {
    if (item)
        printf("%d,%s,%d,%s", item->key, item->name, item->relevance, item->URL);
        for(int i = 0; keywords[i] == TRUE; i++) printf(",%s"item->keywords[i]);
        printf("\n");
    else
        printf("Item não existe");
}

int item_getkey(ITEM *item) {
    if (item) return item->key;
    exit(1);
}

boolean item_setkey(ITEM *item, int newKey) {
    if (!item) return FALSE;

    item->key = newKey;
    return TRUE;
}