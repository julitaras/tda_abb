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

/*
* Agrega el elemento a la posicion 
* del array correspondiente
*/
void agregar_elemento(void* elemento, int* i, void** array){

    array[*i] = elemento;
    
    (*i)++;
}

/*
* Funcion que hace el recorrido in_order 
* y se encarga de llamar a una funcion que 
* asigna el elemento al array
*/
void in_order(nodo_abb_t* nodo, int* i, void** array, int tamanio_array){
    if(!nodo){
        return;
    }

    if(nodo->izquierda){
        in_order(nodo->izquierda, i, array, tamanio_array);
    }

    if(nodo){
        if(*i < tamanio_array){
            agregar_elemento(nodo->elemento, i, array);
        }
    }

    if(nodo->derecha){
        in_order(nodo->derecha, i, array, tamanio_array);
    }
}

/*
* Funcion que hace el recorrido pre_order 
* y se encarga de llamar a una funcion que 
* asigna el elemento al array
*/
void pre_order(nodo_abb_t* nodo, int* i, void** array, int tamanio_array){
    if(!nodo){
        return;
    }

    if(nodo){
        if(*i < tamanio_array){
            agregar_elemento(nodo->elemento, i, array);
        }
    }
    
    if(nodo->izquierda){
        pre_order(nodo->izquierda, i, array, tamanio_array);
    }


    if(nodo->derecha){
        pre_order(nodo->derecha, i, array, tamanio_array);
    }
}

/*
* Funcion que hace el recorrido post_order 
* y se encarga de llamar a una funcion que 
* asigna el elemento al array
*/
void post_order(nodo_abb_t* nodo, int* i, void** array, int tamanio_array){
    if(!nodo){
        return;
    }

    if(nodo->izquierda){
        post_order(nodo->izquierda, i, array, tamanio_array);
    }

    if(nodo->derecha){
        post_order(nodo->derecha, i, array, tamanio_array);
    }

    if(nodo){
        if(*i < tamanio_array){
            agregar_elemento(nodo->elemento, i, array);
        }
    }
}

int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
    if(!arbol){
        return 0;
    }

    int a = 0;
    int* i = &a;
    if(!arbol_vacio(arbol)){
        in_order(arbol->nodo_raiz, i, array, tamanio_array);
    }

    return *i;
}

int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
    if(!arbol){
        return 0;
    }

    int a = 0;
    int* i = &a;
    if(!arbol_vacio(arbol)){
        //NODO ACTUAL, IZQ, DERECHO
       pre_order(arbol->nodo_raiz, i, array, tamanio_array);
    }

    return *i;
}

int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
    if(!arbol){
        return 0;
    }
    //IZQ, DER, NODO
    int a = 0;
    int* i = &a;
    if(!arbol_vacio(arbol)){
       post_order(arbol->nodo_raiz, i, array, tamanio_array);
    }

    return *i;
}

/*
* Funcion que busca el nodo 
* que reemplazaria el nodo a eliminar. 
* Se busca el inmediato superior o inmediato inferior.
*/
nodo_abb_t* arbol_buscar_nodo_reemplazo(nodo_abb_t* nodo){
    if(nodo->derecha){
        arbol_buscar_nodo_reemplazo(nodo->derecha);
    }

    return nodo;
}

