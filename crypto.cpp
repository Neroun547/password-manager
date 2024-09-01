#include "crypto.h"
#include <QByteArray>

Crypto::Crypto() {}

QString Crypto::encrypt(QString key, QString data) {
    QByteArray dataBytesArr = QByteArray();
    QByteArray keyBytesArr = QByteArray();

    for(int i = 0; i < data.length(); i++) {
        dataBytesArr.append(static_cast<char>(data.at(i).toLatin1()));
    }
    for(int i = 0; i < key.length(); i++) {
        keyBytesArr.append(static_cast<char>(key.at(i).toLatin1()));
    }
    QString result = "";

    for(int i = 0; i < dataBytesArr.length(); i++) {
        result += static_cast<char>(dataBytesArr[i] ^ keyBytesArr[i % keyBytesArr.length()]);
    }
    return result;
}

QString Crypto::decrypt(QString key, QString data) {
    return this -> encrypt(key, data);
}
