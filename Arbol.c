#include "Arbol.h"

void crearArbol(tArbol*arbol){
  (*arbol) = NULL;
}

int insertarElemento(tArbol*arbol, void * elemento,unsigned tamElemento, tCmp cmp){

    int codigo = INSERTO;

    if( (*arbol) == NULL ){
        tNodo * nuevonodo = (tNodo*) malloc(sizeof(tNodo));
        if(!nuevonodo){
            codigo = NOMEM;
            return codigo;
        }
        nuevonodo->dato = malloc(tamElemento);
        if(!(nuevonodo->dato)){
            free(nuevonodo);
            codigo = NOMEM;
            return codigo;
        }
        nuevonodo->tamDato = tamElemento;
        nuevonodo->izq = NULL;
        nuevonodo->der = NULL;
        memcpy(nuevonodo->dato,elemento,tamElemento);

        (*arbol) = nuevonodo;

        codigo = INSERTO;
        return codigo;
    }

    if( cmp(elemento, (*arbol)->dato ) > 0 ){
        codigo = insertarElemento( &((*arbol)->izq) , elemento, tamElemento,cmp);
    }else{
       if( cmp(elemento, (*arbol)->dato )<0 ){
         codigo =  insertarElemento( &((*arbol)->der) , elemento, tamElemento,cmp);
       }else{
          codigo = CLAVEDUPLICADA;
          return codigo;
       }
    }
    return codigo;
}

void vaciarArbol(tArbol*arbol){
  if( (*arbol) == NULL ){
    return;
  }

  vaciarArbol( &(*arbol)->izq);
  vaciarArbol( &(*arbol)->der);

  free((*arbol)->dato);
  free((*arbol));
  (*arbol) = NULL;
};

void recorrerPreOrden(tArbol * arbol, tAccion accion){

   if( (*arbol) == NULL ){
     return;
   }

   accion( (*arbol)->dato );
   recorrerPreOrden( &((*arbol)->izq ),accion);
   recorrerPreOrden( &((*arbol)->der ),accion);
}

void recorrerPostOrden(tArbol * arbol, tAccion accion){
   if( (*arbol) == NULL ){
     return;
   }

   recorrerPostOrden( &((*arbol)->izq),accion);
   recorrerPostOrden( &((*arbol)->der),accion);
   accion( (*arbol)->dato );
}

void recorrerInOrden(tArbol * arbol, tAccion accion){
   if( (*arbol) == NULL ){
     return;
   }

   recorrerInOrden( &((*arbol)->izq),accion);
   accion( (*arbol)->dato );
   recorrerInOrden( &((*arbol)->der),accion);

}
void recorrerInOrdenAgregado(tArbol * arbol, tAccionAgregado accion, void * agregado){
   if( (*arbol) == NULL ){
     return;
   }

   recorrerInOrdenAgregado( &((*arbol)->izq),accion,agregado);
   accion( (*arbol)->dato , agregado);
   recorrerInOrdenAgregado( &((*arbol)->der),accion, agregado);

}


void crearABBBalanceado(tArbol * arbol,FILE* pf, unsigned tamElemento, int cantElementos)
{
    (*arbol) = crearABBBalanceadoAux(pf, tamElemento, 0, cantElementos - 1);
}


tNodo* crearABBBalanceadoAux(FILE* pf, unsigned tamElemento, int inicio, int fin)
{
    if(inicio > fin)
        return NULL;

    int medio = (inicio + fin) / 2;
    tNodo* nodo;

    void* buffer = malloc(tamElemento);
    if(!buffer)
        return NULL;

    fseek(pf, medio * tamElemento, SEEK_SET);
    fread(buffer, tamElemento, 1, pf);

    nodo = crearNodo(buffer,tamElemento); // TENÉS que crear el nodo directamente

    if(!nodo){
        free(buffer);
        return NULL;
    }
    free(buffer);

    if(!nodo)
        return NULL;

    nodo->izq = crearABBBalanceadoAux(pf, tamElemento, inicio, medio - 1);
    nodo->der = crearABBBalanceadoAux(pf, tamElemento, medio + 1, fin);

    return nodo;
}
tNodo * crearNodo(void * dato, unsigned tamDato){

   tNodo * nuevonodo = (tNodo*)malloc(sizeof(tNodo));
   if(!nuevonodo){
    return NULL;
   }
   nuevonodo->dato = malloc(tamDato);
   if(!nuevonodo->dato){
    free(nuevonodo);
    return NULL;
   }
   memcpy(nuevonodo->dato,dato,tamDato);

   return nuevonodo;
}







