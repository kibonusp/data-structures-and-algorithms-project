#ifndef SITE_H
#define SITE_H

#define TRUE 1
#define FALSE 0
#define boolean int

typedef struct site_ SITE;

SITE *site_create(int key, char *name, int relevance, char *URL, char **keywords, int nKeywords);
boolean site_delete(SITE **site);

void site_print(SITE *site);

int site_get_key(SITE *site);
char *site_getname(SITE *site);
char *site_getURL(SITE *site);
int site_get_relevance(SITE *site);
int site_set_relevance(SITE *site, int relevance);
char *site_getkeywords(SITE *site, int index);
int site_get_nkeywords(SITE *site);

boolean site_add_keyword(SITE *site, char *word);
boolean site_remove_keyword(SITE *site, char *word);

char *site_struct_to_string(SITE *site);

boolean compare_string_with_keywords(SITE *site, char *str);

#endif 