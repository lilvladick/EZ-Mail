#ifndef SMPT_H
#define SMPT_H

typedef struct SmtpClient SmtpClient;

SmtpClient* createSmtpClient();
void destroySmtpClient(SmtpClient** client);
void connectAndSendEmail(SmtpClient* client);

#endif 