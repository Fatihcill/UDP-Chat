#include "PackageManager.hpp"

// test package manager
int main()
{
    QByteArray Buffer;
    std::vector<INT32> data = {3680, 50, -680};

    PackageManager::int32_Paketle(&Buffer, data[0]);
    PackageManager::int32_Paketle(&Buffer, data[1]);
    PackageManager::int32_Paketle(&Buffer, data[2]);

    qDebug() << Buffer.toHex();

    return 0;
}