#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
SITE *site_create(int key, char *name, int relevance, char *URL, char **keywords, int nKeywords) {
    SITE *site = malloc(sizeof(SITE));

    if (site){
        site->key = key;
        site->name = malloc((strlen(name)+1)*sizeof(char));
        strcpy(site->name, name);
        site->relevance = relevance;
        site->URL = malloc((strlen(URL)+1)*sizeof(char));
        strcpy(site->URL, URL);
        site->keywords = NULL;
        site->keywords = malloc(nKeywords*sizeof(char*));
        site->num_kw = nKeywords;
        for(int i = 0; i < site->num_kw; i++){
            site->keywords[i] = malloc((strlen(keywords[i])+1)*sizeof(char));
            strcpy(site->keywords[i], keywords[i]);
        }
    }
    return site;
}

//deletes the site and all content inside it
boolean site_delete(SITE **site) {
    if (!site)
        return FALSE;

    free((*site)->name); (*site)->name = NULL;
    free((*site)->URL); (*site)->URL = NULL;
    for(int i = 0; i < (*site)->num_kw; i++){
        free((*site)->keywords[i]);
        (*site)->keywords[i] = NULL;
    }
    free((*site)->keywords);
    free(*site); *site = NULL;

    return TRUE;
}

void site_print(SITE *site) {
    if (site){
        printf("%d,%s,%d,%s", site->key, site->name, site->relevance, site->URL);
        for(int i = 0; i < site->num_kw; i++) printf(",%s", site->keywords[i]);
        printf("\n");
    }
    else
        printf("Site não existe");
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
    if(!site) return FALSE;
    site->keywords = realloc(site->keywords, sizeof(char *) * (site->num_kw + 1));
    site->keywords[site->num_kw] = strPart(word, NULL, NULL);
    site->num_kw++;
    return TRUE;
}

boolean site_remove_keyword(SITE *site, char *word){
    if(!site) return FALSE;
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

boolean site_set_key(SITE *site, int newKey) {
    if (!site) return FALSE;

    site->key = newKey;
    return TRUE;
}