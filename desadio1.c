//Franklin Tuapante, Mateo Guillen, desafio 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Producto
{
    char nombre_prod[40];
    int codigo;
    struct Producto *sig;
} Producto;

// Pila
Producto *cima = NULL;

// Cola
Producto *frente = NULL;
Producto *final = NULL;

// Prototipos de funciones
int menu();
void ingresar_producto(int version);

// Funciones Pila
void push_producto(char nombre[40], int codigo);
void pop_producto();
void imprimir_pila();
void liberarMemoria_pila();

// Funciones Cola


int main() {
    int op, version;

    do {
        printf("Usar Pila = 1 o Cola = 2\n");
        printf("Version: ");
        scanf("%d", &version);
    } while (version != 1 && version != 2);

    do {
        op = menu();

        switch (op) {
            case 1: 
                ingresar_producto(version);
                break;
            case 2: 
                if (version == 1) {
                    pop_producto();
                } else {
                    
                }
                break;
            case 3: 
                if (version == 1) {
                    imprimir_pila();
                } else {
                  //  imprimir_cola();
                }
                break;
            case 4: 
                if (version == 1) {
                    liberarMemoria_pila();
                } else {
                    
                }
                printf("Salir\n");
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
    printf("\n--- MENU DE OPCIONES ---\n");
    printf("1. Ingresar Producto\n");
    printf("2. Eliminar Producto\n");
    printf("3. Imprimir Productos\n");
    printf("4. Salir\n");
    printf("Opcion: ");
    scanf("%d", &opcion);
    return opcion;
}

void ingresar_producto(int version) {
    char nombre[40];
    int codigo;

    printf("\nIngrese el codigo: ");
    scanf("%d", &codigo);
    
    printf("Ingrese el nombre del producto: ");
    scanf(" %39[^\n]", nombre); 

    if (version == 1) {
        push_producto(nombre, codigo);
    } 
    
}

//Pila

void push_producto(char nombre[40], int codigo)
{
    Producto *nuevo = (Producto *)malloc(sizeof(Producto));
    if (nuevo == NULL)
    {
        printf("No hay memoria suficiente.\n");
        return;
    }
    
    nuevo->codigo = codigo;
    strcpy(nuevo->nombre_prod, nombre);
    nuevo->sig = cima;
    cima = nuevo;

    printf("\n-------------------------\nProducto ingresado a la Pila.\n-------------------------\n");
}

void pop_producto()
{
    if (cima == NULL)
    {
        printf("\nNo hay productos ingresados en la Pila.\n");
        return;
    }

    Producto *temp = cima;
    cima = cima->sig;
    printf("\n--------------\nProducto '%s' (Codigo: %d) eliminado de la Pila.\n--------------\n", temp->nombre_prod, temp->codigo);
    free(temp);
}

void imprimir_pila()
{
    if (cima == NULL)
    {
        printf("\nLa Pila esta vacia.\n");
        return;
    }

    Producto *actual = cima;
    printf("\n=== PRODUCTOS EN LA PILA (Cima -> Base) ===\n");
    while (actual != NULL)
    {
        printf("Codigo: %d | Nombre: %s\n", actual->codigo, actual->nombre_prod);
        actual = actual->sig;
    }
    
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


