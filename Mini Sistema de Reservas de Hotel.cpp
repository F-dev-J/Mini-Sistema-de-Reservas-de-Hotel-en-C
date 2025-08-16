#include<stdio.h>
#include<conio.h>
#define FILAS 10
#define COLUMNAS 3
struct Habitacion {
    int numero;
    int ocupada; // 0 = libre, 1 = ocupada
};
void cargarHotel(struct Habitacion hotel[FILAS][COLUMNAS],FILE *archDisp);
void mostrarHotel(struct Habitacion hotel[FILAS][COLUMNAS],FILE *archDisp);
void agregarModificarHotel(struct Habitacion hotel[FILAS][COLUMNAS], FILE *archDisp, int fila, int columna);

main(){	
FILE *archDisp; 
 struct Habitacion hotel[FILAS][COLUMNAS];
 int opcion;
 bool band1=true;
 do{
 printf("ingrese una opcion:\n");
  printf("1)crecion/reseteo de los pisos x habitaciones:\n");
  printf("2)agregar o modificar habitacion:\n");
  printf("3)ver habitaciones disponibles:\n");
  printf("4)salir:");
 scanf("%d",&opcion);   
 switch(opcion){
//----------------------------------------------------- 
	case 1:
 archDisp=fopen("disponibilidad.dat","wb");
    if (archDisp == NULL) {
    printf("Error al abrir el archivo\n");
    return 1;
    }
 cargarHotel(hotel,archDisp);
fclose(archDisp);
break;
//----------------------------------------------------- 
case 2:
  archDisp=fopen("disponibilidad.dat","rb+");
    if (archDisp == NULL) {
    printf("Error al abrir el archivo\n");
    return 1;
    }
    agregarModificarHotel(hotel,archDisp,0,1);
 fclose(archDisp);
 break;
 //-----------------------------------------------------
 case 3:
  archDisp=fopen("disponibilidad.dat","rb");
    if (archDisp == NULL) {
    printf("Error al abrir el archivo\n");
    return 1;
    }
 mostrarHotel(hotel,archDisp);
 fclose(archDisp);
 break;
 case 4:
 printf("Muchas gracias");
 band1=false;
 break;
 default:
 	printf("seleccione una opcion dentro del rango");
  }	
 }
 while(band1!=false);
 return 0;	
}
void cargarHotel(struct Habitacion hotel[FILAS][COLUMNAS],FILE *archDisp) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            hotel[i][j].numero = i * COLUMNAS + j + 1;
            hotel[i][j].ocupada = 0; 
            fwrite(&hotel[i][j],sizeof(struct Habitacion),1,archDisp);
        }
    }
    fclose(archDisp);
}
void mostrarHotel(struct Habitacion hotel[FILAS][COLUMNAS], FILE *archDisp) {
    printf("\n--- Estado del Hotel ---\n");
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
        	fread(&hotel[i][j], sizeof(struct Habitacion), 1, archDisp);
            printf("Hab %02d: %s\t", hotel[i][j].numero,hotel[i][j].ocupada ? "Ocupada" : "Libre");    
        }
        printf("\n");
    }
   fclose(archDisp);
}
void agregarModificarHotel(struct Habitacion hotel[FILAS][COLUMNAS],FILE *archDisp, int fila, int columna) {
   
      for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            hotel[i][j].numero = i * COLUMNAS + j + 1;
            fseek(archDisp, (fila * COLUMNAS + columna) * sizeof(struct Habitacion), SEEK_SET);
              hotel[fila][columna].ocupada = 1; // marcar como ocupada
            fwrite(&hotel[fila][columna], sizeof(struct Habitacion), 1, archDisp);
        }
    }
   
   
}
