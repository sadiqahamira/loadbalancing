#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#define MAX_LISTEN_BACKLOG 1
#define BUFFER_SIZE 4096
void handle_client_connection(int client_socket_fd, 
                              char *backend_host, 
                              char *backend_port_str)
{
	   struct addrinfo hints;
    struct addrinfo *addrs;
    struct addrinfo *addrs_iter;
    int getaddrinfo_error;

    int backend_socket_fd;

    char buffer[BUFFER_SIZE];
    int bytes_read;
	 struct addrinfo hints;
	  memset(&hints, 0, sizeof(struct addrinfo));
	   hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
	getaddrinfo_error = getaddrinfo(backend_host, backend_port_str, &hints, &addrs);
    if (getaddrinfo_error != 0) {
        fprintf(stderr, "Couldn't find backend: %s\n", gai_strerror(getaddrinfo_error));
        exit(1);
    }
	 for (addrs_iter = addrs; 
         addrs_iter != NULL; 
         addrs_iter = addrs_iter->ai_next) 
    {
		  backend_socket_fd = socket(addrs_iter->ai_family, 
                                   addrs_iter->ai_socktype,
                                   addrs_iter->ai_protocol);
        if (backend_socket_fd == -1) {
            continue;
        }
		  if (connect(backend_socket_fd, 
                    addrs_iter->ai_addr, 
                    addrs_iter->ai_addrlen) != -1) { 
            break;
        }
		    close(backend_socket_fd);
    }
	 for (addrs_iter = addrs; 
         addrs_iter != NULL; 
         addrs_iter = addrs_iter->ai_next) 
    {
		if (connect(backend_socket_fd, 
                    addrs_iter->ai_addr, 
                    addrs_iter->ai_addrlen) != -1) { 
            break;
        }
		    close(backend_socket_fd);
    }
	 if (addrs_iter == NULL) {
        fprintf(stderr, "Couldn't connect to backend");
        exit(1);
    }
	   freeaddrinfo(addrs);
	    bytes_read = read(client_socket_fd, buffer, BUFFER_SIZE);
    write(backend_socket_fd, buffer, bytes_read);
	  while (bytes_read = read(backend_socket_fd, buffer, BUFFER_SIZE)) {
        write(client_socket_fd, buffer, bytes_read);
    }
	    close(client_socket_fd);
}