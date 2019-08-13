#ifndef MASTERBOOTRECORD_H
#define MASTERBOOTRECORD_H
#include "partition.h"

class MasterBootRecord
{
public:
    MasterBootRecord();
    int mbr_tamano;
    char mbr_fecha_creacion[30];
    int mbr_disk_signature;
    char disk_fit;
    Partition *mbr_partition_1;
    Partition *mbr_partition_2;
    Partition *mbr_partition_3;
    Partition *mbr_partition_4;
};

#endif // MASTERBOOTRECORD_H
