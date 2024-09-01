#ifndef CRYPTO_H
#define CRYPTO_H

#include <qobject.h>
class Crypto
{
public:
    Crypto();
    QString encrypt(QString key, QString data);
    QString decrypt(QString key, QString data);
};

#endif // CRYPTO_H
