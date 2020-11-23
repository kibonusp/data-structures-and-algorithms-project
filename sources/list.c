#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "site.h"
#include "utils.h"

struct node_{
	SITE *site;
	NODE *next;
};

struct list_{
	NODE *start;
	int size;
};

LIST *list_create(){
	LIST *list = malloc(sizeof(LIST));
	if(!list) return FALSE;

	list->start = NULL;
	list->size = 0;
	return list;
}

// ordered insertion using the key
boolean list_insert_site(LIST *list, SITE *newsite){
	//in case there is no list
	if(!list) return FALSE;

	NODE *elem = malloc(sizeof(NODE));
	//if the list is empty, put the site in the start
	if(list_empty(list)){
		elem->site = newsite;
		elem->next = NULL;
		list->start = elem;
		list->size = 1;
		return TRUE;
	}

	//if the list already has content, it needs to be added by order
	elem->site = newsite;
	NODE *prior = NULL, *actual = list->start;

	//gets the position to be alocated
	// while key is smaller than actual, keep going...
	while(actual && site_get_key(actual->site) < site_get_key(newsite)){
		prior = actual;
		actual = actual->next;	
	}

	// verifies if already has a site with this key
	if(acutal && site_get_key(actual->site) == site_get_key(newsite)){
		site_delete(&newsite);
		printf("Sorry, but this site already exists\n");
		return FALSE;
	}
	
	// if is the first element
	if(actual == list->start){
		elem->next = list->start;
		list->start = elem;
	}
	// if is the last element
	else if(!actual){
		prior->next = elem;
		elem->next = NULL;
	}
	// inserts in the "middle" of the list
	else{
		elem->next = actual;
		prior->next = elem;
	}
	list->size++;
	return TRUE;
}

boolean list_remove_site(LIST *list, int key){
	if(list == NULL) return FALSE;
	NODE *actual = list->start;

	while(actual && site_get_key(actual->site) < key)
		actual = actual->next;

	if(actual && site_get_key(actual->site) == key){
		site_delete(&actual->site);
		return TRUE;
	}

	printf("Sorry, but there is no site with this code\n");
	return FALSE;	
}

boolean list_insert_keyword(LIST *list, int key, char *keyword){
	if(list == NULL) return FALSE;
	NODE *actual = list->start;

	while(actual && site_get_key(actual->site) < key)
		actual = actual->next;

	if(actual && site_get_key(actual->site) == key){
		//function to add a keyword in the site content
		site_add_keyword(actual->site, keyword);
		printf("New keyword added\n");
		return TRUE;
	}

	printf("Sorry, but there is no site with this code\n");
	return FALSE;
}

boolean list_update_relevance(LIST *list, int key, int relevance){
	if(list == NULL) return FALSE;
	NODE *actual = list->start;

	while(actual && site_get_key(actual->site) < key)
		actual = actual->next;

	if(actual && site_get_key(actual->site) == key){
		//function to access site relevance content
		site_set_relevance(actual->site, relevance);
		printf("Revelance updated with success\n");
		return TRUE;
	}

	printf("Sorry, but there is no site with this code\n");
	return FALSE;
}

//erase the list and all its content
void list_erase(LIST **list){
	if(!list) return;

	NODE *actual = (*list)->start, *next = NULL;

	while(actual){
		next = actual->next;
		site_delete(&actual->site);
		free(actual);
		actual = next;
	}
	actual = NULL;
	free(*list);
	*list = NULL;
}

SITE *list_getsite(LIST *list, int key){
	NODE *actual = list->start;

	while(actual && site_get_key(actual->site) < key)
		actual = actual->next;

	if(actual && site_get_key(actual->site) == key) return actual->site;

	printf("Sorry, no site with this key\n");
	return NULL;
}

int list_size(LIST *list){
	if(list == NULL) return FALSE;
	return list->size;
}

boolean list_empty(LIST *list){
	if(!list || !list->size) return TRUE;
	return FALSE;
}

void list_print(LIST *list){
	if(list == NULL) return;
	
	NODE *aux = malloc(sizeof(NODE));
	aux = list->start;

	while(aux){
		site_print(aux->site);
		aux = aux->next;
	}
}

SITE **search_sites_with_keyword(LIST *list, char *str, int *count, int *total_kw){
	if(list_empty(list)) return NULL;

	// matrix with site that has 'str' as keyword
	SITE **mat = malloc(sizeof(SITE *));

	// search for all sites that has the string 'str'
	NODE *aux = list->start;
	while(aux){
		// looks if site has the input string
		if(compare_string_with_keywords(aux->site, str, total_kw)){
			mat = realloc(mat, sizeof(SITE *) * (*count + 1));
			mat[*count] = aux->site;
			*count++;
		}
		aux = aux->next;
	}
	return mat;
}

char **collect_sites_keywords(SITE **mat, int nsites, int total_kw){
	// matrix with all keywords of the selected sites
	char **kw = malloc(sizeof(char *) * total_kw);

	int i = 0;
	for(int j = 0; j < nsites; j++){

		// number of keywords in that mat[j]
		int aux = site_get_nkeywords(mat[j]);

		// collect all keywords from sites in 'mat'
		for(int k = 0; k < aux; k++)
			kw[i++] = site_getkeywords(mat[j], k);
	}

	return kw;
}

SITE **sites_with_suggested_keywords(LIST *list, char **kw, int total_kw, int *n_sites){
	SITE **sites = malloc(sizeof(SITE *) * list->size);

	NODE *aux = list->start;
	while(aux){

		for(int i = 0; i < total_kw; i++){
			if(compare_string_with_keywords(aux->site, kw[i], NULL)){
				sites[*n_sites++] = aux->site;
				break;
			}
		}
		aux = aux->next;
	}
	sites = realloc(sites, sizeof(SITE *) * (*n_sites));
	return sites;
}

SITE **search_for_largest_relevance(SITE **sites, int n_sites){
	SITE **top5 = malloc(sizeof(SITE *) * 5);

	// bubble sort for 5 iteration, so the last five will have largest relevance
	for(int i = 0; i < 5; i++){          
       	for(int j = 0; j < n_sites - i -1; j++){  
          	if(site_get_relevance(sites[j]) > site_get_relevance(sites[j+1])){
              	SITE *temp = sites[j+1]; 
    			sites[j+1] = sites[j]; 
    			sites[j] = temp;
    		}
    	}
    }

    // get the last five to another matrix
    for(int i = 0, j = n_sites - 1; i < 5; i++, j--)
    	top5[i] = sites[j];

    return top5;
}

void sites_suggestions(LIST *list, char *str){

	// matrix of site with a specific keyword
	int total_kw = 0, count = 0;
	SITE **mat = search_sites_with_keyword(list, str, &count, &total_kw);

	// collect all keywords from the matrix 'mat'
	char **kw = collect_sites_keywords(mat, count, total_kw);
 	
 	// get sites with the keywords from 'kw'
 	int n_sites = 0;
	SITE **sites = sites_with_suggested_keywords(list, kw, total_kw, &n_sites);

	// looks for the 5 sites with larger relevance
	SITE **top5 = search_for_largest_relevance(sites, n_sites);

	printf("\nThanks for waiting, these are our suggestions for you:\n");
	for(int i = 0; i < 5; i++)
		printf("%d: %s - %s\n", i+1, site_getname(sites[i]), site_getURL(sites[i]));

	free(mat);
	free(kw);
	free(sites);
	free(top5);
}