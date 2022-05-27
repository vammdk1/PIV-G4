#ifndef CARTA_H_
#define CARTA_H_

#include <stdlib.h>
typedef struct{

int negra; //bool, negro = 0
char* texto;
int id;

}Carta;

void imprimirCarta(Carta c);
void setTexto(Carta* c, char* text);
void freeTexto(Carta* c);


#endif /* CARTA_H_ */