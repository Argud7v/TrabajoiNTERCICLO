//Trabajo Interciclo
//MAteo Guillen, Franklin Tuapante


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//funciones
void bailecito();
void crearCliente();
void crearSolicitud(int version);
void imprimirClientes();
void imprimirSolicitudes();
void push_dinamico(char cedula_enc[15]);
void push_version2(char cedula_enc[15]);

void liberarMemoria_cli();
void liberarMemoria_sol();
void liberarMemoria();


// datos de una solicitud
typedef struct Solicitud {
    char cedula[15];
    char servicio[50];
    char tecnico[50];
    char descripcion[100];
    struct Solicitud *sig_sol;              
} Solicitud;

 Solicitud *cima_sol=NULL; // tope de la pila de solicitudes

//prototipos que usan Solicitud (van despues del struct)
void push2(Solicitud **tope, Solicitud *nuevo);
Solicitud *pop2(Solicitud **tope);

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
    Cliente *nuevo = (Cliente *)malloc(sizeof(Cliente)); //se crea un nuevo nodo
    nuevo->sig_cli = NULL;

    printf("Ingrese los datos del cliente\n");
	printf("Cedula: ");
	scanf(" %14[^\n]", nuevo->cedula);
	
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

void crearSolicitud(int version){
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
        actual = actual->sig_cli;
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
    else //version 2: push con nodo ya creado
        push_version2(actual->cedula);
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
        printf("%d. Cedula: %s | Servicio: %s | Tecnico: %s | Descripcion: %s\n", contador, aux->cedula,
		aux->servicio, aux->tecnico, aux->descripcion);
    	aux = aux->sig_sol;
        contador++;
    }
	
	
}

//push: version 1

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
        nuevo->sig_sol = NULL;
        cima_sol = nuevo;
    }
    else // Si ya hay elementos en la pila
    {
        nuevo->sig_sol = cima_sol;
        cima_sol = nuevo;
    }

    printf("\n-------------------------\nIngresado con exito.\n-------------------------\n");
}


// push version 2: recibe un nodo ya creado
// se usa doble puntero para poder cambiar la cima desde la funcion
void push2(Solicitud **tope, Solicitud *nuevo) {
    nuevo->sig_sol = *tope; //el nuevo apunta a la cima actual
    *tope = nuevo;          //el nuevo pasa a ser la cima
}

// pop version 2: saca el nodo de la cima y lo devuelve
Solicitud *pop2(Solicitud **tope) {
    if (*tope == NULL) //pila vacia, no hay nada que sacar
        return NULL;

    Solicitud *aux = *tope;
    *tope = (*tope)->sig_sol; //la cima baja al siguiente
    aux->sig_sol = NULL;      //el nodo sale desconectado de la pila
    return aux;
}

// crea el nodo de la solicitud y lo pasa a push2
void push_version2(char cedula_enc[15])
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
        printf("6. Salir\n");
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
				crearSolicitud(version);
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

    liberarMemoria(); //liberar clientes y solicitudes al salir
    return 0;
}