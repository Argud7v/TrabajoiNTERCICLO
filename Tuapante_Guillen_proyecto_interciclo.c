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
    struct Solicitud *sol_sig;              
} Solicitud;

// nodo de la lista de clientes, linsta enlazada simple
typedef struct Cliente {
    char cedula[15];
    char nombres[50];
    char apellidos[50];
    struct Cliente *cli_sig;
} Cliente;

Solicitud *cima_sol = NULL;   // tope de la pila de solicitudes

Cliente *primer_cli = NULL; //primer y ultimo de la lista enlazada
Cliente *fin_cli = NULL;

#define MAX_SOLICITUDES 100

Solicitud pila_estatica[MAX_SOLICITUDES];
int tope_estatico = -1; // -1 indica que la pila esta vacia

//funciones
//uso general
int menu();
void liberarMemoria_cli(); //libera la lista enlazada de los clientes
void liberarMemoria_sol(); //libera la pila de solicitudes
void liberarMemoria(); //llama a las dos funciones anteriores para liberar la memoria por completo
void imprimirClientes(); //muestra los clientes en pantalla
void imprimirSolicitudes(int version); //muestra las solicitudes en pantalla

//manejo de datos
void crearCliente(); //toma los datos del cliente y los agrega a un lista sin orden
void crearSolicitud(int version); //crea la solicitud si existe el cliente
void push_dinamico(char cedula_enc[15]);
void eliminarSolicitud(int version);//borra la solicitud si existe el cliente
void pop_dinamico();

//versiones estaticas de push y pop
void push_estatico(char cedula_enc[15]);
void pop_estatico();


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
                crearCliente();
				break;
            case 2: //registrar solicitud (push, ambas versiones)
                crearSolicitud(version);
				break;
            case 3: //retirar solicitud (pop, ambas versiones)
                eliminarSolicitud(version);
				break;
            case 4: //mostar clientes
                imprimirClientes();
                break;
            case 5: //mostrar solicitudes
                imprimirSolicitudes(version);
                break;
            case 6: //salir
				printf("Saliendo del programa.\n"); 
				break;
            default: 
			printf("Opcion no valida\n");
			 
        }
    } while (op != 6);

    liberarMemoria();

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

void crearCliente()
{
    //se guardara los clientes en una lista enlazada simple
    Cliente *nuevo = malloc(sizeof(Cliente)); //se crea un nuevo nodo
    nuevo->cli_sig = NULL;

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
    fin_cli->cli_sig = nuevo;
    fin_cli = nuevo;
}

void liberarMemoria_cli()
{
    Cliente *actual; //para moverse a traves de la lista

    actual = primer_cli;
    Cliente *siguiente;

    while (actual != NULL)
    {
        siguiente = actual->cli_sig; //guardar el siguiente nodo para no perder la lista
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
        siguiente = actual->sol_sig; //guardar el siguiente nodo para no perder la lista
        free(actual); //liberar
        actual = siguiente;
    }
    cima_sol = NULL; 
}

void liberarMemoria()
{
    liberarMemoria_cli();
    liberarMemoria_sol();
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

    printf("\nLista de Clientes\n----------------------------------------\n");
    while (baile != NULL) //recorre la lista desde el primero hasta el ultimo
    {
        printf("%d. Cedula: %s | Nombres: %s | Apellidos: %s\n", contador, baile->cedula, baile->nombres, 
		baile->apellidos);
    	baile = baile->cli_sig;
        contador++;
    }
}

void crearSolicitud(int version)
{
    char ced_buscar[15];

    printf("Ingrese la cedula del cliente que desea crear una solicitud: ");
    scanf("%14s", ced_buscar);

    //por si la pila esta vacia
    if (primer_cli == NULL)
    {
        printf("\n--------------La lista de clientes esta vacia.\n--------------\n");
        return;
    }

    Cliente *actual = primer_cli;

    while (actual != NULL && strcmp(ced_buscar, actual->cedula) != 0)
    {
        actual = actual->cli_sig;
    }

    if (actual == NULL)
    {
        printf("\n-------------------------\nLa cedula no esta reegistrada como cliente. Por favor registrarse.\n-------------------------\n");
        return;
    }

    printf("\n-------------------------\nCliente encontrado:\n");
     printf("Cedula: %s | Nombres: %s | Apellidos: %s\n--------------------------\n", actual->cedula, actual->nombres, 
		actual->apellidos);
    
    if (version == 1) //version memoria dinamica
        push_dinamico(actual->cedula);
    else //version estatica
        push_estatico(actual->cedula);
}

