/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"





static const tCMDS  s_bases     [] = {
   /*---(yKEYS)-------------------------------------------------------------------------------------------------------------------------------*/
   { 'b', 'f', "quit"            , "q"   , yKEYS_quit                , "-"    , "quit current file (if no changes), exit if the only file"    },
   { 'b', 'f', "quitall"         , "qa"  , yKEYS_quit                , "-"    , "quit all files (if no changes), and exit"                    },
   { 'b', 'f', "writequit"       , "wq"  , yKEYS_writequit           , "-"    , ""                                                            },
   { 'b', 'f', "writequitall"    , "wqa" , yKEYS_writequitall        , "-"    , ""                                                            },
   /*> { 'b', 'c', "delay"           , ""    , yvikeys_loop_set          , "ss"   , "adjust the main loop wait and screen update timings"         },   <* 
    *> { 'b', 'c', "play"            , ""    , yvikeys_prog_play         , "-"    , "cause the progress to play"                                  },   <* 
    *> { 'b', 'c', "stop"            , ""    , yvikeys_prog_stop         , "-"    , "cause the progress to stop"                                  },   <* 
    *> { 'b', 'c', "p_scale"         , ""    , yvikeys_scale_prog        , "s"    , "adjust the progress scale"                                   },   <* 
    *> { 'b', 'c', "p_speed"         , ""    , yvikeys_speed_prog        , "s"    , "adjust the progress speed"                                   },   <* 
    *> { 'b', 'e', "mark"            , ""    , yvikeys_mark_direct       , "s"    , ""                                                            },   <*/
   /*> { 'b', 'v', "help"            , ""    , yvikeys_help              , "c"    , ""                                                            },   <* 
    *> { 'b', 'c', "sreg"            , ""    , yvikeys_sreg__direct      , "a"    , "direct definition of source registers"                       },   <*/
   /*---(yFILE)-------------------------------------------------------------------------------------------------------------------------------*/
   /*---(naming)------------*/
   { 'b', 'f', "cd"              , ""    , yFILE_loc                 , "a"    , "set the default directory for file reading and writing"      },
   { 'b', 'f', "file"            , ""    , yFILE_name                , "a"    , "rename a file for reading and writing"                       },
   { 'b', 'f', "browse"          , ""    , yFILE_browse              , "a"    , "find existing file name for reading and writing"             },
   /*---(versioning)--------*/
   { 'b', 'f', "control"         , ""    , yFILE_control             , "-"    , "turn version control ON for current file"                    },
   { 'b', 'f', "nocontrol"       , ""    , yFILE_nocontrol           , "-"    , "turn version control OFF for current file"                   },
   { 'b', 'f', "vernum"          , ""    , yFILE_vernum              , "s"    , "set a specific file version ([0-9A-Z].[0-9A-Z][a-z])"        },
   { 'b', 'f', "vertxt"          , ""    , yFILE_vertxt              , "a"    , "set a file version description"                              },
   { 'b', 'f', "major"           , ""    , yFILE_major               , "-"    , "increment the version number by a MAJOR version"             },
   { 'b', 'f', "minor"           , ""    , yFILE_minor               , "-"    , "increment the version number by a MINOR version"             },
   { 'b', 'f', "bump"            , ""    , yFILE_inc                 , "-"    , "increment the version number by a INC version"               },
   /*---(io)----------------*/
   { 'b', 'f', "write"           , "w"   , yFILE_writer              , "-"    , "write/update the current file"                               },
   { 'b', 'f', "writeas"         , "was" , yFILE_writeas             , "s"    , "write/update the current file"                               },
   { 'b', 'f', "read"            , ""    , yFILE_reader              , "-"    , "clear existing contents and open/read new file"              },
   { 'b', 'f', "edit"            , "e"   , yFILE_reader              , "-"    , "clear existing contents and open/read new file"              },
   { 'b', 'f', "new"             , ""    , yFILE_new                 , "-"    , "purge all contents and set-up a new, blank file"             },
   /*---(special)-----------*/
   { 'b', 'e', "dump"            , ""    , yFILE_dump                , "s"    , "dump a specified data table to the clipboard in flat text"   },
   /*> { 'b', 'c', "menu"            , ""    , yvikeys_menu_reanchor     , "c"    , "change the menu anchoring"                                   },   <*/
   /*---(yMACRO)------------------------------------------------------------------------------------------------------------------------------*/
   { 'b', 'r', "macro"           , ""    , yMACRO_direct             , "a"    , "direct definition of a keyboard macro"                       },
   { 'b', 'r', "script"          , "@"   , yMACRO_script_start       , "s"    , "execution of macro script from a file"                       },
   { 'b', 'r', "playback"        , ""    , yMACRO_script_playback    , "s"    , "execution of macro script from a file"                       },
   { 'b', 'r', "follow"          , ""    , yMACRO_script_follow      , "s"    , "execution of macro script from a file"                       },
   { 'b', 'r', "blitz"           , ""    , yMACRO_script_blitz       , "s"    , "execution of macro script from a file"                       },
   { 'b', 'r', "edelay"          , ""    , yMACRO_edelay             , "c"    , ""                                                            },
   { 'b', 'r', "eupdate"         , ""    , yMACRO_eupdate            , "c"    , ""                                                            },
   { 'b', 'r', "ddelay"          , ""    , yMACRO_ddelay             , "c"    , ""                                                            },
   { 'b', 'r', "dupdate"         , ""    , yMACRO_dupdate            , "c"    , ""                                                            },
   { 'b', 'r', "flatten"         , ""    , yMACRO_flatten            , "cc"   , ""                                                            },
   { 'b', 'r', "install"         , ""    , yMACRO_install            , "c"    , ""                                                            },
   /*---(yCOLOR)------------------------------------------------------------------------------------------------------------------------------*/
   { 'b', 'v', "palette"         , ""    , yCOLOR_palette            , "isss" , ""                                                            },
   { 'b', 'v', "wheel"           , ""    , yCOLOR_wheel              , "s"    , ""                                                            },
   { 'b', 'v', "degree"          , "deg" , yCOLOR_deg                , "i"    , ""                                                            },
   { 'b', 'v', "harmony"         , "har" , yCOLOR_harm               , "s"    , ""                                                            },
   { 'b', 'v', "value"           , "val" , yCOLOR_val                , "s"    , ""                                                            },
   { 'b', 'v', "saturation"      , "sat" , yCOLOR_sat                , "s"    , ""                                                            },
   /*---(yVIEW)-------------------------------------------------------------------------------------------------------------------------------*/
   { 'b', 'v', "layout"          , ""    , yVIEW_layout              , "s"    , ""                                                            },
   { 'b', 'v', "title"           , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "version"         , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "buffer"          , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "formula"         , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "nav"             , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "xaxis"           , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "yaxis"           , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "alt"             , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "details"         , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "ribbon"          , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "progress"        , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "modes"           , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "status"          , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "command"         , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "keys"            , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "cursor"          , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "grid"            , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "edges"           , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "guides"          , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "overlay"         , "o"   , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "layers"          , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "notes"           , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "mask"            , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "color"           , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "back"            , ""    , yVIEW_switch              , "Cs"   , "allow control of individual sceen elements"                  },
   { 'b', 'v', "float_loc"       , ""    , yVIEW_loc_float           , "c"    , "change where the float appears in the main window"           },
   { 'b', 'v', "hist_loc"        , ""    , yVIEW_loc_history         , "c"    , "change where the history appears in the main window"         },
   { 'b', 'v', "menu_loc"        , ""    , yVIEW_loc_menu            , "c"    , "change where the menu appears in the main window"            },
   /*> { 'b', 'v', "gridoff"         , ""    , VIEW__grid_offset         , "iii"  , ""                                                            },   <*/
   /*> { 'b', 'v', "gridsize"        , ""    , VIEW__grid_size           , "iii"  , ""                                                            },   <*/
   /*> { 'b', 'v', "layer"           , "l"   , yvikeys_layer_action      , "ss"   , ""                                                            },   <*/
   /*> { 'b', 'i', "note"            , ""    , yvikeys_note              , "a"    , "manage screen annotations (notes)"                           },   <*/
   /*---(yX11)--------------------------------------------------------------------------------------------------------------------------------*/
   /*> { 'b', 'x', "winreset"        , ""    , yX11_reset                , ""     , "move between window manager desktops"                        },   <* 
    *> { 'b', 'x', "desktop"         , ""    , yX11_desk_goto            , "c"    , "move between window manager desktops"                        },   <* 
    *> { 'b', 'x', "term"            , ""    , yX11_yvikeys_term         , "a"    , "create a terminal session"                                   },   <* 
    *> { 'b', 'x', "winname"         , ""    , yX11_yvikeys_name         , "a"    , "name an existing window"                                     },   <* 
    *> { 'b', 'x', "sendkeys"        , ""    , yX11_yvikeys_sendkeys     , "a"    , "sendkeys to a specific window"                               },   <* 
    *> { 'b', 'x', "blitzkeys"       , ""    , yX11_yvikeys_blitzkeys    , "a"    , "sendkeys to a specific window"                               },   <* 
    *> { 'b', 'x', "winexact"        , ""    , yX11_yvikeys_winexact     , "cciiii", "sendkeys to a specific window"                              },   <* 
    *> { 'b', 'x', "winplace"        , ""    , yX11_yvikeys_winplace     , "a"    , "sendkeys to a specific window"                               },   <* 
    *> { 'b', 'x', "winbring"        , ""    , yX11_yvikeys_winbring     , "c"    , "sendkeys to a specific window"                               },   <* 
    *> { 'b', 'x', "wingoto"         , ""    , yX11_yvikeys_wingoto      , "c"    , "sendkeys to a specific window"                               },   <* 
    *> { 'b', 'x', "winsend"         , ""    , yX11_yvikeys_winsend      , "cc"   , "sendkeys to a specific window"                               },   <* 
    *> { 'b', 'x', "wintake"         , ""    , yX11_yvikeys_wintake      , "cc"   , "sendkeys to a specific window"                               },   <* 
    *> { 'b', 'x', "mydesk"          , ""    , yX11_yvikeys_mydesk       , "c"    , "change position of current window"                          },    <* 
    *> { 'b', 'x', "myhome"          , ""    , yX11_yvikeys_myhome       , "ii"   , "change position of current window"                          },    <* 
    *> { 'b', 'x', "mysize"          , ""    , yX11_yvikeys_mysize       , "ii"   , "change size of current window"                              },    <* 
    *> { 'b', 'x', "mysizer"         , ""    , yX11_yvikeys_mysizer      , "iiii" , "reset all desktops, windows, and shortcuts"                  },   <*/
   /*---(done)--------------------------------------------------------------------------------------------------------------------------------*/
   { 0  , 0  , "-"               , ""    , NULL                      , ""     , ""                                                            },
};



