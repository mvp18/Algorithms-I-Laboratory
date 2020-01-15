#include <iostream>
#include <stdlib.h> 
#include <time.h>
using namespace std;

extern void registerme ( );
extern void startgame ( int );
extern int guess ( int );
extern void verifysoln ( int );

/* Linear search */
int playgame1 ()
{
   int a;

   startgame(1);
   for (a=1; a<=100000000; ++a) {
      if (guess(a) == 1) return a;
   }
   return 0;
}

/* Random search */
int playgame2 ()
{
   int a;

   startgame(2);
   while (1) {
      a = 1 + rand() % 100000000;
      if (guess(a) == 1) return a;
   }
}

/* ~ 2 lg N search */
int playgame3 ()
{
   int L, R, M;
   int d1, d2;

   startgame(3);
   L = 1; R = 100000000;
   while (L < R) {
      d1 = guess(L); if (d1 == 1) return L;
      d2 = guess(R); if (d2 == 1) return R;
      M = (L + R + 1) / 2;
      if (d2 == 2) L = M; else R = M-1;
   }
   return L;
}

/* ~ lg N search */
int playgame4 ()
{
   int L, R;  /* The current search interval [L,R] contains a4 */
   int P;     /* The previous guess */
   int G;     /* The current guess */
   int d;

   startgame(4);

   /* Initially L = 1, R = 100000000. Make the first guess at L */
   P = L = 1; d = guess(L); if (d == 1) return L;
   R = 100000000;

   /* Repeat until the search interval reduces to only one element */
   while (L < R) {
      /* All guesses lie outside the open interval (L,R). It is allowed
         to have a guess < L or > R. The black box still provides hints.
         In order to make a new guess G, look at the previous guess P.
         Place G equidistant from (the center of) [L,R] on the opposite
         side of P. That is, if the previous query was L - D for some
         D >= 0, then the current query should be R + D, and conversely.
         Since L and R change from iteration to iteration, the distance
         D is to be calculated dynamically. */
      if (P <= L) {
         G = R + (L - P);
         d = guess(G); if (d == 1) return G;
         if (d == 2) L = (L + R + 1) / 2; else R = (L + R - 1) / 2;
      } else if (P >= R) {
         G = L - (P - R);
         d = guess(G); if (d == 1) return G;
         if (d == 2) R = (L + R) / 2; else L = (L + R) / 2 + 1;
      } else {
         cout << "*** This case should not have occurred" << endl;
         return 0;
      }
      P = G; /* The current guess is the previous guess in the next iteration */
   }
   return L;
}

int main ()
{
   int a1, a2, a3, a4;
   clock_t c1, c2;

   registerme();

   c1 = clock(); a1 = playgame1(); c2 = clock();
   cout << "\n+++ Game 1\n    a1 = " << a1 << endl;
   cout << "    Time taken = " << (double)(c2-c1)/(double)CLOCKS_PER_SEC << "sec" << endl;
   verifysoln(a1);

   c1 = clock(); a2 = playgame2(); c2 = clock();
   cout << "\n+++ Game 2\n    a2 = " << a2 << endl;
   cout << "    Time taken = " << (double)(c2-c1)/(double)CLOCKS_PER_SEC << "sec" << endl;
   verifysoln(a2);

   c1 = clock(); a3 = playgame3(); c2 = clock();
   cout << "\n+++ Game 3\n    a3 = " << a3 << endl;
   cout << "    Time taken = " << (double)(c2-c1)/(double)CLOCKS_PER_SEC << "sec" << endl;
   verifysoln(a3);

   c1 = clock(); a4 = playgame4(); c2 = clock();
   cout << "\n+++ Game 4\n    a4 = " << a4 << endl;
   cout << "    Time taken = " << (double)(c2-c1)/(double)CLOCKS_PER_SEC << "sec" << endl;
   verifysoln(a4);
}