#ifndef CRYPT_H
#define CRYPT_H

#include <QString>
using std::array;

class Crypt
{
public:
    Crypt(QString text): initText(text) {}
    QString atbash();
    QString caesar(int, bool);
    QString playfair(QString, bool);
    QString vigenere(QString, bool);
    static array<int, 2> findIndex(array<array<QChar, 5>, 5>&, QChar&);
private:
    QString initText;
    const QString alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

};

#endif // CRYPT_H
