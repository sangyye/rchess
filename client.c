#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <unistd.h>
#include "chess.h"


void printBoard(board *b);

int main(int argc, char **argv) {
/* Baue Verbindung auf 
   Regestriere dich beim Server 
   Hole dir das initial Board 
   do 
   while(!(Bin ich dran?)) 
    
	Aktualisiere Brett 
	Bewege Figur
	Aktualisiere Brett 
	Nächster Spieler 
   while ( spiel nicht zu ende, oder abbruch ) 
*/

 CLIENT *cl;
 board *b;
 movefunc_arg moveit;
 boardfunc_arg boardfunc;   
 playerfunc_arg player; 
 boardret_arg *ret; 
 char arg,check,*side, *pos,*ret_player,a_geschlagen,b_geschlagen; 
 int i; 
 
 /* Verbindung zum Server */ 
 cl = clnt_create("127.0.0.1", CHESS_PROG, CHESS_VERS, "tcp"); 
 if ( cl == NULL) { 
	clnt_pcreateerror("127.0.0.1"); 
	return -1; 
	}
 /* Regestriere beim Server */ 
 arg = '0'; 
 side = manageplayer_1(&arg,cl); 
 if ( side == NULL) { 
	clnt_perror(cl,"manageplayer_1"); 
	return -1; 
 }
 moveit.currentplayer = *side;
 if ( *side == '0') { 
	perror("server ausgelastet"); 
	return -1;
 }
 /* init board */ 
 b = initialboard_1((void *)1, cl);
 if ( b == NULL) { 
	clnt_perror(cl,"initialboard_1"); 
	return -1; 
 }
  /* zug um zug */ 
  pos = (char *) malloc (3 * sizeof(char)) ;
  check = '0';
  a_geschlagen ='1'; 
  b_geschlagen ='1';
  do{
	/* Bin ich dran ?? */ 
	player.currentplayer = *side;
	player.func = 0;
	ret_player = currentplayer_1(&player,cl);  
  	while( *ret_player != *side ){ 
		ret_player = currentplayer_1(&player,cl);
		if ( ret_player == NULL) { 
			clnt_perror(cl,"ret_player");
			return -1;
		}
		sleep(1); 	
		}
	
	/* GET BOARD */ 
	if ( check != '0' || *side =='2') { 
		boardfunc.func = 0; 
		b = manageboard_1(&boardfunc,cl);
		if( b == NULL) { 
			clnt_perror(cl,"manageboard"); 
			return -1; 
		}
		}
	
	printBoard(b);
	do{ 
	/* Alte Position */ 
	printf("Alte Position eingeben: [a-h][1-8]\n"); 
	
	do{ 
	check = '0';
	fgets(pos,3,stdin);
	moveit.pos_old.x = pos[0] % 97 ; 
	moveit.pos_old.y = 7-(pos[1] % 49); 
	if((moveit.pos_old.x >= 0 && moveit.pos_old.x < 8) && (moveit.pos_old.y >= 0 && moveit.pos_old.y < 8 )) 
		check = '1';
	}while(check == '0');
	/* 
	NEUE POSITION 
	*/
	printf("Neue Position eingeben: [a-h][1-8]\n"); 	
	do{ 
	check='0';
	fgets(pos,3,stdin); 
	moveit.pos_new.x = pos[0] % 97; 
	moveit.pos_new.y = 7-(pos[1] % 49); 
	if((moveit.pos_new.x >= 0 && moveit.pos_new.x < 8) && (moveit.pos_new.y >= 0 && moveit.pos_new.y < 8))
		check ='1';
	}while(check == '0'); 
	
	for(i=0; i < 64; i++) 
		moveit.spielfeld.field[i] = b->field[i];
	ret = movepieces_1(&moveit,cl);
	if(ret == NULL) { 
		clnt_perror(cl,"movepieces");
		return -1;
	} 
	if(ret->ret == '0') 
		printf("Falsche Position, Feld besetzt, Weg blockiert\n");
	if(ret->ret == '2') 
		printf("SCHACH\n");
	}while((ret->ret == '0') || (ret->ret == '2'));
	
	printBoard(&ret->gameBoard); 
	
	/* set Board */ 
	boardfunc.func = 1; 
	for(i=0; i < 64; i++) 
		boardfunc.gameBoard.field[i] = ret->gameBoard.field[i]; 
	b = manageboard_1(&boardfunc,cl); 
	if ( b == NULL) { 
		clnt_perror(cl,"manageboard");
		return -1;
	}
	/* Wechsel den Spieler */
	player.func = 1; 
	if (*side == '1') 
		player.currentplayer = '2';
	else
		player.currentplayer = '1';
	ret_player = currentplayer_1(&player,cl);
	if (ret_player == NULL) { 
		clnt_perror(cl,"currentplayer"); 
		return -1; 
	}
	printf("\n");	
		
	}while(1 == 1);
  

 return 0; 
}

void printBoard(board *b){
        int i;
        printf("      a      b     c      d      e      f      g      h  \n");
        printf("8  ");
	for(i=0; i < 64; i++) { 
                if(b->field[i] == 1) 
			printf("  wb   "); 
		if(b->field[i] == 2) 
			printf("  wl   ");
		if(b->field[i] == 3)
			printf("  ws   "); 
		if(b->field[i] == 4)
			printf("  wt   "); 
		if(b->field[i] == 5)
			printf("  wd   "); 
		if(b->field[i] == 6) 
			printf("  wk   "); 
		if(b->field[i] == 11) 
			printf("  sb   "); 
		if(b->field[i] == 12)
			printf("  sl   "); 
		if(b->field[i] == 13)
			printf("  sp   "); 
		if(b->field[i] == 14) 
			printf("  st   "); 
		if(b->field[i] == 15)
			printf("  sd   "); 
		if(b->field[i] == 16) 
			printf("  sk   "); 
            	if(b->field[i] == 0)
			printf("   .   ");
		if(i == 7)
                  printf("\n7  ");
                if(i == 15)
                  printf("\n6 ");
                if(i == 23)
                  printf("\n5 ");
                if(i == 31)
                 printf("\n4 ");
                if(i == 39)
                 printf("\n3 ");
                if(i == 47)
                 printf("\n2  ");
                if(i == 55)
                 printf("\n1  ");
	        if(i == 63)
                 printf("\n    ");
        }
}
