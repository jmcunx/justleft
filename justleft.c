/*
 * Copyright (c) 1999 ... 2021 2022
 *     John McCue <jmccue@jmcunx.com>
 *
 * Permission to use, copy, modify, and distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <sys/param.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#ifdef IS_BSD
#include <err.h>
#endif

#include <j_lib2.h>
#include <j_lib2m.h>

#include "justleft.h"

#define SARG 80

/*
 * show_file_heading() -- Show run stats
 */
void show_file_heading(char *fname)

{

  fprintf(stderr, "%s\n", LIT_C80);

  if (fname == (char *) NULL)
    fprintf(stderr, "%s\n", LIT_STDIN);
  else
    {
      if (strcmp(fname, FILE_NAME_STDIN) == 0)
	fprintf(stderr, "%s\n", LIT_STDIN);
      else
	fprintf(stderr, "%s\n", fname);
    }

} /* show_file_heading() */

/*
 * get_args() -- load arguments
 */
void get_args(int argc, char **argv, struct s_work *w)

{

  char ckarg[SARG];
  int opt;
  int ok;
  char *out_file = (char *) NULL;
  char *err_file = (char *) NULL;
  int display_help = (int) FALSE;
  int display_rev  = (int) FALSE;

  init_finfo(&(w->err));
  init_finfo(&(w->out));
  w->out.fp     = stdout;
  w->err.fp     = stderr;
  w->verbose    = (int) 0;
  w->force      = (int) FALSE;
  w->rtw        = (int) FALSE;

  snprintf(ckarg, SARG, "%c:%c:%c%c%c%c%c", 
          ARG_ERR, 
          ARG_OUT, 
          ARG_HELP, 
          ARG_RTW, 
          ARG_FORCE, 
          ARG_VERSION, 
          ARG_VERBOSE);

  while ((opt = getopt(argc, argv, ckarg)) != -1)
    {
      switch (opt)
	{
	  case ARG_HELP:
	    display_help = (int) TRUE;
	    break;
	  case ARG_VERSION:
	    display_rev = (int) TRUE;
	    break;
	  case ARG_FORCE:
	    w->force = (int) TRUE;
	    break;
	  case ARG_VERBOSE:
	    (w->verbose)++;
	    break;
	  case ARG_RTW:
	    w->rtw = (int) TRUE;
	    break;
	  case ARG_OUT:
	    out_file = optarg;
	    break;
	  case ARG_ERR:
	    err_file = optarg;
	    break;
	  default:
	    fprintf(stderr, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
	    exit(EXIT_FAILURE);
	    break;
	}
    }

  /*** if necessary - save stdout/err files and open ***/
  ok = open_out(stderr, &(w->err), err_file, w->force);
  if (ok == EXIT_SUCCESS)
    ok = open_out(w->err.fp, &(w->out), out_file, w->force);
  if (ok != EXIT_SUCCESS)
    {
      fprintf(w->err.fp, MSG_ERR_E000, PROG_NAME, SWITCH_CHAR, ARG_HELP);
      exit(EXIT_FAILURE);
    }

  /*** show help/rev and exit ? ***/
  ok = EXIT_SUCCESS;
  if (display_help)
    ok = show_help(w->out.fp, PROG_NAME);
  if (display_rev)
    ok = show_rev(w->out.fp, PROG_NAME);
  if (ok != EXIT_SUCCESS)
    {
      close_out(&(w->out));
      close_out(&(w->err));
      exit(ok);
    }

} /* get_args() */

/*
 * process_a_file() -- reads in file, creating out file
 */
void process_a_file(struct s_work *w, char *fname, char **buf, size_t *bsize,
		    struct s_counts *t)

{
  ssize_t cbytes = (ssize_t) 0;
  size_t  rsize  = (ssize_t) 0;
  FILE *fp;
  struct s_counts lines;

  init_counts(&lines);
  
  if (w->verbose > 0)
    show_file_heading(fname);
  
  if ( ! open_in(&fp, fname, w->err.fp) )
    return;

  /*** process data ***/
  while ((cbytes = getline(buf, bsize, fp)) > (ssize_t) -1)
    {
      lines.read++;
      lines.bytes_read += cbytes;
      j2_bye_nl((*buf));
      j2_justleft((*buf));
      if (w->rtw == (int) TRUE)
	j2_rtw((*buf));
      rsize = strlen((*buf));
      if (rsize > 0)
	fprintf(w->out.fp,"%s\n",(*buf));
      else
	fprintf(w->out.fp,"\n");
      lines.bytes_writes += (rsize + 1);
      lines.writes++;
    }
  
  /*** complete ***/
  if (w->verbose > 1)
    {
      t->read += lines.read;
      t->writes += lines.writes;
      t->bytes_read += lines.bytes_read;
      t->bytes_writes += lines.bytes_writes;
      fprintf(stderr, MSG_INFO_I023, lines.read);
      fprintf(stderr, MSG_INFO_I035, lines.writes);
      fprintf(stderr, MSG_INFO_I024, lines.bytes_read);
      fprintf(stderr, MSG_INFO_I041, lines.bytes_writes);
    }
  
  close_in(&fp, fname);

} /* process_a_file() */

/*
 * process_all() -- Process all files
 */
void process_all(int argc, char **argv, struct s_work *w)

{
  int i;
  char *buf = (char *) NULL;
  size_t bsiz = (size_t) 200;
  struct s_counts totl;
  
  init_counts(&totl);

  /* allocate initial read buffer memory (optional) */
  buf = (char *) calloc(bsiz, sizeof(char));
  if (buf == (char *) NULL)
    {
      fprintf(w->err.fp, MSG_ERR_E080, strerror(errno));
      return;
    }

  /* process files */
  for (i = optind; i < argc; i++)
    process_a_file(w, argv[i], &buf, &bsiz, &totl);

  if (i == optind)
    process_a_file(w, FILE_NAME_STDIN, &buf, &bsiz, &totl);

  if (buf != (char *) NULL)
    free(buf);

  if (w->verbose > 1)
    {
      show_file_heading(LIT_TALLF);
      fprintf(stderr, MSG_INFO_I023, totl.read);
      fprintf(stderr, MSG_INFO_I035, totl.writes);
      fprintf(stderr, MSG_INFO_I024, totl.bytes_read);
      fprintf(stderr, MSG_INFO_I041, totl.bytes_writes);
    }

}  /* process_all() */

/*
 * main()
 */
int main(int argc, char **argv)

{

  struct s_work w;

#ifdef OpenBSD
  if(pledge("stdio rpath wpath cpath",NULL) == -1)
    err(1,"pledge\n");
#endif

  get_args(argc, argv, &w);
  process_all(argc, argv, &w);

  close_out(&(w.out));
  close_out(&(w.err));
  exit(EXIT_SUCCESS);

}  /* main() */

/* END: justleft.c */
