#include <stdio.h>
#include "abb.h"
#define EXITO 0
#define ERROR -1

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

nodo_abb_t* arbol_buscar_nodo_padre(nodo_abb_t* nodo, nodo_abb_t* padre, abb_comparador comparador, void* elemento){
    if(!nodo){
        return padre;
    }
    
    padre = nodo;

    int resultado = comparador(nodo->elemento, elemento);
	
	if (resultado >= 0){
		return arbol_buscar_nodo_padre(nodo->izquierda, padre, comparador, elemento); 
    }

	return arbol_buscar_nodo_padre(nodo->derecha, padre, comparador, elemento);
}

/*Funcion que busca un nodo en el arbol*/
nodo_abb_t* arbol_buscar_nodo(nodo_abb_t* nodo, abb_comparador comparador, void* elemento){
    if(!nodo){
        return NULL;
    }

    int resultado = comparador(nodo->elemento, elemento);
	
	if(resultado == 0){ // elemento == nodo->elemento
		return nodo;
    }

	if (resultado == 1){
		return arbol_buscar_nodo(nodo->izquierda, comparador, elemento); // elemento < nodo->elemento => va a estar a la izquierda
    }

	return arbol_buscar_nodo(nodo->derecha, comparador, elemento); // elemento > nodo->elemento => va a estar a la derecha
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(!arbol || arbol_vacio(arbol)){
        return NULL;
    }

    // nodo_abb_t *aux = arbol->nodo_raiz;

    // int resultado = arbol->comparador(aux->elemento, elemento);

    // while(resultado != 0){
    //     if(resultado == 1){
    //         aux = arbol->nodo_raiz->izquierda;
    //     }else{
    //         aux = arbol->nodo_raiz->derecha;
    //     }

    //     resultado = arbol->comparador(aux->elemento, elemento);
    // }

    // return elemento;

   nodo_abb_t* nodo_buscado = arbol_buscar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);

   return nodo_buscado->elemento;
}  

int arbol_insertar(abb_t* arbol, void* elemento){
    if (!arbol){
        return ERROR;
    }

    nodo_abb_t * nodo_nuevo = nodo_crear();

    if (!nodo_nuevo){
        return ERROR;
    }

    /*Es el nodo raiz el que vamos a insertar*/
    if(arbol_vacio(arbol)){
        nodo_nuevo->elemento = elemento;
        nodo_nuevo->izquierda = NULL;
        nodo_nuevo->derecha = NULL;

        arbol->nodo_raiz = nodo_nuevo;
        return EXITO;
    }

    /*Insertamos un nodo que no es la raiz*/
    nodo_abb_t* padre = NULL;
    
    padre =  arbol_buscar_nodo_padre(arbol->nodo_raiz, padre, arbol->comparador, elemento);

    /*Busco si el nodo nuevo debe ir a la izq o a la derecha*/
    abb_comparador cmp = arbol->comparador;

    int restultado = cmp(padre->elemento, elemento);

    if(restultado >= 0){
        //va a la izq
        padre->izquierda = nodo_nuevo;
        padre->derecha = NULL;

    }else{
        //va a la derecha
        padre->derecha = nodo_nuevo;
        padre->izquierda = NULL;
    }

    return EXITO;
} 

bool arbol_vacio(abb_t* arbol){
    if(!arbol){
        return true;
    }
    if(!arbol->nodo_raiz){
        return true;
    }

    return false;
}

void* arbol_raiz(abb_t* arbol){
    if(!arbol){
        return NULL;
    }

    return arbol->nodo_raiz->elemento;
}