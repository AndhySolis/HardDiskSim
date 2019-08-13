#ifndef EXTENDEDBOOTRECORD_H
#define EXTENDEDBOOTRECORD_H


class ExtendedBootRecord
{
public:
    ExtendedBootRecord();
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];
private:

};

#endif // EXTENDEDBOOTRECORD_H
