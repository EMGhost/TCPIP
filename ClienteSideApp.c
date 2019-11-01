#include <stdio.h>
#include <sys/socket.h> 
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h> 
#include <netinet/in.h> 
#include <arpa/inet.h>
#include <ctype.h>


int main(int argc, char const *argv[]){

    int origin_socket, err,i, start, end;
    int serverIPAddress[4] = {};
    char hostname[100];
    struct sockaddr_in sa = {0};
    struct hostent *host;
    start =1100; //Puerto de incio del escaneo
    end=1200;   //Puerto de fin del escaneo
/*
    //Ingreso la IP con verficacion que no se ingresen numeros invalidos
    do{
        printf("\n----------------------------Ingrese la direccion IP del Servidor----------------------------\n ");
        scanf("%d%*c%d%*c%d%*c%d%*c",&serverIPAddress[0],&serverIPAddress[1],&serverIPAddress[2],&serverIPAddress[3]);
    }while (serverIPAddress[0]<0 || serverIPAddress[0]>255 || serverIPAddress[1]<0 || serverIPAddress[1]>255 || serverIPAddress[2]<0 || serverIPAddress[2]>255 || serverIPAddress[3]<0 || serverIPAddress[3]>255);
    printf("La direccion IP ingresada es %d.%d.%d.%d\n",serverIPAddress[0],serverIPAddress[1],serverIPAddress[2],serverIPAddress[3]);
    
    for(i=0; i<=3; i=i+1){
        itoa(serverIPAddress[i],hostname,10);
        printf("%c", hostname[i]);
    }
*/
    printf("Ingrese la direccion IP: ");
    gets(hostname);

   //strncpy((char*)(struct sockaddr*) &sa , "" , sizeof sa);
   //memccpy(&sa.sin_addr, hostname, sizeof(hostname));
   
    

    printf("\nEmpezando el escaneo de puertos: \n");
    for( i = start ; i <= end ; i++) 
    {
        //Creamos el Socket para IPv4 del tipo Stream
        origin_socket = socket(AF_INET , SOCK_STREAM , 0);

        //Chequeo que el usuario haya ingresado una direccion IP y la asigno en la estructura
        if(isdigit(hostname[0])){
            sa.sin_addr.s_addr = inet_addr(hostname);
        }
        //En la estructura asigno IPv4
        sa.sin_family = AF_INET;
        //Selecciono el puerto a verificar
        sa.sin_port = htons(i);
        printf("\nComprobando puerto %d\n", i);
        //Establezo la conexion con el Socket
        err = connect(origin_socket ,(struct sockaddr *) &sa , sizeof (sa));
        //Si la conexion fue exitosa muestro que puerto esta abierto, al encontrar un puerto abierto finalizo el escaneo
        if(err != -1){
            char host[128];
            char service[128];
            getnameinfo((struct sockaddr *)&sa, sizeof sa, host, (sizeof host), service, sizeof service, 0);
            printf("\nPort : %d, Service : %s, Open\n", i, service);
            exit(1); 
        }
        close(origin_socket);
        


        /*
        //Check whether socket created fine or nots
        if(origin_socket < 0) 
        {
            printf("\nError en puerto %d",i);
        }
        //Connect using that socket and sockaddr structure
    
        
        //not connected
        if( err < 0 )
        {
            printf("Error al conectar");
            printf("%s %-5d %s\r" , hostname , i, strerror(errno));
            close(origin_socket);
        }
        //connected
        else
        {
            printf("%-5d open\n",i);
        }
        */
        //close(origin_socket);
    }
   
    return 0;
}


