#include "mkdisk.h"
MKDISK::MKDISK(int Size, const char *Fit, char Unit, const char *Path){

        Fun = new Functions();
        int Origi=Size;
        FILE *f;
        MBR r;
        f=fopen(Path,"w");
        Size=Fun->Mult(Size,Unit);
        if (!f){
            std::cout<<"No Se Pudo Crear El Disco En La Ubicacion "<<Path<<std::endl;
            return ;
        }else{
            r.mbr_tamano=Size;
            Fun->Fecha(&r.mbr_fecha_creacion);
            r.mbr_disk_signature=Fun->GenerarNumeroRandom();
            Fun->FillPAR(&r.mbr_partition[0]);
            Fun->FillPAR(&r.mbr_partition[1]);
            Fun->FillPAR(&r.mbr_partition[2]);
            Fun->FillPAR(&r.mbr_partition[3]);
            r.disk_fit[0]=char(tolower(Fit[0]));
            r.disk_fit[1]=char(tolower(Fit[1]));
            fwrite(&r,sizeof(MBR),1,f);
            fclose(f);
            Fun->FillDisk(sizeof(MBR),Size-int(sizeof(MBR)),'\0',Path);
        }
        if(Fun->ExisteArchivo(Path)){
            std::cout<<"Se Creo Creo Disco Duro Tamanio:"<<Origi<<Unit<<" En:"<<Path<<std::endl;
        }

}



