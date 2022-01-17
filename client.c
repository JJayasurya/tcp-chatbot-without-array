#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main()
{ 
 	char *ip="127.0.0.1";
 	int port=5619;

	int socket_desc;
	struct sockaddr_in server_addr;
	char *server_message;
	char *client_message;
  
  
 
	// create TCP socket
	socket_desc=socket(AF_INET, SOCK_STREAM, 0);
	if (socket_desc<0)
	{ 
		perror("[-]unable to establish a socket \a");
		exit(1);
 	}
  	printf("\n[+] TCP socket connection created \a");

  	// assigning port and ip;
  	server_addr.sin_family = AF_INET;
  	server_addr.sin_port = htons(port);
  	server_addr.sin_addr.s_addr = inet_addr(ip);
  
  	// Send connection request to server:
    	if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    	{
     		perror("[-]unable to establish a connection \a");
     		exit(1);
    	}
    	printf("\n[+]Connected with server successfully \a\n");
	printf("\n[------]type exit to quit the program \a\n");

         int size=100;
         server_message=(char*)calloc(size, sizeof(char));
         client_message=(char*)calloc(size, sizeof(char));
   
  	while(1)
  	{
       
         memset(server_message,'\0',size);
  	 memset(client_message,'\0',size);

  		//sending message to server
  		printf("\n[+]client_message:   \a");
                fgets(client_message, size, stdin);
  		if(send(socket_desc, client_message, strlen(client_message), 0) < 0)
  		{
   			perror("[-] unable to send message to server \a");
   			exit(1);
 		}

  		if(strcmp(client_message, "exit\n") == 0)
          	{
	     		goto label;
		}

  

  		//reciving messages form server
  		if(recv(socket_desc,server_message,100,0)<0)
  		{
   			perror("[-] unable to recive a message from server \a");
   			exit(1);
  		}
  		printf("\n[+]server_message:  \a%s",server_message);   // if server disconnect , client also disconnected
                if(strcmp(server_message, "exit\n") == 0)
          	{
	     		goto label;
		}
  
 	}      //end of while loop

	//closing client and socket connection
	label:
	{
        // clean buffer 
        free(server_message);
        free(client_message);  
	close(socket_desc);
	perror("[-] disconnected from server \a");
	} 
  	return 0;
}
