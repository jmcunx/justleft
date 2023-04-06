/*
 * Copyright (c) 1999 ... 2023 2024
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

#ifndef JLIB2_CHAR_NULL
#define NO_JLIB 1
#define JLIB2_INT_NULL   ((int) '\0')
#define JLIB2_CHAR_NULL  ((char) '\0')
#define JLIB2_UCHAR_NULL ((unsigned char) '\0' )
#endif

#ifndef NULL
#define NULL '\0'
#endif
#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

#ifndef SSIZE_T
#define SSIZE_T ssize_t
#endif
#ifndef TAB_CHAR
#define TAB_CHAR 0x09
#endif

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

/*** messages ***/
#ifdef NO_JLIB
#define ARG_ERR           'e'  /* Output Error File                  */
#define ARG_FORCE         'f'  /* force create files                 */
#define ARG_HELP          'h'  /* Show Help                          */
#define ARG_OUT           'o'  /* Output File                        */
#define ARG_RTW           'R'  /* remove trailing spaces             */
#define ARG_VERBOSE       'v'  /* Verbose                            */
#define ARG_VERSION       'V'  /* Show Version Information           */
#define FILE_NAME_STDIN   "-"
#define LIT_C80           "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"
#define LIT_INFO_01       "\tBuild: %s %s\n"
#define LIT_REV           "Revision"
#define LIT_STDIN         "(standard input)"
#define LIT_TALLF         "Total all Files"
#define MSG_ERR_E000      "Try '%s %c%c' for more information\n"
#define MSG_ERR_E002      "ERROR E002: Cannot open '%s' for write, processing aborted\n"
#define MSG_ERR_E025      "ERROR E025: File %s cannot be created, already exists\n"
#define MSG_ERR_E080      "ERROR E080: cannot allocate initial memory : %s\n"
#define MSG_INFO_I023     "I023:            Lines Read:  %9ld\n"
#define MSG_INFO_I024     "I024:            Bytes Read:                      %9ld\n"
#define MSG_INFO_I035     "I035:         Lines Written:  %9ld\n"
#define MSG_INFO_I041     "I041:         Bytes Written:                      %9ld\n"
#define MSG_WARN_W002     "W002: Open Error Bypass File '%s' : %s\n"
#define SWITCH_CHAR       '-'
#define USG_MSG_ARG_ERR        "\t%c%c file\t\t: Write errors to file 'file', default stderr\n"
#define USG_MSG_ARG_FORCE      "\t%c%c\t\t: force create of files when found\n"
#define USG_MSG_ARG_HELP       "\t%c%c\t\t: Show brief help and exit\n"
#define USG_MSG_ARG_OUT        "\t%c%c file\t\t: Write output to file 'file', default stdout\n"
#define USG_MSG_ARG_RTW        "\t%c%c\t\t: Remove Trailing White space\n"
#define USG_MSG_ARG_VERBOSE_5  "\t%c%c\t\t: show run stats on stderr\n"
#define USG_MSG_ARG_VERSION    "\t%c%c\t\t: Show revision information and exit\n"
#define USG_MSG_OPTIONS        "Options\n"
#define USG_MSG_USAGE          "usage:\t%s [OPTIONS] [FILES ...]\n"
#endif /* NO_JLIB */

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

#ifdef NO_JLIB
SSIZE_T j2_getline(char **buf, size_t *n, FILE *fp);
int j2_f_exist(char *file_name);
long int j2_bye_last(char *x, char lastc);
long int j2_clr_str(char *s, char c, int size);
long int j2_justleft(char *s);
long int j2_rtw(char *buffer);
#define j2_bye_nl(x)    j2_bye_last((x), '\n')
#define j2_bye_ctlm(x)  j2_bye_last((x), '\r')
#endif /* NO_JLIB */

#endif /* JUSTLEFT_H */

/* END: justleft.h */
