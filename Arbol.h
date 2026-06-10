#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INSERTO 1
#define NOMEM -1
#define CLAVEDUPLICADA -2

typedef struct sNodo{
  void*dato;
  unsigned tamDato;
  struct sNodo * izq;
  struct sNodo * der;
}tNodo;

typedef tNodo * tArbol;
typedef int (*tCmp)(void*a,void*b);
typedef void (*tAccion)(void*a);
typedef void (*tAccionAgregado)(void*a, void*agregado);


void crearArbol(tArbol*arbol);
int insertarElemento(tArbol*arbol, void * elemento,unsigned tamElemento, tCmp cmp);
void recorrerPreOrden(tArbol * arbol, tAccion accion);
void recorrerPostOrden(tArbol * arbol, tAccion accion);
void recorrerInOrden(tArbol * arbol, tAccion accion);

void recorrerInOrdenAgregado(tArbol * arbol, tAccionAgregado accion, void * agregado);

void vaciarArbol(tArbol*arbol);

void crearABBBalanceado(tArbol * arbol,FILE* pf, unsigned tamElemento, int cantElementos);
tNodo* crearABBBalanceadoAux(FILE* pf, unsigned tamElemento, int inicio, int fin);
tNodo * crearNodo(void * dato, unsigned tamDato);
#endif // ARBOL_H_INCLUDED
