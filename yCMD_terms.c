/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"


char        g_print     [LEN_RECD]  = "";

/*
 *  terms
 *
 *
 *
 */


/*===[[ TERMS ]]==============================================================*/
const tTERMS  s_terms [] = {
   /*-name----   ---display-------------------------*/
   { "v"       , "void"                              },
   { "c"       , "char"                              },
   { "cc"      , "char, char"                        },
   { "i"       , "int"                               },
   { "is"      , "int, char*"                        },
   { "s"       , "char*"                             },
   { "ss"      , "char*, char*"                      },
   { "si"      , "char*, int"                        },
   { "a"       , "char*"                             },  /* string includes spaces       */
   { "ii"      , "int, int"                          },
   { "iii"     , "int, int, int"                     },
   { "sii"     , "char*, int, int"                   },
   { "isss"    , "int, char*, char*, char*"          },
   { "Cs"      , "char*, char*"                      },  /* command and arg both        */
   { "css"     , "char, char*, char*"                },
   { "cs"      , "char, char*"                       },
   { "f"       , "float"                             },
   { "cciiii"  , "char, char, int, int, int, int"    },
   { "iiii"    , "int, int, int, int"                },
   { "ci"      , "char, int"                         },
   { "-"       , "-"                                 },
};
static  int s_nterm  = 0;



/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
ycmd_terms_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (MODE_COMMAND)) {
      DEBUG_YCMD   yLOG_note    ("status is not ready for init");
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(terms)--------------------------*/
   DEBUG_YCMD   yLOG_note    ("initialize term system");
   s_nterm = 0;
   for (i = 0; i < MAX_TERMS; ++i) {
      if (s_terms [i].name [0] == '-')  break;
      ++s_nterm;
   }
   /*---(parsing)------------------------*/
   for (i = 0; i < 10; ++i)  strlcpy (myCMD.p_fields [i], "", LEN_RECD);
   strlcpy (myCMD.p_all    , "", LEN_RECD);
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd_terms_clear        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   DEBUG_YCMD   yLOG_note    ("clear term system");
   s_nterm = 0;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       simple accessors                       ----===*/
/*====================------------------------------------====================*/
static void      o___ACCESSOR________________o (void) {;}

char  ycmd_terms_count     (void) { return s_nterm; }

char*
ycmd_terms_show         (char n)
{
   if (n < 0 || n >= s_nterm)  return  "n/a";
   sprintf (g_print, "%-6.6s  å%sæ", s_terms [n].name, s_terms [n].disp);
   return g_print;
}



/*====================------------------------------------====================*/
/*===----                     new command support                      ----===*/
/*====================------------------------------------====================*/
static void      o___NEW_____________________o (void) {;}

char
ycmd_terms              (uchar *a_terms)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_spoint  (a_terms);
   --rce;  if (a_terms == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_snote   (a_terms);
   /*---(short-cuts)---------------------*/
   i = strlen (a_terms);
   if (i == 0) {
      DEBUG_YCMD   yLOG_snote   ("short-cut for empty");
      DEBUG_YCMD   yLOG_sint    (0);
      DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   if (i == 1 && a_terms [0] == '-') {
      DEBUG_YCMD   yLOG_snote   ("short-cut for dash");
      DEBUG_YCMD   yLOG_sint    (0);
      DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(walk)---------------------------*/
   for (i = 0; i < s_nterm; ++i) {
      if (a_terms [0] != s_terms [i].name [0])       continue;
      if (strcmp (a_terms, s_terms [i].name) != 0)   continue;
      DEBUG_YCMD   yLOG_snote   ("found");
      DEBUG_YCMD   yLOG_sint    (i);
      DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
      return i;
   }
   /*---(failed)-------------------------*/
   --rce;
   DEBUG_YCMD   yLOG_snote   ("FAILED");
   DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}



/*====================------------------------------------====================*/
/*===----                     execution support                        ----===*/
/*====================------------------------------------====================*/
static void      o___EXEC____________________o (void) {;}

char
ycmd_launch             (tLINK *a_link, char *a_rc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_point   ("link"      , a_link);
   --rce;  if (a_link == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_value   ("nterms"    , a_link->nterms);
   --rce;  if (a_link->nterms < 0 || a_link->nterms >= s_nterm) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_point   ("->data"    , a_link->data);
   --rce;  if (a_link->data == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_point   ("->f.v"     , a_link->data->f.v);
   --rce;  if (a_link->data->f.v == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("terms"     , a_link->data->terms);
   /*---(run)----------------------------*/
   --rce;  switch (a_link->nterms) {
   case  0 : rc = a_link->data->f.v      ();                                                                break;
   case  1 : rc = a_link->data->f.c      (myCMD.p_fields [1][0]);                                                 break;
   case  2 : rc = a_link->data->f.cc     (myCMD.p_fields [1][0], myCMD.p_fields [2][0]);                                break;
   case  3 : rc = a_link->data->f.i      (atoi (myCMD.p_fields [1]));                                             break;
   case  4 : rc = a_link->data->f.is     (atoi (myCMD.p_fields [1]), myCMD.p_fields [1]);                               break;
   case  5 : rc = a_link->data->f.s      (myCMD.p_fields [1]);                                                    break;
   case  6 : rc = a_link->data->f.ss     (myCMD.p_fields [1], myCMD.p_fields [2]);                                      break;
   case  7 : rc = a_link->data->f.si     (myCMD.p_fields [1], atoi (myCMD.p_fields [2]));                               break;
   case  8 : rc = a_link->data->f.s      (myCMD.p_all);                                                           break;
   case  9 : rc = a_link->data->f.ii     (atoi (myCMD.p_fields [1]), atoi (myCMD.p_fields [2]));                        break;
   case 10 : rc = a_link->data->f.iii    (atoi (myCMD.p_fields [1]), atoi (myCMD.p_fields [2]), atoi (myCMD.p_fields [3]));   break;
   case 11 : rc = a_link->data->f.sii    (myCMD.p_fields [1], atoi (myCMD.p_fields [2]), atoi (myCMD.p_fields [3]));          break;
   case 12 : rc = a_link->data->f.isss   (atoi (myCMD.p_fields [1]), myCMD.p_fields [2], myCMD.p_fields [3], myCMD.p_fields [4]);   break;
   case 13 : rc = a_link->data->f.ss     (myCMD.p_fields [0], myCMD.p_fields [1]);                                      break;
   case 14 : rc = a_link->data->f.css    (myCMD.p_fields [1][0], myCMD.p_fields [2], myCMD.p_fields [3]);                     break;
   case 15 : rc = a_link->data->f.cs     (myCMD.p_fields [1][0], myCMD.p_fields [2]);                                   break;
   case 16 : rc = a_link->data->f.f      (atof (myCMD.p_fields [1]));                                             break;
   case 17 : rc = a_link->data->f.cciiii (myCMD.p_fields [1][0], myCMD.p_fields [2][0], atoi (myCMD.p_fields [3]), atoi (myCMD.p_fields [4]), atoi (myCMD.p_fields [5]), atoi (myCMD.p_fields [6]));  break;
   case 18 : rc = a_link->data->f.iiii   (atoi (myCMD.p_fields [1]), atoi (myCMD.p_fields [2]), atoi (myCMD.p_fields [3]), atoi (myCMD.p_fields [4]));  break;
   case 19 : rc = a_link->data->f.ci     (myCMD.p_fields [1][0], atoi (myCMD.p_fields [2]));  break;
   default : rc = -1;                                                                                       break;
             DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
             return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_value   ("rc"        , rc);
   if (a_rc != NULL)  *a_rc = rc;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}


