/*============================----beg-of-source---============================*/
#ifndef yCMD_priv
#define yCMD_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "command processor"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "ponos (hard labor and toil)"
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yCMD"
#define     P_FULLNAME  "/usr/local/lib64/libyCMD"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, separated into independent library"
#define     P_VERNUM    "2.0a"
#define     P_VERTXT    "initial separation"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
/*---(custom)----------------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */
#include    <yMODE.h>             /* heatherly vi/vim mode control            */
#include    <yKEYS.h>             /* heatherly vi/vim key handling            */
#include    <ySRC.h>              /* heatherly vi/vim source editing          */


typedef  struct cCMDS   tCMDS;
struct  cCMDS {
   uchar       base;
   uchar       menu;                        /* category                       */
   uchar       name        [LEN_LABEL];     /* full command name              */
   uchar       abbr        [LEN_TERSE];     /* abbreviation of name           */
   union {
      char        (*v    ) (void);
      char        (*c    ) (char);
      char        (*cc   ) (char , char );
      char        (*i    ) (int);
      char        (*ii   ) (int, int);
      char        (*iii  ) (int, int, int);
      char        (*isss ) (int, char*, char*, char*);
      char        (*is   ) (int  , char*);
      char        (*s    ) (char*);
      char        (*ss   ) (char*, char*);
      char        (*si   ) (char*, int  );
      char        (*sii  ) (char*, int, int);
      char        (*css  ) (char, char*, char*);
      char        (*cs   ) (char, char*);
      char        (*f    ) (float);
      char        (*cciiii) (char, char, int, int, int, int);
      char        (*iiii)  (int, int, int, int);
   } f;
   uchar       terms       [LEN_TERSE];     /* type of terms/args             */
   uchar       desc        [LEN_DESC];      /* descriptive label              */
};
extern const tCMDS  s_base      [];


#define     MAX_TERMS         20
typedef    struct   cTERMS  tTERMS;
struct cTERMS {
   char        name        [LEN_LABEL];
   char        disp        [LEN_DESC ];
};
extern const tTERMS  s_terms [];


typedef  struct cLINK   tLINK;
struct cLINK {
   tCMDS      *data;     /* actual command                  */
   char        nlen;     /* length of name (speed searches) */
   char        alen;     /* length of name (speed searches) */
   char        nterms;   /* index to terms db (speed exec)  */
   tLINK      *m_next;
};



typedef    struct    cMY    tMY;
struct cMY {
   /*---(parsing)--------------*/
   char        p_fields    [10][LEN_RECD];
   int         p_nfield;
   char        p_all       [LEN_RECD];
   /*---(done)-----------------*/
};
extern tMY         myCMD;




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char        ycmds__purge            (void);



char        ycmds_term_init         (void);



#endif

