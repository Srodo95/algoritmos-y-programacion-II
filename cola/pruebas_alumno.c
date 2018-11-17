#include "cola.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


void destruir_dato(void* dato){
    free(dato);
}

void pruebas_bordes(){
    /*declaro la variable a utilizar*/
    cola_t* cola = cola_crear(); 
    print_test("creo una cola vacia", cola!=NULL);
    print_test("la cola esta vacia", cola_esta_vacia(cola) == true);
    print_test("ver primer elemento, pero como esta vacia, debe devolver null", cola_ver_primero(cola) == NULL);
    print_test("desencolar una cola que esta vacia, deberia devolver NULL", cola_desencolar(cola) == NULL);
    print_test("obtener valor del primer elemento de la cola vacia, debe devolver NULL ya que no hay elemento", cola_ver_primero(cola) == NULL);

    int* numero=malloc(sizeof(int));
    *numero=10;

    cola_encolar(cola,numero);
    print_test("encolar un elemento(entero) en la cola", cola_encolar(cola,numero) == true);

    cola_encolar(cola,NULL);
    print_test("encolar un elemento(de valor NULL) debe ser valido", cola_encolar(cola,NULL) == true);

    char* caracter=malloc(sizeof(char));
    *caracter='b';

    cola_encolar(cola,caracter);
    print_test("volver a encolar un elemento(caracter) en la cola", cola_encolar(cola,caracter) == true);

    print_test("la cola NO esta vacia", !cola_esta_vacia(cola));

    //desencolar
    cola_desencolar(cola);
    print_test("desacolar el primer valor que se ingresa", cola_desencolar(cola) == numero);

    //desencolar
    cola_desencolar(cola);
    print_test("sigo desacolando (elemento de valor NULL)", cola_desencolar(cola) == NULL);

    printf("vuelvo a agregar un entero y un caracter");
    cola_encolar(cola,numero);
    cola_encolar(cola,caracter);
    print_test("encolar un elemento(entero) en la cola", cola_encolar(cola,numero) == true);
    print_test("volver a encolar un elemento(caracter) en la cola", cola_encolar(cola,caracter) == true);

    printf("destruyo la cola\n");
    cola_destruir(cola,NULL);
    free(caracter);
    free(numero);
}

void pruebas_volumen(){
    cola_t* cola = cola_crear();
    
    int a=19;
    int* numero=&a;
    char c='b';
    char* caracter=&c;

    size_t cantidad_elementos = 1000;
    size_t i;

    bool encolar = true;
    printf("-----------------PRUEBAS DE VOLUMEN-----------------\n");
    for(i = 0 ; i < cantidad_elementos ; i++){
        encolar &= cola_encolar(cola,numero);
        numero++;
    }
    print_test("se pudieron encolar 1000 elementos(enteros) en la cola",encolar);

    encolar=true;
    for(i = 0; i < cantidad_elementos ; i++){
        encolar &= cola_encolar(cola,caracter);
    }
    print_test("se pudieron encolar 1000 elementos(cadena de caracteres) en la cola",encolar);

    //desencolar
    printf("desencolar hasta que quede vacio la cola\n");
    while(!cola_esta_vacia(cola)){
        cola_desencolar(cola);
    }


    printf("destruyo la cola\n");
    cola_destruir(cola,free);
}

void pruebas_cola_alumno() {
    cola_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    pruebas_bordes();
    pruebas_volumen();
}
