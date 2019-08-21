#include "reports.h"
//PARTREPORT ES SIMILAR A LOS FIT
//No guarda en la ubicacion variable
Reports::Reports()
{

}


std::string Reports::TablaPAR(PAR Parti,int Num){
    std::string  Reporte="";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_status_"+std::to_string(Num)+" </TD><TD> "+Parti.part_status+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_type_"+std::to_string(Num)+" </TD><TD> "+Parti.part_type+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_fit_"+std::to_string(Num)+" </TD><TD> "+Parti.part_fit+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_start_"+std::to_string(Num)+" </TD><TD> "+std::to_string(Parti.part_start)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_size_"+std::to_string(Num)+" </TD><TD> "+std::to_string(Parti.part_size)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_name_"+std::to_string(Num)+" </TD><TD> "+Parti.part_name+"</TD> </TR> \n";
    return Reporte;
}
void Reports::ReporteTablaMBR(const char *Path,const char *Guardar){
    FILE *f;
    MBR Main;
    f=fopen(Path,"r+");
    if (!f){
        return;
    }
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);


    std::string Reporte="";
    Reporte =Reporte+"digraph Gr { \n graph [ratio=fill]; \n graph [bb=\"0,0,352,154\"];"+ "node [label=\"\\N\", fontsize=15, shape=plaintext]; ";
    Reporte =Reporte+"labelloc=\"t\"  \n label="+"MBR "+Path+";";
    Reporte =Reporte+"Conte [label=< <TABLE BORDER=\"1\" ALIGN=\"center\" COLOR=\"#03fc20\">";
    Reporte = Reporte+"\n <TR>  <TD> Nombre </TD><TD> Valor </TD> </TR> \n";
    //Contenido MBR
    Reporte = Reporte+"\n <TR>  <TD> mbr_tamaño </TD><TD>"+ std::to_string(Main.mbr_tamano) +"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> mbr_fecha_creacion </TD><TD>" + std::to_string(Main.mbr_fecha_creacion.tm_hour) + "</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> mbr_disk_signature </TD><TD> " + std::to_string(Main.mbr_disk_signature) + " </TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> Disk_fit </TD><TD> " + Main.disk_fit + "r </TD> </TR> \n";
    for (int i=0;i<4;i++) {
        PAR Parti =Main.mbr_partition[i];
        if(Parti.part_status=='t'){
            Reporte = Reporte+this->TablaPAR(Parti,i);
        }
    }
    Reporte = Reporte+"\n </TABLE> \n >]; \n}";
    char Cop[1+Reporte.size()];
    strcpy(Cop,Reporte.c_str());
    f=fopen("G.dot","w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }
    const char *command = "dot -Tpng G.dot -o Tabla.png";
    system(command);

}


