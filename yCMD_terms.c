/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"



/*
 *  terms
 *
 *
 *
 */


/*===[[ TERMS ]]==============================================================*/
const tTERMS  s_terms [] = {
   { ""      , "void"                       },  /* void                         */
   { "v"     , "void"                       },
   { "c"     , "char"                       },
   { "cc"    , "char, char"                 },
   { "i"     , "int"                        },
   { "is"    , "int, char*"                 },
   { "s"     , "char*"                      },
   { "ss"    , "char*, char*"               },
   { "si"    , "char*, int"                 },
   { "a"     , "char*"                      },  /* string includes spaces       */
   { "ii"    , "int, int"                   },
   { "iii"   , "int, int, int"              },
   { "sii"   , "char*, int, int"            },
   { "isss"  , "int, char*, char*, char*"   },
   { "Cs"    , "char*, char*"               },  /* command and arg both        */
   { "css"   , "char, char*, char*"         },
   { "cs"    , "char, char*"                },
   { "f"     , "float"                      },
   { "cciiii", "char, char, int, int, int, int"},
   { "iiii"  , "int, int, int, int"         },
   { "-"    , "-"                           },
};
static  int s_nterm  = 0;

char
ycmds_launch            (tLINK *a_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   DEBUG_CMDS   yLOG_info    ("terms"     , a_link->data->terms);
   DEBUG_CMDS   yLOG_value   ("nterms"    , a_link->nterms);
   DEBUG_CMDS   yLOG_point   ("function"  , a_link->data->f.v);
   /*---(run)----------------------------*/
   switch (a_link->nterms) {
   case  0 : rc = a_link->data->f.v      ();                                                                break;
   case  1 : rc = a_link->data->f.v      ();                                                                break;
   case  2 : rc = a_link->data->f.c      (myCMD.p_fields [1][0]);                                                 break;
   case  3 : rc = a_link->data->f.cc     (myCMD.p_fields [1][0], myCMD.p_fields [2][0]);                                break;
   case  4 : rc = a_link->data->f.i      (atoi (myCMD.p_fields [1]));                                             break;
   case  5 : rc = a_link->data->f.is     (atoi (myCMD.p_fields [1]), myCMD.p_fields [1]);                               break;
   case  6 : rc = a_link->data->f.s      (myCMD.p_fields [1]);                                                    break;
   case  7 : rc = a_link->data->f.ss     (myCMD.p_fields [1], myCMD.p_fields [2]);                                      break;
   case  8 : rc = a_link->data->f.si     (myCMD.p_fields [1], atoi (myCMD.p_fields [2]));                               break;
   case  9 : rc = a_link->data->f.s      (myCMD.p_all);                                                           break;
   case 10 : rc = a_link->data->f.ii     (atoi (myCMD.p_fields [1]), atoi (myCMD.p_fields [2]));                        break;
   case 11 : rc = a_link->data->f.iii    (atoi (myCMD.p_fields [1]), atoi (myCMD.p_fields [2]), atoi (myCMD.p_fields [3]));   break;
   case 12 : rc = a_link->data->f.sii    (myCMD.p_fields [1], atoi (myCMD.p_fields [2]), atoi (myCMD.p_fields [3]));          break;
   case 13 : rc = a_link->data->f.isss   (atoi (myCMD.p_fields [1]), myCMD.p_fields [2], myCMD.p_fields [3], myCMD.p_fields [4]);   break;
   case 14 : rc = a_link->data->f.ss     (myCMD.p_fields [0], myCMD.p_fields [1]);                                      break;
   case 15 : rc = a_link->data->f.css    (myCMD.p_fields [1][0], myCMD.p_fields [2], myCMD.p_fields [3]);                     break;
   case 16 : rc = a_link->data->f.cs     (myCMD.p_fields [1][0], myCMD.p_fields [2]);                                   break;
   case 17 : rc = a_link->data->f.f      (atof (myCMD.p_fields [1]));                                             break;
   case 18 : rc = a_link->data->f.cciiii (myCMD.p_fields [1][0], myCMD.p_fields [2][0], atoi (myCMD.p_fields [3]), atoi (myCMD.p_fields [4]), atoi (myCMD.p_fields [5]), atoi (myCMD.p_fields [6]));  break;
   case 19 : rc = a_link->data->f.iiii   (atoi (myCMD.p_fields [1]), atoi (myCMD.p_fields [2]), atoi (myCMD.p_fields [3]), atoi (myCMD.p_fields [4]));  break;
   default : rc = -1;                                                                                       break;
   }
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
ycmd_terms_init         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (MODE_COMMAND)) {
      DEBUG_CMDS   yLOG_note    ("status is not ready for init");
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(terms)--------------------------*/
   DEBUG_CMDS   yLOG_note    ("initialize term system");
   s_nterm = 0;
   for (i = 0; i < MAX_TERMS; ++i) {
      if (s_terms [i].name [0] == '-')  break;
      ++s_nterm;
   }
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvikeys_terms           (char *a_terms)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CMDS   yLOG_spoint  (a_terms);
   --rce;  if (a_terms == NULL) {
      DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk)---------------------------*/
   for (i = 0; i < s_nterm; ++i) {
      if (a_terms [0] != s_terms [i].name [0])       continue;
      if (strcmp (a_terms, s_terms [i].name) != 0)   continue;
      DEBUG_CMDS   yLOG_snote   ("found");
      DEBUG_CMDS   yLOG_sint    (i);
      DEBUG_CMDS   yLOG_sexit   (__FUNCTION__);
      return i;
   }
   /*---(failed)-------------------------*/
   --rce;
   DEBUG_CMDS   yLOG_snote   ("FAILED");
   DEBUG_CMDS   yLOG_sexitr  (__FUNCTION__, rce);
   return rce;
}
