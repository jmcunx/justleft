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

#ifndef JUSTLEFT_H

#define JUSTLEFT_H "INCLUDED"

#define USG_MSG_JUSTLEFT_1 "\tRemove leading white space (Left Justify) each line in a Text File\n"
#define PROG_NAME  "justleft"

struct s_file_info
{
  FILE *fp;
  char *fname;
} ;

struct s_counts
{
  long int read;
  long int writes;
  long int bytes_read;
  long int bytes_writes;
} ;

struct s_work
{
  struct s_file_info err;
  struct s_file_info out;
  int verbose;
  int force;          /* TRUE or FALSE */
  int rtw;            /* TRUE or FALSE */
} ;

/*** prototypes ***/
int open_in(FILE **, char *, FILE *);
void close_in(FILE **, char *);
int open_out(FILE *, struct s_file_info *, char *, int);
void close_out(struct s_file_info *);
char *get_progname(char *, char *);
void init_finfo(struct s_file_info *);
void init_counts(struct s_counts *);

int show_rev(FILE *, char *);
int show_help(FILE *, char *);

#endif /* JUSTLEFT_H */

/* END: justleft.h */
