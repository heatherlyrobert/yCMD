/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"





#define     CMDS_BASE        'b'  /* fully standard in base           */
#define     CMDS_CUST        'c'  /* fully custom, not in base        */

#define     CMDS_FIND        'f'  /* find command in list             */
#define     CMDS_EXEC        'x'  /* execute command                  */

static const uchar  *s_valid     = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_@";



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
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (MODE_COMMAND)) {
      DEBUG_PROG   yLOG_note    ("status is not ready for init");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(terms)--------------------------*/
   DEBUG_PROG   yLOG_note    ("initialize term system");
   ycmds_term_init ();
   /*---(commands)-----------------------*/
   DEBUG_PROG   yLOG_note    ("initialize command system");
   ycmds__purge ();
   /*> ycmds__load  ();                                                               <*/
   /*---(update status)------------------*/
   DEBUG_PROG   yLOG_note    ("update status");
   yMODE_init_set   (MODE_COMMAND, NULL, ySRC_mode);
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmds__purge            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   /*> char        rce         =  -10;                                                                 <* 
    *> int         i           =    0;                                                                 <* 
    *> tLINK      *x_curr      = NULL;                                                                 <* 
    *> tLINK      *x_next      = NULL;                                                                 <* 
    *> /+---(header)-------------------------+/                                                        <* 
    *> DEBUG_CMDS   yLOG_enter   (__FUNCTION__);                                                       <* 
    *> /+---(defense)------------------------+/                                                        <* 
    *> x_curr = s_head;                                                                                <* 
    *> /+---(clear)--------------------------+/                                                        <* 
    *> DEBUG_CMDS   yLOG_value   ("s_ncmd"    , s_ncmd);                                               <* 
    *> while (x_curr != NULL) {                                                                        <* 
    *>    DEBUG_CMDS   yLOG_complex ("focus"     , "%c %s", x_curr->data->base, x_curr->data->name);   <* 
    *>    x_next = x_curr->m_next;                                                                     <* 
    *>    if (x_curr->data->base != CMDS_BASE) {                                                       <* 
    *>       free (x_curr->data);                                                                      <* 
    *>    }                                                                                            <* 
    *>    x_curr->data = NULL;                                                                         <* 
    *>    free (x_curr);                                                                               <* 
    *>    x_curr = NULL;                                                                               <* 
    *>    x_curr = x_next;                                                                             <* 
    *> }                                                                                               <* 
    *> /+---(initialize pointers)------------+/                                                        <* 
    *> DEBUG_CMDS   yLOG_note    ("pointers");                                                         <* 
    *> s_head   = NULL;                                                                                <* 
    *> s_found  = NULL;                                                                                <* 
    *> /+---(initialize counters)------------+/                                                        <* 
    *> DEBUG_CMDS   yLOG_note    ("counters");                                                         <* 
    *> s_ncmd   = 0;                                                                                   <* 
    *> s_nbase  = 0;                                                                                   <* 
    *> /+---(fields)-------------------------+/                                                        <* 
    *> for (i = 0; i < 10; ++i)  myCMD.p_fields [i][0] = '\0';                                               <* 
    *> s_nfield  = 0;                                                                                  <* 
    *> myCMD.p_all [0] = '\0';                                                                               <*/
   /*---(complete)-----------------------*/
   DEBUG_CMDS   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvikeys_cmds_wrap       (void)
{
   ycmds__purge ();
   return  0;
}



