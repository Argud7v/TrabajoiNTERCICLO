//Trabajo Interciclo
//Mateo Guillen, Franklin Tuapante

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// datos de una solicitud, pila
typedef struct Solicitud {
    char cedula[15];
    char servicio[50];
    char tecnico[50];
    char descripcion[100];
    struct Solicitud *sig;              
} Solicitud;


// nodo de la lista de clientes, linsta enlazada simple
typedef struct Cliente {
    char cedula[15];
    char nombres[50];
    char apellidos[50];
    struct Cliente *sig;
} Cliente;

Solicitud *cima_sol = NULL;   // tope de la pila de solicitudes

Cliente *primer_cli = NULL; //primer y ultimo de la lista enlazada
Cliente *fin_cli = NULL;


//funciones
int menu();


int main() {
    int op, version;

    // primero se elige la version
    do {
        printf("Version de push/pop:\n1. Version memoria dinamica\n2. Version memoria estatica\n> ");
        scanf("%d", &version);
    } while (version != 1 && version != 2);

    do {
        op = menu();

        switch (op) {
            case 1: //crear cliente
			
				break;
            case 2: //registrar solicitud (push, ambas versiones)
			    if (version == 1)
                {
                } 
                else
                {}
				break;
            case 3: //retirar solicitud (pop, ambas versiones)
                if (version == 1)
                {
                } 
                else
                {}
				break;
            case 4: //mostar clientes
                break;
            case 5: //mostrar solicitudes
                break;
            case 6: //salir
				printf("Saliendo del programa.\n"); 
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
    printf("\n--- SIGSAT ---\n");
        printf("1. Crear cliente\n");
        printf("2. Registrar solicitud\n");
        printf("3. Retirar solicitud\n");
        printf("4. Mostrar todos los clientes\n");
        printf("5. Mostrar todas las solicitudes\n");
        printf("6. Salir\n");
        printf("> ");
        scanf("%d", &opcion);
        return opcion;
}


