#include <stdio.h>
#include "abb.h"
#include <stdbool.h>

#define COLOR_ROJO	   "\x1b[1m\x1b[31m"
#define COLOR_VERDE   "\x1b[1m\x1b[32m"
#define COLOR_NORMAL   "\x1b[0m"
#define COLOR_VIOLETA "\x1b[35;1m"


/*Funcion comparadora de elementos*/
int comparador(void* elem1, void* elem2){

    if(!elem1 || !elem2){
		return 0;
    }

    if(*(int*)elem1 > *(int*)elem2){
        return 1;
    }

    if(*(int*)elem1 < *(int*)elem2){
        return -1;
    }

    return 0;
}

/*
* Funcion prueba, recibe el mensaje a dar 
* y si el resultado esta bien o mal. 
* De estar bien se pone en verde, de estar mal se pone en rojo
*/
void prueba(const char* mensaje, bool ok) {
	if (ok) {
		printf(COLOR_NORMAL "%s... ", mensaje);
		printf(COLOR_VERDE "OK\n");
	} else {
		printf(COLOR_NORMAL "%s: ", mensaje);
		printf(COLOR_ROJO "ERROR\n");
	}
	printf(COLOR_NORMAL);
}

/*Prueba para funcion abb_crear*/
void prueba_arbol_crear(){
    printf("\nINICIO DE PRUEBAS ARBOL CREAR\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(NULL, NULL);

    /*Inicio de pruebas*/
    prueba("El abb se creo con exito", abb != NULL);
    prueba("El abb esta vacio", arbol_vacio(abb));
    
    arbol_destruir(abb);
}

/*Prueba para funcion arbol_insertar*/
void prueba_arbol_insertar(){
    printf("\nINICIO DE PRUEBAS ARBOL INSERTAR\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 5, d = 1;

    /*Inicio de pruebas*/
    prueba("El abb se creo con exito", abb != NULL);
    prueba("El abb esta vacio", arbol_vacio(abb));

    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));
    
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("Inserto el tercer nodo", arbol_insertar(abb, &c) == 0);
    prueba("Inserto el cuarto nodo", arbol_insertar(abb, &d) == 0);
    
    arbol_destruir(abb);
}

/*Prueba para funcion arbol_vacio*/
void prueba_arbol_vacio(){
    printf("\nINICIO DE PRUEBAS ARBOL VACIO\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 1;

    /*Inicio de pruebas*/
    prueba("El abb esta vacio", arbol_vacio(abb));

    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb)); 
    
    arbol_destruir(abb);  
}

