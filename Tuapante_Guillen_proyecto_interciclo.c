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


//funciones
//uso general
int menu();
void liberarMemoria_cli(); //libera la lista enlazada de los clientes
void liberarMemoria_sol(); //libera la pila de solicitudes
void liberarMemoria(); //llama a las dos funciones anteriores para liberar la memoria por completo
void imprimirClientes(); //muestra los clientes en pantalla
void imprimirSolicitudes(); //muestra las solicitudes en pantalla

//manejo de datos
void crearCliente(); //toma los datos del cliente y los agrega a un lista sin orden
void crearSolicitud(int version); //crea la solicitud si existe el cliente
void push_dinamico(char cedula_enc[15]);
void eliminarSolicitud(int version);//borra la solicitud si existe el cliente
void pop_dinamico();

//versiones estaticas de push y pop
void push2(Solicitud **tope, Solicitud *nuevo);
void push_estatico(char cedula_enc[15]);
Solicitud *pop2(Solicitud **tope);
Solicitud *pop_estatico(Solicitud **tope);


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
                imprimirSolicitudes();
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

void imprimirSolicitudes()
{
	Solicitud *aux = cima_sol;
	int contador=1;
	
	if(aux==NULL){
		printf("No hay solicitudes registradas\n");
        return;		
	}
	
	printf("\n-------------------------\nLista de Solicitud\n-------------------------\n");
    while (aux != NULL) //recorre la lista desde el primero hasta el ultimo
    {
        printf("%d. Cedula: %s\nServicio: %s\necnico: %s\nDescripcion: %s\n-------------------------\n", contador, aux->cedula, 
		aux->servicio, aux->tecnico, aux->descripcion);
    	aux = aux->sol_sig;
        contador++;
    }
}

void eliminarSolicitud(int version)
{
    //por si la pila esta vacia
    if (primer_cli == NULL)
    {
        printf("\n--------------La lista de clientes esta vacia.\n--------------\n");
    }

    if (version == 1) //version memoria dinamica
    {
        pop_dinamico();
        printf("\n--------------\nPrimera solicitud de la pila eliminada exitosamente.\n--------------\n");
    }
    else //version estatica
    {
        pop_estatico(cima_sol);
        printf("\n--------------\nPrimera solicitud de la pila eliminada exitosamente.\n--------------\n");
    }
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
}

// push version 2: recibe un nodo ya creado
// se usa doble puntero para poder cambiar la cima desde la funcion
void push2(Solicitud **tope, Solicitud *nuevo)
{
    nuevo->sol_sig= *tope; //el nuevo apunta a la cima actual
    *tope = nuevo;          //el nuevo pasa a ser la cima
}

void push_estatico(char cedula_enc[15])
{
    Solicitud *nuevo = (Solicitud *)malloc(sizeof(Solicitud));

    if (nuevo == NULL)
    {
        printf("No hay memoria suficiente.\n");
        return;
    }

    strcpy(nuevo->cedula, cedula_enc);
    printf("Ingrese el servicio que necesita: ");
    scanf(" %49[^\n]", nuevo->servicio);
    printf("Ingrese el nombre del tecnico: ");
    scanf(" %49[^\n]", nuevo->tecnico);
    printf("Ingrese una descripcion del problema: ");
    scanf(" %99[^\n]", nuevo->descripcion);

    push2(&cima_sol, nuevo);

    printf("\n-------------------------\nIngresado con exito.\n-------------------------\n");
}

// pop version 2: saca el nodo de la cima y lo devuelve
Solicitud *pop2(Solicitud **tope)
{
    if (*tope == NULL) //pila vacia, no hay nada que sacar
        return NULL;

    Solicitud *aux = *tope;
    *tope = (*tope)->sol_sig; //la cima baja al siguiente
    aux->sol_sig = NULL;      //el nodo sale desconectado de la pila
    return aux;
}

// crea el nodo de la solicitud y lo pasa a push2
Solicitud *pop_estatico(Solicitud **tope)
{
    if (*tope == NULL) //pila vacia, no hay nada que sacar
        return NULL;

    Solicitud *aux = *tope;
    *tope = (*tope)->sol_sig; //la cima baja al siguiente
    aux->sol_sig = NULL;      //el nodo sale desconectado de la pila
    return aux;
}

void bailecito()
{
	printf("Elija un balicecito\n");
	printf("Baile 1: Campanas de Belen\n");
	printf("Baile 2: Por definir");
}
