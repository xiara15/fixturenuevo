#ifndef FUNCION_H_INCLUDED
#define FUNCION_H_INCLUDED
#include <stdio.h>     // Incluir librer�a para printf y scanf
#include <stdlib.h>    // Incluir librer�a para system y exit
#include <string.h>

// Declaraci�n de archivos globales
FILE *archivoEquipos;
FILE *archivoGrupo;

// Estructura para guardar los nombres de los equipos
struct equipos {
    char nombreEquipo[50];
};

// Estructura para guardar los grupos de los equipos
struct grupos {
    struct equipos equipo[4];
    struct estadisticas estadistica;
};
// Estructura para guardar las estad�sticas de los partidos
struct estadisticas {
    int partidoGanado;
    int partidoPerdido;
    int partidoEmpatado;
    int partidoJugados;
    int golesFavor;
    int golesContra;
    int diferenciaGol;
    int puntos;
};
//Estructura para guardar el nombre de la competencia y los equipos
struct competencia {
    char nombreCompetencia[50];
    struct grupos grupo [8];

};

// Prototipos de funciones
void CrearMenu();
void crearFixture();
void verFixtureCompleto();
void verGrupo();
void cargarEstadisticas();
void modificarDato();
void menuFixture();

// Funci�n para el men� principal
void CrearMenu() {
    int opcion;
    do {
        printf("\n========== Menu Principal =========");
        printf("\n|        1.Crear Fixture          |");
        printf("\n|        2.Menu Fixture           |");
        printf("\n|        3.Salir                  |");
        printf("\n===================================");
        printf("\nIngrese la opcion que desee ver: ");
        fflush(stdin);
        scanf("%d", &opcion);
        fflush(stdin);

        switch (opcion) {
            case 1:
                system("cls");
                crearFixture();
                break;
            case 2:
                system("cls");
                menuFixture ();
                break;
            case 3:
                exit(0);
                break;
            default:
                system("cls");
                printf("La opcion es incorrecta, volve a intentar de nuevo.\n");
                break;
        }
    } while (opcion != 3);
}

// Definici�n de la funci�n crearFixture

