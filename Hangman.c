#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <conio.c>
#include <math.h>
#include <time.h>

#define MAX 200
#define TRUE 1
#define FALSE 0
#define INICIAL 32
#define ESC 27
#define PUNTOS 6
#define BASE 193
#define HOR 196
#define VER 179
#define ESQIZQ 218
#define ESQDER 191
#define UNO 49
#define DOS 50

void showDraw(int, int);
int score(char);
int verifUsed(char[], char);
int getChances(char[]);
void getText(char[]);
void showTime(int);

int main()
{
   int acertado, repetido, usadasPos = 0, puntos = 0, puntosTotales = 0, tiempo, comienzo = TRUE, chances, key, usadasLong = 0, racha = 0, puntosRacha = 0, puntosTemporales = 0, pos = 0, falladas = 0, chancesTotales;
   char palabra[MAX], palabraTemp[MAX], usadas[MAX] = {0}, caracter = INICIAL;
   do
   {
      system("cls");
      printf("Bienvenido a %cEl Ahorcado%c\n\nMen%c:\n1. Jugar\n2. Salir\n", 34, 34, 163);
      fflush(stdin);
      key = getche();
      if (key == UNO)
      {
         system("cls");
         gotoxy(40, 13);
         printf("Ingrese una palabra: ");
         fflush(stdin);
         getText(palabra);
         tiempo = time(NULL);
         chances = getChances(palabra);
         chancesTotales = chances;
         do
         {
            if (comienzo == TRUE)
            {
               for (pos = 0; palabra[pos]; pos++)
               {
                  if (palabra[pos] != ' ')
                     palabraTemp[pos] = '*';
                  else
                     palabraTemp[pos] = ' ';
               }
               palabraTemp[pos] = '\0';
               comienzo = FALSE;
            }
            else
            {
               repetido = verifUsed(usadas, caracter);
               if (repetido == FALSE)
               {
                  acertado = FALSE;
                  usadas[usadasPos++] = caracter;
                  for (int pos = 0; palabra[pos]; pos++)
                  {
                     if (caracter == palabra[pos])
                     {
                        palabraTemp[pos] = caracter;
                        acertado = TRUE;
                     }
                  }
                  if (acertado == TRUE && caracter != INICIAL)
                  {
                     puntos = 0;
                     puntos = score(caracter);
                     puntosTotales += puntos;
                     puntosTemporales += puntos;
                     racha++;
                     if (racha > 1)
                     {
                        puntosRacha = puntosTemporales;
                        puntosTotales += puntosRacha;
                     }
                  }
                  if (acertado == FALSE && caracter != INICIAL)
                  {
                     chances--;
                     falladas++;
                     puntos = 0;
                     puntosTemporales = 0;
                     puntosRacha = 0;
                     racha = 0;
                  }
               }
               else
               {
                  gotoxy(30, 12);
                  printf("Ya se ha utilizado el caracter \"%c\".", caracter);
               }
               if (chances >= 0)
               {
                  if (strcmp(palabra, palabraTemp) == 0)
                  {
                     gotoxy(30, 8);
                     puts(palabraTemp);
                     gotoxy(30, 13);
                     textcolor(GREEN);
                     printf("%cFelicidades, has ganado%c\n", 173, 33);
                     textcolor(WHITE);
                     gotoxy(30, 14);
                     system("pause");
                     system("cls");
                     printf("%cFelicidades, has ganado%c\n", 173, 33);
                     printf("La palabra era: \"%s\"\n", palabra);
                     printf("Con un total de:\n");
                     printf("Puntos totales: %d\n", puntosTotales);
                     printf("Chances restantes: %d\n", chances);
                     printf("Racha actual: %d\n", racha);
                     system("pause");
                     main();
                  }
                  if (repetido == FALSE)
                  {
                     system("cls");
                     showDraw(falladas, chancesTotales);
                     gotoxy(30, 8);
                     puts(palabraTemp);
                     gotoxy(30, 1);
                     printf("Chances Restantes: %d", chances);
                     gotoxy(1, 1);
                     printf("Tiempo: ");
                     gotoxy(1, 14);
                     printf("Racha Actual: %d", racha);
                     gotoxy(30, 5);
                     printf("Caracteres usados: %s", usadas);
                     gotoxy(1, 16);
                     printf("Puntos obtenidos: %d", puntos);
                     gotoxy(1, 17);
                     printf("Puntos de racha : %d", puntosRacha);
                     gotoxy(1, 18);
                     printf("Puntos totales  : %d", puntosTotales);
                     gotoxy(30, 11);
                     printf("Introduzca un caracter: ");
                     gotoxy(9, 1);
                     showTime(time(NULL) - tiempo);
                  }
                  if (chances == 0)
                  {
                     gotoxy(30, 12);
                     textcolor(RED);
                     printf("Mala suerte, has perdido.");
                     textcolor(WHITE);
                     gotoxy(30, 13);
                     system("pause");
                     system("cls");
                     printf("Mala suerte, has perdido.\n");
                     printf("La palabra era: \"%s\"\n", palabra);
                     printf("Con un total de:\n");
                     printf("Puntos totales: %d\n", puntosTotales);
                     system("pause");
                     main();
                  }
                  fflush(stdin);
                  gotoxy(54, 11);
                  do
                  {
                     key = tolower(getch())
                     if (key >= 'a' && key <= 'z' || key == ESC)
                     {
                        caracter = key;
                        if (key == ESC)
                           main();
                     }
                  } while (key < 'a' && key > 'z');
               }
            }
         } while (chances > 0);
      }
      if (key == DOS || key == ESC)
      {
         system("cls");
         printf("%cGracias por jugar%c\n", 173, 33);
         system("pause");
         exit(0);
      }
   } while (key != UNO || key != DOS);
   return 0;
}
/*
Función:    getText
Argumento:  (char[]) palabra. Palabra a ingresar por el usuario.
Objetivo:   Obtener la palabra con la que se va a jugar.
Retorno:    (void)
Lógica:     Obtener caracter por caracter, mediante un getch(para no mostrar el caracter), luego imprimir * por cada caracter diferente de espacio.
*/
void getText(char palabra[])
{
   int pos = 0;
   char caracter;
   fflush(stdin);
   gotoxy(61, 13);
   while ((caracter = tolower(getch())) != 13 && pos < MAX)
   {
      if (caracter >= 'a' && caracter <= 'z' || caracter == ESC || caracter == ' ')
      {
         palabra[pos++] = caracter;
         if (caracter != ' ')
            printf("*");
         if (caracter == ' ')
            printf(" ");
         if (caracter == ESC)
            main();
      }
   }
   palabra[pos] = '\0';
}
/*
Función:    getChances
Argumento:  (char[]) palabra a evaluar
Objetivo:   Obtener la cantidad de chances que tendrá el jugador.
Retorno:    (int) Cantidad de chances.
Lógica:     Obtener primero un arreglo con las palabras sin repeticiones, luego, contar las vocales y consonante para obtener los chances bajo una formula.
*/
int getChances(char palabra[])
{
   int used = 0;
   float contVocales = 0;
   char vocales[5] = "aeiou", usadas[MAX] = " ";
   for (int pos = 0; palabra[pos]; pos++)
      for (int ind = 0, cont = 0; usadas[ind]; ind++)
         if (palabra[pos] != ' ')
         {
            if (palabra[pos] != usadas[ind])
               cont++;
            if (usadas[cont] == 0)
               usadas[used++] = palabra[pos];
         }
   usadas[used] = '\0';
   for (int pos = 0; usadas[pos]; pos++)
      for (int ind = 0; vocales[ind]; ind++)
         if (usadas[pos] == vocales[ind])
            contVocales++;
   return round(((strlen(usadas) - contVocales) * (60.0 / 100)) + (contVocales / 2));
}
/*
Función:    verifUsed
Argumento:  (char[]) cadena, (char) caracter. Cadena y caracter a evaluar
Objetivo:   Verificar si el caracter ya se encuentra en la cadena.
Retorno:    (int) (true or false) 1 si ya ha sido usado, 0 si no.
*/
int verifUsed(char cadena[], char caracter)
{
   for (int pos = 0; cadena[pos]; pos++)
      if (caracter == cadena[pos])
         return 1;
   return 0;
}
/*
Función:    showTime
Argumento:  (int) seg. Segundos a evaluar.
Objetivo:   Obtener y mostrar el tiempo actual.
Retorno:    (void)
*/
void showTime(int seg)
{
   int min, hour;

   min = (seg / 60);
   seg -= (min * 60);
   hour = (min / 60);
   seg -= (hour * 3600);
   printf("%02d:%02d:%02d", hour, min, seg);
}
/*
Función:    score
Argumento:  (char) caracter. Carácter a evaluar.
Objetivo:   Obtener el puntaje del o caracteres acertados.
Retorno:    (int) puntos pos caracter.
*/
int score(char caracter)
{
   int pos;
   char pts20[PUNTOS] = "aeioc", pts25[PUNTOS] = "udlpr", pts30[PUNTOS] = "btfmn", pts35[PUNTOS] = "ghjqv", pts40[PUNTOS] = "kwxyz";
   for (pos = 0; pts20[pos]; pos++)
      if (caracter == pts20[pos])
         return 20;

   for (pos = 0; pts25[pos]; pos++)
      if (caracter == pts25[pos])
         return 25;

   for (pos = 0; pts30[pos]; pos++)
      if (caracter == pts30[pos])
         return 30;

   for (pos = 0; pts35[pos]; pos++)
      if (caracter == pts35[pos])
         return 35;

   for (pos = 0; pts40[pos]; pos++)
      if (caracter == pts40[pos])
         return 40;
}
/*
Función:    showDraw
Argumento:  (int) fallada, (int) chancesTotales
Objetivo:   Dibujar al muñeco en proporciones
Retorno:    (void)
*/
void showDraw(int falladas, int chancesTotales)
{
   // Base
   gotoxy(9, 3);
   printf("%c%c%c%c%c%c%c", ESQIZQ, HOR, HOR, HOR, HOR, HOR, ESQDER);
   gotoxy(9, 4);
   printf("%c     %c", VER, VER);
   gotoxy(9, 5);
   printf("%c", VER);
   gotoxy(9, 6);
   printf("%c", VER);
   gotoxy(9, 7);
   printf("%c", VER);
   gotoxy(9, 8);
   printf("%c", VER);
   gotoxy(9, 9);
   printf("%c", VER);
   gotoxy(9, 10);
   printf("%c", VER);
   gotoxy(4, 11);
   printf("%c%c%c%c%c%c%c%c%c%c%c", HOR, HOR, HOR, HOR, HOR, BASE, HOR, HOR, HOR, HOR, HOR);
   gotoxy(15, 5);
   printf("%c", falladas >= (0.14 * chancesTotales) ? 79 : 32);
   gotoxy(15, 6);
   printf("%c", falladas >= (0.28 * chancesTotales) ? 179 : 32);
   gotoxy(14, 5);
   printf("%c", falladas >= (0.42 * chancesTotales) ? 92 : 32);
   gotoxy(16, 5);
   printf("%c", falladas >= (0.56 * chancesTotales) ? 47 : 32);
   gotoxy(14, 7);
   printf("%c", falladas >= (0.70 * chancesTotales) ? 47 : 32);
   gotoxy(16, 7);
   printf("%c", falladas >= (0.84 * chancesTotales) ? 92 : 32);
   gotoxy(15, 5);
   if (falladas == chancesTotales)
   {
      textcolor(RED);
      printf("%c", 88);
      textcolor(WHITE);
   }
}