#ifndef FUNCION_H_INCLUDED
#define FUNCION_H_INCLUDED
#include <stdio.h>     // Incluir librería para printf y scanf
#include <stdlib.h>    // Incluir librería para system y exit
#include <string.h>

// Declaración de archivos globales
FILE *archivoEquipos;
FILE *archivoGrupo;

// Estructura para guardar los nombres de los equipos
struct equipos {
    char nombreEquipo[50];
    int partidoGanado;
    int partidoPerdido;
    int partidoEmpatado;
    int partidoJugados;
    int golesFavor;
    int golesContra;
    int diferenciaGol;
    int puntos;
};

// Estructura para guardar los grupos de los equipos
struct grupos {
    struct equipos equipo[4];
};

//Estructura para guardar el nombre de la competencia y los equipos
struct competencia {
    char nombreCompetencia[50];
    struct grupos grupo [8];
};
// Declarar una variable global de tipo Competencia
struct competencia comp;

// Prototipos de funciones
void CrearMenu();
void crearFixture();
void verFixtureCompleto();
void verGrupo();
void cargarEstadisticas();
void modificarDato();
void menuFixture();

// Función para el menú principal
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

// Definición de la función crearFixture

void crearFixture() {
    char nombreCompetencia[50];
    struct grupos grupo[4];  // Mantener 4 grupos
    struct equipos;
    int numGrupos;
    int grupoElegido;


    // Solicitar nombre de la competencia
    printf("Ingrese el nombre de la competencia que se va a jugar: ");
    fflush(stdin);
    fgets(nombreCompetencia, 50, stdin);
    nombreCompetencia[strcspn(nombreCompetencia, "\n")] = 0;  // Eliminar salto de línea

    // Solicitar la cantidad de grupos
    printf("Ingrese el numero de los grupos, no mas de 4: ");
    scanf("%d", &numGrupos);

    // Validación del número de grupos
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
            grupo[i].equipo[j].nombreEquipo[strcspn(grupo[i].equipo[j].nombreEquipo, "\n")] = 0;  // Eliminar salto de línea

            // Inicializar estadísticas del equipo
            grupo[i].equipo[j].partidoGanado = 0;
            grupo[i].equipo[j].partidoPerdido = 0;
            grupo[i].equipo[j].partidoEmpatado = 0;
            grupo[i].equipo[j].partidoJugados = 0;
            grupo[i].equipo[j].golesFavor = 0;
            grupo[i].equipo[j].golesContra = 0;
            grupo[i].equipo[j].diferenciaGol = 0;
            grupo[i].equipo[j].puntos = 0;
}
}
  // Mostrar el fixture y las estadísticas iniciales de los equipos
    for (int i = 0; i < numGrupos; i++) {
        printf("\n================================= GRUPO %d ===================================\n", i + 1);
        printf("| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
        printf("|--------------------|------|------|------|------|------|------|------|------|\n");

        for (int j = 0; j < 4; j++) {
            printf("| %-18s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d |\n",
                   grupo[i].equipo[j].nombreEquipo,
                   grupo[i].equipo[j].partidoJugados,
                   grupo[i].equipo[j].partidoGanado,
                   grupo[i].equipo[j].partidoEmpatado,
                   grupo[i].equipo[j].partidoPerdido,
                   grupo[i].equipo[j].puntos,
                   grupo[i].equipo[j].golesFavor,
                   grupo[i].equipo[j].golesContra,
                   grupo[i].equipo[j].diferenciaGol);
        }
        printf("================================================================================\n");
    }

    // Guardar la competencia y equipos en el archivo

    FILE *archivoEquipos = fopen("miarchivo.txt", "w");
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

}
// aqui comienza las funciones del menuFixture

// Función para ver fixture completo


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

// Función para ver un grupo específico

void verGrupo() {
    char nombreCompetencia[50];
    struct grupos grupo[4];  // Mantener 4 grupos
    int numGrupos;
    int grupoElegido;

    printf("Ingrese el numero del grupo (1-4): ");
    scanf("%d", &grupoElegido);

    // Validar que el número del grupo sea válido
    if (grupoElegido < 1 || grupoElegido > 4) {
        printf("El numero es incorrecto, volve a intentar\n");
        return;
    }

    // Ajustar índice del grupo para recorrer correctamente la estructura
    grupoElegido--; // Convertir a índice basado en cero (0-3).

    printf("\n--- Estadisticas del Grupo %d ---\n", grupoElegido + 1);
    printf("\n================================= GRUPO %d ===================================\n", grupoElegido + 1);
    printf("| Equipo             | PJ   | PG   | PE   | PP   | Pts  | GF   | GC   | DG   |\n");
    printf("|--------------------|------|------|------|------|------|------|------|------|\n");

    // Iterar por los equipos del grupo y mostrar las estadísticas
    for (int j = 0; j < 4; j++) {
        printf("| %-18s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d |\n",
               comp.grupo[grupoElegido].equipo[j].nombreEquipo,  // Nombre del equipo
               comp.grupo[grupoElegido].equipo[j].partidoJugados, // Partidos jugados
               comp.grupo[grupoElegido].equipo[j].partidoGanado,  // Partidos ganados
               comp.grupo[grupoElegido].equipo[j].partidoEmpatado,// Partidos empatados
               comp.grupo[grupoElegido].equipo[j].partidoPerdido, // Partidos perdidos
               comp.grupo[grupoElegido].equipo[j].puntos,         // Puntos
               comp.grupo[grupoElegido].equipo[j].golesFavor,     // Goles a favor
               comp.grupo[grupoElegido].equipo[j].golesContra,    // Goles en contra
               comp.grupo[grupoElegido].equipo[j].diferenciaGol); // Diferencia de goles
    }
    printf("================================================================================\n");
}

