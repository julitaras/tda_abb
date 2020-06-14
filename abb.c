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
	
	if(resultado == 0){ 
		return nodo;
    }

	if (resultado == 1){
		return arbol_buscar_nodo(nodo->izquierda, comparador, elemento); 
    }

	return arbol_buscar_nodo(nodo->derecha, comparador, elemento); 
}

void* arbol_buscar(abb_t* arbol, void* elemento){
    if(!arbol || arbol_vacio(arbol)){
        return NULL;
    }

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
    nodo_nuevo->elemento = elemento;

    if(arbol_vacio(arbol)){
        nodo_nuevo->izquierda = NULL;
        nodo_nuevo->derecha = NULL;

        arbol->nodo_raiz = nodo_nuevo;
        return EXITO;
    }

    /*Insertamos un nodo que no es la raiz*/
    nodo_abb_t* padre = NULL;
    
    padre =  arbol_buscar_nodo_padre(arbol->nodo_raiz, padre, arbol->comparador, elemento);

    int restultado = arbol->comparador(padre->elemento, elemento);

    if(restultado >= 0){
        padre->izquierda = nodo_nuevo;

    }else{
        padre->derecha = nodo_nuevo;
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

int arbol_borrar(abb_t* arbol, void* elemento){
    if(!arbol){
        return ERROR;
    }
    return EXITO;
}

void in_order(nodo_abb_t* nodo){
    if(!nodo){
        //llegamos al nodo hoja
        return;
    }

    if(nodo->izquierda){
        in_order(nodo->izquierda);
    }

    if(nodo){
        printf("Elemento: %i \n", *(int*)nodo->elemento);
        //este elemento es el que deberia guardar en el arrya
        //ACA SE GUARDA EN EL ARRAY EN VEZ DE IMPRIMIR
;   }

    if(nodo->derecha){
        in_order(nodo->derecha);
    }
}


int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
    if(!arbol){
        return 0;
    }

    //si existe el nodo raiz o sea si el arbol no esta vacio llamo a inorden 
    if(!arbol_vacio(arbol)){
        in_order(arbol->nodo_raiz);
    }

    //Secuencia inorden: hijo Izquierdo, nodo, hijo derecho

    return tamanio_array;
}

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

int main(){
    abb_t* abb = arbol_crear(comparador, NULL);
    int a = 4, b = 2, c = 5, d = 1;

    arbol_insertar(abb, &a);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &d);
    in_order(abb->nodo_raiz);

    return 0;
}