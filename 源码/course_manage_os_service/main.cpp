#include <QCoreApplication>
#include <iostream>

#include "networkbase.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    NetWorkBase service;
    return a.exec();
}
