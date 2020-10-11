/*
 _________________________________________________ 
/        _________________________________        \
| == .  |      Gabriel Alves KUabara      |       |
|   _   |   Gabriel Freitas Vasconcelos   |    B  |
|  / \  |                                 | A   O |
| | O | |         N° USP 11275043         |  O    |
|  \_/  |         N° USP 11819084         |       |
|       |                                 |       |
|       |    gabrielalveskuabara@usp.br   | . . . |
|  :::  |    gabriel.vasconcelos@usp.br   | . . . |
|  :::  |_________________________________| . . . |
|                      G A K                      |
\_________________________________________________/
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "site.h"
#include "utils.h"

int count_char (char *string, char searched){
	int count = 0;
	for (int i = 0; i < strlen(string); i++)
		if (string[i] == searched) count++;
	return count;
}

SITE* create_site_from_googlebot(FILE* fp){
	char* line = readLine(fp);
	int nKeywords = 0;
	nKeywords = count_char(line, ',')-3;
	char* codeChar = strsep(&line, ",");
	int code = atoi(codeChar);
	char* name = strsep(&line, ",");
	int relevance = atoi(strsep(&line, ","));
	char* url = strsep(&line, ",");
	char** keywords = malloc(nKeywords*sizeof(char*));
	for (int i = 0; i < nKeywords; i++){
		keywords[i] = strsep(&line, ",");
	}

	SITE* site = site_create(code, name, relevance, url, keywords, nKeywords);

	free(codeChar);
	free(keywords);
	return site;
}

void operations(LIST *list){

	printf("Hello my friend, welcome to this program! Enjoy the trip!\n");
	printf("These are the possible commands for this program:\n");
	printf("1 - Insert site\n");
	printf("2 - Remove site\n");
	printf("3 - Insert new keyword\n");
	printf("4 - Update site relevance\n");
	printf("5 - Exit Program\n");

	while(TRUE){
		printf("Please, type a command:\n");
		int op;
		scanf("%d", &op);

		switch(op){
			//insert new site
			case 1:
				printf("Please, write all the site information as CSV:\n");
				SITE *site = create_site_from_googlebot(stdin);
				list_insert_site(list, site);
				break;

			//remove site
			case 2:
				printf("Type the site code you want to delete: ");
				int code2;
				scanf("%d", &code2);
				list_remove_site(list, code2);
				break;

			//new key word
			case 3:
				printf("Type the site code you want to add a keyword:\n");
				int code3;
				scanf("%d", &code3);
				printf("Type the new keyword\n");
				char *keyword = readLine(stdin);
				list_insert_keyword(list, code3, keyword);
				free(keyword); keyword = NULL;
				break;

			//update relevance
			case 4:
				printf("Type the site code you want to update relevance:\n");
				int code4;
				scanf("%d", &code4);
				int relevance;
				scanf("%d", &relevance);
				list_update_relevance(list, code4, relevance);
				break;

			//get out:
			case 5:
				printf("Oh no, this is a Good bye?\nSo I'm going to give you a present!\nTake this new googlebot file updated with your commands!\nTake care of yourself! And Good Bye!!!\n");				
				return;
		}
	}
}

int main() {
	int nSites = 0;
	LIST* list = list_create();
	printf("hello1\n");
	FILE *fp = fopen("googlebot.txt", "r");
	printf("hello1\n");
	while (!feof(fp)){
		SITE* site = create_site_from_googlebot(fp);
		list_insert_site(list, site);
		nSites++;
	}
	printf("hello1\n");
	operations(list);
	writing_file(list);
	list_erase(&list);

	fclose(fp);

	return 0;	
}