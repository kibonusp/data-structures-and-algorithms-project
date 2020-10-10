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

int countChar (char *string, char searched){
	int count = 0;
	for (int i = 0; i < strlen(string); i++)
		if (string[i] == searched) count++;
	return count;
}

SITE* createSiteFromGooglebot(){
	FILE *fp = fopen("googlebot.txt", "r");
	char* line = readLine(fp);
	int nKeywords = 0;
	nKeywords = countChar(line, ',')-3;
	
	char* codeChar = strsep(&line, ",");
	int code = atoi(codeChar);
	printf("%d, ", code);

	char* name =  strsep(&line, ",");
	printf("%s, ", name);

	int relevance = atoi(strsep(&line, ","));
	printf("%d, ", relevance);

	char* url = strsep(&line, ",");
	printf("%s", url);

	char** keywords = malloc(nKeywords*sizeof(char*));
	for (int i = 0; i < nKeywords; i++){
		keywords[i] = strsep(&line, ",");
		printf(", %s", keywords[i]);
	}
	printf("\n");
	
	SITE* site = site_create(code, name, relevance, url, keywords);

	free(codeChar);
	free(keywords);
	fclose(fp);
	return site;
}

int main() {
	//LIST* list = list_create();

	SITE* site = createSiteFromGooglebot();
	site_print(site);

	return 0;	
}