//Trabajo Interciclo
//MAteo Guillen, Franklin Tuapante


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
//funciones
void crearCliente();
void registrar(); 
//void retirar(); */





// datos de una solicitud
struct Solicitud {
    char cedula[15];
    char servicio[50];
    char tecnico[50];
    char descripcion[100];
};


// nodo de la lista de clientes
struct Cliente {
    char cedula[15];
    char nombres[50];
    char apellidos[50];
    Nodo *pila;   // tope de la pila de solicitudes
    Cliente *sig;
};


//Clientes
// crea un cliente y lo pone al inicio de la lista


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
        printf("0. Salir\n");
        printf("Opcion: ");
        scanf("%d", &op);

        switch (op) {
            case 1: 
			//	crearCliente(); 
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
            default: 
			printf("Opcion no valida\n");
			 
        }
    } while (op != 4);

    return 0;
}
