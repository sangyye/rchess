#include <stdio.h>
#include "chess.h"

/* DEF */
#define GETCURRENTPLAYER 0
#define SETCURRENTPLAYER 1 
#define GETBOARD 0
#define SETBOARD 1
#define WEISS '1' 
#define SCHWARZ '2'
#define WBAUER 1 
#define WLAEUFER 2
#define WSPRINGER 3
#define WTURM 4 
#define WDAME 5
#define WKOENIG 6
#define SBAUER 11
#define SLAEUFER 12
#define SSPRINGER 13
#define STURM 14 
#define SDAME 15 
#define SKOENIG 16

static int calcPos(position act) { 
	return ((act.y)*8 + act.x);

}

static char occupied(char currentplayer,position next,board game) { 
	/* 
		output: 0 Feld leer 
		output: 1 Feld besetzt, eigene Farbe 
		output: 2 Feld besetzt, gegnerische Farbe
	*/
	char res='3';
	int nextPos = calcPos(next);
	if(game.field[nextPos] == 0)
		res ='0';
	
	if ((currentplayer == '1') && ( res != '0')){ 
	 
		if (game.field[nextPos] < 10)
			res ='1'; 		
		else  
			res ='2'; 
		
	}
	if((currentplayer =='2') && ( res != '0')){ 
	
		if(game.field[nextPos] > 10) 
			res ='1'; 
	
		else  
			res ='2';  
	}
 return res;
}

static char moveBauer(char currentplayer, position act, position next,board game){ 
	/* input: 
		currentplayer, act pos, next pos, gameboard 
	   next pos ok? 
	   output: 
		0 besetzt, inkorrekte pos
		1 ok, geschlagen
	*/
	char res='9';
	char occ=occupied(currentplayer,next,game);
	
	if( occ =='1' ) 
		res = '0'; 
	else { 
		/* WEIß */ 
		if (currentplayer == '1') { 
			/* FELD drüber frei ? */ 
			if(next.x == act.x) {
				if((act.y == 1) && (next.y == 3) && (occ=='0'))
					res ='1';
				if((next.y == (act.y+1)) && res =='9'){
					if(occ == '0' && res =='9') 
						res = '1';
					else 
						res = '0';
				} 
				else 
					res = '0';
		}
			/* GESCHLAGEN */ 
		if( res == '9') { 
			if((next.x == act.x+1) && (next.y == act.y+1) && ( occ =='2')) 
				res='1';
			if((next.x == act.x-1) && (next.y == act.y+1) && ( occ == '2'))
				res='1';
			if ( res !='1')
				res='0'; 
		}
	}
		/* SCHWARZER BAUER */ 
		if ( currentplayer == '2') { 
		if ( next.x == act.x) {  
			if((act.y == 6) && ( next.y == 4) && (occ == '0'))
				res='1';
			
			if(next.y == (act.y-1) && (res=='9')){ 
					if ( occ == '0' && res =='9') 
						res = '1';
					else 
						res ='0';
				}
				else 
				res='0';
		}
			if(res == '9') {
			if((next.x == act.x+1) && (next.y == act.y-1) && ( occ =='2')) 
			res='1'; 
			if((next.x == act.x-1) && (next.y == act.y-1) && ( occ =='2'))
			res='1';
			if(res !='1')
			res='0';	          
			}
 		}
	}
	return res;
}

