//Trabajo Interciclo
//MAteo Guillen, Franklin Tuapante


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//funciones
void bailecito();
void crearCliente();
//void registrar(); 
//void retirar(); 





// datos de una solicitud
typedef struct Solicitud {
    char cedula[15];
    char servicio[50];
    char tecnico[50];
    char descripcion[100];
    struct Solicitud *sig;              
} Solicitud;

 Solicitud *cima_sol=NULL; // tope de la pila de solicitudes

// nodo de la lista de clientes
typedef struct Cliente {
    char cedula[15];
    char nombres[50];
    char apellidos[50];
    struct Cliente;
}Cliente;

 Cliente *cima_cli=NUll;
 Cliente *fin_cli=NULL;
 
void bailecito(){
	
	printf("Eliga un balicecito");
	printf("Baile 1: Campanas de Belen");
	printf("Baile 2: Por definir");
}


void crearCliente(){
	
	Cliente *nuevo = (Cliente*)malloc(sizeof(Clie<));
	
	printf("Ingrese los datos del cliente");
	printf("Cedula: ")
	scanf("%s", nuevo->cedula);
	
	printf("Nombres: ");
	scanf("%s", nuevo->nombres);
	
	printf("Apellidos: ");
	scanf("%s", nuevo->apellidos);
	

	 
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
        printf("1. Crear cliente\n");
        printf("2. Registrar solicitud\n");
        printf("3. Retirar solicitud\n");
        printf("4. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1: 
			 
				break;
            case 2: 
			//	registrar(); 
				break;
            case 3: 
			//	retirar(); 
				break;
            case 4: 
				printf("Salir\n"); 
				break;
				
			case 5: 
            default: 
			printf("Opcion no valida\n");
			 
        }
    } while (op != 4);

    return 0;
}
