#ifndef ITEM_H
#define ITEM_H

#define TRUE 1
#define FALSE 0
#define boolean int

typedef struct _item ITEM;

ITEM *item_create(int key);
boolean item_delete(ITEM **item);
void item_print(ITEM *item);
int item_getkey(ITEM *item);
boolean item_setkey(ITEM *item, int newKey);

#endif 