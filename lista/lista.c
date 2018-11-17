#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "lista.h"
const size_t TAM=20;


typedef struct nodo{
	void* elemento;
	struct nodo* siguiente;
}nodo_t;

struct lista{
	nodo_t* primero;
	nodo_t* ultimo;
	size_t largo;
};

struct lista_iter{
	nodo_t* anterior;
	nodo_t* actual;
	lista_t* lista;
};

nodo_t* crear_nodo(void* dato){
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if(!nodo){
		return NULL;
	}
	nodo->elemento = dato;
	nodo->siguiente = NULL;
	return nodo;
}


lista_t *lista_crear(void){
	lista_t* lista = malloc(sizeof(lista_t));
	if(!lista){
		return NULL;
	}
	lista->primero=NULL;
	lista->ultimo=NULL;
	lista->largo = 0;
	return lista;
}

bool lista_esta_vacia(const lista_t *lista){
	if(lista->largo == 0){
		return true;
	}
	return false;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
	nodo_t* nodo = crear_nodo(dato);
	nodo->siguiente = lista->primero;
	lista->primero = nodo;
	if(lista_esta_vacia(lista)){
		lista->ultimo = nodo;
	}
	lista->largo++;
	return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
	nodo_t* nodo = crear_nodo(dato);
	if(lista_esta_vacia(lista)){
		lista->primero = nodo;
		lista->ultimo = nodo;
	}
	else{
		lista->ultimo->siguiente = nodo;
		lista->ultimo = nodo;
	}
	lista->largo++;
	return true;
}

void *lista_borrar_primero(lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	nodo_t* nodo = lista->primero;
	void* auxiliar = nodo->elemento;
	lista->primero = nodo->siguiente;
	lista->largo--;
	if(lista_esta_vacia(lista)){
		lista->ultimo = NULL;
	}
	free(nodo);
	return auxiliar;
}

void *lista_ver_primero(const lista_t *lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->primero->elemento;
}

void *lista_ver_ultimo(const lista_t* lista){
	if(lista_esta_vacia(lista)){
		return NULL;
	}
	return lista->ultimo->elemento;
}

size_t lista_largo(const lista_t *lista){
	return lista->largo;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
	while(!lista_esta_vacia(lista)){
		void* auxiliar = lista_borrar_primero(lista);
		if(destruir_dato!=NULL){
			destruir_dato(auxiliar);
		}
	}
	free(lista);
}


// ITERADOR INTERNO

void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){
	if(!lista){
		return;
	}
	nodo_t* nodo = lista->primero;
	while(nodo != NULL && visitar(nodo->elemento,extra)){
		nodo = nodo->siguiente;
	}
}

//ITERADOR EXTERNO

lista_iter_t *lista_iter_crear(lista_t *lista){
	lista_iter_t* iterador = malloc(sizeof(lista_iter_t));
	if(!iterador){
		return NULL;
	}
	iterador->lista = lista;
	iterador->actual = lista->primero;
	iterador->anterior = NULL;
	return iterador;
}

bool lista_iter_avanzar(lista_iter_t *iter){
	if(lista_esta_vacia(iter->lista) || lista_iter_al_final(iter)){
		return false;
	}
	iter->anterior = iter->actual;
	iter->actual = iter->actual->siguiente;
	return true;
}

void *lista_iter_ver_actual(const lista_iter_t *iter){
	if(!iter->actual){
		return NULL;
	}
	return iter->actual->elemento;
}

bool lista_iter_al_final(const lista_iter_t *iter){
	if(!iter->actual){
		return true;
	}
	return false;
}

void lista_iter_destruir(lista_iter_t *iter){
	free(iter);
}


bool lista_iter_insertar(lista_iter_t *iter, void *dato){
	if(!iter){
		return false;
	}
	if(!iter->anterior){
		if(lista_insertar_primero(iter->lista,dato)){
			iter->actual = iter->lista->primero;
		}
	}else if(!iter->actual){
		if(lista_insertar_ultimo(iter->lista,dato)){
			iter->actual = iter->lista->ultimo;
		}
	}else{
		nodo_t* nodo = crear_nodo(dato);
		iter->anterior->siguiente = nodo;
		nodo->siguiente = iter->actual;
		iter->actual = nodo;
		iter->lista->largo++;
	}
	return true;
}

void *lista_iter_borrar(lista_iter_t *iter){
	if(lista_iter_al_final(iter) || lista_esta_vacia(iter->lista)){
		return NULL;
	}
	nodo_t* nodo = iter->actual;
	void* auxiliar = iter->actual->elemento;
	iter->actual = iter->actual->siguiente;
	if(!iter->anterior){
		iter->lista->primero = iter->actual;
	}else{
		if(!iter->actual){
			iter->lista->ultimo = iter->anterior;
		}
		iter->anterior->siguiente = iter->actual;
	}
	free(nodo);
	iter->lista->largo--;
	return auxiliar;
}
