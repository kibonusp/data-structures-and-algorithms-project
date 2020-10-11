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

int main() {
	int nSites = 0;
	LIST* list = list_create();
	FILE *fp = fopen("googlebot.txt", "r");
	while (!feof(fp)){
		SITE* site = create_site_from_googlebot(fp);
		list_insert_site(list, site);
		nSites++;
	}
	list_erase(&list);

	fclose(fp);

	return 0;	
}