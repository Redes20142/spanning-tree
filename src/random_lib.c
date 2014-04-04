#include "random_lib.h"

/*
 * Implementa funciones que nos permiten trabajar con números aleatoreos.
 *
 * Creado por: Manuel Ignacio Castillo López; 3-0801743-8.
 * manuel_castillo_cc@ciencias.unam.mx
 * Version 1, enero 2014
 */

//devuelve un enero aleatoreo entre 0 y a
int ale0a(int a)
{
	srand(time(NULL));
	int result;
	if(a < 0)
	{
		result = (-1) *a;
		result = rand() %(result +1);
		result *= -1;
	}
	else
	{
		result = rand() %(a +1);
	}//dependiendo si a es negativa
	return result;
}//ale0a

//devuelve un entero aleatoreo entre a y b
int aleab(int a, int b)
{
	if(a > b)
	{
		printf("random_lib -> aleab : a cannot be greather than b");
		return 0;
	}//si a es mayor que b
	srand(time(NULL));
	int result;
	if(a < 0)
	{
		if(b < 0)
		{
			result = (-1) *a;
			int aux = (-1) *b;
			result = result +(rand() %(aux +1));
			result *= -1;
		}
		else
		{
			result = (-1) *a;
			result = result +(rand() %(b +1));
			if(ale01() < 5)
			{
				result *= -1;
			}//hechamos un volado para ver si el aleatoreo es negativo
		}//si a y b son menores que 0 o sólo a
	}
	else
	{
		result = a +(rand() %(b +1));
	}
	return result;
}//aleab

//devuelve un double aleatoreo entr 0 y 1
double ale01(void)
{
	srand(time(NULL));
	return ((double) rand()) / (double) RAND_MAX;
}//ale01

//devuelve un flotante aleatoreo entre 0 y a
float alef0a(float a)
{
	int flr = (int) floor(a);
	float rest = a -abs(flr);
	float result = ale0a(flr);
	if(abs((int) ceil(result +rest)) >= abs((int) ceil(a)))
	{
		return result;
	}
	else
	{
		return result +rest;
	}//si excede el valor de a
}//alef0a

//devuelve un flotante aleatoreo entre a y b
float alefab(float a, float b)
{
	int flra = (int) floor(a);
	int flrb = (int) floor(b);
	float resta = a -abs(flra);
	float restb = b -abs(flrb);
	float result = aleab((int) flra, (int) flrb);
	if(abs((int) ceil(result +resta +restb)) <= abs((int) ceil(b)))
	{
		return result +resta +restb;
	}
	if(abs((int) ceil(result +resta)) <= abs((int) ceil(b)))
	{
		return result +resta;
	}
	if(abs((int) ceil(result +restb)) <= abs((int) ceil(b)))
	{
		return result +restb;
	}
	else
	{
		return result;
	}//si excede algún límite
}//alefab

