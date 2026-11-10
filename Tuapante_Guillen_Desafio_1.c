//Franklin Tuapante, Mateo Guillen, desafio 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Producto
{
	char nombre_prod[40];
	int codigo;
	struct Producto *sig;
} Producto;

//pila
Producto *cima = NULL;

//cola
Producto *frente = NULL;
Producto *final = NULL;

//funciones
//pila
void push_producto();
void pop_producto();
void liberarMemoria_pila();
//cola

int main()
{
	int version;
	int cod;
	char nombre[40];
	
	printf("Ingrese el nombre del producto: ");
	scanf(" %39[^\n]", nombre);
	printf("Ingrese el codigo del producto: ");
	scanf("%d", &cod);
	
}

//funciones para la pila
void push_producto(char nombre[40], int codigo)
{
	Producto *nuevo = (Producto *)malloc(sizeof(Producto));
	
	if (nuevo == NULL)
    {
        printf("No hay memoria suficiente.\n");
        return;
    }
    
    nuevo->sig = NULL;
	nuevo->codigo = codigo;
	strcpy(nuevo->nombre_prod, nombre);
	
	if (cima == NULL)// pila vacia
	{
		cima = nuevo;
	}
	else
	{
		nuevo->sig = cima;
		cima = nuevo;
	}
	
    printf("\n-------------------------\nIngresado con exito.\n-------------------------\n");
}

void pop_producto()
{
	if (cima == NULL)
    {
        printf("No hay pproductos ingresados.\n");
        return;
    }

    Producto *temp = cima;
    
    cima = cima->sig;
    free(temp);
    printf("\n--------------\nEliminado exitosamente.\n--------------\n");
}

void liberarMemoria_pila()
{
	Producto *actual = cima;
	Producto *siguiente = NULL;
	
	while (actual != NULL)
	{
		siguiente = actual->sig;
		free(actual);
		actual = siguiente;
	}
	
	cima = NULL;
}

