//Trabajo Interciclo
//MAteo Guillen, Franklin Tuapante


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//funciones
void bailecito();
void crearCliente();
void imprimirClientes();
void imprimirSolicitudes();
//void registrar(); 
//void retirar(); 





// datos de una solicitud
typedef struct Solicitud {
    char cedula[15];
    char servicio[50];
    char tecnico[50];
    char descripcion[100];
    struct Solicitud *sig_sol;              
} Solicitud;

 Solicitud *cima_sol=NULL; // tope de la pila de solicitudes

// nodo de la lista de clientes
typedef struct Cliente {
    char cedula[15];
    char nombres[50];
    char apellidos[50];
    struct Cliente *sig_cli;
} Cliente;;

 Cliente *primer_cli=NULL; // inicio de la lista de clientes
 Cliente *fin_cli=NULL;
 
void bailecito(){
	
	printf("Eliga un balicecito");
	printf("Baile 1: Campanas de Belen");
	printf("Baile 2: Por definir");
}


void crearCliente()
{
	//se guardara los clientes en una lista enlazada simple
    Cliente *nuevo = malloc(sizeof(Cliente)); //se crea un nuevo nodo
    nuevo->sig_cli = NULL;

    printf("Ingrese los datos del cliente\n");
	printf("Cedula: ");
	scanf("%s", nuevo->cedula);
	
	printf("Nombres: ");
	scanf("%s", nuevo->nombres);
	
	printf("Apellidos: ");
	scanf("%s", nuevo->apellidos);

    if (primer_cli == NULL) //si la lista esta vacia (no hay clientes)
    {
        primer_cli = nuevo; 
        fin_cli = nuevo;
        return;
    }
    
    //insertar al final si el numero de nodos es mayor a cero
    fin_cli->sig_cli = nuevo;
    fin_cli = nuevo;
}



void imprimirClientes()
{
    Cliente *baile = primer_cli;
    int contador = 1;

    if (baile == NULL)
    {
        printf("No hay clientes registrados\n");
        return;
    }

    printf("\nLista de Clientes\n");
    while (baile != NULL) //recorre la lista desde el primero hasta el ultimo
    {
        printf("%d. Cedula: %s | Nombres: %s | Apellidos: %s\n", contador, baile->cedula, baile->nombres, 
		baile->apellidos);
    	baile = baile->sig_cli;
        contador++;
    }
}


void imprimirSolicitudes(){
	
	
}


int main() {
    int op, version;

    // primero se elige la version
    do {
        printf("Version de push/pop (1 o 2): ");
        scanf("%d", &version);
    } while (version != 1 && version != 2);

    do {
        printf("\n--- SIGSAT ---\n");
        printf("1. Bailecito\n");
        printf("2. Crear cliente\n");
        printf("3. Registrar solicitud\n");
        printf("4. Retirar solicitud\n");
        printf("5. Mostrar clientes\n");
        printf("6. Mostrar solicitudes\n");
        printf("7. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1:
				bailecito();
				break;
            case 2: 
				crearCliente(); 
				break;
            case 3: 
				imprimirClientes();
				break;
            case 4:
				imprimirSolicitudes();
				break;
            case 5:
				
				break;
            case 6:
				printf("Salir\n");
				break;
            default:
			printf("Opcion no valida\n");
			 
        }
    } while (op != 6);

    return 0;
}
