#include <stdio.h>
#include "abb.h"
#include <stdbool.h>

#define COLOR_ROJO	   "\x1b[1m\x1b[31m"
#define COLOR_VERDE   "\x1b[1m\x1b[32m"
#define COLOR_NORMAL   "\x1b[0m"


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
}

/*Prueba para funcion arbol_raiz*/
void prueba_arbol_raiz(){
    printf("\nINICIO DE PRUEBAS ARBOL RAIZ\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 1, b = 2;

    /*Inicio de pruebas*/
    prueba("El abb esta vacio", arbol_vacio(abb));

    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("La raiz del arbol es el elemento que acabo de insertar", arbol_raiz(abb) == &a);
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("La raiz del arbol sigue siendo la misma", arbol_raiz(abb) == &a);
    prueba("El abb no esta vacio", !arbol_vacio(abb));   
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
}

/*Prueba para funcion arbol_recorrido_inorden*/
void prueba_in_order(){
    printf("\nINICIO DE PRUEBAS ARBOL RECORRIDO IN ORDEN\n");

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

   // prueba("rECORRIDO EN ORDEN", in_order(abb));
}

int main(){
    prueba_arbol_crear();
    prueba_arbol_insertar();
    prueba_arbol_vacio();
    prueba_arbol_raiz();
    prueba_arbol_buscar();
    prueba_in_order();
    return 0;
}