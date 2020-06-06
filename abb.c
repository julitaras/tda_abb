#include <stdio.h>
#include "abb.h"

abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

    abb_t* abb = malloc(sizeof(abb_t));

    if(!abb){
        return NULL;
    }    
    
    abb->nodo_raiz = NULL;

    abb->comparador = comparador;
    abb->destructor = destructor;

    return abb;
}

/*Creo un nodo de un abb y reservando memoria para el mismo*/
nodo_abb_t * nodo_crear(){

    nodo_abb_t * nodo = calloc(1, sizeof(nodo_abb_t));

    return nodo;
}

int arbol_insertar(abb_t* arbol, void* elemento){
    if (!arbol){
        return -1;
    }
    //Ver video de clase de hoy (05/06)--> hacer recursivo el insertar
}