#ifndef SITE_H
#define SITE_H

#define TRUE 1
#define FALSE 0
#define boolean int

typedef struct _site SITE;

SITE *site_create(int key);
boolean site_delete(SITE **site);
void site_print(SITE *site);
int site_getkey(SITE *site);
boolean site_setkey(SITE *site, int newKey);

#endif 