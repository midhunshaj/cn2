#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1234

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);


    sockfd = socket(AF_INET, SOCK_DGRAM, 0);


    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    while (1) {
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; 


        sendto(sockfd, buffer, strlen(buffer) + 1, 0, (struct sockaddr *)&server_addr, len);

        if (strcmp(buffer, "stop") == 0)
            break;

        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &len);
        printf("Server Time: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}
