#include <iostream>
using namespace std;

#define N 1000000000

extern void registerme ( );
extern void startgame ( int );
extern int valquery ( int );
extern int sgnquery ( int );
extern int delquery ( int );
extern int sumquery ( int );
extern void checksoln ( int, int );

void playgame0 ()
{
   int query, resp;
   int L, R;

   L = R = -1;
   startgame(0);
   for (query=0; query<N; ++query) {
      resp = valquery(query);
      if (resp != query) {
         L = query;
         R = resp;
         break;
      }
   }
   checksoln(L,R);
}

void recsearch ( int l, int r, int *L, int *R )
{
   int query, resp;

   if ((l > r) || (*L >= 0)|| (*R >= 0)) return;
   query = (l + r) / 2;
   resp = valquery(query);
   if (resp < query) {
      *L = resp; *R = query;
   } else if (resp > query) {
      *L = query; *R = resp;
   } else {
      recsearch(l,query-1,L,R);
      recsearch(query+1,r,L,R);
   }
}

void playgame1 ()
{
   int L, R;

   startgame(1);
   L = R = -1;
   recsearch(0,N-1,&L,&R);
   checksoln(L,R);
}

void playgame2 ()
{
   int l, r, query, resp;
   int L, R;

   startgame(2);
   l = 0; r = N-1;
   while (l < r) {
      query = (l + r) / 2;
      resp = sgnquery(query);
      if (resp == 0) { l = r = query; }
      else if (resp == -1) {
         l = query + 1;
      } else {
         r = query-1;
      }
   }
   l *= 2;
   r = delquery(0);
   R = (l + r) / 2; L = R - r;
   checksoln(L,R);
}

/* Let us see what the sum query returns for a query q in the range
   [0,N-1]. At q = 0, the return value is L+R. Then, as you increase
   q by 1, the return value decreases by 2. This behavior continues
   until q becomes L (this range of q will be called the left hill).
   For L <= q <= R, the return value remains constant at R-L (call
   this region the valley). For q >= R, the return value keeps on
   increasing by two for each increase in q (this range of q will be
   called the right hill). At q = N-1, the return value reaches
   (N-1-L)+(N-1-R)=2(N-1)-(L+R). A query on q = 0 (or N-1) gives you
   the value of R+L. A binary search eventually lets you land in
   the valley, where you get the return value R-L (for any query in
   the valley). Solve for L and R from these two equations. */
void playgame3 ( )
{
   int query, resp;
   int L, R;
   int l, r;
   int U, V;

   startgame(3);
   U = sumquery(0);   /* L+R */
   V = 2*(N-1) - U;   /* 2(N-1)-(L+R) */
   l = 0; r = N-1;
   while (l < r) {
      query = (l + r) / 2;
      resp = sumquery(query);
      if (resp == U - 2*query) l = query + 1;             /* query is in left hill */
      else if (resp == V - 2*(N-1-query)) r = query - 1;  /* query is in right hill */
      else l = r = query;                                 /* query is in the valley */
   }
   V = sumquery(l);   /* R-L */
   R = (U + V) / 2; L = (U - V) / 2;
   checksoln(L,R);
}

/* sumquery(0) returns L+R. This response divided by two must lie in the
   valley. */
void playgame3_2queries ( )
{
   int L, R;
   int U, V;

   startgame(3);
   U = sumquery(0);
   V = sumquery(U/2);
   R = (U + V) / 2; L = (U - V)/2;
   checksoln(L,R);
}

int main ()
{
   registerme();
   playgame0();
   playgame1();
   playgame2();
   playgame3();
   playgame3_2queries();
}