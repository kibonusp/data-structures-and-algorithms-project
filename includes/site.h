#ifndef SITE_H
#define SITE_H

#define TRUE 1
#define FALSE 0
#define boolean int

typedef struct site_ SITE;

SITE *site_create(int key, char *name, int relevance, char *URL, char **keywords);
boolean site_delete(SITE **site);
void site_print(SITE *site);
int site_get_key(SITE *site);
int site_set_relevance(SITE *site, int relevance);
boolean site_add_keyword(SITE *site, char *word);
boolean site_remove_keyword(SITE *site, char *word);
char *site_struct_to_string(SITE *site);

#endif 