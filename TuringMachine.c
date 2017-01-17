#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


int main() {

    FILE *file = fopen("tm.in", "r");
    char line[12000]; //marimea liniei
    char **a;
    int nr_linii = 0, i;
    a = malloc(10000 * sizeof(char *));

    while (fgets(line, sizeof(line), file) != NULL) //citesc o linie
    {
        char *remove_newline;
        if ((remove_newline = strchr(line, '\n')) != NULL)
            *remove_newline = '\0';
        a[nr_linii] = strdup(line);//pun linia in vector
        nr_linii++;

    }

    fclose(file);//pana aici citesc fisierul tm.in


    char tape[5001];

    FILE *banda = fopen("tape.in", "r");//citesc banda
    fgets(tape, sizeof(tape), banda);
    fclose(banda);

    for (i = strlen(tape) - 1; i < 5001; i++)
        tape[i] = '#';
    tape[5000] = '\0';

    char *str, **stari;
    stari = malloc(20000 * sizeof(char *));

    str = strtok(a[0], " \n");

    int p = 0;
    while (str) {

        stari[p] = str;//pun toate valori in un vector de stari
        p++;
        str = strtok(NULL, " \n");
    }


    char *stari_finale;
    char buffer[400];
    stari_finale = strdup(a[1]);


    char stare_initiala[200], stare_curenta[200];

    strcpy(stare_initiala, a[2]);

    strcpy(stare_curenta, stare_initiala);


    int nr_tranzitii;
    nr_tranzitii = atoi(strtok(a[3], " "));//numarul de tranzitii

    int x, index = 1, agatat = 0;

    strcat(stari_finale, " ");//ca sa nu verific mai multe cazuri(ex,daca e \n dupa stare),pun " "la fiecare
    FILE *output = fopen("tape.out", "w");

    while (!strstr(stari_finale, strcat(stare_curenta, " "))) {

        stare_curenta[strlen(stare_curenta) - 1] = '\0';
        agatat = 0;
        

        for (x = 4; x < 4 + nr_tranzitii; x++) {

            strcpy(buffer, a[x]);//copie a sirului ca sa nu il stric;
            char *buffer2 = strtok(buffer, " \n");


            if (strcmp(buffer2, stare_curenta) == 0) {//verific daca ma aflu in starea indicata



                buffer2 = strtok(NULL, " \n");//elementul de pe banda

                if (buffer2[0] == tape[index]) {//verific daca pe banda e elementul din tranz
                    agatat++;


                    buffer2 = strtok(NULL, " \n");//starea in care se trece

                    strcpy(stare_curenta, buffer2);


                    buffer2 = strtok(NULL, " \n");//elementul de scris pe banda

                    tape[index] = buffer2[0];


                    buffer2 = strtok(NULL, " \n");//pozitia capului

                    if (buffer2[0] == 'R') index++;
                    if (buffer2[0] == 'L') index--;


                }


            }


        }
        if (!agatat) {
            fprintf(output, "Se agata!");
            fclose(output);
            return 0;
        }


    }

    fprintf(output, "%s", tape);
    fclose(output);


    return 0;
}