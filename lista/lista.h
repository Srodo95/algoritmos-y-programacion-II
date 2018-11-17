#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdbool.h>

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/
//Primitivas de la lista

typedef struct lista lista_t;

/*crea una lista
post: devuelve una cola vacia
*/

lista_t *lista_crear(void);

/*verifica si la lista esta vacia
post: devuelve true si la lista esta vacia, caso contrario devuelve false
pre: la lista fue creada
*/
bool lista_esta_vacia(const lista_t *lista);

/*inserta un valor al inicio de la lista
post: devuelve true si se inserta exitosamente, caso contrario devuelve false
pre; la lista fue creada
*/
bool lista_insertar_primero(lista_t *lista, void *dato);

/*inserta un valor al final de la lista
post: devuelve true si se inserta exitosamente, caso contrario devuelve false
pre; la lista fue creada
*/
bool lista_insertar_ultimo(lista_t *lista, void *dato);

/*
post: elimina el primer elemento de la lista
pre; la lista debe estar creada
*/
void *lista_borrar_primero(lista_t *lista);

/*
post: devuele el primer elemento de la lista
pre; la lista debe estar creada
*/
void *lista_ver_primero(const lista_t *lista);

/*
post: devuelve el ultimo elemento de la lista
pre; la lista debe estar creada
*/
void *lista_ver_ultimo(const lista_t* lista);

/*
post: devuelve la cantidad de elementos de la lista 
pre; la lista debe estar creada
*/
size_t lista_largo(const lista_t *lista);

/*Destruye la lista. Si se recibe la función destruir_dato por parámetro,
para cada uno de los elementos de la lista llama a destruir_dato.
Pre: la lista fue creada. destruir_dato es una función capaz de destruir
los datos de la lista, o NULL en caso de que no se la utilice.
Post: se eliminaron todos los elementos de la lista.
*/
void lista_destruir(lista_t *lista, void destruir_dato(void *));


//Primitiva de iterador interno


/*recorre los elementos de la lista, desde el inicio hasta el fin, la funcion bool visitar devuelve false
cuando no se pueda iterar dicha posicion, caso contrario true
post: 
pre; la lista debe estar creada
*/
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);

//Primitivas del iterador externo

typedef struct lista_iter lista_iter_t;

/*
post: devuelve el iterador de la lista con posicion inicial al comienzo de la lista.
pre; debe existir la lista.
*/
lista_iter_t *lista_iter_crear(lista_t *lista);

/*
post: devuelve true si se avanzo con exito, caso contrario(sea por tener la lista sin
elementos o no haya mas elemento en la posicion en donde este el iterador) devuelve false 
pre; 
*/
bool lista_iter_avanzar(lista_iter_t *iter);

/*
post: devuelve el elemento en donde se encuentra posicionado el elemento.
pre; 
*/
void *lista_iter_ver_actual(const lista_iter_t *iter);

/*
post: devuelve true si el iterador esta al final de la lista, caso contrario devuelve false
pre; debe existir el iterador;
*/
bool lista_iter_al_final(const lista_iter_t *iter);

/* destrue el iterador de la lista.
*/
void lista_iter_destruir(lista_iter_t *iter);

/* inserta el valor en la posicion donde se escuentre el iterador
post: devuelve true si se inserta con exito, caso contrario false.
pre; 
*/
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

/*
post: devuelve el elemento de la posicion del iterador que se borra
pre; debe existir el iterador
*/
void *lista_iter_borrar(lista_iter_t *iter);


#endif /* LISTA_H */
