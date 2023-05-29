# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# define N 1000
# define MW 10

/* M1 =10; M2 =8; M3 =6; M4 =4; M5 =2;
W1 =9; W2 =7; W3 =5; W4 =3; W5 =1;
*/
void arand ( int a [] , int n ){
int i , k , tmp ;
for ( i = 0; i < n ; i ++) a [ i ] = i + 1;
for ( i = n - 1; i > 0; i--){
k = rand () % i ;
tmp = a [ i ];
a [ i ] = a [ k ];
a [ k ] = tmp ;
}
}
int hjudge ( int a [] , int n ){
int i , j , max ;
max = 0;
for ( i = 0; i < n ; i ++){
if ( a [ i ] > max ){
if ( a [ i ] % 2 == 0) max = a [ i ];
else return 0;
}
}
return 1;
}
int main ( int argc , char * argv []){
int n , i , j , k , tmp , hsuc , err , max ;
int h [ MW ];
hsuc = 0;
srand ( time ( NULL ));
for ( n = 0; n < N ; n ++){
arand (h , MW );
hsuc += hjudge (h , MW );
}
printf ("%d \n " , hsuc );
}