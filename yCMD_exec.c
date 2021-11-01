/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"




/*---(true useful vars)---------------*/
tLINK  *g_head   = NULL;              /* head of link chain            */
tLINK  *g_tail   = NULL;              /* tail of link chain            */
/*---(menu grphics/unit testing)------*/
tLINK  *g_found  = NULL;              /* result of last find           */
/*---(DEBUGGING FASTER)---------------*/
short   g_ncmd   = 0;                 /* all menu items in list        */
/*---(done)---------------------------*/



/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
ycmd_exec_purge         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   tLINK      *x_curr      = NULL;
   tLINK      *x_next      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   x_curr = g_head;
   /*---(clear)--------------------------*/
   DEBUG_CMDS   yLOG_value   ("g_ncmd"    , g_ncmd);
   while (x_curr != NULL) {
      DEBUG_CMDS   yLOG_complex ("focus"     , "%c %s", x_curr->data->base, x_curr->data->name);
      x_next = x_curr->m_next;
      if (x_curr->data->base != CMDS_BASE) {
         free (x_curr->data);
      }
      x_curr->data = NULL;
      free (x_curr);
      x_curr = x_next;
   }
   /*---(initialize pointers)------------*/
   DEBUG_CMDS   yLOG_note    ("pointers");
   g_head   = NULL;
   g_tail   = NULL;
   /*---(initialize counters)------------*/
   DEBUG_CMDS   yLOG_note    ("counters");
   g_ncmd   = 0;
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      searching data                          ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;}

int  ycmd_exec_count    (void)  { return g_ncmd; }

char
ycmd_exec_by_name       (uchar *a_name, tLINK **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   tLINK      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CMDS   yLOG_point   ("r_link"    , r_link);
   --rce;  if (r_link == NULL) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *r_link = NULL;
   DEBUG_CMDS   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CMDS   yLOG_info    ("a_name"    , a_name);
   /*---(prepare)------------------------*/
   x_len   = strlen (a_name);
   x_curr  = g_head;
   /*---(walk structure)-----------------*/
   --rce;  while (x_curr != NULL) {
      /*---(output)----------------------*/
      DEBUG_CMDS   yLOG_complex ("checking"  , "%c %-5.5s %s", x_curr->data->base, x_curr->data->abbr, x_curr->data->name);
      /*---(check abbr)------------------*/
      if (x_curr->alen > 0 && x_curr->alen == x_len) {
         if (x_curr->data->abbr [0] == a_name [0]) {
            if (strcmp (x_curr->data->abbr, a_name) == 0) {
               DEBUG_CMDS   yLOG_note    ("found by abbreviation");
               *r_link = x_curr;
               DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
               return 1;
            }
         }
      }
      /*---(check name)------------------*/
      if (x_curr->nlen > 0 && x_curr->nlen == x_len) {
         if (x_curr->data->name [0] == a_name [0]) {
            if (strcmp (x_curr->data->name, a_name) == 0) {
               DEBUG_CMDS   yLOG_note    ("found by full name");
               *r_link = x_curr;
               DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
               return 1;
            }
         }
      }
      /*---(next)------------------------*/
      x_curr = x_curr->m_next;
   }
   DEBUG_CMDS   yLOG_note    ("never found");
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}

char
ycmd_exec_by_index      (short a_index, tLINK **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         c           =    0;
   tLINK      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_CMDS   yLOG_point   ("r_link"    , r_link);
   --rce;  if (r_link == NULL) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   *r_link = NULL;
   x_curr  = g_head;
   /*---(walk structure)-----------------*/
   --rce;  while (x_curr != NULL) {
      /*---(output)----------------------*/
      DEBUG_CMDS   yLOG_complex ("checking"  , "%c %-5.5s %s", x_curr->data->base, x_curr->data->abbr, x_curr->data->name);
      if (c >= a_index) {
         DEBUG_CMDS   yLOG_note    ("found index");
         *r_link = x_curr;
         DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      ++c;
      x_curr = x_curr->m_next;
   }
   DEBUG_CMDS   yLOG_note    ("never found");
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}


