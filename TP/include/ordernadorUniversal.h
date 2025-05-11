#ifndef ORDERNADOR_UNIVERSAL_H
#define ORDENADOR_UNIVERSAL_H

#include"estatistica.h"
#include"quickSort.h"
#include"insertionSort.h"
#include"lerEntrada.h"

void ordernadorUniversal(int* V,int tam,int minTamParticao,int limiarQuebras,struct Estatistica* est);



#endif