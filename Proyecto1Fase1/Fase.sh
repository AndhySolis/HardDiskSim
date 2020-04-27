#exec -path=/home/pc/Desktop/Fase.sh
mkdisk -size=50000 -unit=k -path=/home/archivos/fase1/Disco1.disk -fit=BF
fdisk -type=P -unit=K -name=Part1 -size=49000-path=/home/archivos/fase1/Disco1.disk -fit=BF
mount -path=/home/archivos/fase1/Disco1.disk -name=Part1 #vda1
#FASE 2
#Crear Particion
mkfs -type=fast -id=vda1
#LOGIN
login -usr=root -pwd=123 -id=vda1
#CREAR CARPETAS
Mkdir -p  -path=/home/casa1
Mkdir -p  -path=/home/casa2
Mkdir -p  -path=/home/casa3
Mkdir -p  -path=/home/casa4
Mkdir -p  -path=/home/casa5
Mkdir -p  -path=/home/casa6
Mkdir -p  -path=/home/casa7
Mkdir -p  -path=/home/casa8
Mkdir -p  -path=/home/casa9
Mkdir -p  -path=/home/casa10

Mkdir -p  -path=/home/casa11
Mkdir -p  -path=/home/casa12
Mkdir -p  -path=/home/casa13
Mkdir -p  -path=/home/casa14
Mkdir -p  -path=/home/casa15
Mkdir -p  -path=/home/casa16

mkFile -SIZE=15 -p -path=/home/pc/Desktop/Prueba.txt  -cont=/home/pc/Desktop/Ark.txt
#Reportar Carpetas
rep -id=vda1 -Path="/home/pc/reporte3.png" -name=tree 