/*Depende de cada caso como borramos*/
int arbol_borrar(abb_t* arbol, void* elemento){
    if(!arbol){
        return ERROR;
    }

    nodo_abb_t* nodo_eliminar = arbol_buscar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);
    nodo_abb_t* nodo_padre = NULL;

    if(!nodo_eliminar->derecha && !nodo_eliminar->izquierda){
        /*Si nodo_eliminar tiene 0 hijos (nodo hoja), Se suprime, asignando nulo al puntero de su antecesor que antes lo apuntaba a él*/

        int restultado = arbol->comparador(nodo_padre->elemento, elemento);

        if(restultado >= 0){
            nodo_padre->izquierda = NULL;

        }else{
            nodo_padre->derecha = NULL;
        }
    }

    if( (nodo_eliminar->derecha && !nodo_eliminar->izquierda) && (!nodo_eliminar->derecha && nodo_eliminar->izquierda) ){
        /*Si nodo_eliminar tiene 1 hijo, El elemento anterior se enlaza con el hijo del que queremos borrar*/
        int restultado = arbol->comparador(nodo_padre->elemento, elemento);

        if(restultado >= 0){
            if(nodo_eliminar->izquierda){
                nodo_padre->izquierda = nodo_eliminar->izquierda;
            }else{
                nodo_padre->izquierda = nodo_eliminar->derecha;
            }
        }else{
            if(nodo_eliminar->derecha){
                nodo_padre->derecha = nodo_eliminar->derecha;
            }else{
                nodo_padre->derecha = nodo_eliminar->izquierda;
            }
        }
    }

    if(nodo_eliminar->derecha && nodo_eliminar->izquierda){
        /*Si nodo_eliminar tiene 2 hijos, Se sustituye por el elemento más próximo en clave, inmediato superior o inmediato inferior.
        Para localizar estos elementos debe situarse en el hijo derecho del nodo a borrar y avanzar desde él siguiendo
        la rama izquierda de cada nodo hasta que a la izquierda ya no haya ningún nodo más, o bien, situarse en el
        hijo izquierdo y avanzar siguiendo siempre la rama derecha de cada nodo hasta llegar al final.*/

        nodo_abb_t* nodo_reemplazo = arbol_buscar_nodo_reemplazo(nodo_eliminar->izquierda);

        int restultado = arbol->comparador(nodo_padre->elemento, elemento);
        if(!nodo_padre){
            arbol->nodo_raiz = nodo_reemplazo;
        }
        if(restultado >= 0){
           nodo_padre->derecha = nodo_reemplazo;
        }else{
            nodo_padre->izquierda = nodo_reemplazo;
        }
    }

    arbol->destructor(nodo_eliminar->elemento);
    free(nodo_eliminar);

    return EXITO;
}

nodo_abb_t* arbol_buscar_padre(abb_t* arbol, nodo_abb_t* nodo_eliminar, nodo_abb_t* nodo_actual, nodo_abb_t* nodo_anterior){
    if(!arbol){
        return NULL;
    }

    int result = arbol->comparador(nodo_actual->elemento, nodo_eliminar->elemento);
    
    if(result == 1){
        return arbol_buscar_padre(arbol, nodo_eliminar, nodo_actual->izquierda, nodo_actual);
    }
    if(result == -1){
        return arbol_buscar_padre(arbol, nodo_eliminar, nodo_actual->derecha, nodo_actual);
    }

    return nodo_anterior;
}


int arbol_borrar(abb_t* arbol, void* elemento){
    if(!arbol){
        return ERROR;
    }

    nodo_abb_t* nodo_eliminar = arbol_buscar_nodo(arbol->nodo_raiz, arbol->comparador, elemento);
    nodo_abb_t* nodo_anterior = NULL;
    nodo_anterior = arbol_buscar_padre(arbol, nodo_eliminar, arbol->nodo_raiz, nodo_anterior);
    
    
    if(!nodo_eliminar->derecha && !nodo_eliminar->izquierda){
        //NO TIENE HIJOS

        if(!nodo_anterior){
            arbol->nodo_raiz = NULL;
        }


    }


}










/*
* Funcion que destruye el elemento 
* con el destructor del arbol y se 
* libera la memoria reservada para el nodo
*/
void arbol_destruir_nodo(nodo_abb_t* nodo, abb_liberar_elemento destructor){
    if(!nodo){
        return;
    }

    if(nodo->izquierda){
        arbol_destruir_nodo(nodo->izquierda, destructor);
    }

    if(nodo->derecha){
        arbol_destruir_nodo(nodo->derecha, destructor);
    }

    if(nodo){
        destructor(nodo->elemento);
    }

    free(nodo);
}

void arbol_destruir(abb_t* arbol){
    if(!arbol){
        return;
    }

    while (!arbol_vacio(arbol)) {
        arbol_destruir_nodo(arbol->nodo_raiz, arbol->destructor);
	}

	free(arbol);
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
    int* elementos[4];
    
    arbol_insertar(abb, &a);
    arbol_insertar(abb, &b);
    arbol_insertar(abb, &c);
    arbol_insertar(abb, &d);

    int cantidad = arbol_recorrido_inorden(abb, (void**)elementos, 4);
    for(int i=0;i<cantidad;i++)
		printf("%i ", *elementos[i]);
	printf("\n");

    int cantidad2 = arbol_recorrido_preorden(abb, (void**)elementos, 4);
    for(int i=0;i<cantidad2;i++)
		printf("%i ", *elementos[i]);
	printf("\n");

    int cantidad3 = arbol_recorrido_postorden(abb, (void**)elementos, 4);
    for(int i=0;i<cantidad3;i++)
		printf("%i ", *elementos[i]);
	printf("\n");

    arbol_borrar(abb, &d);

    return 0;
}