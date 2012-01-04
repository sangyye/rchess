#include <stdio.h>
#include <stdlib.h>
#include "chess.h"

void printBoard(board *b);

int main(int argc, char **argv) {
/* Baue Verbindung auf 
   Regestriere dich beim Server 
   Hole dir das initial Board 
   do 
   while(!(Bin ich dran?)) 
   while(1) 
	Aktualisiere Brett 
	Bewege Figur
	Aktualisiere Brett 
	Nächster Spieler 
*/
 /* 
	DECLARE 
 */
 CLIENT *cl;
 board *b;
 char *side; 
 char arg; 
 int i;
 arg = '0';

 cl = clnt_create("127.0.0.1", CHESS_PROG, CHESS_VERS,"tcp");
 if (cl == NULL) {
        clnt_pcreateerror("127.0.0.1");
        return 2;
        }
 side = manageplayer_1(&arg, cl);
 if ( side == NULL) {
        clnt_perror(cl,"manageplayer_1");
        return 3;
 }
 
 b = initialboard_1((void *)1, cl);
 if ( b == NULL) {
        clnt_perror(cl,"initalboard_1");
        return 3;
 }
 printf("\n %s \n", side);
 printBoard(b); 

 while(1)
  i++;
 
 return 0;
}

void printBoard(board *b){
        int i;
        printf("    a  b  c  d  e  f  g  h \n");
	printf("8 ");
        for(i=0; i < 64; i++) { 
		printf(" %d ",b->field[i]);
		if(i == 7)
		  printf("\n7 ");
		if(i == 15)
		  printf("\n6 ");
		if(i == 23)
		  printf("\n5 ");
	        if(i == 31)
                 printf("\n4 ");
                if(i == 39)
                 printf("\n3 ");
                if(i == 47)
                 printf("\n2 ");
                if(i == 55)
                 printf("\n1 ");
		if(i == 63)
		 printf("\n ");
	}
	/* for(i=0; i < 8; i++){
               printf("%d  ",(8-i));
                for(j=0; j < 8;  j++){
				printf(" %d ",b->field[(8*i) + j]);
			
		}
        	printf("\n");
	}*/
		
}
