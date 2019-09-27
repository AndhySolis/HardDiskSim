#ifndef STRUCTSEXT_H
#define STRUCTSEXT_H
#include <time.h>
struct  Inodo{

};
typedef struct  SuperBloque{
    int s_filesystem_type;
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    struct tm s_mtime;
    struct tm s_umtime;
    int s_mnt_count;
    int s_magic;
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
}SPB;
typedef struct  TablaInodo{
    int i_uid;
    int i_gid;
    int i_size;
    struct tm i_atime;
    struct tm i_ctime;
    struct tm  i_mtime;
    int i_block[16];
    char i_type;
    int i_perm;
   // int Vac;
}INO;
typedef  struct Contennt{
    char b_name[12];
    int b_inodo;
}CON;
typedef struct  BloqueCarpetas{
    CON content[4];
}BCA;

typedef struct  BloqueArchivos{
    char b_content[64];
}BAR;

typedef struct  Journaling{
    int b_pointers[50];
}JOR;
typedef struct  BloqueApuntadores{
    int b_pointers[16];
}BAP;
#endif // STRUCTSEXT_H
