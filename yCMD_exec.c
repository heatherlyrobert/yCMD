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
   DEBUG_CMDS   yLOG_value   ("g_ncmd"    , g_ncmd);
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

char         /*-> tbd --------------------------------[ ------ [ge.#M5.1C#.#7]*/ /*-[03.0000.013.L]-*/ /*-[--.---.---.--]-*/
ycmd_parse              (uchar *a_str)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char       *p           = NULL;
   char       *q           = " ";
   char       *r           = NULL;
   uchar       x_work      [LEN_RECD]   = "";
   uchar       t           [LEN_RECD]   = "";
   int         x_len       = 0;
   int         x_len2      = 0;
   int         i           = 0;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(default)------------------------*/
   myCMD.p_nfield = 0;
   for (i = 0; i < 10; ++i)  strlcpy (myCMD.p_fields [i], "", LEN_RECD);
   strlcpy  (myCMD.p_all, "", LEN_RECD);
   /*---(defense)------------------------*/
   DEBUG_CMDS   yLOG_point   ("a_str"     , a_str);
   --rce;  if (a_str == NULL) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CMDS   yLOG_info    ("a_str"     , a_str);
   DEBUG_CMDS   yLOG_char    ("a_str [0]" , a_str [0]);
   --rce;  if (a_str [0] != ':') {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy  (x_work, a_str + 1, LEN_RECD);
   x_len    = strllen (x_work, LEN_RECD);
   DEBUG_CMDS   yLOG_value   ("x_len"     , x_len);
   strldchg    (x_work, G_CHAR_STORAGE, G_KEY_SPACE, LEN_RECD);
   strlrequote (x_work, LEN_RECD);
   DEBUG_CMDS   yLOG_info    ("x_work"    , x_work);
   /*---(parse command)------------------*/
   p     = strtok_r (x_work, q, &r);
   DEBUG_CMDS   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy  (myCMD.p_fields [0], p, LEN_DESC);
   DEBUG_CMDS   yLOG_info    ("p_cmd"     , p);
   /*---(parse all)----------------------*/
   x_len2 = strllen (myCMD.p_fields [0], LEN_RECD);
   DEBUG_CMDS   yLOG_value   ("x_len2"    , x_len2);
   if (x_len > x_len2) {
      strlcpy     (myCMD.p_all, p + x_len2 + 1, LEN_RECD);
      strltrim    (myCMD.p_all, ySTR_BOTH, LEN_RECD);
   }
   DEBUG_CMDS   yLOG_info    ("p_all"     , myCMD.p_all);
   /*---(parse)--------------------------*/
   for (i = 1; i < 10; ++i) {
      p = strtok_r (NULL  , q, &r);
      if (p == NULL)  break;
      DEBUG_CMDS   yLOG_value   ("i"         , i);
      DEBUG_CMDS   yLOG_info    ("p"         , p);
      strlcpy  (myCMD.p_fields [i], p, LEN_RECD);
      strltrim (myCMD.p_fields [i], ySTR_BOTH, LEN_RECD);
      strldchg (myCMD.p_fields [i], '¤', ' ', LEN_RECD);
      myCMD.p_nfield = i;
   }
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                    <* 
 *> yVIKEYS_cmds_direct     (char *a_text)                                                  <* 
 *> {                                                                                       <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                             <* 
 *>    char        rce         =  -10;                                                      <* 
 *>    char        rc          =    0;                                                      <* 
 *>    int         x_len       =    0;                                                      <* 
 *>    int         b, x, y, z;                                                              <* 
 *>    /+---(header)-------------------------+/                                             <* 
 *>    DEBUG_CMDS   yLOG_enter   (__FUNCTION__);                                            <* 
 *>    /+---(defense)------------------------+/                                             <* 
 *>    DEBUG_CMDS   yLOG_point   ("a_text"    , a_text);                                    <* 
 *>    --rce;  if (a_text == NULL) {                                                        <* 
 *>       DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                    <* 
 *>       return rce;                                                                       <* 
 *>    }                                                                                    <* 
 *>    DEBUG_CMDS   yLOG_info    ("a_text"    , a_text);                                    <* 
 *>    x_len = strlen (a_text);                                                             <* 
 *>    DEBUG_CMDS   yLOG_value   ("x_len"     , x_len);                                     <* 
 *>    /+---(check address)------------------+/                                             <* 
 *>    rc = yvikeys_map_locator (a_text + 1, &b, &x, &y, &z);                               <* 
 *>    DEBUG_CMDS   yLOG_value   ("locator"   , rc);                                        <* 
 *>    --rce;  if (rc >= 0) {                                                               <* 
 *>       DEBUG_CMDS   yLOG_complex ("position"  , "%3db, %3dx, %3dy, %3dz", b, x, y, z);   <* 
 *>       rc = yVIKEYS_jump (b, x, y, z);                                                   <* 
 *>       DEBUG_CMDS   yLOG_value   ("jump"      , rc);                                     <* 
 *>       if (rc < 0) {                                                                     <* 
 *>          DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                 <* 
 *>          return rce;                                                                    <* 
 *>       }                                                                                 <* 
 *>       DEBUG_CMDS   yLOG_exit    (__FUNCTION__);                                         <* 
 *>       return rc;                                                                        <* 
 *>    }                                                                                    <* 
 *>    /+---(normal command)-----------------+/                                             <* 
 *>    rc = yvikeys_hist_text (MODE_COMMAND, a_text);                                       <* 
 *>    DEBUG_CMDS   yLOG_value   ("history"   , rc);                                        <* 
 *>    --rce;  if (rc < 0) {                                                                <* 
 *>       DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                    <* 
 *>       return rce;                                                                       <* 
 *>    }                                                                                    <* 
 *>    rc = yvikeys_hist_exec (MODE_COMMAND);                                               <* 
 *>    DEBUG_CMDS   yLOG_value   ("exec"      , rc);                                        <* 
 *>    --rce;  if (rc < 0) {                                                                <* 
 *>       DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                    <* 
 *>       return rce;                                                                       <* 
 *>    }                                                                                    <* 
 *>    /+---(complete)-----------------------+/                                             <* 
 *>    DEBUG_CMDS   yLOG_exit    (__FUNCTION__);                                            <* 
 *>    return 0;                                                                            <* 
 *> }                                                                                       <*/

char         /*-> tbd --------------------------------[ ------ [ge.#M5.1C#.#7]*/ /*-[03.0000.013.L]-*/ /*-[--.---.---.--]-*/
yCMD_exec               (uchar *a_command, char *a_rc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_rc        =    0;
   tLINK      *x_link      = NULL;
   /*---(header)-------------------------*/
   DEBUG_CMDS   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_rc != NULL)  *a_rc = 0;
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_operational (MODE_COMMAND)) {
      DEBUG_CMDS   yLOG_note    ("can not execute until operational");
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(defense)-----------------------*/
   DEBUG_CMDS   yLOG_point   ("a_command" , a_command);
   --rce;  if (a_command == NULL || a_command [0] == '\0') {
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   DEBUG_CMDS   yLOG_info    ("a_command" , a_command);
   /*---(look for system)---------------*/
   if (strncmp (a_command, ":!", 2) == 0) {
      DEBUG_CMDS   yLOG_note    ("this is a direct run");
      rc = system (a_command + 2);
      DEBUG_CMDS   yLOG_value   ("system"    , rc);
      if (a_rc != NULL)  *a_rc = rc;
      DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(parse)-------------------------*/
   rc = ycmd_parse (a_command);
   DEBUG_CMDS   yLOG_value   ("parse"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find command)------------------*/
   rc = ycmd_exec_by_name (myCMD.p_fields [0], &x_link);
   DEBUG_CMDS   yLOG_value   ("find exec" , rc);
   --rce;  if (rc < 0) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(launch)------------------------*/
   rc = ycmd_launch (x_link, &x_rc);
   DEBUG_CMDS   yLOG_value   ("launch"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_CMDS   yLOG_value   ("return"    , x_rc);
   if (a_rc != NULL)  *a_rc = x_rc;
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 1;
}

char         /*-> tbd --------------------------------[ ------ [ge.#M5.1C#.#7]*/ /*-[03.0000.013.L]-*/ /*-[--.---.---.--]-*/
yCMD_direct             (uchar *a_command)
{
   char        rc          =    0;
   char        x_rc        =    0;
   rc = yCMD_exec (a_command, &x_rc);
   if (rc < 0) return rc;
   return 0;
}


