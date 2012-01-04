/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "chess.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

boardret_arg *
movepieces_1(movefunc_arg *argp, CLIENT *clnt)
{
	static boardret_arg clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MOVEPIECES,
		(xdrproc_t) xdr_movefunc_arg, (caddr_t) argp,
		(xdrproc_t) xdr_boardret_arg, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

board *
manageboard_1(boardfunc_arg *argp, CLIENT *clnt)
{
	static board clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MANAGEBOARD,
		(xdrproc_t) xdr_boardfunc_arg, (caddr_t) argp,
		(xdrproc_t) xdr_board, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

char *
currentplayer_1(playerfunc_arg *argp, CLIENT *clnt)
{
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, CURRENTPLAYER,
		(xdrproc_t) xdr_playerfunc_arg, (caddr_t) argp,
		(xdrproc_t) xdr_char, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

char *
manageplayer_1(char *argp, CLIENT *clnt)
{
	static char clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, MANAGEPLAYER,
		(xdrproc_t) xdr_char, (caddr_t) argp,
		(xdrproc_t) xdr_char, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

board *
initialboard_1(void *argp, CLIENT *clnt)
{
	static board clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, INITIALBOARD,
		(xdrproc_t) xdr_void, (caddr_t) argp,
		(xdrproc_t) xdr_board, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}