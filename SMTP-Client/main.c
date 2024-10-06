#include "smtp.h"
#include <stdio.h>

int main() {
    SmtpClient *client = createSmtpClient();

    if (!client) {
        fprintf(stderr, "Failed to create SMTP client\n");
        return 1;
    }

    connectAndSendEmail(client);

    destroySmtpClient(&client);

    return 0;
}