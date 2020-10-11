#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

char* readLine(FILE* stream) {
    //Fazendo uma alocação inicial
    char *word = (char*) malloc (32 * sizeof(char));

    int i = 0, tamanho = 32;
    do  {
        //Realocando a memória heap caso a palavra exceda o espaço máximo
        if (i == tamanho)  { 
            word = realloc (word, 2 * tamanho);
            tamanho *= 2;
        }
        //Recebendo os caracteres
        word[i] = (char) fgetc(stream); 
        //faço com que exclua o '\r' caso tenha
        if (word[i] == '\r') i--;
        i++;
    } while (word[i-1] != '\n' && !feof(stream));

    //Tirando epaço adicional
    word[i - 1] = '\0'; 
    word = realloc(word, i); 

    return word;
}

//função tanto copia quanto particiona strings
char* strPart(char* str, const void* init, const void* end) {
    int size = strlen(str);
    char* copy = (char*) malloc((size + 1) * sizeof(char));
    
    int i = 0;

    //faço contagem do número de bytes até chegar ao valor init
    if (init != NULL) {
        while (str[i] != *(char*)init && i <= size - 1) {
            i++;
        }
        i++;
    }
    if (i == size + 1) i--;

    if (end == NULL) end = "\0";
    int j = 0;

    //faço a copia da posição onde tem o valor init até o valor end
    while (str[i] != *(char*)end && i <= size - 1) {
        copy[j] = str[i];
        j++;
        i++;
    }
    copy[j++] = '\0';

    //faço o ajuste do tamanho da string copiada ou particionada
    if (j < size) {
        copy = (char*) realloc(copy, j);
    }

    return copy;
}

//faço junção de duas strings
char* strAppend(char* str, char* add) {
    int sizeStr = strlen(str);
    int sizeAdd = strlen(add);
    char *new = (char*) malloc((sizeStr + sizeAdd + 1) * sizeof(char));

    //faço a cópia das string umas sobre a outra
    for (int i = 0; i <= sizeStr; i++) 
        new[i] = str[i];
    for (int i = sizeStr, j = 0; j <= sizeAdd; i++, j++) 
        new[i] = add[j];
    
    return new;
}