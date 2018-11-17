#include "cola.h"
#include <stdlib.h>
const size_t TAMANIO=10;

typedef struct nodo{
	void* elemento;
	struct nodo* siguiente;
}nodo_t;

struct cola{
	nodo_t* primero;
	nodo_t* ultimo;
};

cola_t* cola_crear(void){
	cola_t* cola=malloc(sizeof(cola_t)*TAMANIO);
	if(!cola){
		return NULL;
	}
	cola->primero=NULL;
	cola->ultimo=cola->primero;
	return cola;
}


void cola_destruir(cola_t *cola, void destruir_dato(void*)){
	while(!cola_esta_vacia(cola)){
		nodo_t* auxiliar = cola->primero;
		if(destruir_dato!=NULL){
			destruir_dato(auxiliar->elemento);
		}
		cola_desencolar(cola);
	}
	free(cola);
}	

bool cola_esta_vacia(const cola_t *cola){
	if(cola->primero == NULL){
		return true;
	}
	return false;
}

bool cola_encolar(cola_t *cola, void* valor){
	if(!cola){
		return false;
	}
	nodo_t* nodo=malloc(sizeof(nodo_t));
	if(!nodo){
		return false;
	}
	nodo->elemento=valor;
	nodo->siguiente=NULL;
	if(cola_esta_vacia(cola)){
		cola->primero=nodo;
		cola->ultimo=nodo;
	}else{
		cola->ultimo->siguiente=nodo;
		cola->ultimo=nodo;
	}
	return true;
}

void* cola_ver_primero(const cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	return cola->primero->elemento;
}

void* cola_desencolar(cola_t *cola){
	if(cola_esta_vacia(cola)){
		return NULL;
	}
	nodo_t* nodo = cola->primero;
	void* auxiliar = nodo->elemento;
	cola->primero = cola->primero->siguiente;
	if(!cola->primero){
		cola->ultimo = NULL;
	}
	free(nodo);
	return auxiliar;
}