/*============================----beg-of-source---============================*/
#ifndef yCMD_priv
#define yCMD_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "vi/vim command processor"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  "ponos-daimon (hard labor and toil)"
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
#define     P_VERNUM    "2.0ef
#define     P_VERTXT    "fixed :! external execution trouble"

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
#include    <yMODE.h>             /* heatherly vi-keys mode control           */
#include    <yKEYS.h>             /* heatherly vi-keys key handling           */
#include    <yMACRO.h>            /* heatherly vi-keys macro processing       */
#include    <ySRC.h>              /* heatherly vi-keys source editing         */
#include    <yVIEW.h>             /* heatherly vi-keys view management        */
#include    <yFILE.h>             /* heatherly vi-keys content file handling  */
#include    <yCOLOR.h>            /* heatherly opengl color handling          */


#define     CMDS_BASE        'b'  /* fully standard in base           */
#define     CMDS_CUST        'c'  /* fully custom, not in base        */

#define     MAX_BASE    500
typedef  struct cCMDS   tCMDS;
struct  cCMDS {
   uchar       base;
   uchar       menu;                        /* category                       */
   uchar       name        [LEN_LABEL];     /* full command name              */
   uchar       abbr        [LEN_TERSE];     /* abbreviation of name           */
   union {
      char        (*v     ) (void);
      char        (*c     ) (char);
      char        (*cc    ) (char , char );
      char        (*i     ) (int);
      char        (*ii    ) (int, int);
      char        (*iii   ) (int, int, int);
      char        (*isss  ) (int, char*, char*, char*);
      char        (*is    ) (int  , char*);
      char        (*s     ) (char*);
      char        (*ss    ) (char*, char*);
      char        (*si    ) (char*, int  );
      char        (*sii   ) (char*, int, int);
      char        (*css   ) (char, char*, char*);
      char        (*cs    ) (char, char*);
      char        (*f     ) (float);
      char        (*cciiii) (char, char, int, int, int, int);
      char        (*iiii  ) (int, int, int, int);
      char        (*ci    ) (char, int);
   } f;
   uchar       terms       [LEN_TERSE];     /* type of terms/args             */
   uchar       desc        [LEN_DESC];      /* descriptive label              */
};


#define     MAX_TERMS         50
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

/*---(true useful vars)---------------*/
extern tLINK  *g_head;                       /* head of link chain            */
extern tLINK  *g_tail;                       /* tail of link chain            */
/*---(menu grphics/unit testing)------*/
extern tLINK  *g_found;                      /* result of last find           */
/*---(DEBUGGING FASTER)---------------*/
extern short   g_ncmd;                       /* all menu items in list        */
extern short   g_nbase;                      /* base menu items in list       */
/*---(done)---------------------------*/



typedef    struct    cMY    tMY;
struct cMY {
   /*---(base)-----------------*/
   short       nbase;                       /* count of bases                 */
   /*---(parsing)--------------*/
   char        p_nfield;
   char        p_fields    [10][LEN_RECD];
   char        p_all       [LEN_RECD];
   /*---(done)-----------------*/
};
extern tMY         myCMD;


extern char g_print     [LEN_RECD];


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char        ycmd__purge             (void);



/*===[[ yCMD_terms.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ycmd_terms_init         (void);
char        ycmd_terms_clear        (void);
/*---(accessor)-------------*/
char        ycmd_terms_count        (void);
char*       ycmd_terms_show         (char n);
/*---(new)------------------*/
char        ycmd_terms              (uchar *a_terms);
/*---(exec)-----------------*/
char        ycmd_launch             (tLINK *a_link, char *a_rc);
/*---(done)-----------------*/



/*===[[ yCMD_load.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        ycmd_load_init          (void);
/*---(support)--------------*/
char        ycmd_check_name         (uchar *a_name, char a_type, int *r_len);
/*---(search)---------------*/
int         ycmd_load_count         (void);
char        ycmd_load_by_name       (uchar *a_name, tCMDS **r_cmds);
/*---(memory)---------------*/
char        ycmd_new_cmd            (uchar a_menu, uchar *a_name, uchar *a_abbr, uchar *a_terms, void *a_func, uchar *a_desc, tCMDS **r_cmds);
char        ycmd_load               (void);
char        ycmd_new_link           (tCMDS *a_cmd, tLINK **r_link);



/*===[[ yCMD_exec.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ycmd_exec_purge         (void);
int         ycmd_exec_count         (void);
char        ycmd_check_dup          (uchar a_base, uchar *a_name, uchar *a_abbr);
char        ycmd_exec_by_name       (uchar *a_name, tLINK **r_link);
char        ycmd_exec_by_index      (short a_index, tLINK **r_link);
char        ycmd_parse              (uchar *a_str);



/*===[[ yCMD_exec.c ]]========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        ycmd__unit_parrot       (char a_value);
char        ycmd__unit_length       (char *a_string);
char        ycmd__unit_tester       (char a_mode, char a_value);


char        ycmd_dump               (FILE *f);



#endif

