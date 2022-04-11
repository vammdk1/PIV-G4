#include <stdio.h>
#include <string.h>
#include "carta.h"

imprimirCarta(Carta c){
    if(c.id == 0){

    
    printf("Carta negra n.%i: %s \n",c.id,c.texto);  }

    else{
        printf("Carta blanca n.%i: %s \n",c.id,c.texto);

    }

}