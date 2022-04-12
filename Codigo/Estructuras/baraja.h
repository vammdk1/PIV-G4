#ifndef BARAJA_H_
#define BARAJA_H_

typedef struct{

Carta* cartas;
int numcartas;


}Baraja;


void crearBaraja(Baraja* baraja, int cuantas , Carta* cartas);
void imprimirBaraja(Baraja baraja);
void liberaBaraja(Baraja* baraja);


#endif /* BARAJA_H_ */