std::string Reports::TablaEBR(EBR Extendida){
    std::string  Reporte="";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_status_"+std::to_string(0)+" </TD><TD> "+Extendida.part_status+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_fit_"+std::to_string(0)+" </TD><TD> "+Extendida.part_fit+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_start_"+std::to_string(0)+" </TD><TD> "+std::to_string(Extendida.part_start)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_size_"+std::to_string(0)+" </TD><TD> "+std::to_string(Extendida.part_size)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_name_"+std::to_string(0)+" </TD><TD> "+std::to_string(Extendida.part_next)+"</TD> </TR> \n";
    Reporte = Reporte+"\n <TR>  <TD> "+"par_name_"+std::to_string(0)+" </TD><TD> "+Extendida.part_name+"</TD> </TR> \n";
    return Reporte;
}
void Reports::ReporteTablaEBR(EBR Extendida, const char *Guardar){
    FILE *f;


    std::string Reporte="";
    Reporte =Reporte+"digraph Gr { \n graph [ratio=fill]; \n graph [bb=\"0,0,352,154\"];"+ "node [label=\"\\N\", fontsize=15, shape=plaintext]; ";
    Reporte =Reporte+"labelloc=\"t\"  \n label="+"EBR "+Extendida.part_name+";";
    Reporte =Reporte+"Conte [label=< <TABLE BORDER=\"1\" ALIGN=\"center\" COLOR=\"#03fc20\">";
    Reporte = Reporte+"\n <TR>  <TD> Nombre </TD><TD> Valor </TD> </TR> \n";
    //Contenido MBR

    Reporte = Reporte+this->TablaEBR(Extendida);

    Reporte = Reporte+"\n </TABLE> \n >]; \n}";
    char Cop[1+Reporte.size()];
    strcpy(Cop,Reporte.c_str());
    f=fopen("G.dot","w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }
    const char *command = "dot -Tpng G.dot -o Tabla.png";
    system(command);






}






std::string Reports::GraphE(RDI Dita,const char *Path,std::queue <RDI> Que){
    std::string Retu="";
    Retu="\n <TD> <TABLE BORDER=\"1\" > ";
    Retu=Retu+" <TR  ><TD  BORDER=\"1\" > Extendida: "+Dita.Info+ " </TD></TR>";
   // std::string Num=std::to_string((Dita.Size)/Fun->FileSize(Path)*100);
    Retu=Retu+" <TR  ><TD   > <TABLE BORDER=\"0\" > <TR > "+GraphL(Path,Que)+ " </TR> </TABLE> </TD></TR>";
    Retu=Retu+"</TABLE> </TD>";
    return Retu;
}
std::string Reports::GraphL(const char *Path, std::queue<RDI> Que){
        std::string Retu="";
        while(!Que.empty()){
            RDI NewAva=Que.front();
            if(NewAva.Size>0){
                switch (NewAva.Type) {
                case 3:{
                    Retu=Retu+"\n <TD> <TABLE BORDER=\"1\" > ";
                    Retu=Retu+" <TR  ><TD  BORDER=\"1\" > EBR "+ " </TD></TR>";
                    Retu=Retu+" <TR  ><TD   >  "+NewAva.Info+" </TD></TR>";
                    Retu=Retu+"</TABLE> </TD>";


                    Retu=Retu+"\n <TD> <TABLE BORDER=\"1\" > ";
                    Retu=Retu+" <TR  ><TD  BORDER=\"1\" > Logica: "+NewAva.Info+ " </TD></TR>";
                    std::ostringstream Str;
                    Str << std::fixed;
                    Str << std::setprecision(2);
                    double Calc=double((int((NewAva.Size))))*100/double(Fun->FileSize(Path));
                    Str << Calc;
                    std::string Num = Str.str();
                    Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
                    Retu=Retu+"</TABLE> </TD>";
                    break;
                }
                case 4:{
                    Retu=Retu+"\n <TD> <TABLE BORDER=\"1\" > ";
                    Retu=Retu+" <TR  ><TD  BORDER=\"1\" > Espacio Libre: "+" </TD></TR>";
                    std::ostringstream Str;
                    Str << std::fixed;
                    Str << std::setprecision(2);
                    double Calc=double((int((NewAva.Size))))*100/double(Fun->FileSize(Path));
                    Str << Calc;
                    std::string Num = Str.str();
                    Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
                    Retu=Retu+"</TABLE> </TD>";
                    break;
                }
                }
            }
            Que.pop();
        }
    return Retu;
}
std::string Reports::GraphP(RDI Dita,const char *Path){
    std::string Retu="";
    Retu="\n <TD> <TABLE BORDER=\"1\" > ";
    Retu=Retu+" <TR  ><TD   BORDER=\"1\"> Primaria: "+Dita.Info+ " </TD></TR>";
    std::ostringstream Str;
    Str << std::fixed;
    Str << std::setprecision(2);
    double Calc=double((int((Dita.Size))))*100/double(Fun->FileSize(Path));
    Str << Calc;
    std::string Num = Str.str();
    Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
    Retu=Retu+"</TABLE> </TD>";
    return Retu;
}
std::string Reports::GraphEmpty(RDI Dita,const char *Path){
    std::string Retu="";
    Retu="\n <TD> <TABLE BORDER=\"1\" > ";
    Retu=Retu+" <TR  ><TD  BORDER=\"1\" >  "+"Espacio Libre"+ " </TD></TR>";
    std::ostringstream Str;
    Str << std::fixed;
    Str << std::setprecision(2);
    double Calc=double((int((Dita.Size))))*100/double(Fun->FileSize(Path));
    Str << Calc;
    std::string Num = Str.str();
    Retu=Retu+" <TR  ><TD   >  "+Num+ " </TD></TR>";
    Retu=Retu+"</TABLE> </TD>";
    return Retu;
}
void Reports::Graphviz(const char *Path){
    std::queue <RDI> Dita=this->PARTReport(Path);
    std::string M;
    M="\n labelloc=\"t\"";
    M=M+"\n label=\""+Path+"\";";
    std::string Graph="digraph Gr { \n  graph [ratio=fill];\n  graph [bb=\"0,0,352,154\"];\n node [label=\"\\N\", fontsize=15, shape=plaintext]; \n "+M+"Conte [label=< <TABLE BORDER=\"0\" ALIGN=\"center\" COLOR=\"#0CB7F2\"> \n <TR> \n";
    Graph=Graph+"\n <TD> <TABLE BORDER=\"1\" > ";
    Graph=Graph+" <TR  ><TD   BORDER=\"1\"> MBR "+ " </TD></TR>";


    std::ostringstream Str;
    Str << std::fixed;
    Str << std::setprecision(2);
    double Calc=double((int(sizeof (MBR))))*100/double(Fun->FileSize(Path));
    Str << Calc;
    std::string Num = Str.str();
    Graph=Graph+" <TR  ><TD   >  "+Num+ " </TD></TR>";
    Graph=Graph+"</TABLE> </TD>";

    while(!Dita.empty()){
        RDI NewAva=Dita.front();
        if(NewAva.Size>0){
            switch (NewAva.Type) {
            case 0:{
                Graph=Graph+this->GraphEmpty(NewAva,Path);
                break;
            }
            case 1:{
                Graph=Graph+this->GraphP(NewAva,Path);
                break;
            }
            case 2:{
                Graph=Graph+this->GraphE(NewAva,Path,this->LogicReport(Path,NewAva.Begin,NewAva.End));
                break;
            }
            }

            std::cout<<NewAva.Begin<<"***"<<NewAva.Size<<"***"<<NewAva.Type<<"***"<<NewAva.Info<<std::endl;
        }
        Dita.pop();
    }
    Graph= Graph+"\n </TR> </TABLE> \n >]; \n}";
    char Cop[1+Graph.size()];
    strcpy(Cop,Graph.c_str());
    FILE *f;
    f=fopen("G.dot","w");
    if (!f){
        return ;
    }else{
        fwrite(&Cop,sizeof(Cop),1,f);
        fclose(f);
    }
    const char *command = "dot -Tpng G.dot -o Dot.png";
    system(command);
   // std::cout<<Graph<<std::endl;
}
//Llena Cola De Primarias Y Extendidas
std::queue <RDI> Reports::PARTReport(const char *Path){
    std::string Out;
    FILE *f;
    f=fopen(Path,"r");
    std::queue <RDI> Dita;
    if (!f)
        return Dita;
    //fseek(f,Num,SEEK_SET);
    //Cola para los fit

    MBR Main;
    fseek(f,0,SEEK_SET);
    fread(&Main,sizeof(MBR),1,f);
    fclose(f);
    int Beg=int(sizeof (MBR));
    int End=Fun->FileSize(Path);

    for (int i=0;i<4;i++) {
        RDI NewAva;
        NewAva.Begin=Beg;
        NewAva.End=Main.mbr_partition[i].part_start;
        NewAva.Size=NewAva.End-NewAva.Begin;
        NewAva.Type=0;
        NewAva.Info="";
        Dita.push(NewAva);
        if(NewAva.End!=0)
            Beg=NewAva.End+Main.mbr_partition[i].part_size;
        {
            RDI NewAva;
            NewAva.Begin=Main.mbr_partition[i].part_start;
            NewAva.End=Main.mbr_partition[i].part_start+Main.mbr_partition[i].part_size;
            NewAva.Size=Main.mbr_partition[i].part_size;
            if(Main.mbr_partition[i].part_type!='e'){
                NewAva.Type=1;
            }else{
                NewAva.Type=2;
            }
            NewAva.Info=Main.mbr_partition[i].part_name;
            Dita.push(NewAva);
            /*
            if(NewAva.Type==2){
               this->FillQueue(&Dita,this->LogicReport(Path,NewAva.Begin,NewAva.End));
            }
            */
        }
    }
    RDI NewAva;

    NewAva.Begin=Beg;
    NewAva.End=End;
    NewAva.Size=NewAva.End-NewAva.Begin;
    NewAva.Type=0;
    NewAva.Info="";
    Dita.push(NewAva);
    /*while(!Dita.empty()){
        NewAva=Dita.front();
        if(NewAva.Size>0){

            if(NewAva.Type==2){
                this->LogicReport(Path,NewAva.Begin,NewAva.End);
            }
            std::cout<<NewAva.Begin<<"***"<<NewAva.Size<<"***"<<NewAva.Type<<std::endl;
        }
        Dita.pop();
    }*/
    return Dita;

}
//Vacia Una Cola EN Otra
void Reports::FillQueue(std::queue<RDI> *Q1, std::queue<RDI> Q2){
    std::queue <RDI> Retu;
    while(!Q2.empty()){
            RDI NewAva=Q2.front();
            if(NewAva.Size>0){
                Q1->push(NewAva);
            }
            Q2.pop();
        }
}
//Llena Cola De Logicas
std::queue <RDI> Reports::LogicReport(const char *Path, int Begin, int End){
    FILE *f;
    std::string Out="";
    EBR Logic;
    //Logic.part_next=0;
    int LogicIndex=Begin;
    std::queue <RDI> Dita;
    f=fopen(Path,"r+");
    if (!f){
        return Dita;
    }

    fseek(f,LogicIndex,SEEK_SET);
    fread(&Logic,sizeof(EBR),1,f);
    EBR First;
    fseek(f,Begin,SEEK_SET);
    fread(&First,sizeof(EBR),1,f);
    EBR Next;
    while(LogicIndex!=-1){
        fseek(f,LogicIndex,SEEK_SET);
        fread(&Logic,sizeof(EBR),1,f);
        LogicIndex=Logic.part_next;
        {
            RDI NewAva;
            NewAva.Begin=Logic.part_start;
            NewAva.End=Logic.part_start+Logic.part_size;
            NewAva.Size=Logic.part_size;
            NewAva.Type=3;
            NewAva.Info=Logic.part_name;
            Dita.push(NewAva);
        }


        if(LogicIndex!=-1){
            fseek(f,LogicIndex,SEEK_SET);
            fread(&Next,sizeof(EBR),1,f);

            RDI NewAva;
            NewAva.Begin=Logic.part_start+Logic.part_size;
            NewAva.End=Next.part_start;
            NewAva.Size=NewAva.End-NewAva.Begin;
            NewAva.Type=4;
            NewAva.Info="";
            Dita.push(NewAva);

            Begin=Next.part_start+Next.part_size;

        }else if (Logic.part_start==Begin && strcmp(Logic.part_name, First.part_name)==0 ) {
            RDI NewAva;
            NewAva.Begin=Logic.part_start+Logic.part_size;
            NewAva.End=End;
            NewAva.Size=NewAva.End-NewAva.Begin;
            NewAva.Type=4;
            NewAva.Info="";
            Dita.push(NewAva);
            Begin=End;

        }
    }

    fclose(f);
    RDI NewAva;
    NewAva.Begin=Begin;
    NewAva.End=End;
    NewAva.Size=NewAva.End-NewAva.Begin;
    NewAva.Type=4;
    NewAva.Info="";
    Dita.push(NewAva);
    //Cola para los fit

        return Dita;
}
/*
digraph Gr {
    graph [ratio=fill];
    graph [bb="0,0,352,154"];
    node [label="\N", fontsize=15, shape=plaintext];

    Conte [label=<
        <TABLE ALIGN="center" COLOR="#0CB7F2">
            <TR>
                <TD>Top left</TD>
                <TD>

                    <TABLE BORDER="0" >
                        <TR  ><TD   >Rowqqqqqqqqqqqqqqqqqq 1</TD></TR>
                        <TR ><TD >

                        <TABLE BORDER="0" >
                                <TR >
                                <TD BORDER="1">Row 1</TD>
                                <TD BORDER="1">Row 1</TD>
                                <TD BORDER="1">Row 1</TD>
                                <TD BORDER="1">Row 1</TD>
                                </TR>
                        </TABLE>


                        </TD></TR>
                    </TABLE>
                </TD>
                <TD>Top left</TD>
                <TD>Top left</TD>
            </TR>

        </TABLE>
    >, ];
}
*/
