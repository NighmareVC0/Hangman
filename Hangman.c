// Includes
#include <conio.c>
#include <ctype.h>
#include <math.h>
#include <time.h>
// Key Bindings
#define ESC 27
#define BKSP 8
#define ONE 49
#define TWO 50
#define ENTER 13
#define SPCE 32
#define ASTRK 42
#define END '\0'
// Colors
#define WINCOL GREEN
#define LOSSCOL RED
// Max size of
#define MAX 35
#define POINTS 6
// Boolean
#define TRUE 1
#define FALSE 0
// Initial character
#define INITIAL 32
// Hangman draw
#define BASE 193
#define HOR 196
#define VER 179
#define ESQIZQ 218
#define ESQDER 191
// int modules
int score(char);
int checkUsed(char[], char);
int getLives(char[]);
int quantVowels(char[]);
// void modules
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
      printf("Welcome to %cThe Hangman%c\n\nMenu:\n1. Play\n2. Exit\n", 34, 34);
      chr = getche();
      if (chr == ONE)
      {
         system("cls");
         gotoxy(40, 13);
         printf("Enter a Word: ");
         getText(word);
         setTemp(temp, word);
         chr = INITIAL;
         timer = time(NULL);
         lives = getLives(word);
         totalLives = lives;
         char usadas[MAX] = "";

         do
         {
            _setcursortype(0);
            repeated = checkUsed(usadas, chr);
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
               printf("This character is already used \"%c\".", chr);
            }
            if (!strcmp(word, temp))
            {
               win = 1;
               gotoxy(30, 8);
               puts(temp);
               gotoxy(30, 13);
               textcolor(GREEN);
               printf("%cCongratulations, you won%c\n", 173, 33);
               textcolor(WHITE);
               gotoxy(30, 14);
               system("pause");
               system("cls");
               printf("%cCongratulations, you won%c\n", 173, 33);
               printf("The word was: \"%s\"\n", word);
               printf("With a total of:\n");
               printf("Total points: %d\n", totalPoints);
               printf("Left lives: %d\n", lives);
               printf("Current row: %d\n", row);
               system("pause");
            }
            if (!repeated)
            {
               system("cls");
               showDraw(failed, totalLives);
               gotoxy(30, 8);
               puts(temp);
               gotoxy(30, 1);
               printf("Left lives: %d", lives);
               gotoxy(1, 1);
               printf("Time: ");
               gotoxy(1, 14);
               printf("Current row: %d", row);
               gotoxy(30, 5);
               printf("Used characters: %s", usadas);
               gotoxy(1, 16);
               printf("Points earned : %d", points);
               gotoxy(1, 17);
               printf("Row points    : %d", rowPoints);
               gotoxy(1, 18);
               printf("Total points  : %d", totalPoints);
               gotoxy(30, 11);
               printf("Enter a character: ");
               gotoxy(9, 1);
               showTime(time(NULL) - timer);
            }
            if (!lives)
            {
               gotoxy(30, 12);
               textcolor(RED);
               printf("Bad luck, you lost.");
               textcolor(WHITE);
               gotoxy(30, 13);
               system("pause");
               system("cls");
               printf("Bad luck, you lost.\n");
               printf("The word was: \"%s\"\n", word);
               printf("With a total of:\n");
               printf("Total points: %d\n", totalPoints);
               system("pause");
            }

            if (lives && strcmp(word, temp))
            {

               gotoxy(49, 11);
               putchar(chr);
               gotoxy(49, 11);
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
         printf("%cThanks for playing%c\n", 173, 33);
         system("pause");
         return 0;
      }

   } while (chr != ONE || chr != TWO);
}
/*
Module:     getText
Arguments:  char word[], word to be ingresen by the player.
Objetive:   to get the original word to be used in the game.
Return:     None.
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
         showWord(temp, 53, 13);
      } while (chr != ENTER);
   } while (!isalpha(word[0]));
   word[pos] = END;
   temp[pos] = END;
   return;
}
/*
Module:     showWord
Arguments:  char word[], string to be printed.
            int xPos, horizontal plane's position to be printing.
            int yPos, vertical plane's position to be printing.

Objetive:   to print the string.
Return:     None.
*/
void showWord(char word[], int xPos, int yPos)
{
   for (int pos = 0; word[pos]; pos++)
   {
      gotoxy((xPos + (pos + 1)), yPos);
      if (word[pos])
         printf("%c", word[pos]);
   }
   return;
}
/*
Module:     setTemp
Arguments:  char temp[], it would be the string which contains '*'.
            char word[], the string that has the original word.

Objetive:   to create the temporal string.
Return:     None.
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
Module:     getLives
Arguments:  char word[], string to be evaluated.
Objetive:   to get the amount of lives the player will have.
Return:     int quantity of lives.
*/
int getLives(char word[])
{
   char used[MAX] = " ";
   setNonRep(word, used);
   int quantVow = quantVowels(used);
   return round(((strlen(used) - quantVow) * (60.0 / 100)) + (quantVow / 2));
}
/*
Module:     setNonRep
Arguments:  char word[], string to be evaluated.
            char used[], string to turn into a non repiten characters.

Objetive:   to create a string with no repetitions of characters.
Return:     None.
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
Module:     quantVowels
Arguments:  char used[], string to be evaluated.

Objetive:   to count the amount of vowels the string has.
Return:     int quantity of vowels.
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
Module:     checkUsed
Arguments:  char cadena[], string to be evaluated.
            char chr, character to be evaluated.

Objetive:   to check if the character 'chr' is already used.
Return:     int true or false
*/
int checkUsed(char cadena[], char chr)
{
   for (int pos = 0; cadena[pos]; pos++)
      if (chr == cadena[pos])
         return 1;
   return 0;
}
/*
Module:     showTime
Arguments:  int seg, seconds to be evaluated.
Objetive:   to get and show the current time lapsed.
Return:     None.
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
Module:     score
Arguments:  char chr, character to be evaluated.
Objetive:   to get the amount of points earned by the correct character.
Return:     int amount of point gotten.
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
Module:     showDraw
Arguments:  int failed, total of failures.
            int totalLives, total amount of lives.
Objetive:   to draw the hangman on proportions.
Return:     None.
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
   // head
   gotoxy(15, 5);
   printf("%c", failed >= (0.14 * totalLives) ? 79 : 32);
   // body
   gotoxy(15, 6);
   printf("%c", failed >= (0.28 * totalLives) ? 179 : 32);
   // arms
   gotoxy(14, 5);
   printf("%c", failed >= (0.42 * totalLives) ? 92 : 32); // left one
   gotoxy(16, 5);
   printf("%c", failed >= (0.56 * totalLives) ? 47 : 32); // right one
   // legs
   gotoxy(14, 7);
   printf("%c", failed >= (0.70 * totalLives) ? 47 : 32); // left one
   gotoxy(16, 7);
   printf("%c", failed >= (0.84 * totalLives) ? 92 : 32); // right one
   // hang
   gotoxy(15, 5);
   if (failed == totalLives)
   {
      textcolor(RED);
      printf("%c", 88);
      textcolor(WHITE);
   }
   return;
}