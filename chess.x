struct position{ 
	int x; 
	int y; 
};
struct board{ 
	int field[64];
};

struct movefunc_arg { 
	 position pos_old;
	 position pos_new;
	 char currentplayer; 
	 board spielfeld;
};

struct playerfunc_arg { 
	int  func; 
	char currentplayer; 
};

struct boardfunc_arg { 
	int  func; 
	board gameBoard;
};

struct boardret_arg { 
	char ret; 
	board gameBoard; 
};

program CHESS_PROG {
	version CHESS_VERS {
		boardret_arg MOVEPIECES(movefunc_arg) = 1;
		board MANAGEBOARD(boardfunc_arg) =2; 
		char CURRENTPLAYER(playerfunc_arg) = 3; 
		char MANAGEPLAYER(char) = 5;
		board INITIALBOARD(void) = 6;
		} = 1;
} = 0x20000008;
