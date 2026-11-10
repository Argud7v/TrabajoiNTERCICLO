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
int menu();
//pila
void push_producto(char nombre[40], int codigo);
void pop_producto();
void liberarMemoria_pila();
//cola
void liberarMemoria_cola();
void insertar_cola(char nombre[40], int codigo);
void eliminar_cola();


int main()
{
	char nombre[40];	
	int op, version, cod;

    do {
        printf("Usar Pila=1 o Cola=2\n");
        printf("Version: ");
        scanf("%d", &version);
    } while (version != 1 && version != 2);

    do {
        op = menu();

        switch (op) {
            case 1: //ingresar
            	printf("Ingrese el nombre del producto: ");
				scanf(" %39[^\n]", nombre);
				printf("Ingrese el codigo del producto: ");
				scanf("%d", &cod);
				
				if (version == 1) //pila
					push_producto(nombre, cod);
				else //cola
					insertar_cola(nombre, cod);
				break;
            case 2: //eliminar
            	if (version == 1) //pila
					pop_producto();
				else //cola
					eliminar_cola();
				break;
            case 3: //mostrar productos
               
				break;
            case 4: //salir
            	printf("Saliendo---\n");
            	if (version == 1)
                    liberarMemoria_pila();
                else
                    liberarMemoria_cola();
            	break;
            default: 
			printf("Opcion no valida\n");
			 
        }
    } while (op != 4);

    return 0;
	
}

int menu()
{
    int opcion;
        printf("1. Ingresar Producto\n");
        printf("2. Eliminar Producto\n");
        printf("3. Imprimir Productos\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &opcion);
        return opcion;
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

void liberarMemoria_cola()
{
	Producto *actual = frente;
	Producto *siguiente = NULL;
	
	while (actual != NULL)
	{
		siguiente = actual->sig;
		free(actual);
		actual = siguiente;
	}
	
	frente = NULL;
	final = NULL;
}

void insertar_cola(char nombre[40], int codigo)
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
    
 
    if (frente == NULL) // cola vacia
    {
        frente = nuevo;
        final = nuevo;
    }
    else //insertar al final
    {
        final->sig = nuevo;
        final = nuevo;
    }
    
    printf("\n-------------------------\nIngresado a la cola con exito.\n-------------------------\n");
}

void eliminar_cola()
{
    if (frente == NULL)
    {
        printf("No hay productos ingresados.\n");
        return;
    }

    // Siempre sale el frente
    Producto *temp = frente;
    frente = frente->sig; 

    // Si al eliminar el elemento la cola queda vacia, el final debe ser NULL
    if (frente == NULL)
    {
        final = NULL;
    }

    free(temp); 
       printf("\n--------------\nEliminado exitosamente.\n--------------\n");
}