/*Prueba para funcion arbol_raiz*/
void prueba_arbol_raiz(){
    printf("\nINICIO DE PRUEBAS ARBOL RAIZ\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 1, b = 2;

    /*Inicio de pruebas*/
    prueba("El abb esta vacio", arbol_vacio(abb));
    prueba("La raiz del arbol es NULL", arbol_raiz(abb) == NULL);

    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("La raiz del arbol es el elemento que acabo de insertar", arbol_raiz(abb) == &a);
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("La raiz del arbol sigue siendo la misma", arbol_raiz(abb) == &a);
    prueba("El abb no esta vacio", !arbol_vacio(abb));   
    
    arbol_destruir(abb);
}

/*Prueba para funcion arbol_buscar*/
void prueba_arbol_buscar(){
    printf("\nINICIO DE PRUEBAS ARBOL BUSCAR\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 5, d = 1;

    /*Inicio de pruebas*/
    prueba("El abb esta vacio", arbol_vacio(abb));

    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("La raiz del arbol es el elemento que acabo de insertar", arbol_raiz(abb) == &a);
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("Inserto el tercer nodo", arbol_insertar(abb, &c) == 0);
    prueba("Inserto el cuarto nodo", arbol_insertar(abb, &d) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));
    prueba("Busco el elemento 5", arbol_buscar(abb, &c) == &c);
    
    arbol_destruir(abb);
}

/*Prueba para funcion arbol_recorrido_inorden*/
void prueba_in_order(){
    printf("\nINICIO DE PRUEBAS ARBOL RECORRIDO IN ORDEN\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 5, d = 1;
    int* elementos[3];
    int* elementos2[6];

    /*Inicio de pruebas*/
    prueba("El abb esta vacio", arbol_vacio(abb));
    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("La raiz del arbol es el elemento que acabo de insertar", arbol_raiz(abb) == &a);
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("Inserto el tercer nodo", arbol_insertar(abb, &c) == 0);
    prueba("Inserto el cuarto nodo", arbol_insertar(abb, &d) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));

    int cantidad = arbol_recorrido_inorden(abb, (void**)elementos, 3);
    prueba("La cantidad de elementos que guardo es la cantidad que pase", cantidad == 3);
    for(size_t i=0;i<cantidad;i++){
        printf(COLOR_VIOLETA "%i ", *elementos[i]);
    }
    printf("\n"); 

    cantidad = arbol_recorrido_inorden(abb, (void**)elementos2, 6);
    prueba("Paso otro array mas grande y guarda todo los elementos que son 4", cantidad == 4);
    for(size_t i=0;i<cantidad;i++){
        printf(COLOR_VIOLETA "%i ", *elementos2[i]);
    }
    printf("\n");

    arbol_destruir(abb);
}
/*Prueba para funcion arbol_recorrido_preorden*/
void prueba_pre_order(){
    printf("\nINICIO DE PRUEBAS ARBOL RECORRIDO PRE ORDEN\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 5, d = 1;
    int* elementos[3];
    int* elementos2[6];

    /*Inicio de pruebas*/
    prueba("El abb esta vacio", arbol_vacio(abb));
    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("La raiz del arbol es el elemento que acabo de insertar", arbol_raiz(abb) == &a);
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("Inserto el tercer nodo", arbol_insertar(abb, &c) == 0);
    prueba("Inserto el cuarto nodo", arbol_insertar(abb, &d) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));
    
    int cantidad = arbol_recorrido_preorden(abb, (void**)elementos, 3);
    prueba("La cantidad de elementos que guardo es la cantidad que pase", cantidad == 3);
    for(size_t i=0;i<cantidad;i++){
        printf(COLOR_VIOLETA "%i ", *elementos[i]);
    }
    printf("\n");

    cantidad = arbol_recorrido_preorden(abb, (void**)elementos2, 6);
    prueba("Paso otro array mas grande y guarda todo los elementos que son 4", 4 == 4);
    for(size_t i=0;i<cantidad;i++){
        printf(COLOR_VIOLETA "%i ", *elementos2[i]);
    }
    printf("\n");

    arbol_destruir(abb);
}

/*Prueba para funcion arbol_recorrido_postorden*/
void prueba_post_order(){
    printf("\nINICIO DE PRUEBAS ARBOL RECORRIDO POST ORDEN\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 5, d = 1;
    int* elementos[3];
    int* elementos2[6];

    /*Inicio de pruebas*/
    prueba("El abb esta vacio", arbol_vacio(abb));
    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("La raiz del arbol es el elemento que acabo de insertar", arbol_raiz(abb) == &a);
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("Inserto el tercer nodo", arbol_insertar(abb, &c) == 0);
    prueba("Inserto el cuarto nodo", arbol_insertar(abb, &d) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));

    int cantidad = arbol_recorrido_postorden(abb, (void**)elementos, 3);
    prueba("La cantidad de elementos que guardo es la cantidad que pase", cantidad == 3);
    printf("Recorrido post order con un array de tamanio 3: \n");
    for(size_t i=0;i<cantidad;i++){
        printf(COLOR_VIOLETA "%i ", *elementos[i]);
    }
    printf("\n");

    cantidad = arbol_recorrido_postorden(abb, (void**)elementos2, 6);
    prueba("Paso otro array mas grande y guarda todo los elementos que son 4", cantidad == 4);
    for(size_t i=0;i<cantidad;i++){
        printf(COLOR_VIOLETA "%i ", *elementos2[i]);
    }
    printf("\n");

    arbol_destruir(abb);
}

/*Prueba para funcion arbol_borrar*/
void prueba_arbol_borrar(){
    printf("\nINICIO DE PRUEBAS ARBOL BORRAR\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 6, d = 5, e = 1 , f = 8, g = 9, h = 7, i = 3;

    /*Inicio de pruebas*/
    prueba("El abb se creo con exito", abb != NULL);
    prueba("El abb esta vacio", arbol_vacio(abb));

    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));
    
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("Inserto el tercer nodo", arbol_insertar(abb, &c) == 0);
    prueba("Inserto el cuarto nodo", arbol_insertar(abb, &d) == 0);
    prueba("Inserto el quinto nodo", arbol_insertar(abb, &e) == 0);
    prueba("Inserto el sexto nodo", arbol_insertar(abb, &f) == 0);
    prueba("Inserto el septimo nodo", arbol_insertar(abb, &g) == 0);
    prueba("Inserto el octavo nodo", arbol_insertar(abb, &h) == 0);
    prueba("Inserto el noveno nodo", arbol_insertar(abb, &i) == 0);
    prueba("Borro el octavo elemento, caso 0 hijos", arbol_borrar(abb, &h) == 0);
    prueba("Borro el sexto elemento, caso 1 hijo", arbol_borrar(abb, &f) == 0);
    prueba("Borro el segundo elemento, caso 2 hijo", arbol_borrar(abb, &b) == 0);
    prueba("Borro la raiz", arbol_borrar(abb, &a) == 0);
    
    arbol_destruir(abb);
}

