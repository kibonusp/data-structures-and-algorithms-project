#ifndef LIST_H
#define LIST_H

#include "site.h"

#define TRUE 1
#define FALSE 0    
#define boolean int

typedef struct node_ NODE;
typedef struct list_ LIST;

LIST *list_create();

boolean list_insert_site(LIST *list, SITE *newsite);
boolean list_remove_site(LIST *list, int key);
boolean list_insert_keyword(LIST *list, int key, char *keyword);
boolean list_update_relevance(LIST *list, int key, int relevance);
void list_erase(LIST **list);

SITE *list_get_site(LIST *site, int key);
int list_size(LIST *list);
boolean list_empty(LIST *list);

void end_program();

#endif