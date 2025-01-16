#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

int main() {
    int sockfd; //socket descriptor
    int len;
    struct sockaddr_in address; // struct for server address
    int result, count;
    char str[80], instr[80];
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // Create socket
    if (sockfd < 0) {
        perror("Error in socket creation");
        exit(1);
    }

    address.sin_family = AF_INET;
    address.sin_port = htons(9129);  // Correctly set port
    address.sin_addr.s_addr = inet_addr("127.0.0.1"); // Set IP address
    
    len = sizeof(address);
    
    result = connect(sockfd, (struct sockaddr*)&address, len); // Connect to server
    if (result == -1) {
        perror("Error connecting to server");
        exit(1);
    }
    
    fflush(stdout);
    printf("\nEnter string: ");
    fgets(instr, sizeof(instr), stdin); // Take input from user

    write(sockfd, instr, strlen(instr) + 1); // Send data to server
    
    count = read(sockfd, str, sizeof(str)); // Receive data from server
    if (count > 0) {
        printf("Received data from server: %s\n", str);
    } else {
        printf("Error in reading from server\n");
    }

    close(sockfd); // Close the socket
    exit(0);
}