void push_dinamico(char cedula_enc[15])
{
    Solicitud *nuevo = (Solicitud *)malloc(sizeof(Solicitud));

    //medida de seguridad
    if (nuevo == NULL)
    {
        printf("No hay memoria suficiente.\n");
        return;
    }

    //Ingreso de datos
    strcpy(nuevo->cedula, cedula_enc); //si la cedula existe se copia como esta
    printf("Ingrese el servicio que necesita: ");
    scanf(" %49[^\n]", nuevo->servicio);
    printf("Ingrese el nombre del tecnico: ");
    scanf(" %49[^\n]", nuevo->tecnico);
    
    printf("Ingrese una descripcion del problema: ");
    scanf(" %99[^\n]", nuevo->descripcion); 

    if (cima_sol == NULL) // Si la pila esta vacia
    {
        nuevo->sol_sig = NULL;
        cima_sol = nuevo;
    }
    else // Si ya hay elementos en la pila
    {
        nuevo->sol_sig = cima_sol;
        cima_sol = nuevo;
    }

    printf("\n-------------------------\nIngresado con exito.\n-------------------------\n");
}

void imprimirSolicitudes(int version)
{
    if (version == 1) {
        Solicitud *aux = cima_sol;
        int contador = 1;
        
        if (aux == NULL) {
            printf("No hay solicitudes registradas en la pila dinamica.\n");
            return;     
        }
        
        printf("\n-------------------------\nLista de Solicitudes\n-------------------------\n");
        while (aux != NULL) {
            printf("%d. Cedula: %s\nServicio: %s\nTecnico: %s\nDescripcion: %s\n-------------------------\n", 
                   contador, aux->cedula, aux->servicio, aux->tecnico, aux->descripcion);
            aux = aux->sol_sig;
            contador++;
        }
    } else {
        if (tope_estatico == -1) {
            printf("No hay solicitudes registradas en la pila estatica.\n");
            return;
        }

        printf("\n-------------------------\nLista de Solicitudes\n-------------------------\n");
        for (int i = tope_estatico; i >= 0; i--) {
            printf("%d. Cedula: %s\nServicio: %s\nTecnico: %s\nDescripcion: %s\n-------------------------\n", 
                   tope_estatico - i + 1, pila_estatica[i].cedula, pila_estatica[i].servicio, 
                   pila_estatica[i].tecnico, pila_estatica[i].descripcion);
        }
    }
}

void eliminarSolicitud(int version)
{
    //por si la pila esta vacia
    if (primer_cli == NULL)
    {
        printf("\n--------------La lista de clientes esta vacia.\n--------------\n");
        return;
    }

    if (version == 1) //version memoria dinamica
        pop_dinamico();

    else //version estatica
        pop_estatico();
}

void pop_dinamico()
{
    if (cima_sol == NULL)
    {
        printf("La pila esta vacia.\n");
        return;
    }

    Solicitud *temp = cima_sol;

    //la solicitud borrada se muestra en pantalla antes de borrarse
    cima_sol = cima_sol->sol_sig;
    free(temp);
    printf("\n--------------\nPrimera solicitud de la pila eliminada exitosamente.\n--------------\n");
}

void push_estatico(char cedula_enc[15])
{
    if (tope_estatico >= MAX_SOLICITUDES - 1)
    {
        printf("Error: La pila estatica esta llena (Overflow).\n");
        return;
    }

    tope_estatico++; // Sube a la cima o tope
    
    // Ingresar datos directamente
    strcpy(pila_estatica[tope_estatico].cedula, cedula_enc);
    
    printf("Ingrese el servicio que necesita: ");
    scanf(" %49[^\n]", pila_estatica[tope_estatico].servicio);
    
    printf("Ingrese el nombre del tecnico: ");
    scanf(" %49[^\n]", pila_estatica[tope_estatico].tecnico);
    
    printf("Ingrese una descripcion del problema: ");
    scanf(" %99[^\n]", pila_estatica[tope_estatico].descripcion);

    printf("\n-------------------------\nIngresado con exito en pila estatica.\n-------------------------\n");
}

void pop_estatico() 
{
    if (tope_estatico == -1)
    {
        printf("La pila esta vacia.\n");
        return;
    }
    tope_estatico--; 

    printf("\n--------------\nPrimera solicitud de la pila eliminada exitosamente.\n--------------\n");
}

/*void bailecito()
{
	printf("Elija un bailecito\n");
	printf("Baile 1: Campanas de Belen\n");
	printf("Baile 2: La Macarena\n");
}*/