static char moveLaeufer(char currentplayer, position act, position next,board game){ 
	/* 
		Ziel korrekt ?  
	   	Prüfe Weg zum Ziel
		Weg blockiert? 
		Out : 
			0 : Eigene Figur, Ziel inkorrekt
			1 : Ziel erreicht, Platziere an neuer pos
			
	*/	
	char res,occ; 
	position act_tmp, next_tmp;
	res = '9';
	act_tmp.x = act.x;
	act_tmp.y = act.y;
	next_tmp.x = next.x;
	next_tmp.y = next.y;
	
	/* 4 Mögliche Fälle 
		   x, y 
		1. +, + 	
		2. +, - 
		3. -, - 
		4. -, + 
	*/
	/* 1. Fall 
		act.x < next.x
		act.y < next.y
	*/ 

	if((act.x < next.x) && ( act.y < next.y) && (res == '9')) {
		while( (act_tmp.x < next_tmp.x) && (act_tmp.y < next_tmp.y)) { 
			act_tmp.x +=1; 
			act_tmp.y +=1; 
			occ = occupied(currentplayer,act_tmp,game);
			if (occ != '0') 
				break;	 
		}
		if((act_tmp.x == next_tmp.x) && (act_tmp.y == next_tmp.y) && (occ !='1')) 
			res = '1';
		else 
			res = '0';
	}
	/* 2. Fall 
		act.x < next.x
		act.y > next.y
	*/ 

	if((act.x < next.x) && (act.y > next.y) && (res =='9')){ 
		while((act_tmp.x < next_tmp.x) && (act_tmp.y > next_tmp.y)) { 
			act_tmp.x +=1; 
			act_tmp.y -=1; 
			occ = occupied(currentplayer,act_tmp,game); 
			if( occ != '0') 
				break;
		}
			if((act_tmp.x == next_tmp.x) && (act_tmp.y == next_tmp.y) && (occ !='1'))
				res = '1'; 
			else 
				res='0';
	}

	/* 3. Fall 
		act.x > next.x
		act.y < next.y 
	*/
	if((act.x > next.x) && (act.y < next.y) && (res =='9')) { 
		while((act_tmp.x > next_tmp.x) && (act_tmp.y < next_tmp.y)){ 
			act_tmp.x -=1; 
			act_tmp.y +=1; 
                        occ = occupied(currentplayer,act_tmp,game);
                        if( occ != '0')
                                break;
                }
                        if((act_tmp.x == next_tmp.x) && (act_tmp.y == next_tmp.y) && (occ != '1'))
                                res = '1';
                        else
                                res='0';
        
	}
	/* 4. Fall 
		act.x > next.x 
		act.y > next.y 
	*/
	if((act.x > next.x) && (act.y > next.y) && (res =='9')) {
                while((act_tmp.x > next_tmp.x) && (act_tmp.y > next_tmp.y)){
                        act_tmp.x -=1;
                        act_tmp.y -=1;
                        occ = occupied(currentplayer,act_tmp,game);
                        if( occ != '0')
                                break;
                }
                        if((act_tmp.x == next_tmp.x) && (act_tmp.y == next_tmp.y) && (occ !='1'))
                                res = '1';
                        else
                                res='0';

        }
	
	return res ;
}

static char moveSpringer(char currentplayer, position act, position next, board game) { 
	/* 
	0 : Eigene Figur, Ziel inkorrekt
        1 : Ziel erreicht, Platziere an neuer pos
	 Fälle : 
		x +/- 1, y +/- 2
		x +/- 2, y +/- 1
	*/
	
	char res, occ; 
	occ = occupied(currentplayer,next,game);
	if ( occ == '1') 
	 res = '0';
	
 	else  { 
		if(((act.x+1) == next.x) && ( (act.y+2) == next.y))
			res = '1';
		if(((act.x+1) == next.x) && ((act.y-2) == next.y))
			res = '1';
		if(((act.x-1) == next.x) && ((act.y+2) == next.y))
			res ='1'; 
		if(((act.x-1) == next.x) && ((act.y-2) == next.y))
			res ='1'; 
		if(((act.x+2) == next.x) && ((act.y+1) == next.y))
			res ='1';
		if(((act.x+2) == next.x) && ((act.y-1) == next.y))
			res ='1';
		if(((act.x-2) == next.x) && ((act.y+1) == next.y)) 
			res ='1'; 
		if(((act.x-2) == next.x) && ((act.y-1) == next.y))
			res ='1'; 
	}
	return res; 
}		

