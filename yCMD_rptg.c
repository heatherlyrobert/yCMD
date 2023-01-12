/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"



#define   MENU_EMPTY  "· · · · -          · · ·   -åæ                           ·  ·  ··-"



char
ycmd_dump               (FILE *f)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tLINK      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   x_curr = myCMD.c_head;
   /*---(clear)--------------------------*/
   DEBUG_YCMD   yLOG_value   ("c_ncmd"    , myCMD.c_ncmd);
   while (x_curr != NULL) {
      DEBUG_YCMD   yLOG_complex ("focus"     , "%c %s", x_curr->data->base, x_curr->data->name);
      fprintf (f, "%c %c %-15.15s %-6.6s %-6.6s %s\n",
            x_curr->data->base,  x_curr->data->menu,
            x_curr->data->name,  x_curr->data->abbr,
            x_curr->data->terms, x_curr->data->desc);
      x_curr = x_curr->m_next;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd_menu_line          (tMLINK *a_curr, char *a_line)
{
   tMENU      *p           = NULL;
   char        x_count     [LEN_TERSE] = "";
   char        x_keys      [LEN_HUND]  = "";
   strcpy (a_line, MENU_EMPTY);
   if (a_line == NULL)  return -1;
   if (a_curr == NULL)  return -1;
   if (a_curr->data == NULL)  return -1;
   p = a_curr->data;
   strlpadn (a_curr->c_count, x_count, '.', '>', 3);
   sprintf (x_keys, "%2då%.25sæ", strlen (p->keys), p->keys);
   sprintf (a_line, "%c %c %c %c %-10.10s %c %c %c  %-29.29s  %c  %c  %s",
         p->base, p->top, p->mid, p->bot,
         p->name, p->active, a_curr->active, p->type, x_keys,
         (a_curr->s_next  != NULL) ? 'N' : '-',
         (a_curr->c_first != NULL) ? 'C' : '-',
         x_count);
   return 0;
}

char*
ycmd_menu_counts        (void)
{
   sprintf (g_print, "%3dn, %3db, %3da, %3dg, %3dh, %3dt, %3dm, %3db",
     myCMD.m_nmenu, myCMD.m_nbase, myCMD.m_nreal,
     myCMD.m_ngrey, myCMD.m_nhide,
     myCMD.m_ntops, myCMD.m_nmids, myCMD.m_nbots);
   return g_print;
}

char*
ycmd_menu_by_index      (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tMLINK     *x_curr      = NULL;
   int         c           =    0;
   if (n < 0)               return MENU_EMPTY;
   if (n >= myCMD.m_nmenu)  return MENU_EMPTY;
   x_curr = myCMD.m_head;
   while (x_curr != NULL) {
      if (c == n) {
         ycmd_menu_line (x_curr, g_print);
         return g_print;
      }
      x_curr = x_curr->m_next;
      ++c;
   }
   return MENU_EMPTY;
}

char
ycmd_menu_dump          (FILE *f)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tMLINK     *x_curr      = NULL;
   int         n           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   x_curr = myCMD.m_head;
   /*---(clear)--------------------------*/
   DEBUG_YCMD   yLOG_value   ("m_nmenu"   , myCMD.m_nmenu);
   while (x_curr != NULL) {
      fprintf (f, "%s\n", ycmd_menu_by_index (n));
      x_curr = x_curr->m_next;
      ++n;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}


