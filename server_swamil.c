#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<pthread.h>

void *server_thread(void *arg) {
    int client_sockfd;
    char instr[80], name[80];
    int count = 0;
    
    client_sockfd = (intptr_t)arg; // Correct the type casting
    count = read(client_sockfd, instr, sizeof(instr)); // Read data from client
    if (count > 0) {
        instr[count] = '\0'; 
        printf("Input from client: %s\n", instr);

        // Process the received message
        strcpy(name, "Thank you, ");
        strcat(name, instr);
        strcpy(instr, name);

        write(client_sockfd, instr, strlen(instr) + 1); // Send response to client
    } else {
        printf("Error reading from client\n");
    }
    
    close(client_sockfd); // Close client socket
    pthread_exit(NULL); // Terminate the thread
}

int main() {
    int server_sockfd, client_sockfd;
    int server_len, client_len;
    struct sockaddr_in server_address, client_address;
    pthread_t t;
    
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create socket
    if (server_sockfd < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(9129); 
    
    server_len = sizeof(server_address);
    if (bind(server_sockfd, (struct sockaddr*)&server_address, server_len) == -1) {
        perror("Error in binding");
        exit(1);
    }

    printf("Server waiting for connection...\n");

    listen(server_sockfd, 5); // Start listening for clients
    
    while (1) {
        client_len = sizeof(client_address);
        client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len); // Accept client connection
        if (client_sockfd < 0) {
            perror("Error accepting client");
            continue;
        }

        printf("Created new client thread\n");

        // Create a new thread to handle client communication
        pthread_create(&t, NULL, server_thread, (void*)(intptr_t)client_sockfd);
    }
    
    close(server_sockfd); // Close server socket
    return 0;
}