static char moveTurm(char currentplayer, position act, position next, board game) { 
	/* 
        0 : Eigene Figur, Ziel inkorrekt
        1 : Ziel erreicht, Platziere an neuer pos
        Fälle : 
		x,y+/-
		x+/-,y
	*/
	char res, occ; 
	position act_tmp;
	act_tmp.x = act.x; 
	act_tmp.y = act.y; 
	res = '9';

	if((act.x != next.x) && (act.y != next.y)) 
		res = '0'; 
	else {
	/* 
		1. Fall
		y =, act.x < next.x
	*/
	if((act.x < next.x) && (res =='9')){ 
		while( act_tmp.x < next.x) { 
			act_tmp.x +=1; 
			occ = occupied(currentplayer,act_tmp,game);
			if ( occ != '0')
				break; 
		}
		if((act_tmp.x == next.x) && (occ !='1'))
			res = '1'; 
		else
			res = '0';
	}
	/* 
		2. Fall
		y =, act.x > next.x
	*/
	if ((act.x > next.x) && (res == '9')){ 
		while (act_tmp.x > next.x){ 
			act_tmp.x -=1; 
			occ = occupied(currentplayer,act_tmp,game);
			if( occ != '0')
				break;
		}
		if ((act_tmp.x == next.x) && (occ != '1'))
			res ='1';
		else
			res ='0';
	}
	/* 
		3. Fall 
		x =, act.y < next.y
	*/
	if ((act.y < next.y) && (res =='9')){ 
		while( act_tmp.y < next.y) { 
			act_tmp.y += 1; 
			occ = occupied(currentplayer,act_tmp,game);
			if ( occ != '0')
				break;
		}
		if((act_tmp.y == next.y) && ( occ != '1')) 
			res ='1'; 
		else
			res ='0';
	}
	/* 
		4. Fall 
		x =, act.y > next.y
	*/
	if ((act.y > next.y) && (res == '9')){ 
		while(act_tmp.y > next.y) { 
			act_tmp.y-=1;
			occ = occupied(currentplayer,act_tmp,game); 
			if( occ != '0') 
				break; 
		}
		if ((act_tmp.y == next.y) && (occ !='1'))
			res ='1'; 
		else
			res ='0';
	}
}
	return res;
}

static char moveDame(char currentplayer, position act, position next, board game) { 
        /* 
        0 : Eigene Figur, Ziel inkorrekt
        1 : Ziel erreicht, Platziere an neuer pos
	
	Läuft die Dame wie ein Läufer, oder wie ein Turm 
		
	*/
	char res; 
	if((act.y != next.y) && (act.x != next.x))
		res = moveLaeufer(currentplayer,act,next,game);
	else 
		res = moveTurm(currentplayer,act,next,game); 
	return res; 
		
}

static char moveKoenig(char currentplayer, position act, position next, board game) { 
	/* 
		        0 : Eigene Figur, Ziel inkorrekt
		        1 : Ziel erreicht, Platziere an neuer pos
	
	*/
	char res, occ; 
	occ = occupied(currentplayer,next,game);
	if ( occ == '1') 
		res ='0'; 
	else { 
		if ((act.x == next.x) && (act.y+1 == next.y)) 
			res='1'; 
		if ((act.x == next.x) && (act.y-1 == next.y))
			res='1'; 
		if ((act.x+1 == next.x) && (act.y == next.y))
			res='1';
		if ((act.x-1 == next.x) && (act.y == next.y))
			res='1';
		if ((act.x-1 == next.x) && (act.y-1 == next.y))
			res='1';
		if((act.x-1 == next.x) && (act.y+1 == next.y)) 
			res='1';
		if((act.x+1 == next.x) && (act.y-1 == next.y)) 
			res='1'; 
		if((act.x+1 == next.x) && (act.y+1 == next.y))
			res='1';
	}
	return res;		
}

static char isInCheck(char currentplayer, board game){ 
	int x,y; 
	position kingpos;
	position attacker;
	char ret,cur;
	ret='0'; 
	/*wo ist der könig */ 
	/* WEIß */ 
	if( currentplayer == WEISS) { 
		cur = '2';
		for(y=0; y < 8; y++) { 
			for(x=0; x < 8; x++){ 
				if(game.field[((y*8)+x)] == 6) { 
					kingpos.x = x; 
					kingpos.y = y;
				}
			}
		}
	/* Kann der weiße König von einen Gegner geschlagen werden? */ 
		for(y=0; y < 8; y++){ 
			for(x=0; x < 8; x++) { 
				if(game.field[((y*8)+x)] > 10){ 
						attacker.x = x; 
						attacker.y = y;
					switch(game.field[((y*8)+x)]){ 
						case SBAUER:
							ret = moveBauer(cur,attacker,kingpos,game);		
							break;
						case SLAEUFER:
							ret = moveLaeufer(cur,attacker,kingpos,game); 
							break;
						case SSPRINGER: 
							ret = moveSpringer(cur,attacker,kingpos,game);
							break; 
						case STURM: 
							ret = moveTurm(cur,attacker,kingpos,game); 
							break;
						case SDAME:
							ret = moveDame(cur,attacker,kingpos,game);
							break; 
						case SKOENIG: 
							ret = moveKoenig(cur,attacker,kingpos,game);
							break;		
					}
				}	 
			}
		}
	}
/*wo ist der könig */ 
	/* SCHWARZ */ 
	if( currentplayer == SCHWARZ) { 
		cur = '1';
		for(y=0; y < 8; y++) { 
			for(x=0; x < 8; x++){ 
				if(game.field[((y*8)+x)] == 16) { 
					kingpos.x = x; 
					kingpos.y = y;
				}
			}
		}
	/* Kann der schwarze König von einen Gegner geschlagen werden? */ 
		for(y=0; y < 8; y++){ 
			for(x=0; x < 8; x++) { 
				if((game.field[((y*8)+x)] < 10) && (game.field[((y*8)+x)] > 0)){ 
						attacker.x = x; 
						attacker.y = y;
					switch(game.field[((y*8)+x)]){ 
						case WBAUER:
							ret = moveBauer(cur,attacker,kingpos,game);		
							break;
						case WLAEUFER:
							ret = moveLaeufer(cur,attacker,kingpos,game); 
							break;
						case WSPRINGER: 
							ret = moveSpringer(cur,attacker,kingpos,game);
							break; 
						case WTURM: 
							ret = moveTurm(cur,attacker,kingpos,game); 
							break;
						case WDAME:
							ret = moveDame(cur,attacker,kingpos,game);
							break; 
						case WKOENIG: 
							ret = moveKoenig(cur,attacker,kingpos,game);
							break;		
					}
				}	 
			}

	}
}
	return ret;

}