/*====================------------------------------------====================*/
/*===----                      program level                           ----===*/
/*====================------------------------------------====================*/
static void      o___PROGRAM_________________o (void) {;}

char
ycmd_load_init          (void)
{
   int         i           =    0;
   myCMD.nbase = 0;
   for (i = 0; i < MAX_BASE; ++i) {
      if (s_bases [i].base == 0)  break;
      ++(myCMD.nbase);
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       simple support                         ----===*/
/*====================------------------------------------====================*/
static void      o___SUPPORT_________________o (void) {;}

char
ycmd_check_name         (uchar *a_name, char a_type, int *r_len)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (r_len != NULL)  *r_len = 0;
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_schar   (a_type);
   --rce;  if (a_type == 0 || strchr ("na", a_type) == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   x_len = strlen (a_name);
   DEBUG_YCMD   yLOG_sint    (x_len);
   --rce;  if (a_type == 'n' && (x_len < 1 || x_len > 18)) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_type == 'a' && x_len <= 0) {
      DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   --rce;  if (a_type == 'a' && x_len > 4) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check characters)---------------*/
   --rce;  if (strchr (YSTR_UPLOW, a_name [0]) == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   for (i = 0; i < x_len; ++i) {
      if (strchr (YSTR_ALNUM "@", a_name [i]) != NULL)  continue;
      DEBUG_YCMD   yLOG_snote   ("bad character in name");
      DEBUG_YCMD   yLOG_sint    (i);
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(output)-------------------------*/
   if (r_len != NULL)  *r_len = x_len;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
ycmd_check_dup          (uchar a_base, uchar *a_name, uchar *a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tCMDS      *x_exist     = NULL;
   tLINK      *x_link      = NULL;
   /*---(name)---------------------------*/
   if (a_base != CMDS_BASE) {
      rc = ycmd_load_by_name (a_name, &x_exist);
      DEBUG_YCMD   yLOG_value   ("base name" , rc);
      --rce;  if (rc > 0) {
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   rc = ycmd_exec_by_name (a_name, &x_link);
   DEBUG_YCMD   yLOG_value   ("base name" , rc);
   --rce;  if (rc > 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(abbreviation)-------------------*/
   if (a_base != CMDS_BASE) {
      rc = ycmd_load_by_name (a_abbr, &x_exist);
      DEBUG_YCMD   yLOG_value   ("base abbr" , rc);
      --rce;  if (rc > 0) {
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   rc = ycmd_exec_by_name (a_abbr, &x_link);
   DEBUG_YCMD   yLOG_value   ("base abbr" , rc);
   --rce;  if (rc > 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      data searching                          ----===*/
/*====================------------------------------------====================*/
static void      o___SEARCH__________________o (void) {;}

int  ycmd_load_count    (void)  { return myCMD.nbase; }

char
ycmd_load_by_name       (uchar *a_name, tCMDS **r_cmds)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         x_len       =    0;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_point   ("r_cmds"    , r_cmds);
   --rce;  if (r_cmds == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *r_cmds = NULL;
   DEBUG_YCMD   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("a_name"    , a_name);
   /*---(walk structure)-----------------*/
   --rce;  for (i = 0; i < myCMD.nbase; ++i) {
      DEBUG_YCMD   yLOG_complex ("checking"  , "%c %-5.5s %s", s_bases [i].base, s_bases [i].abbr, s_bases [i].name);
      if (strcmp (s_bases [i].abbr, a_name) == 0) {
         DEBUG_YCMD   yLOG_note    ("found by abbreviation");
         *r_cmds = s_bases + i;
         DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      if (strcmp (s_bases [i].name, a_name) == 0) {
         DEBUG_YCMD   yLOG_note    ("found by full name");
         *r_cmds = s_bases + i;
         DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
         return 1;
      }
      /*---(next)------------------------*/
   }
   DEBUG_YCMD   yLOG_note    ("never found");
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
   return rce;
}



/*====================------------------------------------====================*/
/*===----                      memory allocation                       ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ycmd_new_cmd            (uchar a_menu, uchar *a_name, uchar *a_abbr, uchar *a_terms, void *a_func, uchar *a_desc, tCMDS **r_cmds)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tCMDS      *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   tCMDS      *x_exist     = NULL;
   tLINK      *x_link      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_point   ("r_cmds"    , r_cmds);
   --rce;  if (r_cmds == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *r_cmds = NULL;
   /*---(menu)---------------------------*/
   DEBUG_YCMD   yLOG_char    ("a_menu"    , a_menu);
   --rce;  if (a_menu == 0 || strchr (YSTR_MENU "-", a_menu) == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(name)---------------------------*/
   rc = ycmd_check_name (a_name, 'n', NULL);
   DEBUG_YCMD   yLOG_value   ("name"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(abbreviation)-------------------*/
   rc = ycmd_check_name (a_abbr, 'a', NULL);
   DEBUG_YCMD   yLOG_value   ("abbr"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(duplicate)----------------------*/
   rc = ycmd_check_dup  (CMDS_CUST, a_name, a_abbr);
   DEBUG_YCMD   yLOG_value   ("dup"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(terms)--------------------------*/
   rc = ycmd_terms (a_terms);
   DEBUG_YCMD   yLOG_value   ("terms"     , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(terms)--------------------------*/
   DEBUG_YCMD   yLOG_point   ("a_func"    , a_func);
   --rce;  if (a_func == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tCMDS *) malloc (sizeof (tCMDS));
   }
   DEBUG_YCMD   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_YCMD   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YCMD   yLOG_note    ("FAILED");
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_YCMD   yLOG_note    ("populate");
   x_new->base     = CMDS_CUST;
   x_new->menu     = a_menu;
   strlcpy (x_new->name , a_name , LEN_LABEL);
   strlcpy (x_new->abbr , a_abbr , LEN_TERSE);
   x_new->f.v      = a_func;
   strlcpy (x_new->terms, a_terms, LEN_TERSE);
   if (a_desc != NULL)  strlcpy (x_new->desc , a_desc , LEN_DESC );
   else                 strlcpy (x_new->desc , ""     , LEN_DESC );
   /*---(save back)----------------------*/
   *r_cmds = x_new;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   /*---(complete)-----------------------*/
   return 1;
}

char
ycmd_new_link           (tCMDS *a_cmds, tLINK **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tLINK      *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   tLINK      *x_curr      = NULL;
   int         x_terms     =   -1;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_point   ("a_cmds"    , r_link);
   --rce;  if (r_link == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   *r_link = NULL;
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_point   ("a_cmds"    , a_cmds);
   --rce;  if (a_cmds == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("a_cmds"    , a_cmds);
   /*---(check values)-------------------*/
   DEBUG_YCMD   yLOG_point   ("name"      , a_cmds->name);
   --rce;  if (a_cmds->name  == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("name"      , a_cmds->name);
   DEBUG_YCMD   yLOG_point   ("abbr"      , a_cmds->abbr);
   --rce;  if (a_cmds->abbr  == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("abbr"      , a_cmds->abbr);
   DEBUG_YCMD   yLOG_point   ("terms"     , a_cmds->terms);
   --rce;  if (a_cmds->terms == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("terms"     , a_cmds->terms);
   x_terms = ycmd_terms (a_cmds->terms);
   DEBUG_YCMD   yLOG_value   ("x_terms"   , x_terms);
   --rce;  if (x_terms < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(duplicate)----------------------*/
   /*> DEBUG_YCMD   yLOG_point   ("->name"    , a_cmds->name);                        <*/
   /*> DEBUG_YCMD   yLOG_info    ("->name"    , a_cmds->name);                        <*/
   /*> DEBUG_YCMD   yLOG_point   ("->abbr"    , a_cmds->abbr);                        <*/
   /*> DEBUG_YCMD   yLOG_info    ("->abbr"    , a_cmds->abbr);                        <*/
   rc = ycmd_check_dup  (a_cmds->base, a_cmds->name, a_cmds->abbr);
   DEBUG_YCMD   yLOG_value   ("dup"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tLINK *) malloc (sizeof (tLINK));
   }
   DEBUG_YCMD   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_YCMD   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YCMD   yLOG_note    ("FAILED");
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_YCMD   yLOG_note    ("populate");
   x_new->data     = a_cmds;
   x_new->nlen     = strlen (a_cmds->name);
   x_new->nterms   = x_terms;
   x_new->alen     = strlen (a_cmds->abbr);
   x_new->m_next   = NULL;
   /*---(tie to master list)-------------*/
   if (g_head == NULL) {
      DEBUG_YCMD   yLOG_note    ("nothing in master list, make first");
      g_head         = x_new;
   } else  {
      DEBUG_YCMD   yLOG_note    ("append to master list");
      g_tail->m_next = x_new;
   }
   g_tail        = x_new;
   DEBUG_YCMD   yLOG_point   ("g_head"    , g_head);
   DEBUG_YCMD   yLOG_point   ("->m_next"  , g_head->m_next);
   DEBUG_YCMD   yLOG_point   ("g_tail"    , g_tail);
   DEBUG_YCMD   yLOG_point   ("m_next"    , x_new->m_next);
   /*---(update counts)------------------*/
   ++g_ncmd;
   if (x_new->data->base  == CMDS_BASE)    ++(myCMD.nbase);
   DEBUG_YCMD   yLOG_value   ("g_ncmd"    , g_ncmd);
   DEBUG_YCMD   yLOG_value   ("nbase"     , myCMD.nbase);
   /*---(save back)----------------------*/
   *r_link = x_new;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 1;
}



/*====================------------------------------------====================*/
/*===----                      data loading                            ----===*/
/*====================------------------------------------====================*/
static void  o___LOAD____________o () { return; }

char
ycmd_load_name          (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   char        rc          =    0;
   tCMDS      *x_cmds      = NULL;
   tLINK      *x_link      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(find)---------------------------*/
   rc = ycmd_load_by_name (a_name, &x_cmds);
   DEBUG_YCMD   yLOG_value   ("by_name"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(link)---------------------------*/
   rc = ycmd_new_link (s_bases + i, &x_link);
   DEBUG_YCMD   yLOG_value   ("link"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 1;
}

char
ycmd_load      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   char        rc          =    0;
   tLINK      *x_curr      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(load)---------------------------*/
   for (i = 0; i < myCMD.nbase; ++i) {
      /*---(check for end)---------------*/
      if (s_bases [i].base     == 0)                   break;
      if (s_bases [i].name [0] == NULL)                break;
      if (strcmp (s_bases [i].name, "-") == 0)         break;
      rc = ycmd_new_link (s_bases + i, &x_curr);
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yCMD_add             (uchar a_menu, uchar *a_name, uchar *a_abbr, uchar *a_terms, void *a_func, uchar *a_desc)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tCMDS      *x_cmds      = NULL;
   tLINK      *x_link      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_note    ("before status check");
   --rce;  if (!yMODE_operational (MODE_COMMAND)) {
      DEBUG_YCMD   yLOG_note    ("can not configure until operational");
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_note    ("after status check");
   /*---(call add)-----------------------*/
   rc = ycmd_new_cmd    (a_menu, a_name, a_abbr, a_terms, a_func, a_desc, &x_cmds);
   DEBUG_YCMD   yLOG_value   ("newcmd"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(call add)-----------------------*/
   rc = ycmd_new_link   (x_cmds, &x_link);
   DEBUG_YCMD   yLOG_value   ("newcmd"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 1;
}


