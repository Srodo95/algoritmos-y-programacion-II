#include "lista.h"
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
    lista_t* lista = lista_crear(); 
    print_test("creo una lista vacia", lista!=NULL);
    print_test("la lista esta vacia", lista_esta_vacia(lista) == true);
    print_test("se borra un elemento que no existe, debe devolver NULL",lista_borrar_primero(lista) == NULL);
    print_test("ver primer elemento, pero como esta vacia, debe devolver null", lista_ver_primero(lista) == NULL);
    print_test("obtener valor del primer elemento de la lista vacia, debe devolver NULL ya que no hay elemento", lista_ver_primero(lista) == NULL);

    int* numero=malloc(sizeof(int));
    *numero=10;

    print_test("agregar un elemento(entero) en la lista", lista_insertar_primero(lista,numero) == true);
    print_test("quiero ver el primer elemento de la lista, que seria un entero", lista_ver_primero(lista) == numero);
    print_test("devolver largo de la lista con un elemento", lista_largo(lista) == 1);

    print_test("enlistar un elemento(de valor NULL) debe ser valido", lista_insertar_ultimo(lista,NULL) == true);

    char* caracter=malloc(sizeof(char));
    *caracter='b';

    print_test("volver a agregar un elemento en la primer posicion(caracter) en la lista", lista_insertar_primero(lista,caracter) == true);

    print_test("la lista NO esta vacia", !lista_esta_vacia(lista));

    print_test("borro el primero, debe devolverme un caracter", lista_borrar_primero(lista) == caracter);

    lista_destruir(lista,free);
    free(caracter);
    printf("destruyo la lista\n");
}

void pruebas_volumen(){
    lista_t* lista = lista_crear();
    
    int a=19;
    int* numero=&a;
    char c='b';
    char* caracter=&c;
    char* palabra = "martin";

    size_t cantidad_elementos = 1000;
    size_t i;

    bool agregar = true;
    printf("-----------------PRUEBAS DE VOLUMEN-----------------\n");
    for(i = 0 ; i < cantidad_elementos ; i++){
        agregar &= lista_insertar_primero(lista,numero);
        numero++;
    }
    print_test("se pudieron agregar 1000 elementos(enteros) en la lista",agregar);

    agregar=true;
    for(i = 0; i < cantidad_elementos ; i++){
        agregar &= lista_insertar_primero(lista,caracter);
    }
    print_test("se pudieron agregar 1000 elementos(cadena de caracteres) en la lista",agregar);
    for(i = 0 ; i < cantidad_elementos ; i++){
        agregar &= lista_insertar_primero(lista,palabra);
    }
    print_test("se pudieron agregar 1000 elementos(cadena de palabras) en la lista",agregar);

    printf("destruyo la lista\n");
    lista_destruir(lista,NULL);
}

void pruebas_iter(){
    printf("-----------------PRUEBAS DE ITERADOR-----------------\n");

    lista_t* lista = lista_crear();
    lista_iter_t* iterador = lista_iter_crear(lista);

     int* numero=malloc(sizeof(int));
    *numero=10;

    char* caracter=malloc(sizeof(char));
    *caracter='b';

    char* palabra = "computadora";

    //print_test("se quiere avanzar el iterador sin elementos, debe devolver false",lista_iter_avanzar(iterador) == false);
    //print_test("se quiere ver el actual, debe devolver NULL",lista_iter_ver_actual(iterador) == NULL);

    print_test("se inserta un numero",lista_iter_insertar(iterador, numero));  
    print_test("se quiere ver el primer elemento, debe devolver un numero", lista_ver_primero(lista) == numero);

    print_test("se inserta una palabra",lista_iter_insertar(iterador, palabra));
    print_test("se quiere ver el primer elemento, debe devolver una palabra", lista_ver_primero(lista) == palabra);
    
    print_test("se inserta un caracter",lista_iter_insertar(iterador, caracter));

    print_test("iter no esta al final", lista_iter_al_final(iterador) == false);

    lista_iter_avanzar(iterador);

    print_test("se avanza una posicion y el valor actual debe ser un palabra",lista_iter_ver_actual(iterador) == palabra);
    print_test("se borra el valor actual: devuelve una palabra",lista_iter_borrar(iterador) == palabra);
    
    print_test("iter NO esta al final", lista_iter_al_final(iterador) == false);

    print_test("se quiere ver el actual, debe devolver numero",lista_iter_ver_actual(iterador) == numero);

    printf("se borra y se destruye el iterador\n");

    printf("avanzo en el iterador\n");
    lista_iter_avanzar(iterador);
    print_test("se quiere avanzar el iterador ya estando al final, debe devolver false",lista_iter_avanzar(iterador) == false);

    lista_destruir(lista,NULL);
    free(numero);
    free(caracter);
    lista_iter_destruir(iterador); 
}

bool sumar_todos(void *dato, void *extra){
    *(int*) extra += *(int*) dato;
    return true;
}

void pruebas_iter_interno(){
    printf("PRUEBA DE ITERADOR INTERNO\n");
    lista_t* lista = lista_crear();
    int numeros[5] = {1,2,3,4,5};
    int comparar_suma_elementos = 0;
    for(int i=0; i<=4; i++){
        lista_insertar_primero(lista,&numeros[i]);
        comparar_suma_elementos += numeros[i];
    }
    int contador = 0;
    lista_iterar(lista, sumar_todos, &contador);
    print_test("se suman todos los valores y debe devolver la sumatoria", comparar_suma_elementos == contador);
    lista_destruir(lista,NULL);
}

void pruebas_lista_alumno(void) {
    lista_t* ejemplo = NULL;
    print_test("Puntero inicializado a NULL", ejemplo == NULL);
    pruebas_bordes();
    pruebas_volumen();
    pruebas_iter();
    pruebas_iter_interno();
}
