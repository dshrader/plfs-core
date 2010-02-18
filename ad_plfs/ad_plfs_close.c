/* -*- Mode: C; c-basic-offset:4 ; -*- */
/* 
 *   $Id: ad_plfs_close.c,v 1.9 2004/10/04 15:51:01 robl Exp $    
 *
 *   Copyright (C) 1997 University of Chicago. 
 *   See COPYRIGHT notice in top-level directory.
 */

#include "ad_plfs.h"

void ADIOI_PLFS_Close(ADIO_File fd, int *error_code)
{
    int err, rank;
    static char myname[] = "ADIOI_PLFS_CLOSE";
    plfs_debug( stderr, "%s: begin\n", myname );

    MPI_Comm_rank( fd->comm, &rank );
    err = plfs_close(fd->fs_ptr, rank);
    fd->fs_ptr = NULL;

    if (err < 0 ) {
	*error_code = MPIO_Err_create_code(MPI_SUCCESS, MPIR_ERR_RECOVERABLE,
					   myname, __LINE__, MPI_ERR_IO,
					   "**io",
					   "**io %s", strerror(-err));
    } else {
         *error_code = MPI_SUCCESS;
    }
}
