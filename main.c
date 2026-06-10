#include "Alumno.h"
#include "Arbol.h"

int compararAlumnos(void*a,void*b);
void mostrarAlumnoProcesado(void*a);
void grabarEnArchivo(void * a, void * pf);

int main()
{

/*  CREO EL ARCHIVO DE ALUMNOS DESORDENADO
    FILE *archivo = fopen("alumnos.dat", "wb");

    if (archivo == NULL) {
        printf("Error al crear el archivo\n");
        return 1;
    }

    // Datos de la imagen
    struct Alumno alumnos[] = {
        { 555},
        { 362},
        { 123},
        { 888},
        { 423},
        { 952},
        { 612},
        { 258},
        { 789},
        { 456},
        { 369},
        { 951},
        { 852},
        { 157},
        { 627},
        { 432,},
        { 128}
    };

    int cantidad = sizeof(alumnos) / sizeof(alumnos[0]);

    // Guardar en el archivo
    for (int i = 0; i < cantidad; i++) {
        fwrite(&alumnos[i], sizeof(struct Alumno), 1, archivo);
    }

    fclose(archivo);

    printf("Archivo alumnos.dat creado correctamente\n");

*/
// GUARDO EN EL ARBOL PARA DESPUES SACARLO ORDENADO
    tArbol miarbol;
    int posicion = 0;

    crearArbol(&miarbol);


    FILE *archivo = fopen("alumnos.dat", "rb");
    if (archivo == NULL) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    struct Alumno alu;
    struct AlumnoProcesado alumnoProcesado;

    while (fread(&alu, sizeof(struct Alumno), 1, archivo)) {
        alumnoProcesado.alumno = alu.alumno;
        alumnoProcesado.posicion = posicion;

        insertarElemento(&miarbol,&alumnoProcesado,sizeof(struct AlumnoProcesado),compararAlumnos);
        posicion++;
        //printf("%d\n",alu.alumno);
       // printf("%d %d")
    }
    //recorrerInOrden(&miarbol,mostrarAlumnoProcesado);



    //Ya tengo los datos dentro del arbol, ahora tengo que generar el archivo indice ordenado

 /// LO SACO ORDENADO DEL ARBOL
/*
    FILE* pArchivoIndice = fopen("alumnosIndice.idx","rb");

    if(!pArchivoIndice){
        fclose(archivo);
        vaciarArbol(&miarbol);
        return 1;
    }

    //recorrerInOrdenAgregado(&miarbol,grabarEnArchivo,pArchivoIndice);


    struct AlumnoProcesado aluproce;

    while(fread(&aluproce,sizeof(struct AlumnoProcesado),1,pArchivoIndice)){
       printf("\nPOS: %d  ALUMNO: %d", aluproce.posicion, aluproce.alumno);
    }
*/

    //Ya tengo el archivo de indice ordenado ahora tengo que hacer el arbol


   // fclose(archivo);
   // vaciarArbol(&miarbol);

//CONSTRUIR EL ALGORITMO DE GENERACION DE ARBOL BINARIO BUSQUEDA BALANCEADO

    FILE*pArch = fopen("alumnosIndice.idx","rb");
    if(!pArch){
        return 1;
    }
    tArbol pincheArbol;
    crearABBBalanceado(&pincheArbol,pArch,sizeof(struct AlumnoProcesado),17);

    recorrerPreOrden(&pincheArbol,mostrarAlumnoProcesado);

    vaciarArbol(&pincheArbol);
    return 0;
}


void grabarEnArchivo(void * a, void * pf){
 FILE *pArch = (FILE*)pf;

 fwrite(a,sizeof(struct AlumnoProcesado),1,pArch);
}

void mostrarAlumnoProcesado(void*a){
   struct AlumnoProcesado alumnoProcesado = *(struct AlumnoProcesado*)a;
   printf("\nPOS: %d    ALUMNO: %d", alumnoProcesado.posicion, alumnoProcesado.alumno);
}
int compararAlumnos(void*a,void*b){
  int x = *(int*)a;
  int y = *(int*)b;

  return y - x;
}


