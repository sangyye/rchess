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
	char func; 
	char currentplayer; 
};

struct boardfunc_arg { 
	char func; 
	board gameBoard;
};

program CHESS_PROG {
	version CHESS_VERS {
		board MOVEPIECES(movefunc_arg) = 1;
		board MANAGEBOARD(boardfunc_arg) =2; 
		char CURRENTPLAYER(playerfunc_arg) = 3; 
		char MANAGEPLAYER(char) = 5;
		board INITIALBOARD(void) = 6;
		} = 1;
} = 0x20000008;
