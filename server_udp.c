#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

#define PORT 1234

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[1024];
    socklen_t len = sizeof(client_addr);
    time_t current_time;
    struct tm *local_time;


    sockfd = socket(AF_INET, SOCK_DGRAM, 0);


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("UDP Server waiting...\n");


    while (1) {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &len);
        printf("Client: %s\n", buffer);

        if (strcmp(buffer, "stop") == 0)
            break;


        current_time = time(NULL);
        local_time = localtime(&current_time);
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", local_time);

        sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr *)&client_addr, len);
    }

    close(sockfd);
    return 0;
}
