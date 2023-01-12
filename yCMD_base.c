/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"


tMY         myCMD;



#define     CMDS_BASE        'b'  /* fully standard in base           */
#define     CMDS_CUST        'c'  /* fully custom, not in base        */

#define     CMDS_FIND        'f'  /* find command in list             */
#define     CMDS_EXEC        'x'  /* execute command                  */




/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yCMD_ver [200] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yCMD_version           (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 18);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yCMD_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yCMD_ver;
}



/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
yCMD_init               (void)
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
   /*---(hook to yVIHUB)-----------------*/
   yVIHUB_from_yCMD (yCMD_direct, yCMD_add);
   /*---(terms)--------------------------*/
   DEBUG_YCMD   yLOG_note    ("initialize term system");
   ycmd_terms_init ();
   /*---(commands)-----------------------*/
   DEBUG_YCMD   yLOG_note    ("initialize command system");
   ycmd_exec_purge ();
   /*---(base/load)----------------------*/
   DEBUG_YCMD   yLOG_note    ("initialize base/load system");
   ycmd_load_init ();
   ycmd_load      ();
   /*---(base/load)----------------------*/
   DEBUG_YCMD   yLOG_note    ("initialize menu system");
   ycmd_menu_init ();
   /*---(other updates)------------------*/
   /*---(update status)------------------*/
   DEBUG_YCMD   yLOG_note    ("update status");
   yMODE_init_set   (MODE_COMMAND, NULL, ySRC_mode);
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yCMD_init_after         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         i           =    0;
   /*---(add)----------------------------*/
   rc = yFILE_dump_add ("cmds"      , "", "inventory of commands"       , ycmd_dump          );
   DEBUG_YCMD   yLOG_value   ("dump_add"  , rc);
   /*> rc = yPARSE_handler_max (MODE_COMMAND , "command"   , 7.4, "cO----------", -1, yvikeys_cmds_reader, yvikeys_cmds_writer, "------------" , "a,command-----------------", "command history"           );   <*/
   /*> DEBUG_YCMD   yLOG_value   ("command"   , rc);                                  <*/
   /*> rc = yPARSE_handler_max (MODE_SEARCH  , "search"    , 7.5, "cO----------", -1, yvikeys_srch_reader, yvikeys_srch_writer, "------------" , "a,search"                  , "search history"            );   <*/
   /*> DEBUG_YCMD   yLOG_value   ("search"    , rc);                                  <*/
   yMODE_after_set  (MODE_COMMAND);
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd_mute               (void)
{
   DEBUG_ANY   yLOG_note    (":mute¦ (ycmd_mute) muted/quiet logging output");
   yLOG_break   ();
   yLOGS_mute   ();
   yURG_name    ("mute", 'y');
   return 0;
}

char
ycmd_unmute             (void)
{
   yURG_name    ("mute", '-');
   yLOGS_unmute ();
   yLOG_break   ();
   DEBUG_ANY   yLOG_note    (":unmute¦ (ycmd_unmute) unmuted/loud logging output");
   return 0;
}

char
ycmd_urgent             (char *a_name, char a_on)
{
   char        rce         =  -10;
   --rce;  if (a_name   == NULL)              return rce;
   --rce;  if (strcmp (a_name, "") == 0)      return rce;
   --rce;  if (a_on     == 0   )              return rce;
   --rce;  if (strchr ("-yY", a_on) == NULL)  return rce;
   DEBUG_ANY   yLOG_note    (":urgent¦ (ycmd_urgent) called to control an urgent");
   DEBUG_ANY   yLOG_char    (a_name    , a_on);
   yURG_name (a_name, a_on);
   yURG_summ ();
   return 0;
}

/*> char                                                                                               <* 
 *> ycmd__purge             (void)                                                                     <* 
 *> {                                                                                                  <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                        <* 
 *>    char        rce         =  -10;                                                                 <* 
 *>    int         i           =    0;                                                                 <* 
 *>    tLINK      *x_curr      = NULL;                                                                 <* 
 *>    tLINK      *x_next      = NULL;                                                                 <* 
 *>    /+---(header)-------------------------+/                                                        <* 
 *>    DEBUG_YCMD   yLOG_enter   (__FUNCTION__);                                                       <* 
 *>    /+---(defense)------------------------+/                                                        <* 
 *>    x_curr = myCMD.c_head;                                                                                <* 
 *>    /+---(clear)--------------------------+/                                                        <* 
 *>    DEBUG_YCMD   yLOG_value   ("c_ncmd"    , myCMD.c_ncmd);                                               <* 
 *>    while (x_curr != NULL) {                                                                        <* 
 *>       DEBUG_YCMD   yLOG_complex ("focus"     , "%c %s", x_curr->data->base, x_curr->data->name);   <* 
 *>       x_next = x_curr->m_next;                                                                     <* 
 *>       if (x_curr->data->base != CMDS_BASE) {                                                       <* 
 *>          free (x_curr->data);                                                                      <* 
 *>       }                                                                                            <* 
 *>       x_curr->data = NULL;                                                                         <* 
 *>       free (x_curr);                                                                               <* 
 *>       x_curr = NULL;                                                                               <* 
 *>       x_curr = x_next;                                                                             <* 
 *>    }                                                                                               <* 
 *>    /+---(initialize pointers)------------+/                                                        <* 
 *>    DEBUG_YCMD   yLOG_note    ("pointers");                                                         <* 
 *>    myCMD.c_head   = NULL;                                                                                <* 
 *>    myCMD.c_found  = NULL;                                                                                <* 
 *>    /+---(initialize counters)------------+/                                                        <* 
 *>    DEBUG_YCMD   yLOG_note    ("counters");                                                         <* 
 *>    myCMD.c_ncmd   = 0;                                                                                   <* 
 *>    myCMD.c_nbase  = 0;                                                                                   <* 
 *>    /+---(fields)-------------------------+/                                                        <* 
 *>    for (i = 0; i < 10; ++i)  myCMD.p_fields [i][0] = '\0';                                         <* 
 *>    s_nfield  = 0;                                                                                  <* 
 *>    myCMD.p_all [0] = '\0';                                                                         <* 
 *>    /+---(complete)-----------------------+/                                                        <* 
 *>    DEBUG_YCMD   yLOG_exit    (__FUNCTION__);                                                       <* 
 *>    return 0;                                                                                       <* 
 *> }                                                                                                  <*/

char
yCMD_wrap               (void)
{
   ycmd_menu_wrap  ();
   ycmd_exec_purge ();
   return  0;
}