// Función para cargar estadísticas de un equipo

void cargarEstadisticas(){

    struct comp;
    int grupo;
    int equipo;
    int equipo1, equipo2;
    int goles1, goles2;

    printf("seleccione el grupo (1,2,3,4): ");
    scanf("%d", &grupo);

   if (grupo < 1 || grupo > 4) {
        printf("El numero del grupo esta mal porfiado. Intente de nuevo.\n");
        return;
    }

    printf("seleccione el primer equipo (1-4): ");
    scanf("%d", &equipo1);
    printf("seleccione el segundo equipo (1-4): ");
    scanf("%d", &equipo2);
    printf("ingrese los goles del primer equipo: ");
    scanf("%d", &goles1);
    printf("ingrese los goles del segundo equipo: ");
    scanf("%d", &goles2);

      // Validamos si los equipos son correctos y diferentes entre sí
    if (equipo1 < 1 || equipo1 > 4 || equipo2 < 1 || equipo2 > 4 || equipo1 == equipo2) {
        printf("Los números de los equipos son inválidos. Intente de nuevo.\n");
        return;
    }

    equipo1--;  //indice para el primer equipo
    equipo2--;  //indice para el segundo equipo

       // Abrir el archivo de datos
    archivoEquipos = fopen("miarchivo.txt", "r");
    if (archivoEquipos == NULL) {
        printf("Error: No se pudo abrir el archivo.\n");
        return;
    }

    FILE *archivoTemp = fopen("temp.txt", "w");
    if (archivoTemp == NULL) {
        printf("Error: No se pudo crear el archivo temporal.\n");
        fclose(archivoEquipos);
        return;
    }

    equipo1--; // Índice para el primer equipo
    equipo2--; // Índice para el segundo equipo


//actualizar estadisticas del primer equipo
    comp.grupo[grupo].equipo[equipo1].partidoJugados++;
    comp.grupo[grupo].equipo[equipo1].golesFavor += goles1;
    comp.grupo[grupo].equipo[equipo1].golesContra += goles2;
    comp.grupo[grupo].equipo[equipo1].diferenciaGol += (goles1 - goles2);
// Actualización de estadísticas del segundo equipo
    comp.grupo[grupo].equipo[equipo2].partidoJugados++;  // Incrementa el número de partidos jugados
    comp.grupo[grupo].equipo[equipo2].golesFavor += goles2;  // Suma los goles a favor
    comp.grupo[grupo].equipo[equipo2].golesContra += goles1;  // Suma los goles en contra
    comp.grupo[grupo].equipo[equipo2].diferenciaGol += (goles2 - goles1);  // Calcula la diferencia de goles

    // Determinar el ganador y actualizar puntos
    if (goles1 > goles2) {
        comp.grupo[grupo].equipo[equipo1].partidoGanado++;  // Incrementa los partidos ganados del primer equipo
        comp.grupo[grupo].equipo[equipo1].puntos += 3;  // El primer equipo recibe 3 puntos
        comp.grupo[grupo].equipo[equipo2].partidoPerdido++;  // Incrementa los partidos perdidos del segundo equipo
    } else if (goles1 < goles2) {
        comp.grupo[grupo].equipo[equipo2].partidoGanado++;  // Incrementa los partidos ganados del segundo equipo
        comp.grupo[grupo].equipo[equipo2].puntos += 3;  // El segundo equipo recibe 3 puntos
        comp.grupo[grupo].equipo[equipo1].partidoPerdido++;  // Incrementa los partidos perdidos del primer equipo
    } else {
        comp.grupo[grupo].equipo[equipo1].partidoEmpatado++;  // Incrementa los partidos empatados del primer equipo
        comp.grupo[grupo].equipo[equipo1].puntos += 1;  // El primer equipo recibe 1 punto
        comp.grupo[grupo].equipo[equipo2].partidoEmpatado++;  // Incrementa los partidos empatados del segundo equipo
        comp.grupo[grupo].equipo[equipo2].puntos += 1;  // El segundo equipo recibe 1 punto
    }

    printf("Estadisticas actualizadas exitosamente.\n");
}



// Función para modificar un dato


void modificarNombreEquipos() {
    char grupoBuscado[20];
    char equipoBuscado[50];
    char nuevoNombre[50];
    char linea[100];
    int encontrado = 0;

    printf("Ingrese el grupo (por ejemplo, 'Grupo 1'): ");
    fflush(stdin);
    fgets(grupoBuscado, 20, stdin);
    grupoBuscado[strcspn(grupoBuscado, "\n")] = 0; // Eliminar salto de línea

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

    // Leer archivo línea por línea y buscar coincidencias
    while (fgets(linea, sizeof(linea), archivoEquipos)) {
        if (strstr(linea, grupoBuscado) && encontrado == 0) {
            encontrado = 1; // Grupo encontrado
        } else if (encontrado && strstr(linea, equipoBuscado)) {
            fprintf(archivoTemp, "Equipo: %s\n", nuevoNombre); // Escribir nueva línea
            encontrado = 0; // Equipo encontrado y modificado
        } else {
            fprintf(archivoTemp, "%s", linea); // Copiar línea sin cambios
        }
    }

    fclose(archivoEquipos);
    fclose(archivoTemp);



    if (encontrado == 0) {
        printf("El equipo fue modificado exitosamente.\n");
    } else {
        printf("No se encontro el equipo o grupo especificado.\n");
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
