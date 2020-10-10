#include <stdio.h>
#include <stdlib.h>
#include "site.h"
#include "utils.h"

struct site_{
    int key;            // primary key
    char *name;
    int relevance;
    char *URL;
    char **keywords;
    int num_kw;
};

//creates list and makes everything NULL or zero
SITE *site_create(int key, char *name, int relevance, char *URL, char **keywords) {
    SITE *site = malloc(sizeof(SITE));

    if (site){
        site->key = key;
        site->name = strPart(name, NULL, NULL);
        site->relevance = relevance;
        site->URL = strPart(URL, NULL, NULL);
        for(int i = 0; keywords[i]; i++) site->keywords[i] = strPart(keywords[i], NULL, NULL);
        site->num_kw = 0;
    }
    return site;
}

//deletes the site and all content inside it
boolean site_delete(SITE **site) {
    if (!site)
        return FALSE;

    free((*site)->name); (*site)->name = NULL;
    free((*site)->URL); (*site)->URL = NULL;
    for(int i = 0; (*site)->keywords[i]; i++){
        free((*site)->keywords[i]);
        (*site)->keywords[i] = NULL;
    }
    free(*site); *site = NULL;
    return TRUE;
}

void site_print(SITE *site) {
    if (site){
        printf("%d,%s,%d,%s", site->key, site->name, site->relevance, site->URL);
        for(int i = 0; site->keywords[i]; i++) printf(",%s", site->keywords[i]);
        printf("\n");
    }
    else
        printf("Sorry bro, no data here\n");
}

int site_get_key(SITE *site) {
    if (site) return site->key;
    exit(1);
}

boolean site_set_relevance(SITE *site, int relevance){
    if(site == NULL) return FALSE;
    site->relevance = relevance;
    return TRUE;
}

boolean site_add_keyword(SITE *site, char *word){
    if(site == NULL) return FALSE;
    site->keywords = realloc(site->keywords, sizeof(char *) * (site->num_kw + 1));
    site->keywords[site->num_kw] = strPart(word, NULL, NULL);
    site->num_kw++;
    return TRUE;
}

boolean site_remove_keyword(SITE *site, char *word){
    if(site == NULL) return FALSE;
    for(int i = 0; i < site->num_kw; i++){
        if(site->keywords[i] == word){
            site->keywords[i] = NULL;
            site->keywords = realloc(site->keywords, sizeof(char *) * (site->num_kw - 1));
            return TRUE;
        }
    }
    printf("There is any '%s' here, get out your nasty furry", word);
    return FALSE;
}