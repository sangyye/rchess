/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "chess.h"

bool_t
xdr_position (XDR *xdrs, position *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->x))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->y))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_board (XDR *xdrs, board *objp)
{
	register int32_t *buf;

	int i;

	if (xdrs->x_op == XDR_ENCODE) {
		buf = XDR_INLINE (xdrs, ( 64 ) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_vector (xdrs, (char *)objp->field, 64,
				sizeof (int), (xdrproc_t) xdr_int))
				 return FALSE;
		} else {
			{
				register int *genp;

				for (i = 0, genp = objp->field;
					i < 64; ++i) {
					IXDR_PUT_LONG(buf, *genp++);
				}
			}
		}
		return TRUE;
	} else if (xdrs->x_op == XDR_DECODE) {
		buf = XDR_INLINE (xdrs, ( 64 ) * BYTES_PER_XDR_UNIT);
		if (buf == NULL) {
			 if (!xdr_vector (xdrs, (char *)objp->field, 64,
				sizeof (int), (xdrproc_t) xdr_int))
				 return FALSE;
		} else {
			{
				register int *genp;

				for (i = 0, genp = objp->field;
					i < 64; ++i) {
					*genp++ = IXDR_GET_LONG(buf);
				}
			}
		}
	 return TRUE;
	}

	 if (!xdr_vector (xdrs, (char *)objp->field, 64,
		sizeof (int), (xdrproc_t) xdr_int))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_movefunc_arg (XDR *xdrs, movefunc_arg *objp)
{
	register int32_t *buf;

	 if (!xdr_position (xdrs, &objp->pos_old))
		 return FALSE;
	 if (!xdr_position (xdrs, &objp->pos_new))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->currentplayer))
		 return FALSE;
	 if (!xdr_board (xdrs, &objp->spielfeld))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_playerfunc_arg (XDR *xdrs, playerfunc_arg *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->func))
		 return FALSE;
	 if (!xdr_char (xdrs, &objp->currentplayer))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_boardfunc_arg (XDR *xdrs, boardfunc_arg *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->func))
		 return FALSE;
	 if (!xdr_board (xdrs, &objp->gameBoard))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_boardret_arg (XDR *xdrs, boardret_arg *objp)
{
	register int32_t *buf;

	 if (!xdr_char (xdrs, &objp->ret))
		 return FALSE;
	 if (!xdr_board (xdrs, &objp->gameBoard))
		 return FALSE;
	return TRUE;
}