boardret_arg *movepieces_1_svc(movefunc_arg *arg, struct svc_req *req){ 
	/*
	 Welcher Spieler ist dran ? 
	 Checke Figur auf Feld (int) 
	 switch/case
	 Wähle entsprechende Funktion aus 
	 return ok/ fehler 
	 board ok
	 NULL error*/
	static boardret_arg board_ret; 
	int old,next,i; 
	char ret='0';
	old = calcPos(arg->pos_old);
	next = calcPos(arg->pos_new);
	for(i=0; i < 64; i++)
		board_ret.gameBoard.field[i] = arg->spielfeld.field[i];
	
 	
	if (arg->currentplayer == WEISS) { 
	switch (arg->spielfeld.field[old]){
	
	case WBAUER: 
		board_ret.ret = moveBauer(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
		if ( (board_ret.ret == '1')){
			board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old];
			board_ret.gameBoard.field[old] = 0;
			ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
		}
		break;
	case WLAEUFER: 
                board_ret.ret = moveLaeufer(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
                if (board_ret.ret == '1')
			{
	                board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old];
        	        board_ret.gameBoard.field[old] = 0;
        	        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
			}
                break;
	case WSPRINGER:
                board_ret.ret = moveSpringer(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
                if ( (board_ret.ret == '1')){
                        board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old];
                        board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
                }
		break;
	case WTURM: 	
		board_ret.ret = moveTurm(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
		if(board_ret.ret == '1'){ 
			board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old]; 
			board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
		}
		break;
	case WDAME:
		board_ret.ret = moveDame(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
		if ( board_ret.ret =='1') { 
			board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old]; 
			board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
		} 
		break;
	case WKOENIG:
		board_ret.ret = moveKoenig(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
		if ( board_ret.ret == '1') { 
			board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old]; 
			board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
		}
		break;
	default:
		break;
	}
	
	}
	if(arg->currentplayer == SCHWARZ) { 
	switch(arg->spielfeld.field[calcPos(arg->pos_old)]){
	case SBAUER:	
		board_ret.ret = moveBauer(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
                if ((board_ret.ret == '1') ){
                	board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old];
                	board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
                }
		break;
	case SLAEUFER:
                board_ret.ret = moveLaeufer(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
                if (board_ret.ret == '1')
                        {
                        board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old];
                        board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
                        }
		break;
	case SSPRINGER:
                board_ret.ret = moveSpringer(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
                if ( (board_ret.ret == '1')){
                        board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old];
                        board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
                }
		break;
	case STURM: 
                board_ret.ret = moveTurm(arg->currentplayer, arg->pos_old, arg->pos_new,arg->spielfeld);
                if(board_ret.ret == '1'){
                        board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old];
                        board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);        
		}
		break; 
	case SDAME: 
		board_ret.ret = moveDame(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld); 
		if( board_ret.ret == '1') { 
			board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old]; 
			board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);	
		}
		break; 
	case SKOENIG: 
		board_ret.ret = moveKoenig(arg->currentplayer, arg->pos_old, arg->pos_new, arg->spielfeld);
		if( board_ret.ret == '1') { 
			board_ret.gameBoard.field[next] = board_ret.gameBoard.field[old]; 
			board_ret.gameBoard.field[old] = 0;
                        ret = isInCheck(arg->currentplayer,board_ret.gameBoard);
		}
		break;
	default:	
		break;
	}
	}
	if(ret == '1') { 
		board_ret.ret = '2'; 
	        for(i=0; i < 64; i++)
        	        board_ret.gameBoard.field[i] = arg->spielfeld.field[i];
		
	}
	
	return &board_ret;
}

