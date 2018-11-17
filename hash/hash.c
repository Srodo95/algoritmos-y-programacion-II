#define _POSIX_C_SOURCE 200809L
#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LARGO 20
#define COTA_SUPERIOR 0.7
#define COTA_INFERIOR 0.2


typedef enum {ocupado, vacio, borrado} estado_t;

typedef struct hash_campo{
	char *clave;
	void *valor;
	estado_t estado;
	
}hash_campo_t;


typedef struct hash{
	size_t cantidad;
	size_t largo;
	float carga;
	hash_campo_t *tabla;
	hash_destruir_dato_t destruir_dato;
	
}hash_t;

struct hash_iter{
	const hash_t* hash;
	int pos;
};

// FUNCION DE HASHING
size_t hashing(const char *key, size_t H_SIZE){
	size_t hash_val = 0;

	while(*key != '\0')
		hash_val = (hash_val << 5) + *key++;
		
	return (hash_val % H_SIZE);
}

// AUXILIARES
size_t buscar(const hash_t* hash, const char* clave){
	size_t pos = hashing(clave, hash->largo);
	size_t posicion_inicial = pos;
	bool vuelta = false;
	while(!vuelta){
		if(hash->tabla[pos].estado == ocupado){
			if(strcmp(hash->tabla[pos].clave, clave) == 0){
				return pos;
			}
		}
		pos++;
    	if(hash->largo == pos){
    		pos = 0;
    	}
    	if(pos+1 == posicion_inicial){
    		vuelta = true;
    	}
	}
	pos = -1;
	return pos;
}

hash_campo_t* crear_tabla(hash_t* hash, size_t largo){
	hash_campo_t* campo = malloc(sizeof(hash_campo_t) * largo);
	
	if(!campo){
		free(hash);
		return NULL;
	}
	
	int i;
	for(i = 0; i < largo; i++){
		campo[i].estado = vacio;
	}
	return campo;
}

hash_t* hash_redimensionar(hash_t* hash, size_t tam_nuevo){
	hash_campo_t* auxiliar = hash->tabla;
	hash->tabla = crear_tabla(hash, tam_nuevo);
	for(size_t i = 0; i < hash->largo; i++){
		if(auxiliar[i].estado == ocupado){
			hash_guardar(hash, auxiliar[i].clave, auxiliar[i].valor);
			free(auxiliar[i].clave);
		}else{
			hash_guardar(hash, auxiliar[i].clave, auxiliar[i].valor);
		}
	}
	free(auxiliar);
	hash->largo = tam_nuevo;
	
	return hash;
}


// PRIMITIVAS
hash_t* hash_crear(hash_destruir_dato_t destruir_dato){
	hash_t* _hash = malloc(sizeof(hash_t));
	
	if(!_hash)
		return NULL;
		
	_hash->largo = LARGO;
	_hash->cantidad = 0;
	_hash->carga = 0;
	_hash->destruir_dato = destruir_dato;
	
	hash_campo_t* tabla = crear_tabla(_hash, _hash->largo);
	_hash->tabla = tabla;
	
	return _hash;
}

bool hash_guardar(hash_t* hash, const char *clave, void *dato){
	if((float)(hash->cantidad) / (float)(hash->largo) >= COTA_SUPERIOR*(float)hash->largo)
		hash = hash_redimensionar(hash, 2 * hash->largo);
	
	size_t pos = hashing(clave, hash->largo);
	size_t posicion_inicial = pos;
	bool vuelta = false;
	while(!vuelta){
		if(hash->tabla[pos].estado == ocupado){
			if(strcmp(hash->tabla[pos].clave,clave) == 0){
				if(hash->destruir_dato)
				hash->destruir_dato(hash->tabla[pos].valor);	
				hash->tabla[pos].valor = dato;			
				return true;
			}
		}
    	if(hash->tabla[pos].estado == vacio || hash->tabla[pos].estado == borrado){
			hash->tabla[pos].clave = strdup(clave);
			hash->tabla[pos].estado = ocupado;
			hash->tabla[pos].valor = dato;
			hash->cantidad++;
			return true;
    	}
    	pos++;
    	if(hash->largo == pos){
    		pos = 0;
    	}
    	if(pos+1 == posicion_inicial){
    		vuelta = true;
    	}
	}
    return false;
}

void *hash_borrar(hash_t *hash, const char *clave){
	if(!clave){
		return NULL;
	}
	size_t pos = buscar(hash,clave);
	if(pos == -1){
		return NULL;
	}
	hash->tabla[pos].estado = borrado;
	void* valor = hash->tabla[pos].valor;
	free(hash->tabla[pos].clave);
	hash->cantidad--;
	/*if(hash->destruir_dato){
		hash->destruir_dato(hash->tabla[pos].valor);
	}*/
	/*if((float)(hash->cantidad) / (float)(hash->largo) <= COTA_INFERIOR*hash->largo){
		hash = hash_redimensionar(hash, hash->largo/2);
	}*/
	return valor;
}

size_t hash_cantidad(const hash_t *hash){
	
	return hash->cantidad;
}

bool recorrer_vuelta(size_t posicion_inicial, size_t posicion_final){
	return (posicion_final+1 == posicion_inicial);
}

void* hash_obtener(const hash_t* hash, const char* clave){
	size_t pos = buscar(hash,clave);
	if(pos == -1){
			return NULL;
	}
	return hash->tabla[pos].valor;
}

bool hash_pertenece(const hash_t* hash, const char* clave){
	size_t pos = buscar(hash,clave);
	if(pos == -1){
		return false;
	}
	return true;
}


void hash_destruir(hash_t *hash){
	size_t pos = 0;
	if(!hash){
		return;
	}
	while(pos != hash->largo){
		if(hash->tabla[pos].estado == ocupado){
			if(hash->destruir_dato)
				hash->destruir_dato(hash->tabla[pos].valor);
			free(hash->tabla[pos].clave);
		}
		pos++;
	}
	free(hash->tabla);
	free(hash);
}

hash_iter_t* hash_iter_crear(const hash_t* hash){
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	
	if(!iter)
		return NULL;
	
	iter->pos = -1;
	iter->hash = hash;
	hash_iter_avanzar(iter);
	
	return iter;
}

bool hash_iter_avanzar(hash_iter_t* iter){
	do{
		if(hash_iter_al_final(iter))
			return false;
		iter->pos++;
		if(iter->pos == iter->hash->largo)
			return true;
		
	}while(iter->hash->tabla[iter->pos].estado != ocupado);
	
	return true;
}

const char* hash_iter_ver_actual(const hash_iter_t* iter){
	if(hash_iter_al_final(iter))
		return NULL;
		
	return iter->hash->tabla[iter->pos].clave;
}

bool hash_iter_al_final(const hash_iter_t* iter){
	size_t pos = iter->pos;
	
	if(pos == iter->hash->largo)
		return true;
		
	do{
		pos++;
		if(pos == iter->hash->largo)
			return false;
		
	}while(iter->hash->tabla[pos].estado != ocupado);
	
	
	return false;
}


void hash_iter_destruir(hash_iter_t* iter){
	free(iter);
}
