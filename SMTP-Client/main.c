#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("Creating socket error");    
        exit(1);
    }

    struct hostent *d_addr = gethostbyname("localhost");
    if (d_addr == NULL){
        perror("Getting host error");
        exit(1);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *((unsigned long *)d_addr->h_addr);
    addr.sin_port = htons(25);

    if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("Connecting error");
        exit(1);
    }

    if (connet(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("Connecting error");
        exit(1);
    }

    char buf[1024];
    recv(sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "HELO smtp.mail.ru\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "MAIL FROM: <test@mail.ru>\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "RCPT TO: <test@mail.ru>\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "DATA\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "From: test@mail.ru\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    strcpy(buf, "To: test@mail.ru\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    strcpy(buf, "Subject: Test\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    strcpy(text, "Hello, world!\r\n");
    send(sock, text, strlen(text), 0);
    printf("Sent: %s\n", text);

    strcpy(buf, "\r\n.\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "QUIT\r\n");
    send(sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    close(sock);

    return 0;
}