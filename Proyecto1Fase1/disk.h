#ifndef DISK_H
#define DISK_H
#include<QDebug>
#include <iostream>


class Disk
{
public:
    Disk(QString Path,int Size, char Unit, int Fit);

private:
    int Size;
    char Unit;
    QString Path;

    int Fit;
};

#endif // DISK_H
