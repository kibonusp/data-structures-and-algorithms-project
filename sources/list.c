#include <stdio.h>
#include <stdlib.h>
#include "list.h"

struct node_{
	SITE *site;
	NODE *next;
}

struct list_{
	NODE *start;
	int size;
}

LIST *list_create(){
	LIST *list = (LIST *) malloc(sizeof(LIST));
	if(list == NULL) return FALSE;

	list->start = NULL;
	list->size = 0;
	return TRUE;
}

boolean *list_insert_site(LIST *list, SITE *newsite){
	//in case there is no list
	if(list == NULL){
		printf("最初のバカのリストを作成してください\n");
		return FALSE;
	}

	NODE *elem = (NODE *) malloc(sizeof(NODE));

	//if the list is empty, put the site in the start
	if(list_empty(list)){
		elem->site = newsite;
		elem->next = NULL;
		list->start = elem;
		list->size = 1;
		return TRUE;
	}

	//if the list already has content, it needs to be added by order
	NODE *prior, *actual = list->start;
	while(actual != NULL && site_getkey(actual->site) < site_getkey(newsite)){
		prior = actual;
		actual = actual->next;
	}
	elem->next = prior->next;
	prior->next = elem;
	elem->site = newsite;

	list->size++;
	return TRUE;
}

boolean list_remove_site(LIST *list, int key){
	if(list == NULL) return FALSE;
	NODE *aux = list->start;

	for(int i = 0; i < list->size; i++){
		if(aux->site->key == key){
			site_delete(aux->site);
			return TRUE;
		}
		aux = aux->next;
	}
	return FALSE;	
}

boolean list_insert_keyword(LIST *list, int key, char *keyword){
	if(list == NULL) return FALSE;
	NODE *aux = site->start;

	for(int i = 0; i < list->size; i++){
		if(aux->site->key == key){
			//function to add a keyword in the site content
			site_add_keyword(site, keyword);
			return TRUE;
		}
		aux = aux->next;
	}
	return FALSE;
}

boolean list_update_relevance(LIST *list, int key, int relevance){
	if(list == NULL) return FALSE;
	NODE *aux = site->start;

	for(int i = 0; i < list->size; i++){
		if(aux->site->key == key){
			//function to access site relevance content
			site_set_relevance(aux->site, relevance);
			return TRUE;
		}
		aux = aux->next;
	}
	return FALSE;
}

//erase the list and all its content
void list_erase(LIST **list){
	if(*list != NULL){
		NODE *aux;
		while(*list != NULL){
			aux = *list->start;
			*list->start = *list->start->next;
			site_delete(&aux->site);
			free(aux);
		}
		free(*list);
	}
}

SITE *list_getsite(LIST *site, int key){
	NODE *aux = site->start;

	for(int i = 0; i < site->size; i++){
		if(aux->site->key == key){
			return aux->site;
		}
		aux = aux->next; 
	}
	return -1;
}

int list_size(LIST *list){
	if(list == NULL) return FALSE;
	return list->size;
}

boolean list_empty(LIST *list){
	if(list == NULL || list->size == 0) return TRUE;
	return FALSE;
}