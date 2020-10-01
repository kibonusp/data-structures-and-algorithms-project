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

}
boolean list_insert_keyword(LIST *list, int key, char *keyword){

}
boolean list_update_relevance(LIST *list, int key, int relevance){

}

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

}

int list_size(LIST *list){
	if(list == NULL) return FALSE;
	return list->size;
}

boolean list_empty(LIST *list){
	if(list == NULL || list->size == 0) return TRUE;
	return FALSE;
}