#include "chess.h"
#define GETCURRENTPLAYER 0
#define SETCURRENTPLAYER 1 
#define GETBOARD 0
#define SETBOARD 1
#define WEISS 1 
#define SCHWARZ 2
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
	return ((act.y-1)*8 + act.x);

}


static char occupied(char currentplayer,position next,board game) { 
	/* 
		output: 0 Feld leer 
		output: 1 Feld besetzt, eigene Farbe 
		output: 2 Feld besetzt, gegnerische Farbe
	*/
	char res;
	if(game.field[(calcPos(next))] == 0){ 
		res ='0';
	}
	if (currentplayer == '1'){ 
	if (game.field[(calcPos(next))] < 10){ 
		res ='1'; 		
	}
	else { 
		res ='2'; 
	}		
	}
	if(currentplayer =='2'){ 
	if(game.field[(calcPos(next))] > 10) {
		res ='1'; 
	}
	else { 
		res ='2';  
	
	}
}
	return res;
}

static char moveBauer(char currentplayer, position act, position next,board game){ 
	/* input: 
		currentplayer, act pos, next pos, gameboard 
	   next pos ok? 
	   output: 
		1 frei
		2 geschlagen
		0 error 
	*/
	char res;
	char tmp=occupied(currentplayer,next,game);;
	/*
		MOVE BAUER WEIß
	*/
	if( currentplayer == '1') { 
		if( next.x == act.x) { 
			if(next.y == (act.y+1)){
				if(tmp == '1'){
					res = '1'; 
				}	
				if(tmp == '2') { 
					res ='2'; 
					}		
		}
	}
	   if (((next.x == (act.x+1) || next.x ==(act.x-1)) && (next.y) == (act.y+1)) && tmp =='2')
			res = '2';
 
	}
	/* 
		MOVE BAUER SCHWARZ
	*/
	else if(currentplayer == '2'){ 

	}

	return res;
}

static char moveLaeufer(char currentplayer, position act, position next,board game){ 

}

static char moveSpringer(char currentplayer, position act, position next, board game) { 

}

static char moveTurm(char currentplayer, position act, position next, board game) { 

}

static char moveDame(char currentplayer, position act, position next, board game) { 

}

static char moveKoenig(char currentplayer, position act, position next, board game) { 

}
board *movepieces_1_svc(movefunc_arg *arg, struct svc_req *req){ 
	/*
	 Welcher Spieler ist dran ? 
	 Checke Figur auf Feld (int) 
	 switch/case
	 Wähle entsprechende Funktion aus 
	 return ok/ fehler 
	 board ok
	 NULL error*/
	static board gameBoard; 
	if (arg->currentplayer == WEISS) { 
	switch (arg->spielfeld.field[calcPos(arg->pos_old)]){
	
	case WBAUER: 
		break;
	case WLAEUFER: 
		break;
	case WSPRINGER:
		break;
	case WTURM: 
		break;
	case WDAME: 
		break;
	case WKOENIG:
		break;
	default:
		break;
	}
	
	}
	if(arg->currentplayer == SCHWARZ) { 
	switch(arg->spielfeld.field[calcPos(arg->pos_old)]){
	case SBAUER: 
		break;
	case SLAEUFER:
		break;
	case SSPRINGER:
		break;
	case STURM: 
		break; 
	case SDAME: 
		break; 
	case SKOENIG: 
		break;
	default:	
		break;
	}
	}
	
	return &gameBoard;
}

char *currentplayer_1_svc(playerfunc_arg *arg, struct svc_req *req) { 
	/* 
	 player: 
		char func; 
		char player; 
		func=0: getCurrentPlayer
			return: currentPlayerNumber
		func=1: setCurrentPlayer 
			ändere Player
	*/
	static char currentPlayer; 
	static char res;
	switch(arg->func){ 
		case GETCURRENTPLAYER: 
			return &currentPlayer;
			break;
		case SETCURRENTPLAYER:
			currentPlayer = !currentPlayer; 
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
	switch(arg->func){ 
		case GETBOARD:
			return &gameBoard;
			break;
		case SETBOARD: 
			gameBoard = arg->gameBoard;
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
