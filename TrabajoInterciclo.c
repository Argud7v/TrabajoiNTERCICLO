//Trabajo Interciclo
//MAteo Guillen, Franklin Tuapante


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//funciones
void bailecito();
void crearCliente();
//void crearSolicitud();
void imprimirClientes();
void imprimirSolicitudes();
void liberarMemoria_cli();
void liberarMemoria_sol();
void liberarMemoria();

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
	
	printf("Eliga un balicecito\n");
	printf("Baile 1: Campanas de Belen\n");
	printf("Baile 2: Por definir");
}


void crearCliente()
{
	//se guardara los clientes en una lista enlazada simple
    Cliente *nuevo = malloc(sizeof(Cliente)); //se crea un nuevo nodo
    nuevo->sig_cli = NULL;

    printf("Ingrese los datos del cliente\n");
	printf("Cedula: ");
	scanf(" %14[^\n]s ", nuevo->cedula);
	
	printf("Nombres: ");
	scanf(" %49[^\n]s", nuevo->nombres);
	
	printf("Apellidos: ");
	scanf(" %49[^\n]s", nuevo->apellidos);

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
	
	Solicitud *aux = cima_sol;
	int contador=1;
	
	if(aux==NULL){
		printf("No hay solicitudes registradas\n");
        return;		
	}
	
	printf("\nLista de Solicitud\n");
    while (aux != NULL) //recorre la lista desde el primero hasta el ultimo
    {
        printf("%d. Cedula: %s | Servicio: %s | Tecnico: %s\n | Descripcion: %s |", contador, aux->cedula, 
		aux->servicio, aux->tecnico, aux->descripcion);
    	aux = aux->sig_sol;
        contador++;
    }
	
	
}


void liberarMemoria_cli()
{
    Cliente *actual; //para moverse a traves de la lista

    actual = primer_cli;
    Cliente *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->sig_cli; //guardar el siguiente nodo para no perder la lista
        free(actual); 
        actual = siguiente;
    }

    primer_cli = NULL; //asegurarse que no apunten a nada
    fin_cli = NULL;
}

void liberarMemoria_sol()
{
    Solicitud *actual; //para moverse a traves de la lista

    actual = cima_sol;
    Solicitud *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->sig_sol; //guardar el siguiente nodo para no perder la lista
        free(actual); //liberar
        actual = siguiente;
    }
    cima_sol = NULL; 
}

void liberarMemoria(){
    liberarMemoria_cli();
    liberarMemoria_sol();
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
        printf("4. Mostrar Clientes\n");
        printf("5. Mostrar Solicitudes\n");
        printf("6. Mostrar nada\n");
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
			//	crearSolicitud();
				break;
            case 4:
				imprimirClientes();
				break;
            case 5:
				imprimirSolicitudes();
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
