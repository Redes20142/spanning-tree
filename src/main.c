#include "binary_converter.h"
#include "error.h"
#include "socket.h"
#include "random_lib.h"
#define BPDU_LENGTH 185
#define EXPECTED_ARGUMENTS 9
#define SLEEP_SECONDS 5

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
//contienen los números de puertos
unsigned short int portno, node;
//descriptor de los socket a usar
unsigned int sock;
//direcciones de internet de los equipos remotos
char *node_addr;
//identificador del nodo
unsigned short int id;
//dirección MAC del nodo
unsigned long long int mac_addr; //ago, in a galaxy far far away...
//indica el orden de ejecución del nodo en la red
unsigned short int execution_order;
//prioridad del enlace
unsigned int priority;
//pesos de los enlaces
unsigned int p0, p1;

//prototipos de funciones
void parse_args(char*, char*);
void parameters_error();

//cuerpo del programa

/*
 * Implementa el protocolo de Spanning Tree. Controla y ejecuta la aplicación
 * que simula el protocolo Spanning Tree
 */
int main(int argc, char **argv)
{
	unsigned short int i;
	if(argc != EXPECTED_ARGUMENTS)
	{
		parameters_error();
	}//verifica que se hayan pasado los argumentos necesarios para ejecutar
	for(i = 1; i < EXPECTED_ARGUMENTS; i += 2)
	{
		parse_args(argv[i], argv[i +1]);
	}//prepara el estado de la aplicación de acuerdo a los parametros dados
	if(asigned_states != 4)
	{
		parameters_error();
	}//vereifica que se hayan asignado todos los estado necesarios
	id = ale0a(15);
	mac_addr = ale0a(0xFFFFFFFF);
	priority = ale0a(32768);
	p0 = ale0a(50);
	p1 = ale0a(50);
	unsigned short int other_id;
	unsigned long long int other_mac;
	unsigned long long int other_priority;
	unsigned int other_bridge;
	unsigned short int root_id = id;
	unsigned long long int root_mac = mac_addr;
	unsigned long long int root_priority = priority;
	unsigned int root_bridge;
	printf("Estableciendo conexi\u00F3n de red\n");
	printf("Esperando por un primer nodo remoto...\n");
	switch(execution_order)
	{
	case 1:
		sock = acceptsocket(portno);
		printf("Conectando con el equipo %s...\n", node_addr);
		sleep(SLEEP_SECONDS +1);
		node = createsocketclient(node_addr, node);
		break;
	case 2:
		sleep(1);
		node = createsocketclient(node_addr, node);
		printf("Conectando con el equipo %s...\n", node_addr);
		sleep(SLEEP_SECONDS);
		sock = acceptsocket(portno);
		break;
	case 3:
		sock = acceptsocket(portno);
		printf("Conectando con el equipo %s...\n", node_addr);
		sleep(SLEEP_SECONDS +2);
		node = createsocketclient(node_addr, node);
		break;
	default:
		printf("No se ha reconocido el orden de ejecuci\u00F3n dado en -b.\n");
		parameters_error();
	}//establece conexión de acuerdo al orden dado*/
	printf("Nodo %i\nMAC addrss: %llx\n", execute_order, mac_addr);
	printf("Soy la ra\u00EDz\n");
	printf("Enviando BPDU al nodo servido\n");
	//inicia el acuerdo del protocolo spanning tree
	//Envía un BPDU a el nodo al que sirve
	char *bpdu = malloc(BPDU_LENGTH);
	char aux[64];
	memset(bpdu, 0, BPDU_LENGTH);
	// 4 bits del ID
	itobin(4, id, aux, 64);
	strcat(bpdu, aux);
	// 8 bytes de MAC
	itobin(64, mac_addr, aux, 64);
	strcat(bpdu, aux);
	// 4 bytes de costo del puente 0
	itobin(32, p0, aux, 64);
	strcat(bpdu, aux);
	// 8 bytes identificador del puente
	itobin(64, priority +mac_addrs, aux, 64);
	strcat(bpdu, aux);
	// finalmente, 2 bytes identificador del puerto
	itobin(16, socket, aux, 64);
	stcat(bpdu);
	// envía el mensaje
	if(writesocket(socket, bpdu, BPDU_LENGTH) < 0)
	{
		printf("Ha ocurrido un error al escribir en el socket\n");
		exit(EXIT_FAILURE);
	}//comprueba que no ocurra algún error
	memset(bpdu, 0, BPDU_LENGTH);
	//lee un BPDU del nodo al que sirve
	printf("Recibiendo BPDU del nodo con direcci\u00F3n %s\n", node_addr);
	if(readsocket(node, bpdu, BPDU_LENGTH) < 0)
	{
		printf("Ha ocurrido un error al leer del socket\n");
		exit(EXIT_FAILURE);
	}//realiza una lectura segura
	/*
	 * de acuerdo a el protocolo spanning-tree; se procede a comprobar quien
	 * tiene la menor prioridad
	 */
	other_id = (short) bintoint(bpdu, 4);
	bpdu += 4;
	other_mac = bintol(bpdu);
	bpdu += 64;
	other_bridge = bintoi(bpdu);
	bpdu += 32;
	other_priority = bintol(bdpu);
	if(priority +mac_addrs == other_priority)
	{
		if(other_bridge < p1)
		{
			printf("El nodo %i con MAC %llx es la ra\u00EDz\n", other_id,
				other_mac);
			root_id = other_id;
			root_mac = other_mac;
			root_priority = other_priority;
			root_bridge = p1;
		}
		else
		{
			printf("Sigo siendo la ra\u00EDz (ha!)\n");
		}
	}
	else if(priority +mac_addrs > other_priority)
	{
		printf("El nodo %i con MAC %llx es la ra\u00EDz\n", other_id,
			other_mac);
		root_id = other_id;
		root_mac = other_mac;
		root_priority = other_priority;
		root_bridge = p1;
	}
	else
	{
		printf("Sigo siendo la ra\u00EDz (ha!)\n");
	}//decide quien fue la raíz entre este y uno de los dos nodos
	//repite el proceso para el siguiente nodo
	//TODO
	free(node_addr);
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
		portno = createsocketserver(atoi(val), 5, 0);
	}
	else if(strcmp(arg, "-a") == 0)
	{
		node_addr = malloc(sizeof(val));
		strcpy(node_addr, val);
	}
	else if(strcmp(arg, "-n") == 0)
	{
		node = atoi(val);
	}
	else if(strcmp(arg, "-b") == 0)
	{
		execution_order = atoi(val);
		if(1 > execution_order || 3 < execution_order)
		{
			printf("El valor para la bandera -b debe ser estrictamente 1, ");
			printf("2 o 3.\n");
			parameters_error();
		}//asigna el orden de ejecución dado por el usuario
	}
	else
	{
		printf("\"%s\" no se reconoce como un argumento v\u00E1lido para ",
			arg);
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
	printf("Debe proporcionar 4 argumentos al programa.\nEstos son:\n\t");
	printf("-p El n\u00FAmero de puerto que va a recibir paquetes de uno ");
	printf("de los equipos remotos.\n\t-a La direcci\u00F3n de internet del ");
	printf("equipo remoto al que se va a conectar.\n\t-n El n\u00FAmero de ");
	printf("puerto del equipo al que se va a conectar.\n\t-b El orden de ");
	printf("conexi\u00F3n entre los 3 equipos involucrados: 1, 2 o 3.\nEs ");
	printf("importante cuidar el valor de este argumento; ya que para ");
	printf("lograr una ejecuci\u00F3n correcta el valor de -b deber\u00E1n ");
	printf("ser diferente para cada equipo (cada instancia de la ");
	printf("aplicaci\u00F3n).\n\nEjemplo de invocaci\u00F3n:\n");
	printf("./spanning-tree -p 50025 -a 10.3.11.37 -n 50027 -b 1\n\nLa ");
	printf("invocaci\u00F3n debe llevarse a cabo de tal manera que se ");
	printf("emparejen dos a dos los equipos invoclucrados; siendo cada nodo ");
	printf("en la red un cliente y un servidor al mismo tiempo.\nCada ");
	printf("cliente y servidor se comunican con dos servidores distintos ");
	printf("de tal manera que es posible crear la conexi\u00F3n de los tres ");
	printf("con una topolog\u00EDa que presenta un ciclo; puesto que ");
	printf("queremos probar que spanning-tree es capaz de cerrar una de las ");
	printf("conexiones redundantes y establecer la configuraci\u00F3n ");
	printf("logica de la red adecuada.\n\nPor ejemplo, considerando la ");
	printf("invocaci\u00F3n del ejemplo anterior; podemos instanciar:\n");
	printf("./spanning-tree -p 50026 -a 10.3.11.34 -n 50025 -b 2\n");
	printf("./spanning-tree -p 50025 -a 10.3.11.36 -n 50026 -b 3\n\nDonde ");
	printf("el equipo 1 tiene IP 10.3.11.35 y escucha por el puerto 50025, ");
	printf("el cual atiende al equipo 2 y se conecta al 3;\nel equipo 2 ");
	printf("tiene IP 10.3.11.36 y escucha por el puerto 50026, el cual ");
	printf("atiende al equipo 3 y se conecta al 1 y finalmente;\nel equipo ");
	printf("3 tiene IP 10.3.11.37 y escucha por el puerto 50027, el cual ");
	printf("atiende al equipo 1 y se conecta con el 2\n\n");
	exit(EXIT_FAILURE);
}//parameters_error

