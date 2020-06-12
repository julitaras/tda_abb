#include <stdio.h>
#include "abb.h"
#include <stdbool.h>

#define COLOR_ROJO	   "\x1b[1m\x1b[31m"
#define COLOR_VERDE   "\x1b[1m\x1b[32m"
#define COLOR_NORMAL   "\x1b[0m"


/*Funcion comparadora de elementos*/
int comparador(void* elem1, void* elem2){
    if(!elem1|| !elem2){
		return 0;
    }

    if(elem1 > elem2){
        return 1;
    }

    if(elem1 < elem2){
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
void prueba_abb_crear(){
    printf("\nINICIO DE PRUEBAS ABB CREAR\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(NULL, NULL);

    /*Inicio de pruebas*/
    prueba("El abb se creo con exito", abb != NULL);
    prueba("El abb esta vacio", arbol_vacio(abb));
}

/*Prueba para funcion abb_insertar*/
void prueba_abb_insertar(){
    printf("\nINICIO DE PRUEBAS ABB INSERTAR\n");

    /* Declaro las variables a utilizar*/
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 1, b = 2;

    /*Inicio de pruebas*/
    prueba("El abb se creo con exito", abb != NULL);
    prueba("El abb esta vacio", arbol_vacio(abb));

    prueba("Inserto el nodo raiz", arbol_insertar(abb, &a) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));
    
    prueba("Inserto el segundo nodo", arbol_insertar(abb, &b) == 0);
    prueba("El abb no esta vacio", !arbol_vacio(abb));
}

int main(){
    prueba_abb_crear();
    prueba_abb_insertar();
    return 0;
}