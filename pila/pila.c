#include "pila.h"
#include <stdlib.h>
const size_t TAM_INICIAL=10;
/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

pila_t* pila_crear(void){
	pila_t* pila = malloc(sizeof(pila_t));
	if(!pila){
		return NULL;
	}
	pila->datos = malloc(TAM_INICIAL*sizeof(void*));
	if(pila->datos == NULL){
		free(pila);
		return NULL;
	}
	pila->cantidad=0;
	pila->capacidad=TAM_INICIAL;
	return pila;
}

void pila_destruir(pila_t *pila){
	free(pila->datos);
	free(pila);
}

bool pila_esta_vacia(const pila_t *pila){
	if(pila->cantidad == 0){
		return true;
	}
	return false;
}

bool redimensionar(pila_t* pila, size_t tamanio){
	void** dato_nuevo = realloc(pila->datos,sizeof(void*)*tamanio);
	if(dato_nuevo == NULL){
		return false;
	}
	pila->datos = dato_nuevo;
	pila->capacidad=tamanio;
	return true;
}

bool pila_apilar(pila_t *pila, void* valor){
	if(pila->cantidad >= pila->capacidad){
		if(!redimensionar(pila,pila->cantidad*2)){
			return false;
		}
	}
	pila->datos[pila->cantidad]=valor;
	pila->cantidad++;
	return true;
}

void* pila_ver_tope(const pila_t *pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	return pila->datos[pila->cantidad-1];
}

void* pila_desapilar(pila_t *pila){
	if(pila_esta_vacia(pila)){
		return NULL;
	}
	if(pila->cantidad < pila->capacidad/4){
		redimensionar(pila,pila->capacidad/2);
	}
	void* auxiliar=pila->datos[pila->cantidad-1];
	pila->cantidad--;
	return auxiliar;
}

// ...
