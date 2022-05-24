#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "carta.h"

void imprimirCarta(Carta c){
    if(c.negra == 0){

    
    printf("Carta negra n.%i: %s \n",c.id,c.texto);  }

    else{
        printf("Carta blanca n.%i: %s \n",c.id,c.texto);

    }

}