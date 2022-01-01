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
   /*---(other updates)------------------*/
   rc = yFILE_dump_add ("cmds"      , "inventory of commands"       , ycmd_dump          );
   /*---(update status)------------------*/
   DEBUG_YCMD   yLOG_note    ("update status");
   yMODE_init_set   (MODE_COMMAND, NULL, ySRC_mode);
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
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
 *>    x_curr = g_head;                                                                                <* 
 *>    /+---(clear)--------------------------+/                                                        <* 
 *>    DEBUG_YCMD   yLOG_value   ("g_ncmd"    , g_ncmd);                                               <* 
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
 *>    g_head   = NULL;                                                                                <* 
 *>    g_found  = NULL;                                                                                <* 
 *>    /+---(initialize counters)------------+/                                                        <* 
 *>    DEBUG_YCMD   yLOG_note    ("counters");                                                         <* 
 *>    g_ncmd   = 0;                                                                                   <* 
 *>    g_nbase  = 0;                                                                                   <* 
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
   ycmd_exec_purge ();
   return  0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char           unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
ycmd__unit_quiet        (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yCMD_unit" };
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yCMD_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
ycmd__unit_loud         (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yCMD_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yURG_name  ("ymode"        , YURG_ON);
   yURG_name  ("ycmd"         , YURG_ON);
   yURG_name  ("ysrc"         , YURG_ON);
   DEBUG_YCMD  yLOG_info     ("yCMD"      , yCMD_version   ());
   yMODE_init (MODE_MAP);
   yMODE_handler_setup ();
   yCMD_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
ycmd__unit_end          (void)
{
   DEBUG_YCMD  yLOG_enter   (__FUNCTION__);
   yCMD_wrap    ();
   DEBUG_YCMD  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char
ycmd__unit_parrot       (char a_value)
{
   return a_value;
}

char
ycmd__unit_length       (char *a_string)
{
   if (a_string == NULL)  return -1;
   return strlen (a_string);
}

char
ycmd__unit_tester       (char a_mode, char a_value)
{
   switch (a_mode) {
   case '+' : a_value += 1;  break;
   case '5' : a_value += 5;  break;
   case '-' : a_value -= 1;  break;
   case '0' : a_value  = 0;  break;
   case '9' : a_value -= 9;  break;
   }
   return a_value;
}

char           unit_answer [LEN_FULL];

char*        /*-> unit test accessor -----------------[ light  [us.420.111.11]*/ /*-[01.0000.00#.Z]-*/ /*-[--.---.---.--]-*/
yCMD__unit              (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        r           [LEN_FULL]  = "";
   char        s           [LEN_FULL]  = "";
   char        t           [LEN_FULL]  = "";
   int         i           =    0;
   tLINK      *x_curr      = NULL;
   tCMDS      *p           = NULL;
   /*---(preprare)-----------------------*/
   strcpy  (unit_answer, "CMD unit         : question not understood");
   /*---(selection)----------------------*/
   if      (strcmp (a_question, "p_all"          )   == 0) {
      sprintf (s, "%2då%-.10sæ", strlen (myCMD.p_fields [0]), myCMD.p_fields [0]);
      sprintf (t, "%2då%-.50sæ", strlen (myCMD.p_all), myCMD.p_all);
      snprintf (unit_answer, LEN_FULL, "CMD p_all        : %-14.14s  %s", s, t);
   }
   else if (strcmp (a_question, "p_field"        )   == 0) {
      snprintf (unit_answer, LEN_FULL, "CMD p_field (%2d) :", myCMD.p_nfield);
      for (i = 1; i < 7; ++i)  {
          sprintf (s, " %2då%-.8sæ", strlen (myCMD.p_fields [i]), myCMD.p_fields [i]);
          sprintf (t, "%-13.13s", s);
          if (i < 6) strlcat (unit_answer, t, LEN_FULL);
          else       strlcat (unit_answer, s, LEN_FULL);
      }
   }
   else if (strcmp (a_question, "master"         )   == 0) {
      ycmd_exec_by_index (n, &x_curr);
      if (x_curr == NULL)  snprintf (unit_answer, LEN_FULL, "CMD master  (%2d) : -   -åæ                      -åæ1234  -åæ          %p", n, NULL);
      else {
         p = x_curr->data;
         sprintf (r, "%2då%-.20sæ", x_curr->nlen, p->name);
         sprintf (s, "%1då%-.4sæ" , x_curr->alen, p->abbr);
         sprintf (t, "%1då%-.8sæ" , x_curr->nterms, p->terms);
         snprintf (unit_answer, LEN_FULL, "CMD master  (%2d) : %c  %-24.24s  %-7.7s  %-11.11s  %p",
               n, p->base, r, s, t, p->f.v);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}



