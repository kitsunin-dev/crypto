#ifndef ENCRYPT_H
#define ENCRYPT_H

#include <QString>

class Encrypt
{
public:
    Encrypt(QString text): initText(text) {}
    QString atbash();
    QString caesar(int shift);
    QString playfair(QString key);
    QString vigenere(QString key);
private:
    QString initText;
    const QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

};

#endif // ENCRYPT_H