bool sumar_elemento(void* elemento, void* extra){
  if(elemento){
    printf(COLOR_VIOLETA "Elemento: %i \n", *(int*)elemento);

    (*(int*)extra) = (*(int*)extra) + *(int*)elemento;
    printf(COLOR_VIOLETA "Suma hasta el momento: %i \n", *(int*)extra);
  }

  return false;
}

/*Prueba para iterador interno del abb*/
void prueba_iterador_interno(){
    printf("\nINICIO DE PRUEBAS ARBOL CON CADA ELEMENTO\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 6, d = 5;

    /*Inicio de pruebas*/
    prueba("El abb se creo con exito", abb != NULL);
    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("Inserto el tercer nodo", arbol_insertar(abb, &c) == 0);
    prueba("Inserto el cuarto nodo", arbol_insertar(abb, &d) == 0);
    
    printf(COLOR_NORMAL "RECORRIDO IN-ORDER, RESULTADO: 2 + 4 + 5 + 6 \n");
    int extra=0;
    abb_con_cada_elemento(abb, ABB_RECORRER_INORDEN, sumar_elemento, (void*)&extra);
    
    printf(COLOR_NORMAL "RECORRIDO PRE-ORDER, RESULTADO: 4 + 2 + 6 + 5 \n");
    extra=0;
    abb_con_cada_elemento(abb, ABB_RECORRER_PREORDEN, sumar_elemento, (void*)&extra);
    
    printf(COLOR_NORMAL "RECORRIDO POST-ORDER, RESULTADO: 2 + 5 + 6 + 4 \n");
    extra=0;
    abb_con_cada_elemento(abb, ABB_RECORRER_POSTORDEN, sumar_elemento, (void*)&extra);
    arbol_destruir(abb);
}

int main(){
    prueba_arbol_crear();
    prueba_arbol_insertar();
    prueba_arbol_vacio();
    prueba_arbol_raiz();
    prueba_arbol_buscar();
    prueba_in_order();
    prueba_pre_order();
    prueba_post_order();
    prueba_arbol_borrar();
    prueba_iterador_interno();
    return 0;
}