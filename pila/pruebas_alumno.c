#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_bordes(){
    /*declaro la variable a utilizar*/
    pila_t* pila = pila_crear(); 

    print_test("creo una pila vacia", pila!=NULL);
    print_test("la pila esta vacia", pila_esta_vacia(pila) == true);
    print_test("desapilo una pila que esta vacia, deberia devolver NULL", pila_desapilar(pila) == NULL);
    print_test("obtener valor del tope de la pila vacia, debe devolver NULL ya que no hay elemento", pila_ver_tope(pila) == NULL);

    int* numero=malloc(sizeof(int));
    *numero=19;

    pila_apilar(pila,numero);
    print_test("apilar un elemento(entero) en la pila", pila_apilar(pila,numero) == true);

    pila_apilar(pila,NULL);
    print_test("apilar un elemento(de valor NULL) debe ser valido", pila_apilar(pila,NULL) == true);

    char* caracter=malloc(sizeof(char));
    *caracter='b';

    pila_apilar(pila,caracter);
    print_test("volver a apilar un elemento(caracter) en la pila", pila_apilar(pila,caracter) == true);

    print_test("la pila NO esta vacia", !pila_esta_vacia(pila));

    /*desapilar*/
    pila_desapilar(pila);
    print_test("desapilo el ultimo valor que se ingresa", pila_desapilar(pila) != NULL);

    /*desapilar*/
    pila_desapilar(pila);
    print_test("sigo desapilando (elemento de valor NULL)", pila_desapilar(pila) == NULL);

    pila_destruir(pila);
    free(numero);
    free(caracter);
    printf("destruyo la pila\n");
}

void pruebas_volumen(){
    pila_t* pila = pila_crear();
    
    int* numero=malloc(sizeof(int));
    *numero=10;

    char* caracter=malloc(sizeof(char));
    *caracter='b';

    size_t cantidad_elementos = 1000;
    size_t i;

    bool apilar = true;
    printf("-----------------PRUEBAS DE VOLUMEN-----------------\n");
    for(i = 0 ; i < cantidad_elementos ; i++){
        apilar &= pila_apilar(pila,numero);
    }
    print_test("se pudieron apilar 1000 elementos(enteros) en la pila",apilar);

    apilar=true;
    for(i = 0; i < cantidad_elementos ; i++){
        apilar &= pila_apilar(pila,caracter);
    }
    print_test("se pudieron apilar 1000 elementos(cadena de caracteres) en la pila",apilar);

    /*desapilar*/
    int desapilar_numero;
    printf("desapilo hasta que quede vacio la pila\n");
    while(i==0){
        pila_desapilar(pila);
        if(i == 900){
            print_test("desapilo el ultimo valor que se ingresa", pila_desapilar(pila) == caracter);
        }
        i--;
    }

    printf("destruyo la pila\n");
    pila_destruir(pila);
    free(numero);
    free(caracter);
}

void pruebas_pila_alumno() {
    pila_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    pruebas_bordes();
    pruebas_volumen();
}
