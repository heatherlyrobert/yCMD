/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"



char
ycmd_dump               (FILE *f)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tLINK      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   x_curr = g_head;
   /*---(clear)--------------------------*/
   DEBUG_YCMD   yLOG_value   ("g_ncmd"    , g_ncmd);
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
