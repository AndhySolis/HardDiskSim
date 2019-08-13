#ifndef STRUCTS_H
#define STRUCTS_H
#include <time.h>
typedef struct  Avaliable{
    int Begin;
    int End;
    int Size;
}AVA;
typedef struct  ExtendedBootRecord {
    char part_status;
    char part_fit[2];
    int part_start;
    int part_size=0;
    int part_next=-1;
    char part_name[16];
}EBR ;

typedef struct Partition{
    char part_status='f';
    char part_type;
    char part_fit[2];
    int part_start;
    int part_size;
    char part_name[16];
}PAR ;
typedef struct MasterBootRecord{
    int mbr_tamano;
    struct tm  mbr_fecha_creacion;
    int mbr_disk_signature;
    char disk_fit[2];
    PAR mbr_partition[4];
}MBR ;
class STRUCTS
{
public:
    STRUCTS();
};

#endif // STRUCTS_H
