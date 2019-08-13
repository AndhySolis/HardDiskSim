#include "disk.h"

Disk::Disk(QString Path,int Size, char Unit, int Fit){
    this->Path=Path;
    this->Size=Size;
    this->Unit=Unit;
    this->Fit=Fit;
}
