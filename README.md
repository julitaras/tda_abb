

<h1 align="center">TDA ABB</h3>

---

<p align="center"> Desarrollo del TDA arbol binario de busqueda
    <br> 
</p>

## 📝 Contenido

- [Enunciado](#enunciado)
- [Compilacion y Ejecucion](#compilacion_ejecucion)
- [FAQS](#faqs)

## Enunciado <a name = "enunciado"></a>

Se pide implementar un Arbol Binario de Búsqueda. Para ello se brindan las firmas de las funciones públicas a implementar y se deja a criterio del alumno la creación de las funciones privadas del TDA para el correcto funcionamiento del Arbol cumpliendo con las buenas prácticas de programación.


Adicionalmente se pide la implementación de un iterador interno para la estructura.


## 🏁 Compilacion y Ejecucion <a name = "compilacion_ejecucion"></a>

- ¿Cómo compilamos?
    `````c
    gcc abb.c abb_pruebas.c -o abb -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O0
    `````

- ¿Cómo ejecutamos ?
    `````c
        ./abb
    `````

### Preguntas <a name = "faqs"></a>

1. Explicar qué es un ABB y cómo se diferencia de un Árbol Binario.

    Un ABB es un tipo de arbol binario. 
    
    Sabemos que la clave/elemento que se encuentra en el hijo izquierdo es menor a la clave/elemento del nodo_padre y por lo tanto, la clave/elemento que se encuentra en el hijo izquierdo es mayor a la clave/elemento del nodo_padre.


2. Explicar cuál es el objetivo de tener una función de destrucción en el TDA y qué implicaría para el usuario no tenerla.

    Entiendo que al tener la funcion de destruccion, conocemos la manera de destruir el dato que colocamos en el arbol. Por lo tanto, llegamoa  a conocer que tipo de dato estan guardando.


    Implicaria que nos hacemos cargo de la destruccion del dato que ingresaria el usario, por lo que deja de tener esa responsabilidad.

3. ¿Cuál es la complejidad de las diferentes operaciones del ABB? Justifique.

    - Complejidad de insertar es `O(N)`, ya que siempre insertamos nodos hojas y lo unico que tenemos que hacer es recorrer hasta donde corresponde, por lo tanto n nodos y luego insertar el nodo que es una operacion de `O(1)`.
   
    - Complejidad de buscar es `O(N)`, ya que vamos recorriendo el arbol y en el peor de los casos seria recorrer n nodos. 
    
    - Complejidad de borrar es `O(N)`, ya que recorremos el arbol hasta encontrar el elemento que queremos eliminar. El peor de los casoss seria recorrer todo el arbol, por lo tanto n elementos.

        Siendo que:
        - El nodo no tenga hijos, solo queda eliminar el nodo. Sigue quedando `O(N)`.
        - El nodo tenga un hijo, quedaria enlazar el hijo al nodo_padre del nodo que queremos eliminar. Sigue quedando `O(N)`.
        - El nodo tenga 2 hijos, se busca un reemplazante que buscamos a partir del nodo que queremos eliminar, lo  que podemos considerar que esta operacion es `O(N)` y luego solo queda reemplazar el nodo_reemplazo por el nodo que queremos eliminar. Entonces nos sigue quedando `O(N)`.
    
    - Complejidad de los recorridos es `O(N)`, ya que recorremos todos los nodos. Por lo tanto, n nodos.