void crearFixture() {
    char nombreCompetencia[50];
    struct grupos grupo[4];  // Mantener 4 grupos
    int numGrupos;
    int grupoElegido;
     int partidoGanado, partidoPerdido, partidoEmpatado, partidoJugados;
    int golesFavor, golesContra, diferenciaGol, puntos;


    // Solicitar nombre de la competencia
    printf("Ingrese el nombre de la competencia que se va a jugar: ");
    fflush(stdin);
    fgets(nombreCompetencia, 50, stdin);
    nombreCompetencia[strcspn(nombreCompetencia, "\n")] = 0;  // Eliminar salto de l�nea

    // Solicitar la cantidad de grupos
    printf("Ingrese el numero de los grupos, no mas de 4: ");
    scanf("%d", &numGrupos);

    // Validaci�n del n�mero de grupos
    if (numGrupos < 1 || numGrupos > 4) {
        printf("El numero del grupo esta mal porfiado. Intente de nuevo.\n");
        return;
    }

    // Solicitar los nombres de los equipos para cada grupo
    for (int i = 0; i < numGrupos; i++) {
        printf("\nIngrese los nombres de los equipos para el Grupo %d:\n", i + 1);
        for (int j = 0; j < 4; j++) {
            printf("Ingrese el nombre del equipo %d: ", j + 1);
            fflush(stdin);
            fgets(grupo[i].equipo[j].nombreEquipo, 50, stdin);
            grupo[i].equipo[j].nombreEquipo[strcspn(grupo[i].equipo[j].nombreEquipo, "\n")] = 0;  // Eliminar salto de l�nea




            // Inicializar estad�sticas del equipo
            grupo[i].equipo[j].estadisticas.partidoJugados = 0;
            grupo[i].equipo[j].partidoGanado = 0;
            grupo[i].equipo[j].partidoEmpatado = 0;
            grupo[i].equipo[j].partidoPerdido = 0;
            grupo[i].equipo[j].Puntos = 0;
            grupo[i].equipo[j].goles = 0;
            grupo[i].equipo[j].golesContra = 0;


        }



        }



    // Guardar la competencia y equipos en el archivo
    archivoEquipos = fopen("miarchivo.txt", "w");
    if (archivoEquipos == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    fprintf(archivoEquipos, "Competencia: %s\n", nombreCompetencia);
    for (int i = 0; i < numGrupos; i++) {
        fprintf(archivoEquipos, "\nGrupo %d:\n", i + 1);
        for (int j = 0; j < 4; j++) {
            fprintf(archivoEquipos, "Equipo %d: %s\n", j + 1, grupo[i].equipo[j].nombreEquipo);
        }
    }

    fclose(archivoEquipos);
    printf("Competencia y equipos guardados correctamente, muy bien\n");

// aqui comienza las funciones del menuFixture

// Funci�n para ver fixture completo

}
void verFixtureCompleto(){
    archivoEquipos = fopen("miarchivo.txt", "r");
    if (archivoEquipos == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    char linea[100];
    printf("Fixture completo:\n");
    while (fgets(linea, sizeof(linea), archivoEquipos)) {
        printf("%s", linea);
    }

    fclose(archivoEquipos);
}

// Funci�n para ver un grupo espec�fico

  void verGrupo()
  {

    archivoEquipos = fopen("miarchivo.txt", "r");
    if (archivoEquipos == NULL) {
        printf("Error: El archivo no existe o no se puede abrir.\n");
        return;
    }

    int grupoNum;
    printf("Ingrese el numero del grupo (1-4): ");
    scanf("%d", &grupoNum);

    if (grupoNum < 1 || grupoNum > 4) {
        printf("Error: Numero de grupo invalido.\n");
        fclose(archivoEquipos);
        return;
    }

    char linea[100];
    int equipoInicio = (grupoNum - 1) * 4 + 1; // C�lculo del �ndice inicial del grupo
    int equipoFin = equipoInicio + 3;         // C�lculo del �ndice final del grupo
    int equipoActual = 1;

    printf("\nGrupo %d:\n", grupoNum);
    while (fgets(linea, sizeof(linea), archivoEquipos)) {
        if (equipoActual >= equipoInicio && equipoActual <= equipoFin) {
            printf("%s", linea);
        }
        if (strstr(linea, "Equipo")) {
            equipoActual++;
        }
    }

    fclose(archivoEquipos);
}

// Funci�n para cargar estad�sticas de un equipo
void cargarEstadisticas();









// Funci�n para modificar un dato


void modificarNombreEquipos() {
    char grupoBuscado[20];
    char equipoBuscado[50];
    char nuevoNombre[50];
    char linea[100];
    int encontrado = 0;

    printf("Ingrese el grupo (por ejemplo, 'Grupo 1'): ");
    fflush(stdin);
    fgets(grupoBuscado, 20, stdin);
    grupoBuscado[strcspn(grupoBuscado, "\n")] = 0; // Eliminar salto de l�nea

    printf("Ingrese el nombre actual del equipo: ");
    fflush(stdin);
    fgets(equipoBuscado, 50, stdin);
    equipoBuscado[strcspn(equipoBuscado, "\n")] = 0;

    printf("Ingrese el nuevo nombre para el equipo: ");
    fflush(stdin);
    fgets(nuevoNombre, 50, stdin);
    nuevoNombre[strcspn(nuevoNombre, "\n")] = 0;

    archivoEquipos = fopen("miarchivo.txt", "r");
    if (archivoEquipos == NULL) {
        printf("Error al abrir el archivo.\n");
        return;
    }

    FILE *archivoTemp = fopen("temp.txt", "w");
    if (archivoTemp == NULL) {
        printf("Error al crear archivo temporal.\n");
        fclose(archivoEquipos);
        return;
    }

    // Leer archivo l�nea por l�nea y buscar coincidencias
    while (fgets(linea, sizeof(linea), archivoEquipos)) {
        if (strstr(linea, grupoBuscado) && encontrado == 0) {
            encontrado = 1; // Grupo encontrado
        } else if (encontrado && strstr(linea, equipoBuscado)) {
            fprintf(archivoTemp, "Equipo: %s\n", nuevoNombre); // Escribir nueva l�nea
            encontrado = 0; // Equipo encontrado y modificado
        } else {
            fprintf(archivoTemp, "%s", linea); // Copiar l�nea sin cambios
        }
    }

    fclose(archivoEquipos);
    fclose(archivoTemp);



    if (encontrado == 0) {
        printf("El equipo fue modificado exitosamente.\n");
    } else {
        printf("No se encontr� el equipo o grupo especificado.\n");
    }
}

void menuFixture(){
    int opcion;
    do{
        printf("\n========== MENU FIXTURE ====================");
        printf("\n||        1.Ver Fixture Completo          ||");
        printf("\n||        2.Ver un Grupo                  ||");
        printf("\n||        3.Cargar Resultados             ||");
        printf("\n||        4.Modificar un dato             ||");
        printf("\n||        5.Volver al menu principal      ||");
        printf("\n============================================");
        printf("\nIngrese su opcion: ");
        fflush(stdin);
        scanf("%d",&opcion);
        fflush(stdin);

        switch(opcion){
            case 1://funcion para ver el fixture completo

               printf("Elegiste ver el Fixture Completo.\n");
               verFixtureCompleto();
               break;

            case 2://funcion para ver un solo grupo

                verGrupo();
                break;

            case 3://funcion para cargar las estadisticas

                cargarEstadisticas();
                break;

            case 4://funcion para modificar un dato

                modificarNombreEquipos() ;
                break;

            default:
                system("cls");
                printf("La opcion es incorrecta, volve a intentar de nuevo.\n");
                break;
}

} while(opcion!=5);


}

#endif // FUNCION_H_INCLUDED
