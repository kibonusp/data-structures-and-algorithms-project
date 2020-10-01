#include <stdio.h>
#include <stdlib.h>
#include "site.h"
#include "utils.h"

struct _site{
    int key;
    char *name;
    int relevance;
    char *URL;
    char **keywords;
    int num_kw;
};

SITE *site_create(int key, char *name, int relevance, char *URL, char **keywords) {
    SITE *site;
    SITE = (SITE *) malloc(sizeof(site));
    
    if (site){
        site->key = key;
        site->name = strPart(name, NULL, NULL);
        site->relevance = relevance;
        site->URL = strPart(URL, NULL, NULL);
        for(int i = 0; keywords[i] == TRUE; i++) site->keywords[i] = strPart(keywords[i], NULL, NULL);
        site->num_kw = 0;
    }
    return site;
}

boolean site_delete(SITE **site) {
    if (!site)
        return FALSE;

    free(*site->name); *site->name = NULL;
    free(*site->URL); *site->URL = NULL;
    for(int i = 0; keywords[i] == TRUE; i++){
        free(*site->keywords[i]);
        *site->keywords[i] = NULL;
    }
    free(*site); *site = NULL;

    return TRUE;
}

void site_print(SITE *site) {
    if (site)
        printf("%d,%s,%d,%s", site->key, site->name, site->relevance, site->URL);
        for(int i = 0; keywords[i] == TRUE; i++) printf(",%s"site->keywords[i]);
        printf("\n");
    else
        printf("site não existe");
}

int site_getkey(SITE *site) {
    if (site) return site->key;
    exit(1);
}

boolean site_setkey(SITE *site, int newKey) {
    if (!site) return FALSE;

    site->key = newKey;
    return TRUE;
}