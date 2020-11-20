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
void list_print(LIST *list);

// sites suggestions functions
SITE **search_sites_with_keyword(LIST *list, char *str, int *count, int *total_kw);
char **collect_sites_keywords(SITE **mat, int nsites, int total_kw);
SITE **sites_with_suggested_keywords(LIST *list, char **kw, int total_kw, int *n_sites);
SITE **search_for_largest_relevance(SITE **sites, int n_sites);
void sites_suggestions(LIST *list, char *str);

#endif