/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _CHESS_H_RPCGEN
#define _CHESS_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct position {
	int x;
	int y;
};
typedef struct position position;

struct board {
	int field[64];
};
typedef struct board board;

struct movefunc_arg {
	position pos_old;
	position pos_new;
	char currentplayer;
	board spielfeld;
};
typedef struct movefunc_arg movefunc_arg;

struct playerfunc_arg {
	int func;
	char currentplayer;
};
typedef struct playerfunc_arg playerfunc_arg;

struct boardfunc_arg {
	int func;
	board gameBoard;
};
typedef struct boardfunc_arg boardfunc_arg;

struct boardret_arg {
	char ret;
	board gameBoard;
};
typedef struct boardret_arg boardret_arg;

#define CHESS_PROG 0x20000008
#define CHESS_VERS 1

#if defined(__STDC__) || defined(__cplusplus)
#define MOVEPIECES 1
extern  boardret_arg * movepieces_1(movefunc_arg *, CLIENT *);
extern  boardret_arg * movepieces_1_svc(movefunc_arg *, struct svc_req *);
#define MANAGEBOARD 2
extern  board * manageboard_1(boardfunc_arg *, CLIENT *);
extern  board * manageboard_1_svc(boardfunc_arg *, struct svc_req *);
#define CURRENTPLAYER 3
extern  char * currentplayer_1(playerfunc_arg *, CLIENT *);
extern  char * currentplayer_1_svc(playerfunc_arg *, struct svc_req *);
#define MANAGEPLAYER 5
extern  char * manageplayer_1(char *, CLIENT *);
extern  char * manageplayer_1_svc(char *, struct svc_req *);
#define INITIALBOARD 6
extern  board * initialboard_1(void *, CLIENT *);
extern  board * initialboard_1_svc(void *, struct svc_req *);
extern int chess_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define MOVEPIECES 1
extern  boardret_arg * movepieces_1();
extern  boardret_arg * movepieces_1_svc();
#define MANAGEBOARD 2
extern  board * manageboard_1();
extern  board * manageboard_1_svc();
#define CURRENTPLAYER 3
extern  char * currentplayer_1();
extern  char * currentplayer_1_svc();
#define MANAGEPLAYER 5
extern  char * manageplayer_1();
extern  char * manageplayer_1_svc();
#define INITIALBOARD 6
extern  board * initialboard_1();
extern  board * initialboard_1_svc();
extern int chess_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_position (XDR *, position*);
extern  bool_t xdr_board (XDR *, board*);
extern  bool_t xdr_movefunc_arg (XDR *, movefunc_arg*);
extern  bool_t xdr_playerfunc_arg (XDR *, playerfunc_arg*);
extern  bool_t xdr_boardfunc_arg (XDR *, boardfunc_arg*);
extern  bool_t xdr_boardret_arg (XDR *, boardret_arg*);

#else /* K&R C */
extern bool_t xdr_position ();
extern bool_t xdr_board ();
extern bool_t xdr_movefunc_arg ();
extern bool_t xdr_playerfunc_arg ();
extern bool_t xdr_boardfunc_arg ();
extern bool_t xdr_boardret_arg ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_CHESS_H_RPCGEN */
