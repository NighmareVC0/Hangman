// Librerías
#include <conio.c>
#include <ctype.h>
#include <math.h>
#include <time.h>
// Mapeo de Teclas
#define ESC 27
#define BKSP 8
#define ONE 49
#define TWO 50
#define ENTER 13
#define SPCE 32
#define ASTRK 42
#define END '\0'
// Colores
#define WINCOL GREEN
#define LOSSCOL RED
// Tamaño máximo de
#define MAX 35
#define POINTS 6
// Boolean
#define TRUE 1
#define FALSE 0
// Caracter Inicial
#define INITIAL 32
// Dibujo del Ahorcado
#define BASE 193
#define HOR 196
#define VER 179
#define ESQIZQ 218
#define ESQDER 191
// Módulos int
int score(char);
int verifUsed(char[], char);
int getChances(char[]);
int quantVowels(char[]);
// Módulos void
void showDraw(int, int);
void setTemp(char[], char[]);
void getText(char[]);
void showTime(int);
void setUsed(char[]);
void clearStr(char[], int);
void showWord(char[], int, int);
void setNonRep(char[], char[]);

int main()
{
   int correct, repeated, usedPos, points, totalPoints, timer, lives,
       row, rowPoints, tempPoints, failed, totalLives, win;
   char word[MAX], temp[MAX], chr;
   do
   {
      correct = repeated = usedPos = points = totalPoints = timer = lives =
          row = rowPoints = tempPoints = failed = totalLives = win = 0;
      word[0] = END, temp[0] = END;
      _setcursortype(0);
      system("cls");
      printf("Bienvenido a %cEl Ahorcado%c\n\nMen%c:\n1. Jugar\n2. Salir\n", 34, 34, 163);
      chr = getche();
      if (chr == ONE)
      {
         system("cls");
         gotoxy(40, 13);
         printf("Ingrese una palabra: ");
         getText(word);
         setTemp(temp, word);
         chr = INITIAL;
         timer = time(NULL);
         lives = getChances(word);
         totalLives = lives;
         char usadas[MAX] = "";

         do
         {
            _setcursortype(0);
            repeated = verifUsed(usadas, chr);
            if (!repeated)
            {
               correct = FALSE;
               usadas[usedPos++] = chr;
               for (int pos = 0; word[pos]; pos++)
               {
                  if (chr == word[pos])
                  {
                     temp[pos] = chr;
                     correct = TRUE;
                  }
               }
               if (correct && chr != INITIAL)
               {
                  points = 0;
                  points = score(chr);
                  totalPoints += points;
                  tempPoints += points;
                  row++;
                  if (row > 1)
                  {
                     rowPoints = tempPoints;
                     totalPoints += rowPoints;
                  }
               }
               if (!correct && chr != INITIAL)
               {
                  lives--;
                  failed++;
                  points = 0;
                  tempPoints = 0;
                  rowPoints = 0;
                  row = 0;
               }
            }
            else
            {
               gotoxy(30, 12);
               printf("Ya se ha utilizado el caracter \"%c\".", chr);
            }
            if (!strcmp(word, temp))
            {
               win = 1;
               gotoxy(30, 8);
               puts(temp);
               gotoxy(30, 13);
               textcolor(GREEN);
               printf("%cFelicidades, has ganado%c\n", 173, 33);
               textcolor(WHITE);
               gotoxy(30, 14);
               system("pause");
               system("cls");
               printf("%cFelicidades, has ganado%c\n", 173, 33);
               printf("La palabra era: \"%s\"\n", word);
               printf("Con un total de:\n");
               printf("Puntos totales: %d\n", totalPoints);
               printf("Vidas restantes: %d\n", lives);
               printf("Racha actual: %d\n", row);
               system("pause");
            }
            if (!repeated)
            {
               system("cls");
               showDraw(failed, totalLives);
               gotoxy(30, 8);
               puts(temp);
               gotoxy(30, 1);
               printf("Vidas Restantes: %d", lives);
               gotoxy(1, 1);
               printf("Tiempo: ");
               gotoxy(1, 14);
               printf("Racha Actual: %d", row);
               gotoxy(30, 5);
               printf("Caracteres usados: %s", usadas);
               gotoxy(1, 16);
               printf("Puntos obtenidos: %d", points);
               gotoxy(1, 17);
               printf("Puntos de racha : %d", rowPoints);
               gotoxy(1, 18);
               printf("Puntos totales  : %d", totalPoints);
               gotoxy(30, 11);
               printf("Introduzca un caracter: ");
               gotoxy(9, 1);
               showTime(time(NULL) - timer);
            }
            if (!lives)
            {
               gotoxy(30, 12);
               textcolor(RED);
               printf("Mala suerte, has perdido.");
               textcolor(WHITE);
               gotoxy(30, 13);
               system("pause");
               system("cls");
               printf("Mala suerte, has perdido.\n");
               printf("La palabra era: \"%s\"\n", word);
               printf("Con un total de:\n");
               printf("Puntos totales: %d\n", totalPoints);
               system("pause");
            }

            if (lives && strcmp(word, temp))
            {

               gotoxy(54, 11);
               putchar(chr);
               gotoxy(54, 11);
               _setcursortype(1);
               do
               {
                  fflush(stdin);
                  chr = tolower(getch());
               } while (!isalpha(chr) && chr != ESC);
               if (chr == ESC)
                  win = 1;
            }
         } while (lives > 0 && chr != ESC && !win);
      }
      else if (chr == TWO)
      {
         system("cls");
         printf("%cGracias por jugar%c\n", 173, 33);
         system("pause");
         return 0;
      }

   } while (chr != ONE || chr != TWO);
}
/*
Función:    getText
Argumento:  char word[], Palabra a ingresar por el usuario.
Objetivo:   Obtener la palabra con la que se va a jugar.
Retorno:    Ninguno.
*/
void getText(char word[])
{
   int pos = 0;
   char chr, temp[MAX] = "\0";
   do
   {
      do
      {
         do
         {
            fflush(stdin);
            chr = tolower(getch());
         } while (!isalpha(chr) && chr != ENTER && chr != BKSP);

         if (chr == BKSP)
         {
            if (pos)
            {
               pos--;
               temp[pos] = SPCE;
            }
         }
         else if (chr != ENTER)
         {
            word[pos] = chr;
            if (chr != SPCE)
               temp[pos] = ASTRK;
            else
               temp[pos] = SPCE;
            pos++;
         }
         showWord(temp, 61, 13);
      } while (chr != ENTER);
   } while (!isalpha(word[0]));
   word[pos] = END;
   temp[pos] = END;
   return;
}
/*
Función:    showWord
Argumento:  char word[], cadena a imprimir.
            int xPos, posición en X a imprimir.
            int yPos, posición en Y a imprimir.

Objetivo:   Imprimir una cadena.
Retorno:    Ninguno.
*/
void showWord(char word[], int xPos, int yPos)
{
   for (int pos = 0; word[pos]; pos++)
   {
      if (word[pos])
         printf("%c", word[pos]);
      gotoxy((xPos + (pos + 1)), yPos);
   }
   return;
}
/*
Función:    setTemp
Argumento:  char temp[], será la cadena que tendrá los '*' asteriscos.
            char word[], es la cadena que contiene la palabra digitada por el usuario.

Objetivo:   Crear la cadena temporal.
Retorno:    Ninguno.
*/
void setTemp(char temp[], char word[])
{
   int pos;
   for (pos = 0; word[pos]; pos++)
   {
      if (word[pos] != SPCE)
         temp[pos] = ASTRK;
      else
         temp[pos] = SPCE;
   }
   temp[pos] = END;
   return;
}
/*
Función:    getChances
Argumento:  char word[], palabra a evaluar.
Objetivo:   Obtener la cantidad de vidas que tendrá el jugador.
Retorno:    int Cantidad de vidas.
*/
int getChances(char word[])
{
   char used[MAX] = " ";
   setNonRep(word, used);
   int quantVow = quantVowels(used);
   return round(((strlen(used) - quantVow) * (60.0 / 100)) + (quantVow / 2));
}
/*
Función:    setNonRep
Argumento:  char word[], cadena a evaluar.
            char used[], cadena a convertir en una cadena sin repetición.

Objetivo:   Crear una cadena sin repetición de caracteres.
Retorno:    Ninguno.
*/
void setNonRep(char word[], char used[])
{
   int usedPos = 0;
   for (int pos = 0; word[pos]; pos++)
      for (int ind = 0, cont = 0; used[ind]; ind++)
         if (word[pos] != SPCE)
         {
            if (word[pos] != used[ind])
               cont++;
            if (used[cont] == 0)
               used[usedPos++] = word[pos];
         }
   used[usedPos] = END;
   return;
}
/*
Función:    quantVowels
Argumento:  char used[], cadena a evaluar.

Objetivo:   Contar las vocales de una cadena.
Retorno:    Cantidad de vocales.
*/
int quantVowels(char used[])
{
   int total = 0;
   char vocales[5] = "aeiou";
   for (int pos = 0; used[pos]; pos++)
      for (int ind = 0; vocales[ind]; ind++)
         if (used[pos] == vocales[ind])
            total++;
   return total;
}
/*
Función:    verifUsed
Argumento:  char cadena[], Cadena a evaluar.
            char chr,  caracter a evaluar.

Objetivo:   Verificar si el chr ya se encuentra en la cadena.
Retorno:    int true or false
*/
int verifUsed(char cadena[], char chr)
{
   for (int pos = 0; cadena[pos]; pos++)
      if (chr == cadena[pos])
         return 1;
   return 0;
}
/*
Función:    showTime
Argumento:  int seg, Segundos a evaluar.
Objetivo:   Obtener y mostrar el tiempo actual.
Retorno:    Ninguno.
*/
void showTime(int seg)
{
   int min, hour;

   min = (seg / 60);
   seg -= (min * 60);
   hour = (min / 60);
   seg -= (hour * 3600);
   printf("%02d:%02d:%02d", hour, min, seg);
   return;
}
/*
Función:    score
Argumento:  char chr. Carácter a evaluar.
Objetivo:   Obtener los puntos de caracter acertado.
Retorno:    int Puntos obtenidos por el caracter.
*/
int score(char chr)
{
   int pos;
   char pts20[POINTS] = "aeioc", pts25[POINTS] = "udlpr", pts30[POINTS] = "btfmn", pts35[POINTS] = "ghjqv", pts40[POINTS] = "kwxyz";
   for (pos = 0; pts20[pos]; pos++)
      if (chr == pts20[pos])
         return 20;

   for (pos = 0; pts25[pos]; pos++)
      if (chr == pts25[pos])
         return 25;

   for (pos = 0; pts30[pos]; pos++)
      if (chr == pts30[pos])
         return 30;

   for (pos = 0; pts35[pos]; pos++)
      if (chr == pts35[pos])
         return 35;

   for (pos = 0; pts40[pos]; pos++)
      if (chr == pts40[pos])
         return 40;
}
/*
Función:    showDraw
Argumento:  int failed, cantidad de veces falladas.
            int totalLives, cantidad de vidas disponibles.

Objetivo:   Dibujar al muñeco en proporciones
Retorno:    Ninguno.
*/
void showDraw(int failed, int totalLives)
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
   // cabeza
   gotoxy(15, 5);
   printf("%c", failed >= (0.14 * totalLives) ? 79 : 32);
   // cuerpo
   gotoxy(15, 6);
   printf("%c", failed >= (0.28 * totalLives) ? 179 : 32);
   // brazos
   gotoxy(14, 5);
   printf("%c", failed >= (0.42 * totalLives) ? 92 : 32); // izquierdo
   gotoxy(16, 5);
   printf("%c", failed >= (0.56 * totalLives) ? 47 : 32); // derecho
   // piernas
   gotoxy(14, 7);
   printf("%c", failed >= (0.70 * totalLives) ? 47 : 32); // izquierdo
   gotoxy(16, 7);
   printf("%c", failed >= (0.84 * totalLives) ? 92 : 32); // derecho
   // ahorcado
   gotoxy(15, 5);
   if (failed == totalLives)
   {
      textcolor(RED);
      printf("%c", 88);
      textcolor(WHITE);
   }
   return;
}
