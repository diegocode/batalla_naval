/*
 *
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define 	MAX_FILA		8
#define 	MAX_COLU		8

#define 	CANT_BARCOS		8

typedef struct {
    char barcos[MAX_COLU + 1][MAX_FILA + 1];
    char disparos[MAX_COLU + 1][MAX_FILA + 1];
} tablero ;

tablero jugador_1;
tablero	jugador_2;

void inicializar_tablero(tablero *tab, char caracter);
void mostrar_tablero(tablero tab);
void distribuir_barcos(tablero *tab, int cant);

int main(int argc, char **argv)
{
    srand(time(NULL));

    inicializar_tablero(&jugador_1, '.');
    inicializar_tablero(&jugador_2, '.');
    distribuir_barcos(&jugador_1, 8);
    distribuir_barcos(&jugador_2, 8);

    char x;
    int y;
    int cant_barcos_1 = 0;
    int cant_barcos_2 = 0;
    do {
        mostrar_tablero(jugador_1);

        printf("\n ingrese coordenadas de disparo x y ");
        do {
            scanf(" %c %dg6", &x, &y);
            //printf("---> %c, %d\n", x, y);
        } while((x < 'a') || (x > ('a' + MAX_COLU)) || (y < 0) || (y > MAX_FILA));

        //printf("%c, %d\n", x, y);
        x = x - 'a' + 1;
        if (jugador_2.barcos[y][x] =='B') {
            jugador_2.barcos[y][x] = 'X';
            jugador_1.disparos[y][x] = 'X';
            cant_barcos_1++;
        } else {
            jugador_1.disparos[y][x] = 'D';
        }

        do {
            x = (rand() % MAX_FILA) + 1;
            y = (rand() % MAX_COLU) + 1;

        } while(jugador_2.disparos[y][x] == 'D');

        jugador_2.disparos[y][x] = 'D';

        if (jugador_1.barcos[y][x] == 'B') {
            jugador_1.barcos[y][x] = 'X';
            cant_barcos_2++;
        }

    } while ((cant_barcos_1 < CANT_BARCOS) && (cant_barcos_2 < CANT_BARCOS));

    printf("puntos jugador 1: %d - puntos jugador 2: %d \n", cant_barcos_1, cant_barcos_2);
    mostrar_tablero(jugador_1);

    return 0;
}

int cuadro_libre(tablero tab, int i, int j) {
    int libre = 1;
    if (
            (tab.barcos[i - 1][j - 1] == 'B') || (tab.barcos[i - 1][j] == 'B') || (tab.barcos[i - 1][j + 1] == 'B') ||
            (tab.barcos[i][j - 1] == 'B') || (tab.barcos[i][j] == 'B') || (tab.barcos[i][j + 1] == 'B') ||
            (tab.barcos[i + 1][j - 1] == 'B') || (tab.barcos[i + 1][j] == 'B') || (tab.barcos[i + 1][j + 1] == 'B')
            )
        libre = 0;

    return  libre;
}

void distribuir_barcos(tablero* tab, int cant){
    int i, j;
    int orientacion;
    int largo;

    for(int p = 0; p < cant; p++) {
        do {
            i = (rand() % MAX_FILA) + 1;
            j = (rand() % MAX_COLU) + 1;

        } while (!cuadro_libre(*tab, i, j));

        tab->barcos[i][j] = 'B';
    }
}

void inicializar_tablero(tablero* tab, char caract) {
    for(int i = 1; i <= MAX_FILA; i++) {
        for(int j = 1; j <= MAX_COLU; j++) {
            tab->barcos[i][j] = caract; // + i + j;
            tab->disparos[i][j] = caract; // + i + j;
        }
    }
}

void mostrar_tablero(tablero tab){
    int p = 0;
    for(int i = 0; i <= MAX_FILA; i++) {
        p = 0;
        for(int j = 0; j <= (MAX_COLU * 2) + 1; j++) {
            if (i == 0)
                if (p == 0)
                    printf("      ");
                else
                    printf("%c ", 'a' + p - 1);
            else
            if (p == 0)
                printf("    %d ", i);
            else
            if (j <= MAX_COLU)
                printf("%c ", tab.barcos[i][p]);
            else
                printf("%c ", tab.disparos[i][p]);

            if (j == MAX_COLU)
                p = 0;
            else
                p++;
        }
        printf("\n");
    }
}
