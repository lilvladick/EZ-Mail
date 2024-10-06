#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "smtp.h"

struct SmtpClient {
    int sock;
};

SmtpClient* createSmtpClient() {
    SmtpClient* client = malloc(sizeof(SmtpClient));
    if (!client) {
        perror("Allocation failed");
        return NULL;
    }

    client->sock = socket(AF_INET, SOCK_STREAM, 0);
    if (client->sock < 0) {
        perror("Creating socket error");
        free(client);
        return NULL;
    }

    return client;
}

void destroySmtpClient(SmtpClient** client) {
    if (*client) {
        close((*client)->sock);
        free(*client);
        *client = NULL;
    }
}

void connectAndSendEmail(SmtpClient* client) {
    struct hostent *d_addr = gethostbyname("localhost");
    if (d_addr == NULL) {
        perror("Getting host error");
        return;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = *((unsigned long *)d_addr->h_addr);
    addr.sin_port = htons(25);

    if (connect(client->sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Connecting error");
        return;
    }

    char buf[1024];
    recv(client->sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "HELO localhost\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(client->sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "MAIL FROM: <sender@example.com>\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(client->sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "RCPT TO: <receiver@example.com>\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(client->sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "DATA\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(client->sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "From: sender@example.com\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    strcpy(buf, "To: receiver@example.com\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    strcpy(buf, "Subject: Test\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    const char* messageText = "Hello, world!";
    send(client->sock, messageText, strlen(messageText), 0);
    printf("Sent: %s\n", messageText);

    strcpy(buf, "\r\n.\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);

    recv(client->sock, buf, sizeof(buf), 0);
    printf("Received: %s\n", buf);

    strcpy(buf, "QUIT\r\n");
    send(client->sock, buf, strlen(buf), 0);
    printf("Sent: %s\n", buf);
}