#include "/home/pallav/experiments/abc2js/emscripten-1.8.9/system/include/emscripten/emscripten.h"
#include "picosat.h"

PicoSAT *a;

int conv(int a, int b, int c) { return a * 81 + b * 9 + c + 1; }
int *inverse(int num) {
    int *arr = (int *)malloc(3 * sizeof(int));
    num -= 1;
    arr[0] = num / 81;
    num %= 81;
    arr[1] = num / 9;
    arr[2] = num % 9;
    return arr;
}
void EMSCRIPTEN_KEEPALIVE solve(char *arr) {
    a = picosat_init();

    int i = 0, j = 0, k = 0, l = 0;
    int list[9][9][2];

    for (i = 0; i < 9; i++) {
        int col = (i % 3) * 3;
        int row = (i / 3) * 3;
        l = 0;
        for (j = row; j < row + 3; j++)
            for (k = col; k < col + 3; k++) {
                list[i][l][0] = j;
                list[i][l][1] = k;
                l++;
            }
    }

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int *arr = (int *)malloc(10 * sizeof(int));
            arr[9] = 0;
            for (k = 0; k < 9; k++) {
                arr[k] = conv(i, j, k);
            }
            picosat_add_lits(a, arr);
        }
    }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            for (k = 0; k < 8; k++)
                for (l = k + 1; l < 9; l++) {
                    int *arr = (int *)malloc(3 * sizeof(int));
                    arr[0] = -conv(i, j, k);
                    arr[1] = -conv(i, j, l);
                    arr[2] = 0;
                    picosat_add_lits(a, arr);
                }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int *arr = (int *)malloc(10 * sizeof(int));
            arr[9] = 0;
            for (k = 0; k < 9; k++) {
                arr[k] = conv(i, k, j);
            }
            picosat_add_lits(a, arr);
        }
    }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            for (k = 0; k < 8; k++)
                for (l = k + 1; l < 9; l++) {
                    int *arr = (int *)malloc(3 * sizeof(int));
                    arr[0] = -conv(i, k, j);
                    arr[1] = -conv(i, l, j);
                    arr[2] = 0;
                    picosat_add_lits(a, arr);
                }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int *arr = (int *)malloc(10 * sizeof(int));
            arr[9] = 0;
            for (k = 0; k < 9; k++) {
                arr[k] = conv(k, i, j);
            }
            picosat_add_lits(a, arr);
        }
    }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            for (k = 0; k < 8; k++)
                for (l = k + 1; l < 9; l++) {
                    int *arr = (int *)malloc(3 * sizeof(int));
                    arr[0] = -conv(k, i, j);
                    arr[1] = -conv(l, i, j);
                    arr[2] = 0;
                    picosat_add_lits(a, arr);
                }
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            int *arr = (int *)malloc(10 * sizeof(int));
            arr[9] = 0;
            for (k = 0; k < 9; k++) {
                arr[k] = conv(list[i][k][0], list[i][k][1], j);
            }
            picosat_add_lits(a, arr);
        }
    }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            for (k = 0; k < 8; k++)
                for (l = k + 1; l < 9; l++) {
                    int *arr = (int *)malloc(3 * sizeof(int));
                    arr[0] = -conv(list[i][k][0], list[i][k][1], j);
                    arr[1] = -conv(list[i][l][0], list[i][l][1], j);
                    arr[2] = 0;
                    picosat_add_lits(a, arr);
                }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++) {
            if (arr[9 * i + j] != '0') {
                int brr[] = {conv(i, j, arr[9 * i + j] - '0' - 1), 0};
                picosat_add_lits(a, (int *)brr);
            }
        }
    picosat_sat(a, -1);
    int output[9][9];
    for (i = 1; i <= 729; i++) {
        int out = picosat_deref(a, i);
        if (out > 0) {
            int *indices = inverse(i);
            output[indices[0]][indices[1]] = indices[2] + 1;
        }
    }
    for (i = 0; i < 9; i++)
        for (j = 0; j < 9; j++)
            arr[9 * i + j] = output[i][j] + '0';
}
int EMSCRIPTEN_KEEPALIVE main() {
    int i, j;
    char str[] =
        "800000000"
        "003600000"
        "070090200"
        "050007000"
        "000045700"
        "000100030"
        "001000068"
        "008500010"
        "090000400";
    solve(str);
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++)
            printf("%c", str[9 * i + j]);
        printf("\n");
    }
    printf("\n");
    char str2[] =
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000"
        "000000000";
    solve(str2);
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++)
            printf("%c", str2[9 * i + j]);
        printf("\n");
    }
    return 0;
}
