#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void cogerCartas(FILE* f)
{
    int id = 1;
    char* frase = NULL;
    size_t len = 0;
    char** cartas;
    char** temp = (char**) malloc(sizeof(char*)*100);

    while (getline(&frase, &len, f) != -1){
        printf("%i - %s\n",id, frase);
        temp[id-1] = (char*) malloc(sizeof(char)*strlen(frase)+1); 
        strcpy(temp[id-1], frase);
        id++;
        
    }
   
    cartas = (char**) malloc(sizeof(char*)*id);
   
    for (int i = 0; i < id-1; i++)
    {
        
        cartas[i] = (char*) malloc(sizeof(char)*250);
        
        strcpy(cartas[i],temp[i]);
        printf("%s\n",cartas[i]);
        
        
    }
    
    /*for(int i = 0; i<100;i++){
        free(temp[i]);
    }*/
    
    free(temp);
    
    printf("\n");
}

int main(int argc, char const *argv[])
{
    printf("cartas blancas\n");
    FILE* f = fopen("cartasBlancas.txt", "r");
    cogerCartas(f);
    fclose(f);
    printf("cartas negras\n");
    FILE* f2 = fopen("cartasNegras.txt", "r");
    cogerCartas(f2);
    fclose(f2);
    return 0;
}
