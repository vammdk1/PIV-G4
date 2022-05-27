#include <stdio.h>
#include <string.h>

#include "carta.h"

void imprimirCarta(Carta c){
    if(c.negra == 0){

    printf("Carta negra n.%i: %s \n",c.id,c.texto);  }

    else{
        printf("Carta blanca n.%i: %s \n",c.id,c.texto);

    }

}

void setTexto(Carta* c, char* text){
    c->texto = (char*) malloc(sizeof(char)*strlen(text)+1);
    strcpy(c->texto, text);
    
}

void freeTexto(Carta* c){
    free(c->texto);
}