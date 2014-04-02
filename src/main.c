#include "binary_converter.h"
#include "error.h"
#include "socket.h"

/*
 * Implemnta un nodo de una red que implementa el protocolo de Spanning Tree
 *
 * Autor: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * Autor: Mijail Gutiérrez Valdéz; 3-423250-3.
 * mij000@ciencias.unam.mx
 * Autor: José Carlos León Pérez
 * carlos.leon@ciencias.unam.mx
 * Version 1, abril 2014
 */

//encabezado del programa

//variables globales
//indica cuantos estado del programa han sido asignados
unsigned short int asigned_states = 0;

//prototipos de funciones
void parse_args(char*, char*);
void parameters_error();

//cuerpo del programa

/*
 * Implementa el protocolo de Spanning Tree. Controla y ejecuta la aplicación
 * que simula el protocolo Spanning Tree
 */
int main(int argc, int argv)
{
	unsigned short int i;
	if(argc != 6)
	{
		parameters_error();
	}//verifica que se hayan pasado los argumentos necesarios para ejecutar
	for(i = 1; i < 6; i += 2)
	{
		parse_args(argv[i], argv[i +1]);
	}//prepara el estado de la aplicación de acuerdo a los parametros dados
	if(asigned_states != 3)
	{
		parameters_error();
	}
	return 0;
}//main

/*
 * Toma un argumento pasado por el usuario por consola con su valor y prepara
 * el estado de la aplicación de acuerdo a ellos.
 */
void parse_args(char *arg, char *val)
{
	if(strcmp(arg, "-p") == 0)
	{
		
	}
	else if(strcmp(arg, "-n0") == 0)
	{
	
	}
	else if(strcmp(arg, "-n1") == 0)
	{
	
	}
	else
	{
		printf("\"%s\" no se reconoce como un argumento v\u00E1lido para ");
		printf("esta aplicaci\u00F3n.\n");
		parameters_error();
	}//asiga un estado de la aplicación
	asigned_states++;
}//parse_args

/*
 * Muestra un error al usuario donde se le explica cuales son los argumentos
 * que la aplicación espera recibir y termina la aplicación (puesto que supone
 * que ha ingresado mal los parametros esperados y no se puede asignar un
 * estado apropiado para ejecutar)
 */
void parameters_error()
{
	printf("Debe proporcionar 3 argumentos al programa.\nEstos son:\n");
	printf("-p El n\u00FAmero de puerto que va a recibir paquetes de un ");
	pritnf("equipo remoto.\n-n0 El n\u00FAmero de puerto de uno de los ");
	printf("equipos remotos al que se deben enviar paquetes.\n-n1 El ");
	printf("n\u00FAmero de puerto del otro equipo remoto al que se ");
	printf("deben enviar paquetes\n\nPor ejemplo: ./spanning-tree -p ");
	printf("50025 -n0 50025 -n1 50025\n\n");
	exit(EXIT_FAILURE);
}//parameters_error

