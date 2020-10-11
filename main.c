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

void reading_file(){
	FILE *fp = fopen("googlebot.txt", "r");
	char *aux = readLine(fp);

	printf("%s\n", aux);
	

	fclose(fp);
	free(aux);
}

void operations(LIST *list){

	printf("Hello my friend, welcome to this program! Enjoy the trip!\n");
	printf("These are the possible commands for this program:\n");
	printf("1 - Insert site\n");
	printf("2 - Remove site\n");
	printf("3 - Insert new keyword%\n");
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
				list_remove_site(list, code);
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
				printf("Oh no, this is a Good bye?\n
					So I'm going to give you a present!\n
					Take this new googlebot file updated with your commands!\n
					Take care of yourself! And Good Bye!!!\n");				
				return;
		}
	}
}

int main() {
	reading_file();

	operations(list);

	writing_file(list);

	return 0;	
}