char *currentplayer_1_svc(playerfunc_arg *arg, struct svc_req *req) { 
	/* 
	 player: 
		int func; 
		char player; 
		func=0: getCurrentPlayer
			return: currentPlayerNumber
		func=1: setCurrentPlayer 
			ändere Player
	*/
	static char currentPlayer='1'; 
	static char res;
	switch(arg->func){ 
		case GETCURRENTPLAYER: 
			return &currentPlayer;
			break;
		case SETCURRENTPLAYER:
			currentPlayer = arg->currentplayer; 
			res = '1';
			return &res; 		
			break;
		default:
			break;
}
			return NULL;
}

board *manageboard_1_svc(boardfunc_arg *arg, struct svc_req *req) { 
	/* 
		arg=0 : getBoard  
		arg=1 : setBoard 
	*/
	static board gameBoard; 
	int i;
	switch(arg->func){ 
		case GETBOARD:
			return &gameBoard;
			break;
		case SETBOARD: 
			for(i=0; i<64; i++) 
				gameBoard.field[i] = arg->gameBoard.field[i];
			return &gameBoard;
			break; 
		default:
			break;
	}
	return NULL;
}

board *initialboard_1_svc(void *arg,struct svc_req *req){ 
	/*
	Belegung: 
	0 : Feld ist leer 
	Weiß:
	1 : Bauer 
	2 : Läufer 
	3 : Springer 
	4 : Turm 
	5 : Dame 
	6 : König
	Schwarz: 
	11 : Bauer 
	12 : Läufer
	13 : Springer
	14 : Turm 
	15 : Dame 
	16 : König
	Da RPC bloß 1D-Arrays kann, 64 Felder Array und aus der Position heraus berechnet man den Platz, 
	(x,y) = ((y-1)*8 + x)
	*/
	static board gameBoard; 
	int i; 
	for(i =0; i < 64; i++) 
	 gameBoard.field[i] = 0;
	/*setze Weiß*/	 
	gameBoard.field[0] = 4; 
	gameBoard.field[1] = 3;
        gameBoard.field[2] = 2; 
        gameBoard.field[3] = 5; 
        gameBoard.field[4] = 6;
        gameBoard.field[5] = 2; 
        gameBoard.field[6] = 3; 
        gameBoard.field[7] = 4; 
	for(i=8; i < 16; i++) 
	 gameBoard.field[i] = 1; 
	/*setze Schwarz*/
	gameBoard.field[56] = 14;
        gameBoard.field[57] = 13;
        gameBoard.field[58] = 12;
        gameBoard.field[59] = 15;
        gameBoard.field[60] = 16;
        gameBoard.field[61] = 12;
        gameBoard.field[62] = 13;
        gameBoard.field[63] = 14;

	for(i=48; i < 56; i++)
	 gameBoard.field[i] = 11;

	return &gameBoard;

}

char *manageplayer_1_svc(char *arg, struct svc_req *req){ 
 /* 
	Anmeldung: 
	arg = 0
	1. Aufruf, setze player_a, res = 1
	2. Aufruf, setze player_b, res = 2
	< 2 Aufrufe return 0	 , res = 0
	Abmeldung: 
	arg= 1 : player a abmelden, res = 3 
	arg= 2 : player b abmelden, res = 4
	
 */
 static char player_a ='0';
 static char player_b ='0';
 static char res;
 if (*arg == '0'){  
	
 if (player_a == '0'){ 
	player_a ='1'; 
	res = '1';
 	return &res;
 }
 if (player_b == '0') { 
	player_b ='1';
	res ='2';
	return &res;		
 }
 /*Fehlerfall*/
 res ='0';
 return &res;
 }
 else { 
	if(*arg == '1'){ 
		player_a ='0';
		res ='3';
		return &res;	
	}
	if(*arg == '2'){ 
		player_b ='0';
		res = '4';
		return &res;
	}
 }
 res = '0';
 return &res;
}
