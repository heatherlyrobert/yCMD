/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"




static const uchar  *s_valid     = "·*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789+-_?!#,.èéêëìíîïðñòóôõö÷øùúûüýþÿ";



/*> static float   s_xpos   [LEN_LABEL] = { 0.0, 2.0, 5.0, 7.0, 7.5, 7.5, 7.0, 5.0, 2.0, 0.0,-2.0,-5.0,-7.0,-7.5,-7.5,-7.0,-5.0,-2.0 };   <*/
static float   s_xpos   [LEN_LABEL] = { 0.0, 2.0, 5.5, 8.0, 9.0, 9.0, 8.0, 5.5, 2.0, 0.0,-2.0,-5.5,-8.0,-9.0,-9.0,-8.0,-5.5,-2.0 };

static float   s_ypos   [LEN_LABEL] = { 3.0, 3.0, 2.0, 1.0, 0.0,-1.0,-2.0,-3.0,-4.0,-4.0,-4.0,-3.0,-2.0,-1.0, 0.0, 1.0, 2.0, 3.0 };

static int     s_align  [LEN_LABEL] = {   2,   1,   1,   1,   1,   1,   1,   1,   1,   2,   3,   3,   3,   3,   3,   3,   3,   3 };
static float   s_abbr   [LEN_LABEL] = { 1.0,   0,   0,   0,   0,   0,   0,   0,   0,-1.0,   0,   0,   0,   0,   0,   0,   0,   0 };

static char    s_type   = YVIEW_FLAT;
static char    s_anchor = YVIEW_TOPCEN;
static float   s_ce     = 0.0;
static float   s_x      = 140.0;
static float   s_mi     = 0.0;
static float   s_y      = 100.0;
static float   s_z      = 300.0;
static int     s_pt     = 8;
static int     s_xoff   = 15.0;
static int     s_yoff   =  0.0;

/*> "fevisomdtplbgaxcsh"                                                                                                                                <* 
 *> "file, edit, veiw, insert, select, format, modify, dataset, tools, palette, layers, buffer, language, auditor, execute, configure, script, share"   <*/

static const tMENU  s_base [] = {
   /*---(root)---------------------------------------------------*/
   { 'b', '·', '·', '·', "ROOT"        , 'y', MENU_GROUP , "-"                              },
   /*---(file menu)----------------------------------------------*/
   { 'b', 'f', '·', '·', "filesys"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'f', 'W', '·', "workspace"   , '-', MENU_GROUP , "-"                              },
   { 'b', 'f', 'w', '·', "new"         , 'y', MENU_CMD   , ":new¦"                          },
   { 'b', 'f', 'c', '·', "chdir"       , 'y', MENU_MORE  , ":cd·"                           },
   { 'b', 'f', 'b', '·', "browse"      , 'y', MENU_MORE  , ":browse·"                       },
   { 'b', 'f', 'n', '·', "name"        , 'y', MENU_MORE  , ":file·"                         },
   { 'b', 'f', 'o', '·', "read"        , 'y', MENU_CMD   , ":read¦"                         },
   { 'b', 'f', 'm', '·', "import"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'f', 'f', '·', "refresh"     , 'y', MENU_CMD   , ":refresh¦"                      },
   { 'b', 'f', 'r', '·', "restore"     , '-', MENU_TBD   , "-"                              },
   { 'b', 'f', 'v', '·', "version"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'f', 'v', 'c', "ctrl"        , 'y', MENU_CMD   , ":control¦"                      },
   { 'b', 'f', 'v', 'n', "noctrl"      , 'y', MENU_CMD   , ":nocontrol¦"                    },
   { 'b', 'f', 'v', '1', "major"       , 'y', MENU_CMD   , ":major¦"                        },
   { 'b', 'f', 'v', '2', "minor"       , 'y', MENU_CMD   , ":minor¦"                        },
   { 'b', 'f', 'v', '3', "bump"        , 'y', MENU_CMD   , ":bump¦"                         },
   { 'b', 'f', 'v', 't', "vertxt"      , 'y', MENU_MORE  , ":vertxt·"                       },
   { 'b', 'f', 'v', 'm', "manual"      , 'y', MENU_MORE  , ":vernum·"                       },
   { 'b', 'f', 'p', '·', "protect"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'f', 'u', '·', "update"      , 'y', MENU_TBD   , "-"                              },
   { 'b', 'f', 's', '·', "write"       , 'y', MENU_CMD   , ":write¦"                        },
   { 'b', 'f', 'a', '·', "writeas"     , 'y', MENU_MORE  , ":writeas·"                      },
   { 'b', 'f', 'x', '·', "export"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'f', 'q', '·', "quit"        , 'y', MENU_CMD   , ":quit¦"                         },
   /*---(edit menu)----------------------------------------------*/
   { 'b', 'e', '·', '·', "editing"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'u', '·', "undo"        , '-', MENU_EXACT , "u"                              },
   { 'b', 'e', 'U', '·', "redo"        , '-', MENU_EXACT , "U"                              },
   { 'b', 'e', '_', '·', "status"      , '-', MENU_EXACT , ":status mundo¦"                 },
   { 'b', 'e', '?', '·', "history"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', '?', 't', "track"       , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', '?', 'u', "untrack"     , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', '?', 'c', "clear"       , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', '?', 'r', "review"      , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'y', '·', "copy"        , '-', MENU_EXACT , "y"                              },
   { 'b', 'e', 'Y', '·', "cut"         , '-', MENU_EXACT , "Y"                              },
   { 'b', 'e', 'p', '·', "paste"       , '-', MENU_EXACT , "p"                              },
   { 'b', 'e', 'P', '·', "special"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'x', '·', "clear"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'x', '.', "inplace"     , '-', MENU_EXACT , "x."                             },
   { 'b', 'e', 'x', 'h', "left"        , '-', MENU_EXACT , "xh"                             },
   { 'b', 'e', 'x', 'l', "right"       , '-', MENU_EXACT , "xl"                             },
   { 'b', 'e', 'x', 'k', "up"          , '-', MENU_EXACT , "xk"                             },
   { 'b', 'e', 'x', 'j', "down"        , '-', MENU_EXACT , "xj"                             },
   { 'b', 'e', 'x', 'i', "in"          , '-', MENU_EXACT , "xi"                             },
   { 'b', 'e', 'x', 'o', "out"         , '-', MENU_EXACT , "xo"                             },
   { 'b', 'e', 'x', 'x', "col_lef"     , '-', MENU_EXACT , "xx"                             },
   { 'b', 'e', 'x', 'X', "col_rig"     , '-', MENU_EXACT , "xX"                             },
   { 'b', 'e', 'x', 'y', "row_abo"     , '-', MENU_EXACT , "xy"                             },
   { 'b', 'e', 'x', 'Y', "row_bel"     , '-', MENU_EXACT , "xY"                             },
   { 'b', 'e', 'x', 'z', "lvl_in"      , '-', MENU_EXACT , "xz"                             },
   { 'b', 'e', 'x', 'Z', "lvl_out"     , '-', MENU_EXACT , "xZ"                             },
   { 'b', 'e', 'd', '·', "delete"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'd', 'l', "left"        , '-', MENU_EXACT , "dl"                             },
   { 'b', 'e', 'd', 'h', "right"       , '-', MENU_EXACT , "dh"                             },
   { 'b', 'e', 'd', 'k', "up"          , '-', MENU_EXACT , "dk"                             },
   { 'b', 'e', 'd', 'j', "down"        , '-', MENU_EXACT , "dj"                             },
   { 'b', 'e', 'd', 'i', "in"          , '-', MENU_EXACT , "di"                             },
   { 'b', 'e', 'd', 'o', "out"         , '-', MENU_EXACT , "do"                             },
   { 'b', 'e', 'd', 'x', "col_left"    , '-', MENU_EXACT , "dx"                             },
   { 'b', 'e', 'd', 'X', "col_right"   , '-', MENU_EXACT , "dX"                             },
   { 'b', 'e', 'd', 'y', "row_above"   , '-', MENU_EXACT , "dy"                             },
   { 'b', 'e', 'd', 'Y', "row_below"   , '-', MENU_EXACT , "dY"                             },
   { 'b', 'e', 'd', 'z', "lvl_in"      , '-', MENU_EXACT , "dz"                             },
   { 'b', 'e', 'd', 'Z', "lvl_out"     , '-', MENU_EXACT , "dZ"                             },
   { 'b', 'e', 'i', '·', "insert"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'i', 'l', "left"        , '-', MENU_EXACT , "al"                             },
   { 'b', 'e', 'i', 'h', "right"       , '-', MENU_EXACT , "ah"                             },
   { 'b', 'e', 'i', 'k', "up"          , '-', MENU_EXACT , "ak"                             },
   { 'b', 'e', 'i', 'j', "down"        , '-', MENU_EXACT , "aj"                             },
   { 'b', 'e', 'i', 'i', "in"          , '-', MENU_EXACT , "ai"                             },
   { 'b', 'e', 'i', 'o', "out"         , '-', MENU_EXACT , "ao"                             },
   { 'b', 'e', 'i', 'x', "col_lef"     , '-', MENU_EXACT , "ax"                             },
   { 'b', 'e', 'i', 'X', "col_rig"     , '-', MENU_EXACT , "aX"                             },
   { 'b', 'e', 'i', 'y', "row_abo"     , '-', MENU_EXACT , "ay"                             },
   { 'b', 'e', 'i', 'Y', "row_bel"     , '-', MENU_EXACT , "aY"                             },
   { 'b', 'e', 'i', 'z', "lvl_in"      , '-', MENU_EXACT , "az"                             },
   { 'b', 'e', 'i', 'Z', "lvl_out"     , '-', MENU_EXACT , "aZ"                             },
   { 'b', 'e', 'g', '·', "group"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'g', 'g', "group"       , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'g', 'u', "ungroup"     , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'g', 'r', "regroup"     , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'g', 'm', "merge"       , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'g', 'f', "free"        , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'g', 'b', "boundary"    , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', '·', "align"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'a', 'k', "top"         , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'j', "bottom"      , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'h', "left"        , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'l', "right"       , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'o', "front"       , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'i', "back"        , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'x', "dist-x"      , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'y', "dist-y"      , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'a', 'z', "dist-z"      , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'o', '·', "order"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'e', 'o', 'n', "front"       , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'o', 'i', "forward"     , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'o', 'o', "backward"    , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'o', 'f', "back"        , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'o', 'r', "reverse"     , '-', MENU_EXACT , "-"                              },
   { 'b', 'e', 'l', '·', "layer"       , '-', MENU_MORE  , "-"                              },
   /*---(view menu)-----------------------------------------------------------*/
   { 'b', 'v', '·', '·', "viewing"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'w', '·', "window"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'l', '·', "layout"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'l', 'n', "minimal"     , 'y', MENU_CMD   , ":layout···min¦"                 },
   { 'b', 'v', 'l', 'n', "work"        , 'y', MENU_CMD   , ":layout···work¦"                },
   { 'b', 'v', 'l', 'n', "gyges"       , 'y', MENU_CMD   , ":layout···gyges¦"               },
   { 'b', 'v', 'l', 'x', "maximum"     , 'y', MENU_CMD   , ":layout···max¦"                 },
   { 'b', 'v', 't', '·', "title"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 't', 's', "show"        , 'y', MENU_CMD   , ":title····show¦"                },
   { 'b', 'v', 't', 'h', "hide"        , 'y', MENU_CMD   , ":title····hide¦"                },
   { 'b', 'v', 't', 'e', "enable"      , 'y', MENU_CMD   , ":title····enable¦"              },
   { 'b', 'v', 't', 'd', "disable"     , 'y', MENU_CMD   , ":title····disable¦"             },
   { 'b', 'v', 'v', '·', "version"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'v', 's', "show"        , 'y', MENU_CMD   , ":version··show¦"                },
   { 'b', 'v', 'v', 'h', "hide"        , 'y', MENU_CMD   , ":version··hide¦"                },
   { 'b', 'v', 'v', 'e', "enable"      , 'y', MENU_CMD   , ":version··enable¦"              },
   { 'b', 'v', 'v', 'd', "disable"     , 'y', MENU_CMD   , ":version··disable¦"             },
   { 'b', 'v', 'b', '·', "buffer"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'b', 's', "show"        , 'y', MENU_CMD   , ":buffer···show¦"                },
   { 'b', 'v', 'b', 'h', "hide"        , 'y', MENU_CMD   , ":buffer···hide¦"                },
   { 'b', 'v', 'b', 'e', "enable"      , 'y', MENU_CMD   , ":buffer···enable¦"              },
   { 'b', 'v', 'b', 'd', "disable"     , 'y', MENU_CMD   , ":buffer···disable¦"             },
   { 'b', 'v', 'f', '·', "formula"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'f', 's', "show"        , 'y', MENU_CMD   , ":formula··show¦"                },
   { 'b', 'v', 'f', 'h', "hide"        , 'y', MENU_CMD   , ":formula··hide¦"                },
   { 'b', 'v', 'f', 'e', "enable"      , 'y', MENU_CMD   , ":formula··enable¦"              },
   { 'b', 'v', 'f', 'd', "disable"     , 'y', MENU_CMD   , ":formula··disable¦"             },
   { 'b', 'v', 'f', 'm', "minimum"     , 'y', MENU_CMD   , ":formula··min¦"                 },
   { 'b', 'v', 'f', 'n', "normal"      , 'y', MENU_CMD   , ":formula··small¦"               },
   { 'b', 'v', 'f', 'l', "label"       , 'y', MENU_CMD   , ":formula··label¦"               },
   { 'b', 'v', 'f', 'x', "maximum"     , 'y', MENU_CMD   , ":formula··max¦"                 },
   { 'b', 'v', 'n', '·', "xaxis"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'n', 's', "show"        , 'y', MENU_CMD   , ":nav······show¦"                },
   { 'b', 'v', 'n', 'h', "hide"        , 'y', MENU_CMD   , ":nav······hide¦"                },
   { 'b', 'v', 'n', 'e', "enable"      , 'y', MENU_CMD   , ":nav······enable¦"              },
   { 'b', 'v', 'n', 'd', "disable"     , 'y', MENU_CMD   , ":nav······disable¦"             },
   { 'b', 'v', 'X', '·', "xaxis"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'X', 's', "show"        , 'y', MENU_CMD   , ":xaxis····show¦"                },
   { 'b', 'v', 'X', 'h', "hide"        , 'y', MENU_CMD   , ":xaxis····hide¦"                },
   { 'b', 'v', 'X', 'e', "enable"      , 'y', MENU_CMD   , ":xaxis····enable¦"              },
   { 'b', 'v', 'X', 'd', "disable"     , 'y', MENU_CMD   , ":xaxis····disable¦"             },
   { 'b', 'v', 'Y', '·', "yaxis"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'Y', 's', "show"        , 'y', MENU_CMD   , ":yaxis····show¦"                },
   { 'b', 'v', 'Y', 'h', "hide"        , 'y', MENU_CMD   , ":yaxis····hide¦"                },
   { 'b', 'v', 'Y', 'e', "enable"      , 'y', MENU_CMD   , ":yaxis····enable¦"              },
   { 'b', 'v', 'Y', 'd', "disable"     , 'y', MENU_CMD   , ":yaxis····disable¦"             },
   { 'b', 'v', 'a', '·', "alt"         , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'a', 's', "show"        , 'y', MENU_CMD   , ":alt······show¦"                },
   { 'b', 'v', 'a', 'h', "hide"        , 'y', MENU_CMD   , ":alt······hide¦"                },
   { 'b', 'v', 'a', 'e', "enable"      , 'y', MENU_CMD   , ":alt······enable¦"              },
   { 'b', 'v', 'a', 'd', "disable"     , 'y', MENU_CMD   , ":alt······disable¦"             },
   { 'b', 'v', 'd', '·', "details"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'd', 's', "show"        , 'y', MENU_CMD   , ":details··show¦"                },
   { 'b', 'v', 'd', 'h', "hide"        , 'y', MENU_CMD   , ":details··hide¦"                },
   { 'b', 'v', 'd', 'e', "enable"      , 'y', MENU_CMD   , ":details··enable¦"              },
   { 'b', 'v', 'd', 'd', "disable"     , 'y', MENU_CMD   , ":details··disable¦"             },
   { 'b', 'v', 'r', '·', "ribbon"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'r', 's', "show"        , 'y', MENU_CMD   , ":ribbon···show¦"                },
   { 'b', 'v', 'r', 'h', "hide"        , 'y', MENU_CMD   , ":ribbon···hide¦"                },
   { 'b', 'v', 'r', 'e', "enable"      , 'y', MENU_CMD   , ":ribbon···enable¦"              },
   { 'b', 'v', 'r', 'd', "disable"     , 'y', MENU_CMD   , ":ribbon···disable¦"             },
   { 'b', 'v', 'p', '·', "progress"    , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'p', 's', "show"        , 'y', MENU_CMD   , ":progress·show¦"                },
   { 'b', 'v', 'p', 'h', "hide"        , 'y', MENU_CMD   , ":progress·hide¦"                },
   { 'b', 'v', 'p', 'e', "enable"      , 'y', MENU_CMD   , ":progress·enable¦"              },
   { 'b', 'v', 'p', 'd', "disable"     , 'y', MENU_CMD   , ":progress·disable¦"             },
   { 'b', 'v', 'x', '·', "modes"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'x', 's', "show"        , 'y', MENU_CMD   , ":modes····show¦"                },
   { 'b', 'v', 'x', 'h', "hide"        , 'y', MENU_CMD   , ":modes····hide¦"                },
   { 'b', 'v', 'x', 'e', "enable"      , 'y', MENU_CMD   , ":modes····enable¦"              },
   { 'b', 'v', 'x', 'd', "disable"     , 'y', MENU_CMD   , ":modes····disable¦"             },
   { 'b', 'v', 's', '·', "status"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 's', 's', "show"        , 'y', MENU_CMD   , ":status···show¦"                },
   { 'b', 'v', 's', 'h', "hide"        , 'y', MENU_CMD   , ":status···hide¦"                },
   { 'b', 'v', 's', 'e', "enable"      , 'y', MENU_CMD   , ":status···enable¦"              },
   { 'b', 'v', 's', 'd', "disable"     , 'y', MENU_CMD   , ":status···disable¦"             },
   { 'b', 'v', 'c', '·', "command"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'c', 's', "show"        , 'y', MENU_CMD   , ":command··show¦"                },
   { 'b', 'v', 'c', 'h', "hide"        , 'y', MENU_CMD   , ":command··hide¦"                },
   { 'b', 'v', 'c', 'e', "enable"      , 'y', MENU_CMD   , ":command··enable¦"              },
   { 'b', 'v', 'c', 'd', "disable"     , 'y', MENU_CMD   , ":command··disable¦"             },
   { 'b', 'v', 'k', '·', "keys"        , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'k', 's', "show"        , 'y', MENU_CMD   , ":keys·····show¦"                },
   { 'b', 'v', 'k', 'h', "hide"        , 'y', MENU_CMD   , ":keys·····hide¦"                },
   { 'b', 'v', 'k', 'e', "enable"      , 'y', MENU_CMD   , ":keys·····enable¦"              },
   { 'b', 'v', 'k', 'd', "disable"     , 'y', MENU_CMD   , ":keys·····disable¦"             },
   { 'b', 'v', 'C', '·', "cursor"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'C', 's', "show"        , 'y', MENU_CMD   , ":cursor···show¦"                },
   { 'b', 'v', 'C', 'h', "hide"        , 'y', MENU_CMD   , ":cursor···hide¦"                },
   { 'b', 'v', 'C', 'e', "enable"      , 'y', MENU_CMD   , ":cursor···enable¦"              },
   { 'b', 'v', 'C', 'd', "disable"     , 'y', MENU_CMD   , ":cursor···disable¦"             },
   { 'b', 'v', 'G', '·', "grid"        , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'G', 's', "show"        , 'y', MENU_CMD   , ":grid·····show¦"                },
   { 'b', 'v', 'G', 'h', "hide"        , 'y', MENU_CMD   , ":grid·····hide¦"                },
   { 'b', 'v', 'G', 'e', "enable"      , 'y', MENU_CMD   , ":grid·····enable¦"              },
   { 'b', 'v', 'G', 'd', "disable"     , 'y', MENU_CMD   , ":grid·····disable¦"             },
   { 'b', 'v', 'E', '·', "edges"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'E', 's', "show"        , 'y', MENU_CMD   , ":edges····show¦"                },
   { 'b', 'v', 'E', 'h', "hide"        , 'y', MENU_CMD   , ":edges····hide¦"                },
   { 'b', 'v', 'E', 'e', "enable"      , 'y', MENU_CMD   , ":edges····enable¦"              },
   { 'b', 'v', 'E', 'd', "disable"     , 'y', MENU_CMD   , ":edges····disable¦"             },
   { 'b', 'v', 'U', '·', "guides"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'U', 's', "show"        , 'y', MENU_CMD   , ":guides···show¦"                },
   { 'b', 'v', 'U', 'h', "hide"        , 'y', MENU_CMD   , ":guides···hide¦"                },
   { 'b', 'v', 'U', 'e', "enable"      , 'y', MENU_CMD   , ":guides···enable¦"              },
   { 'b', 'v', 'U', 'd', "disable"     , 'y', MENU_CMD   , ":guides···disable¦"             },
   { 'b', 'v', 'O', '·', "overlay"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'O', 's', "show"        , 'y', MENU_CMD   , ":overlay··show¦"                },
   { 'b', 'v', 'O', 'h', "hide"        , 'y', MENU_CMD   , ":overlay··hide¦"                },
   { 'b', 'v', 'O', 'e', "enable"      , 'y', MENU_CMD   , ":overlay··enable¦"              },
   { 'b', 'v', 'O', 'd', "disable"     , 'y', MENU_CMD   , ":overlay··disable¦"             },
   { 'b', 'v', 'L', '·', "layers"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'L', 's', "show"        , 'y', MENU_CMD   , ":layers···show¦"                },
   { 'b', 'v', 'L', 'h', "hide"        , 'y', MENU_CMD   , ":layers···hide¦"                },
   { 'b', 'v', 'L', 'e', "enable"      , 'y', MENU_CMD   , ":layers···enable¦"              },
   { 'b', 'v', 'L', 'd', "disable"     , 'y', MENU_CMD   , ":layers···disable¦"             },
   { 'b', 'v', 'N', '·', "notes"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'N', 's', "show"        , 'y', MENU_CMD   , ":notes····show¦"                },
   { 'b', 'v', 'N', 'h', "hide"        , 'y', MENU_CMD   , ":notes····hide¦"                },
   { 'b', 'v', 'N', 'e', "enable"      , 'y', MENU_CMD   , ":notes····enable¦"              },
   { 'b', 'v', 'N', 'd', "disable"     , 'y', MENU_CMD   , ":notes····disable¦"             },
   { 'b', 'v', 'P', '·', "color"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'P', 's', "show"        , 'y', MENU_CMD   , ":color····show¦"                },
   { 'b', 'v', 'P', 'h', "hide"        , 'y', MENU_CMD   , ":color····hide¦"                },
   { 'b', 'v', 'P', 'e', "enable"      , 'y', MENU_CMD   , ":color····enable¦"              },
   { 'b', 'v', 'P', 'd', "disable"     , 'y', MENU_CMD   , ":color····disable¦"             },
   { 'b', 'v', 'B', '·', "back"        , 'y', MENU_GROUP , "-"                              },
   { 'b', 'v', 'B', 's', "show"        , 'y', MENU_CMD   , ":back·····show¦"                },
   { 'b', 'v', 'B', 'h', "hide"        , 'y', MENU_CMD   , ":back·····hide¦"                },
   { 'b', 'v', 'B', 'e', "enable"      , 'y', MENU_CMD   , ":back·····enable¦"              },
   { 'b', 'v', 'B', 'd', "disable"     , 'y', MENU_CMD   , ":back·····disable¦"             },
   { 'b', 'v', '?', '·', "help"        , 'y', MENU_GROUP , "-"                              },
   /*---(insert menu)--------------------------------------------*/
   { 'b', 'i', '·', '·', "insert"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 't', '·', "text"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'i', '·', "image"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'l', '·', "lines"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'e', '·', "ellises"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 't', '·', "tris"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'r', '·', "rects"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'h', '·', "hexagons"    , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'p', '·', "polygons"    , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 's', '·', "stars"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'a', '·', "arrows"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'f', '·', "flowchart"   , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'j', '·', "joiners"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'n', '·', "notes"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'm', '·', "misc"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', '-', '·', "nurbs"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', '-', '·', "tiling"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', 'b', '·', "beziers"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', '-', '·', "3d"          , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', '-', '·', "surfaces"    , '-', MENU_GROUP , "-"                              },
   { 'b', 'i', '-', '·', "meshes"      , '-', MENU_GROUP , "-"                              },
   /*---(select menu)--------------------------------------------*/
   { 'b', 's', '·', '·', "select"      , '-', MENU_GROUP , "-"                              },
   { 'b', 's', '!', '·', "highlight"   , '-', MENU_EXACT , "-"                              },
   { 'b', 's', '_', '·', "status"      , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'c', '·', "clear"       , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'a', '·', "all"         , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'b', '·', "buffer"      , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'w', '·', "window"      , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'l', '·', "layer"       , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'g', '·', "geometry"    , '-', MENU_MORE  , "-"                              },
   { 'b', 's', 't', '·', "type"        , '-', MENU_MORE  , "-"                              },
   { 'b', 's', 'x', '·', "regex"       , '-', MENU_MORE  , "-"                              },
   { 'b', 's', 'u', '·', "touching"    , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 's', '·', "save"        , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'r', '·', "reselect"    , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'j', '·', "join"        , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'd', '·', "deselect"    , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'i', '·', "inverse"     , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'x', '·', "all_on_x"    , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'y', '·', "all_on_y"    , '-', MENU_EXACT , "-"                              },
   { 'b', 's', 'z', '·', "all_on_z"    , '-', MENU_EXACT , "-"                              },
   /*---(format menu)--------------------------------------------*/
   { 'b', 'o', '·', '·', "format"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'f', '·', "face"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'p', '·', "point"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 's', '·', "spacing"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'i', '·', "indent"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'c', '·', "color"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'a', '·', "align"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'n', '·', "numbers"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'z', '·', "sfill"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'd', '·', "decimals"    , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'u', '·', "units"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'l', '·', "lists"       , '-', MENU_GROUP , "-"                              },
   { 'b', 'o', 'y', '·', "style"       , '-', MENU_GROUP , "-"                              },
   /*---(modify menu)--------------------------------------------*/
   { 'b', 'm', '·', '·', "modify"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'm', 'è', '·', "resize"      , '-', MENU_MORE  , "-"                              },
   { 'b', 'm', 'é', '·', "dims"        , '-', MENU_MORE  , "-"                              },
   { 'b', 'm', 'ê', '·', "extent"      , '-', MENU_MORE  , "-"                              },
   { 'b', 'm', 'ë', '·', "scale"       , '-', MENU_MORE  , "-"                              },
   { 'b', 'm', 'ì', '·', "trim"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'm', 'í', '·', "join"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'm', 'î', '·', "move"        , '-', MENU_TBD   , "-"                              },
   { 'b', 'm', 'ï', '·', "array"       , '-', MENU_TBD   , "-"                              },
   { 'b', 'm', 'ð', '·', "rotate"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'm', 'ñ', '·', "snap"        , '-', MENU_TBD   , "-"                              },
   { 'b', 'm', 'ò', '·', "fill"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'm', 'ó', '·', "hatching"    , '-', MENU_GROUP , "-"                              },
   { 'b', 'm', 'ô', '·', "outline"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'm', 'õ', '·', "centers"     , '-', MENU_TBD   , "-"                              },
   { 'b', 'm', 'ö', '·', "ends"        , '-', MENU_TBD   , "-"                              },
   /*---(dataset menu)-------------------------------------------*/
   { 'b', 'd', '·', '·', "dataset"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'd', 's', '·', "sort"        , 'y', MENU_GROUP , "-"                              },
   { 'b', 'd', 'f', '·', "filter"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'd', '-', '·', "blur"        , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "enhance"     , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "distort"     , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "noise"       , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "edges"       , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "combine"     , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "light"       , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "shadow"      , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "pixelate"    , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "render"      , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "sharpen"     , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "smooth"      , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "stylize"     , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "liquify"     , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "oils"        , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "map"         , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "decor"       , 'y', MENU_TBD   , "-"                              },
   { 'b', 'd', '-', '·', "vanish"      , 'y', MENU_TBD   , "-"                              },
   /*---(tools menu)---------------------------------------------*/
   { 'b', 't', '·', '·', "toolset"     , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "pen"         , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "callig"      , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "pencil"      , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "airbrush"    , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "chalk"       , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "brush"       , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "roller"      , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "spray"       , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "fill"        , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "sponge"      , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "blob"        , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "blur"        , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "sharpen"     , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "smudge"      , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "burn"        , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "eraser"      , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "magic_e"     , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "healer"      , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "highlight"   , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "zoom"        , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "move"        , '-', MENU_GROUP , "-"                              },
   { 'b', 't', '-', '·', "lasso"       , '-', MENU_GROUP , "-"                              },
   /*---(pallette menu)------------------------------------------*/
   { 'b', 'p', '·', '·', "palette"     , '-', MENU_GROUP , "-"                              },
   /*---(layers menu)--------------------------------------------*/
   { 'b', 'l', '·', '·', "layers"      , '-', MENU_GROUP , "-"                              },
   { 'b', 'l', '-', '·', "saved"       , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "highlight"   , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "status"      , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "new"         , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "rename"      , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "copy_all"    , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "copy_with"   , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "join"        , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "flatten"     , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "delete"      , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "type"        , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "hide"        , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "mask"        , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "alignment"   , '-', MENU_TBD   , "-"                              },
   { 'b', 'l', '-', '·', "locking"     , '-', MENU_TBD   , "-"                              },
   /*---(buffers menu)-------------------------------------------*/
   { 'b', 'b', '·', '·', "buffers"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'b', '_', '·', "status"      , '-', MENU_EXACT , ":status buffer¦"                },
   { 'b', 'b', 'x', '·', "maximum"     , '-', MENU_MORE  , ":bmax·"                         },
   { 'b', 'b', 'b', '·', "browse"      , '-', MENU_EXACT , ":bbrowse·"                      },
   { 'b', 'b', 'g', '·', "goto"        , '-', MENU_GROUP , "-"                              },
   { 'b', 'b', 'g', 'a', "abbrev"      , '-', MENU_MORE  , ":buf·"                          },
   { 'b', 'b', 'g', 'r', "return"      , '-', MENU_EXACT , ",,"                             },
   { 'b', 'b', 'g', 'f', "first"       , '-', MENU_EXACT , ",["                             },
   { 'b', 'b', 'g', 'p', "prev"        , '-', MENU_EXACT , ",<"                             },
   { 'b', 'b', 'g', 'n', "next"        , '-', MENU_EXACT , ",>"                             },
   { 'b', 'b', 'g', 'l', "last"        , '-', MENU_EXACT , ",]"                             },
   { 'b', 'b', 'g', 'u', "summary"     , '-', MENU_EXACT , ",®"                             },
   { 'b', 'b', 'g', 'y', "system"      , '-', MENU_EXACT , ",¯"                             },
   { 'b', 'b', '-', '·', "showall"     , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', 'w', '·', "new"         , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', 'n', '·', "rename"      , '-', MENU_MORE  , ":btitle·"                       },
   { 'b', 'b', 'z', '·', "size"        , '-', MENU_MORE  , ":bsize·"                        },
   { 'b', 'b', 't', '·', "type"        , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', 'f', '·', "defaults"    , '-', MENU_GROUP , "-"                              },
   { 'b', 'b', 'f', 'w', "col_wide"    , '-', MENU_MORE  , ":defwide·"                      },
   { 'b', 'b', 'f', 't', "row_tall"    , '-', MENU_MORE  , ":deftall·"                      },
   { 'b', 'b', 'f', 'd', "dep_thick"   , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', '-', '·', "scale"       , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', '-', '·', "delete"      , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', '-', '·', "freeze"      , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', '-', '·', "split"       , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', '-', '·', "hiding"      , '-', MENU_TBD   , "-"                              },
   { 'b', 'b', '-', '·', "locking"     , '-', MENU_TBD   , "-"                              },
   /*---(auditor menu)-------------------------------------------*/
   { 'b', 'a', '·', '·', "analyze"     , '-', MENU_GROUP , "-"                              },
   { 'b', 'a', 's', '·', "spell"       , '-', MENU_TBD   , "-"                              },
   { 'b', 'a', 'd', '·', "dump"        , '-', MENU_TBD   , "-"                              },
   /*---(execute menu)-------------------------------------------*/
   { 'b', 'x', '·', '·', "execute"     , '-', MENU_GROUP , "-"                              },
   /*---(macro menu)---------------------------------------------*/
   { 'b', 'r', '·', '·', "scripts"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'r', 'e', '·', "execute"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'r', 'e', '0', "blitz"       , 'y', MENU_CMD   , ":edelay 0¦"                     },
   { 'b', 'r', 'e', '1', "fast"        , 'y', MENU_CMD   , ":edelay 1¦"                     },
   { 'b', 'r', 'e', '2', "thousand"    , 'y', MENU_CMD   , ":edelay 2¦"                     },
   { 'b', 'r', 'e', '3', "hundred"     , 'y', MENU_CMD   , ":edelay 3¦"                     },
   { 'b', 'r', 'e', '4', "twenty"      , 'y', MENU_CMD   , ":edelay 4¦"                     },
   { 'b', 'r', 'e', '5', "tenth"       , 'y', MENU_CMD   , ":edelay 5¦"                     },
   { 'b', 'r', 'e', '6', "half"        , 'y', MENU_CMD   , ":edelay 6¦"                     },
   { 'b', 'r', 'e', '7', "second"      , 'y', MENU_CMD   , ":edelay 7¦"                     },
   { 'b', 'r', 'e', '8', "double"      , 'y', MENU_CMD   , ":edelay 8¦"                     },
   { 'b', 'r', 'e', '9', "triple"      , 'y', MENU_CMD   , ":edelay 9¦"                     },
   { 'b', 'r', 'e', '+', "faster"      , 'y', MENU_CMD   , ":edelay +¦"                     },
   { 'b', 'r', 'e', '-', "slower"      , 'y', MENU_CMD   , ":edelay -¦"                     },
   { 'b', 'r', 'e', 'f', "fast"        , 'y', MENU_CMD   , ":eupdate f¦"                    },
   { 'b', 'r', 'e', 'n', "normal"      , 'y', MENU_CMD   , ":eupdate n¦"                    },
   { 'b', 'r', 'e', 's', "slow"        , 'y', MENU_CMD   , ":eupdate s¦"                    },
   { 'b', 'r', 'e', 'b', "blinks"      , 'y', MENU_CMD   , ":eupdate b¦"                    },
   { 'b', 'r', 'e', 'p', "peeks"       , 'y', MENU_CMD   , ":eupdate p¦"                    },
   { 'b', 'r', 'e', 'd', "blind"       , 'y', MENU_CMD   , ":eupdate d¦"                    },
   { 'b', 'r', 'e', 'D', "demo mode"   , 'y', MENU_CMD   , ":edelay 4¦"                     },
   { 'b', 'r', 'd', '·', "debug"       , 'y', MENU_GROUP , "-"                              },
   { 'b', 'r', 'd', '0', "blitz"       , 'y', MENU_CMD   , ":ddelay 0¦"                     },
   { 'b', 'r', 'd', '1', "fast"        , 'y', MENU_CMD   , ":ddelay 1¦"                     },
   { 'b', 'r', 'd', '2', "thousand"    , 'y', MENU_CMD   , ":ddelay 2¦"                     },
   { 'b', 'r', 'd', '3', "hundred"     , 'y', MENU_CMD   , ":ddelay 3¦"                     },
   { 'b', 'r', 'd', '4', "twenty"      , 'y', MENU_CMD   , ":ddelay 4¦"                     },
   { 'b', 'r', 'd', '5', "tenth"       , 'y', MENU_CMD   , ":ddelay 5¦"                     },
   { 'b', 'r', 'd', '6', "half"        , 'y', MENU_CMD   , ":ddelay 6¦"                     },
   { 'b', 'r', 'd', '7', "second"      , 'y', MENU_CMD   , ":ddelay 7¦"                     },
   { 'b', 'r', 'd', '8', "double"      , 'y', MENU_CMD   , ":ddelay 8¦"                     },
   { 'b', 'r', 'd', '9', "triple"      , 'y', MENU_CMD   , ":ddelay 9¦"                     },
   { 'b', 'r', 'd', '+', "faster"      , 'y', MENU_CMD   , ":ddelay +¦"                     },
   { 'b', 'r', 'd', '-', "slower"      , 'y', MENU_CMD   , ":ddelay -¦"                     },
   { 'b', 'r', 'd', 'n', "normal"      , 'y', MENU_CMD   , ":dupdate n¦"                    },
   { 'b', 'r', 'd', 's', "slow"        , 'y', MENU_CMD   , ":dupdate s¦"                    },
   { 'b', 'r', 'd', 'b', "blinks"      , 'y', MENU_CMD   , ":dupdate b¦"                    },
   { 'b', 'r', 'd', 'p', "peeks"       , 'y', MENU_CMD   , ":dupdate p¦"                    },
   { 'b', 'r', 'd', 'd', "blind"       , 'y', MENU_CMD   , ":dupdate d¦"                    },
   { 'b', 'r', 'w', '·', "new"         , '-', MENU_EXACT , "-"                              },
   { 'b', 'r', 'o', '·', "open"        , '-', MENU_EXACT , "-"                              },
   { 'b', 'r', 'm', '·', "import"      , '-', MENU_EXACT , "-"                              },
   { 'b', 'r', 's', '·', "save"        , '-', MENU_EXACT , "-"                              },
   { 'b', 'r', 'x', '·', "export"      , '-', MENU_EXACT , "-"                              },
   { 'b', 'r', 'i', '·', "list"        , '-', MENU_EXACT , "-"                              },
   { 'b', 'r', 'g', '·', "globals"     , '-', MENU_EXACT , "-"                              },
   /*---(snippet menu)-------------------------------------------*/
   { 'b', 'g', '·', '·', "dialect"     , '-', MENU_GROUP , "-"                              },
   /*---(config menu)--------------------------------------------*/
   { 'b', 'c', '·', '·', "config"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'c', 's', '·', "search"      , 'y', MENU_GROUP , "-"                              },
   { 'b', 'c', 's', 'r', "reset all"   , 'y', MENU_MORE  , "-"                              },
   { 'b', 'c', 'M', '·', "menu"        , 'y', MENU_TRIPLE, "-"                              },
   { 'b', 'c', 'M', 't', "-- top --"   , 'y', MENU_CMD   , ":menus······t¦"                 },
   { 'b', 'c', 'M', '1', "top-lef"     , 'y', MENU_CMD   , ":menus······1¦"                 },
   { 'b', 'c', 'M', '2', "top-cen"     , 'y', MENU_CMD   , ":menus······2¦"                 },
   { 'b', 'c', 'M', '3', "top-rig"     , 'y', MENU_CMD   , ":menus······3¦"                 },
   { 'b', 'c', 'M', '¬', "¬"           , 'y', MENU_SKIP  , ""                               },
   { 'b', 'c', 'M', 'k', "-- ups --"   , 'y', MENU_CMD   , ":menus······k¦"                 },
   { 'b', 'c', 'M', 'A', "ups-beg"     , 'y', MENU_CMD   , ":menus······A¦"                 },
   { 'b', 'c', 'M', 'T', "ups-cen"     , 'y', MENU_CMD   , ":menus······T¦"                 },
   { 'b', 'c', 'M', 'U', "ups-end"     , 'y', MENU_CMD   , ":menus······U¦"                 },
   { 'b', 'c', 'M', '¬', "¬"           , 'y', MENU_BREAK , ""                               },
   { 'b', 'c', 'M', 'm', "-- mid --"   , 'y', MENU_CMD   , ":menus······m¦"                 },
   { 'b', 'c', 'M', '4', "mid-lef"     , 'y', MENU_CMD   , ":menus······4¦"                 },
   { 'b', 'c', 'M', 'S', "mid-beg"     , 'y', MENU_CMD   , ":menus······S¦"                 },
   { 'b', 'c', 'M', '5', "mid-cen"     , 'y', MENU_CMD   , ":menus······5¦"                 },
   { 'b', 'c', 'M', 'E', "mid-end"     , 'y', MENU_CMD   , ":menus······E¦"                 },
   { 'b', 'c', 'M', '6', "mid-rig"     , 'y', MENU_CMD   , ":menus······6¦"                 },
   { 'b', 'c', 'M', '¬', "¬"           , 'y', MENU_BREAK , ""                               },
   { 'b', 'c', 'M', 'j', "-- low --"   , 'y', MENU_CMD   , ":menus······j¦"                 },
   { 'b', 'c', 'M', 'D', "low-beg"     , 'y', MENU_CMD   , ":menus······D¦"                 },
   { 'b', 'c', 'M', 'B', "low-cen"     , 'y', MENU_CMD   , ":menus······B¦"                 },
   { 'b', 'c', 'M', 'Z', "low-end"     , 'y', MENU_CMD   , ":menus······Z¦"                 },
   { 'b', 'c', 'M', '¬', "¬"           , 'y', MENU_SKIP  , ""                               },
   { 'b', 'c', 'M', 'b', "-- bot --"   , 'y', MENU_CMD   , ":menus······b¦"                 },
   { 'b', 'c', 'M', '7', "bot-lef"     , 'y', MENU_CMD   , ":menus······7¦"                 },
   { 'b', 'c', 'M', '8', "bot-cen"     , 'y', MENU_CMD   , ":menus······8¦"                 },
   { 'b', 'c', 'M', '9', "bot-rig"     , 'y', MENU_CMD   , ":menus······9¦"                 },
   { 'b', 'c', 'F', '·', "float"       , 'y', MENU_TRIPLE, "-"                              },
   { 'b', 'c', 'F', 't', "-- top --"   , 'y', MENU_CMD   , ":float······t¦"                 },
   { 'b', 'c', 'F', '1', "top-lef"     , 'y', MENU_CMD   , ":float······1¦"                 },
   { 'b', 'c', 'F', '2', "top-cen"     , 'y', MENU_CMD   , ":float······2¦"                 },
   { 'b', 'c', 'F', '3', "top-rig"     , 'y', MENU_CMD   , ":float······3¦"                 },
   { 'b', 'c', 'F', '¬', "¬"           , 'y', MENU_SKIP  , ""                               },
   { 'b', 'c', 'F', 'k', "-- ups --"   , 'y', MENU_CMD   , ":float······k¦"                 },
   { 'b', 'c', 'F', 'A', "ups-beg"     , 'y', MENU_CMD   , ":float······A¦"                 },
   { 'b', 'c', 'F', 'T', "ups-cen"     , 'y', MENU_CMD   , ":float······T¦"                 },
   { 'b', 'c', 'F', 'U', "ups-end"     , 'y', MENU_CMD   , ":float······U¦"                 },
   { 'b', 'c', 'F', '¬', "¬"           , 'y', MENU_BREAK , ""                               },
   { 'b', 'c', 'F', 'm', "-- mid --"   , 'y', MENU_CMD   , ":float······m¦"                 },
   { 'b', 'c', 'F', '4', "mid-lef"     , 'y', MENU_CMD   , ":float······4¦"                 },
   { 'b', 'c', 'F', 'S', "mid-beg"     , 'y', MENU_CMD   , ":float······S¦"                 },
   { 'b', 'c', 'F', '5', "mid-cen"     , 'y', MENU_CMD   , ":float······5¦"                 },
   { 'b', 'c', 'F', 'E', "mid-end"     , 'y', MENU_CMD   , ":float······E¦"                 },
   { 'b', 'c', 'F', '6', "mid-rig"     , 'y', MENU_CMD   , ":float······6¦"                 },
   { 'b', 'c', 'F', '¬', "¬"           , 'y', MENU_BREAK , ""                               },
   { 'b', 'c', 'F', 'j', "-- low --"   , 'y', MENU_CMD   , ":float······j¦"                 },
   { 'b', 'c', 'F', 'D', "low-beg"     , 'y', MENU_CMD   , ":float······D¦"                 },
   { 'b', 'c', 'F', 'B', "low-cen"     , 'y', MENU_CMD   , ":float······B¦"                 },
   { 'b', 'c', 'F', 'Z', "low-end"     , 'y', MENU_CMD   , ":float······Z¦"                 },
   { 'b', 'c', 'F', '¬', "¬"           , 'y', MENU_SKIP  , ""                               },
   { 'b', 'c', 'F', 'b', "-- bot --"   , 'y', MENU_CMD   , ":float······b¦"                 },
   { 'b', 'c', 'F', '7', "bot-lef"     , 'y', MENU_CMD   , ":float······7¦"                 },
   { 'b', 'c', 'F', '8', "bot-cen"     , 'y', MENU_CMD   , ":float······8¦"                 },
   { 'b', 'c', 'F', '9', "bot-rig"     , 'y', MENU_CMD   , ":float······9¦"                 },
   { 'b', 'c', 'H', '·', "history"     , 'y', MENU_GROUP , "-"                              },
   { 'b', 'c', 'H', 'f', "full"        , 'y', MENU_CMD   , ":history····f¦"                 },
   { 'b', 'c', 'H', 'l', "left"        , 'y', MENU_CMD   , ":history····l¦"                 },
   { 'b', 'c', 'H', 'c', "center"      , 'y', MENU_CMD   , ":history····c¦"                 },
   { 'b', 'c', 'H', 'r', "right"       , 'y', MENU_CMD   , ":history····r¦"                 },
   /*---(share menu)---------------------------------------------*/
   { 'b', 'h', '·', '·', "sharing"     , 'y', MENU_GROUP , "-"                              },
   /*---(footer)-------------------------------------------------*/
   {  0 ,  0 ,  0 ,  0 , ""            , 0  , 0          , ""                               },
   /*---(done)---------------------------------------------------*/
};


/*====================------------------------------------====================*/
/*===----                       shared helpers                         ----===*/
/*====================------------------------------------====================*/
static void  o___SHARED__________o () { return; }

char
ycmd__menu_fix_path       (uchar *a_path, int *a_len, uchar *a_fixed)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   static int  x_len       =    0;
   static uchar x_path     [LEN_LABEL];
   int         i           =    0;
   static uchar x_save     [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_senter  (__FUNCTION__);
   /*---(prepare)------------------------*/
   if (a_len   != NULL)   *a_len = 0;
   if (a_fixed != NULL)   ystrlcpy (a_fixed, "", LEN_LABEL);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_spoint  (a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_snote   (a_path);
   /*---(short-cutting)------------------*/
   DEBUG_YCMD   yLOG_snote   (x_save);
   if (strcmp (a_path, x_save) == 0) {
      DEBUG_YCMD   yLOG_snote   ("short-cut invoked");
      if (a_len   != NULL)   *a_len = x_len;
      if (a_fixed != NULL)   ystrlcpy (a_fixed, x_path, LEN_LABEL);
      DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
      return 1;
   }
   /*---(check length)-------------------*/
   x_len = strlen (a_path);
   DEBUG_YCMD   yLOG_sint    (x_len);
   --rce;  if (x_len < 1 || x_len > 4) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check prefix)-------------------*/
   --rce;  if (a_path [0] != G_KEY_BSLASH && a_path [0] != G_CHAR_DBSLASH) {
      DEBUG_YCMD   yLOG_snote   ("must start with \\ or µ");
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(fix)----------------------------*/
   snprintf (x_path, 5, "µ%s······", a_path + 1);
   DEBUG_YCMD   yLOG_snote   (x_path);
   /*---(valid characters)---------------*/
   --rce;  for (i = 1; i < 4; ++i) {
      if (strchr (s_valid, x_path [i]) != NULL)   continue;
      DEBUG_YCMD   yLOG_sint    (i);
      DEBUG_YCMD   yLOG_sint    (x_path [i]);
      DEBUG_YCMD   yLOG_schar   (x_path [i]);
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check spacers)------------------*/
   --rce;  if (x_path [1] == G_CHAR_SPACE && x_path [2] != G_CHAR_SPACE) {
      DEBUG_YCMD   yLOG_snote   ("pos1/2, spacer (·) followed by specific character");
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (x_path [2] == G_CHAR_SPACE && x_path [3] != G_CHAR_SPACE) {
      DEBUG_YCMD   yLOG_snote   ("pos2/3, spacer (·) followed by specific character");
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check wildcarding)--------------*/
   --rce;  if (x_path [1] == '*') {
      if (x_path [2] != G_CHAR_SPACE && x_path [2] != '*') {
         DEBUG_YCMD   yLOG_snote   ("pos1/2, asterisk (*) followed by specific character");
         DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (x_path [2] == '*') {
      if (x_path [3] != G_CHAR_SPACE && x_path [3] != '*') {
         DEBUG_YCMD   yLOG_snote   ("pos2/3, asterisk (*) followed by specific character");
         DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(fix length)---------------------*/
   x_len = 4;
   if (x_path [3] == G_CHAR_SPACE)  --x_len;
   if (x_path [2] == G_CHAR_SPACE)  --x_len;
   if (x_path [1] == G_CHAR_SPACE)  --x_len;
   /*---(prepare)------------------------*/
   ystrlcpy (x_save, a_path, LEN_LABEL);
   if (a_len   != NULL)   *a_len = x_len;
   if (a_fixed != NULL)   ystrlcpy (a_fixed, x_path, LEN_LABEL);
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        memory allocation                     ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char
ycmd__menu_newlink      (tMENU *a_menu)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tMLINK     *x_cur       = NULL;
   tMLINK     *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_spoint  (a_menu);
   --rce;  if (a_menu == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_snote   (a_menu->name);
   /*---(check for existing)-------------*/
   x_cur = myCMD.m_head;
   --rce;  while (x_cur != NULL) {
      if (x_cur->data == a_menu)  {
         DEBUG_YCMD   yLOG_snote   ("found  matching data pointer");
         DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      x_cur = x_cur->m_next;
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tMLINK *) malloc (sizeof (tMLINK));
   }
   DEBUG_YCMD   yLOG_sint    (x_tries);
   DEBUG_YCMD   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YCMD   yLOG_snote   ("FAILED");
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_YCMD   yLOG_snote   ("populate");
   x_new->data     = a_menu;
   x_new->active   = x_new->data->active;
   x_new->m_next   = NULL;
   x_new->m_prev   = NULL;
   x_new->s_next   = NULL;
   x_new->c_first  = NULL;
   x_new->c_count  = 0;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
   /*---(now place)----------------------*/
   rc = ycmd_menu_place (x_new);
   --rce;  if (rc <= 0) {
      DEBUG_YCMD   yLOG_note    ("placement failed, freeing link");
      free (x_new);
      return rce;
   }
   /*---(tie to master list)-------------*/
   if (myCMD.m_head == NULL) {
      DEBUG_YCMD   yLOG_note    ("nothing in master list, make first");
      myCMD.m_head         = x_new;
   } else  {
      DEBUG_YCMD   yLOG_note    ("append to master list");
      myCMD.m_tail->m_next = x_new;
      x_new->m_prev  = myCMD.m_tail;
   }
   myCMD.m_tail        = x_new;
   /*---(update counts)------------------*/
   ++myCMD.m_nmenu;
   if (x_new->data->base  == MENU_BASE)    ++myCMD.m_nbase;
   if (x_new->active      == MENU_ACTIVE)  ++myCMD.m_nreal;
   if (x_new->active      == MENU_GREY)    ++myCMD.m_ngrey;
   if (x_new->active      == MENU_HIDE)    ++myCMD.m_nhide;
   DEBUG_YCMD   yLOG_complex ("counters"  , "%dm, %dr, %db", myCMD.m_nmenu, myCMD.m_nreal, myCMD.m_nbase);
   /*---(complete)-----------------------*/
   return 0;
}

char
ycmd__menu_new          (uchar *a_path, char *a_name, char *a_keys)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tMLINK     *x_cur       = NULL;
   tMENU      *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   char        x_path      [LEN_TERSE] = "";
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_spoint  (a_path);
   --rce;  if (a_path == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_snote   (a_path);
   DEBUG_YCMD   yLOG_spoint  (a_name);
   --rce;  if (a_name == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_spoint  (a_keys);
   --rce;  if (a_keys == NULL) {
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(check for existing)-------------*/
   if (a_path [2] != '¬') {
      x_cur = myCMD.m_head;
      --rce;  while (x_cur != NULL) {
         if (x_cur->data->top == a_path [0]) {
            if (x_cur->data->mid == a_path [1]) {
               if (x_cur->data->bot == a_path [2]) break;
            }
         }
         x_cur = x_cur->m_next;
      }
      if (x_cur != NULL)  {
         DEBUG_YCMD   yLOG_snote   ("found  matching data pointer");
         DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tMENU *) malloc (sizeof (tMENU));
   }
   DEBUG_YCMD   yLOG_sint    (x_tries);
   DEBUG_YCMD   yLOG_spoint  (x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YCMD   yLOG_snote   ("FAILED");
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_YCMD   yLOG_snote   ("populate");
   x_new->base     = MENU_CUSTOM;
   x_new->top      = a_path [1];
   x_new->mid      = a_path [2];
   x_new->bot      = a_path [3];
   ystrlcpy (x_new->name, a_name, LEN_LABEL);
   x_new->active   = MENU_ACTIVE;
   ystrlcpy (x_new->keys, a_keys, LEN_TITLE );
   /*---(typing)-------------------------*/
   x_len = strlen (a_keys);
   if      (a_keys [x_len - 1] == G_CHAR_RETURN) x_new->type   = MENU_EXACT;
   else if (a_keys [0]         != ':'          ) x_new->type   = MENU_EXACT;
   else                                          x_new->type   = MENU_MORE;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
   /*---(now place)----------------------*/
   rc = ycmd__menu_newlink (x_new);
   --rce;  if (rc != 0) {
      DEBUG_YCMD   yLOG_note    ("link failed, freeing menu item");
      free (x_new);
      DEBUG_YCMD   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_sexit   (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                    hierarchy actions                         ----===*/
/*====================------------------------------------====================*/
static void  o___ACTIONS_________o () { return; }

int
ycmd__menu_action       (uchar *a_path, int a_max, int a_lvl, tMLINK *a_parent, char a_act, tMLINK *a_new)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         rc          =    0;
   tMLINK      *x_curr      = NULL;
   tMLINK      *x_sib       = NULL;
   uchar       x_abbr      =  '·';
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   DEBUG_YCMD   yLOG_complex ("args"      , "%p %d %d %p %c %p", a_path, a_max, a_lvl, a_parent, a_act, a_new);
   /*---(defense)------------------------*/
   --rce;  if (a_path == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("a_path"    , a_path);
   --rce;  if (a_parent == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("a_parent"  , a_parent->data->name);
   /*---(walk children)------------------*/
   x_curr = a_parent->c_first;
   DEBUG_YCMD   yLOG_point   ("c_first"   , x_curr);
   while (x_curr != NULL) {
      /*---(prepare)-----------*/
      DEBUG_YCMD   yLOG_complex ("checking"  , "%c %c %c %s", x_curr->data->top, x_curr->data->mid, x_curr->data->bot, x_curr->data->name);
      switch (a_lvl) {
      case 1 : x_abbr = x_curr->data->top;  break;
      case 2 : x_abbr = x_curr->data->mid;  break;
      case 3 : x_abbr = x_curr->data->bot;  break;
      }
      /*---(filter)------------*/
      if (a_lvl == 3 && x_abbr == (uchar) '¬') {
         x_sib  = x_curr;
         x_curr = x_curr->s_next;
         continue;
      }
      if (a_path [a_lvl] != x_abbr && a_path [a_lvl] != '*') {
         x_sib  = x_curr;
         x_curr = x_curr->s_next;
         continue;
      }
      /*---(act)---------------*/
      if (a_lvl == a_max || a_path [a_lvl] == '*' || (a_path [a_lvl] != '*' && a_path [a_lvl + 1] == '*')) {
         DEBUG_YCMD   yLOG_note    ("found existing with exact path");
         switch (a_act) {
         case MENU_FIND    :
         case MENU_MENU    :
            DEBUG_YCMD   yLOG_note    ("saving to m_found/m_level for unit testing");
            myCMD.m_parent = a_parent;
            myCMD.m_found  = x_curr;
            myCMD.m_level  = a_lvl;
            ++c;
            break;
            /*> case MENU_DELETE  :                                                      <* 
             *>    DEBUG_YCMD   yLOG_note    ("deleting current");                       <* 
             *>    rc = yvikeys_menu__delete (a_parent, x_sib, x_curr);                  <* 
             *>    ++c;                                                                  <* 
             *>    break;                                                                <*/
         case MENU_ACTIVE  :
            DEBUG_YCMD   yLOG_note    ("marking current as active");
            switch (x_curr->active) {
            case MENU_ACTIVE : --myCMD.m_nreal;  break;
            case MENU_GREY   : --myCMD.m_ngrey;  break;
            case MENU_HIDE   : --myCMD.m_nhide;  break;
            }
            x_curr->active = MENU_ACTIVE;
            ++myCMD.m_nreal;
            ++c;
            break;
         case MENU_GREY    :
            DEBUG_YCMD   yLOG_note    ("marking current as grey");
            switch (x_curr->active) {
            case MENU_ACTIVE : --myCMD.m_nreal;  break;
            case MENU_GREY   : --myCMD.m_ngrey;  break;
            case MENU_HIDE   : --myCMD.m_nhide;  break;
            }
            x_curr->active = MENU_GREY;
            ++myCMD.m_ngrey;
            ++c;
            break;
         case MENU_HIDE    :
            DEBUG_YCMD   yLOG_note    ("marking current as hidden");
            switch (x_curr->active) {
            case MENU_ACTIVE : --myCMD.m_nreal;  break;
            case MENU_GREY   : --myCMD.m_ngrey;  break;
            case MENU_HIDE   : --myCMD.m_nhide;  break;
            }
            x_curr->active = MENU_HIDE;
            ++myCMD.m_nhide;
            ++c;
            break;
         case MENU_PLACE   :
            DEBUG_YCMD   yLOG_note    ("can not add when already exists");
            DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
      }
      /*---(recurse)-----------*/
      if (a_lvl < a_max) {
         if (a_act == MENU_MENU) {
            myCMD.m_found  = x_curr;
            myCMD.m_level  = a_lvl;
         }
         if (a_act == MENU_ACTIVE) {
            switch (x_curr->active) {
            case MENU_ACTIVE : --myCMD.m_nreal;  break;
            case MENU_GREY   : --myCMD.m_ngrey;  break;
            case MENU_HIDE   : --myCMD.m_nhide;  break;
            }
            x_curr->active = MENU_ACTIVE;
            ++myCMD.m_nreal;
            ++c;
         }
         DEBUG_YCMD   yLOG_note    ("matched so far, recurse into menu another level");
         rc = ycmd__menu_action (a_path, a_max, a_lvl + 1, x_curr, a_act, a_new);
         DEBUG_YCMD   yLOG_value   ("rc"        , rc);
         if (rc >= 0)  c += rc;
      }
      /*---(errors)------------*/
      if (rc < 0) {
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*---(next)--------------*/
      x_sib  = x_curr;
      x_curr = x_curr->s_next;
      /*---(done)--------------*/
   }
   /*---(fall-out empty)-----------------*/
   if (a_act != MENU_PLACE) {
      DEBUG_YCMD   yLOG_value   ("c"         , c);
      DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
      return c;
   }
   /*---(fall-out empty)-----------------*/
   --rce;  if (a_lvl != a_max) {
      DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
      return c;
   }
   /*---(add child)----------------------*/
   if (x_sib == NULL) {
      DEBUG_YCMD   yLOG_note    ("adding as first child");
      a_parent->c_first = a_new;
   } else  {
      DEBUG_YCMD   yLOG_note    ("adding to tail of list of children");
      x_sib->s_next    = a_new;
   }
   ++a_parent->c_count;
   DEBUG_YCMD   yLOG_value   ("c_count"   , a_parent->c_count);
   switch (a_lvl) {
   case 1 : ++myCMD.m_ntops;  break;
   case 2 : ++myCMD.m_nmids;  break;
   case 3 : ++myCMD.m_nbots;  break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 1;
}

int
ycmd_menu_action        (char a_act, uchar *a_path, tMLINK *a_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_len       =    0;
   uchar       x_path      [LEN_LABEL];
   int         x_max       =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   DEBUG_YCMD   yLOG_complex ("args"      , "%c %-10p %-10p", a_act, a_path, a_link);
   /*---(prepare)------------------------*/
   myCMD.m_parent = NULL; /* reset unit testing holder */
   myCMD.m_found  = NULL; /* reset unit testing holder */
   myCMD.m_level  =    0; /* reset unit testing holder */
   /*---(defense)------------------------*/
   --rce;  if (a_link   != NULL) {
      sprintf (x_path, "µ%c%c%c", a_link->data->top, a_link->data->mid, a_link->data->bot);
      x_len = 4;
   } else if (a_path != NULL) {
      rc = ycmd__menu_fix_path (a_path, &x_len, x_path);
      DEBUG_YCMD   yLOG_value   ("fix_path"  , rc);
      if (rc < 0) {
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   } else {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_info    ("x_path"    , x_path);
   /*---(shortcut)-----------------------*/
   if ((a_act == MENU_FIND || a_act == MENU_MENU) && x_len == 1) {
      DEBUG_YCMD   yLOG_note    ("shortcut, looking for root");
      myCMD.m_parent = myCMD.m_head;
      myCMD.m_found  = myCMD.m_head;
      myCMD.m_level  = 0;
      rc       = 1;
      DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   if (a_act == MENU_MENU) {
      myCMD.m_parent = myCMD.m_head;
      myCMD.m_found  = myCMD.m_head;
      myCMD.m_level  = 0;
   }
   /*---(calc max)-----------------------*/
   if (x_len > 1 && x_path [1] != G_CHAR_SPACE)  ++x_max;
   if (x_len > 2 && x_path [2] != G_CHAR_SPACE)  ++x_max;
   if (x_len > 3 && x_path [3] != G_CHAR_SPACE)  ++x_max;
   DEBUG_YCMD   yLOG_value   ("x_max"     , x_max);
   /*---(check wildcarding)--------------*/
   --rce;  if (x_path [1] == '*') {
      if (x_path [2] != G_CHAR_SPACE && x_path [2] != '*') {
         DEBUG_YCMD   yLOG_note    ("asterisk (*) followed by specific character");
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   --rce;  if (x_path [2] == '*') {
      if (x_path [3] != G_CHAR_SPACE && x_path [3] != '*') {
         DEBUG_YCMD   yLOG_note    ("asterisk (*) followed by specific character");
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(run)----------------------------*/
   if (myCMD.m_head == NULL) {
      rc = 1;
   } else {
      rc = ycmd__menu_action (x_path, x_max, 1, myCMD.m_head, a_act, a_link);
      DEBUG_YCMD   yLOG_value   ("rc"        , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return rc;
}

char ycmd_menu_place   (tMLINK *a_new)  { return ycmd_menu_action (MENU_PLACE , NULL  , a_new); }
int  ycmd_menu_delete  (uchar *a_path)  { return ycmd_menu_action (MENU_PLACE , a_path, NULL ); }
int  ycmd_menu_find    (uchar *a_path)  { return ycmd_menu_action (MENU_FIND  , a_path, NULL ); }
int  ycmd_menu_menu    (uchar *a_path)  { return ycmd_menu_action (MENU_MENU  , a_path, NULL ); }
int  yCMD_menu_active  (uchar *a_path)  { return ycmd_menu_action (MENU_ACTIVE, a_path, NULL ); }
int  yCMD_menu_grey    (uchar *a_path)  { return ycmd_menu_action (MENU_GREY  , a_path, NULL ); }
int  yCMD_menu_hide    (uchar *a_path)  { return ycmd_menu_action (MENU_HIDE  , a_path, NULL ); }



/*====================------------------------------------====================*/
/*===----                         menu display                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
ycmd__menu_purge        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   tMLINK     *x_curr      = NULL;
   tMLINK     *x_prev      = NULL;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_point   ("m_tail"    , myCMD.m_tail);
   --rce;  if (myCMD.m_tail == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_curr = myCMD.m_tail;
   /*---(clear)--------------------------*/
   DEBUG_YCMD   yLOG_value   ("m_nmenu"   , myCMD.m_nmenu);
   while (x_curr != myCMD.m_head && x_curr != NULL) {
      DEBUG_YCMD   yLOG_complex ("focus"     , "%c %s", x_curr->data->base, x_curr->data->name);
      x_prev = x_curr->m_prev;
      if (x_curr->data->base != MENU_BASE) {
         free (x_curr->data);
      }
      free (x_curr);
      x_curr = x_prev;
   }
   /*---(initialize pointers)------------*/
   DEBUG_YCMD   yLOG_note    ("pointers");
   myCMD.m_head->m_next  = myCMD.m_head->m_prev = myCMD.m_head->s_next = myCMD.m_head->c_first = NULL;
   myCMD.m_tail   = myCMD.m_head;
   myCMD.m_parent = NULL;
   myCMD.m_found  = NULL;
   /*---(initialize counters)------------*/
   DEBUG_YCMD   yLOG_note    ("counters");
   myCMD.m_head->c_count = 0;
   myCMD.m_level  = 0;
   myCMD.m_nmenu  = 1;
   myCMD.m_nbase  = 1;
   myCMD.m_nreal  = 1;
   myCMD.m_ngrey  = 0;
   myCMD.m_nhide  = 0;
   myCMD.m_ntops  = 0;
   myCMD.m_nmids  = 0;
   myCMD.m_nbots  = 0;
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yCMD_menu_config        (char a_layout)
{
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   DEBUG_YCMD   yLOG_value   ("a_layout"  , a_layout);
   ycmd__menu_purge ();
   switch (a_layout) {
   case '-' :
      myCMD.m_config = '-';
      break;
   case '1' :
      myCMD.m_config = '1';
      break;
   case '2' :
      myCMD.m_config = '2';
      break;
   case '3' : case 'x' : default  :
      myCMD.m_config = 'x';
      break;
   }
   ycmd__menu_base_load ();
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd_menu_init          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (SMOD_MENUS)) {
      DEBUG_YCMD   yLOG_note    ("status is not ready for init");
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(menus)--------------------------*/
   DEBUG_YCMD   yLOG_note    ("initialize menu system");
   ycmd__menu_purge  ();
   /*---(add the root)-------------------*/
   myCMD.m_head = myCMD.m_tail = NULL;
   ycmd__menu_newlink (s_base);
   /*---(handle total)-------------------*/
   yCMD_menu_config ('3');
   /*---(update status)------------------*/
   yMODE_init_set   (SMOD_MENUS, ycmd_menu_start, ycmd_menu_smode);
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd_menu_wrap          (void)
{
   ycmd__menu_purge  ();
   yCMD_menu_config ('-');
   if (myCMD.m_head != NULL)  free  (myCMD.m_head);
   myCMD.m_head = myCMD.m_tail = NULL;
   myCMD.m_nmenu  = 0;
   myCMD.m_nbase  = 0;
   myCMD.m_nreal  = 0;
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       working with base                      ----===*/
/*====================------------------------------------====================*/
static void  o___BASE____________o () { return; }

char
ycmd__menu_in_base     (uchar *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   uchar       x_path      [LEN_LABEL];
   /*---(fix path)-----------------------*/
   rc = ycmd__menu_fix_path (a_path, NULL, x_path);
   --rce;  if (rc < 0) return rce;
   /*---(handle)-------------------------*/
   for (n = 0; n < MAX_MENU; ++n) {
      /*---(check for end)---------------*/
      if (s_base [n].name [0] == NULL)                break;
      if (strcmp (s_base [n].name, "-") == 0)         break;
      /*---(filter)----------------------*/
      if (s_base [n].top != x_path [1])               continue;
      if (s_base [n].mid != x_path [2])               continue;
      if (s_base [n].bot != x_path [3])               continue;
      /*---(matching)--------------------*/
      if (s_base [n].bot == '¤')                      continue;
      return 1;
      /*---(done)------------------------*/
   }
   /*---(complete)-----------------------*/
   return 0;;
}

char
ycmd__menu_base_num     (int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YCMD   yLOG_spoint  (myCMD.m_head);
   --rce;  if (myCMD.m_head == NULL) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(add)----------------------------*/
   rc = ycmd__menu_newlink (s_base + n);
   DEBUG_YCMD   yLOG_value   ("newlink"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd__menu_base_path    (uchar *a_path)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         n           =    0;
   uchar       x_path      [LEN_LABEL];
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(fix path)-----------------------*/
   rc = ycmd__menu_fix_path (a_path, NULL, x_path);
   DEBUG_YCMD   yLOG_value   ("fix_path"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle)-------------------------*/
   for (n = 0; n < MAX_MENU; ++n) {
      /*---(check for end)---------------*/
      if (s_base [n].name [0] == NULL)                break;
      if (strcmp (s_base [n].name, "-") == 0)         break;
      /*---(filter)----------------------*/
      DEBUG_YCMD   yLOG_complex ("checking"  , "%c %c %c %s", s_base [n].top, s_base [n].mid, s_base [n].bot, s_base [n].name);
      if (s_base [n].top != x_path [1] && (x_path [1] != '*' && s_base [n].top != G_CHAR_SPACE)) {
         DEBUG_YCMD   yLOG_note    ("top rule bounded this one");
         continue;
      }
      if (s_base [n].mid != x_path [2] && (x_path [2] != '*' && s_base [n].top != G_CHAR_SPACE)) {
         DEBUG_YCMD   yLOG_note    ("mid rule bounded this one");
         continue;
      }
      if (s_base [n].bot != x_path [3] && (x_path [3] != '*' && s_base [n].top != G_CHAR_SPACE)) {
         DEBUG_YCMD   yLOG_note    ("bot rule bounded this one");
         continue;
      }
      /*---(create)----------------------*/
      rc = ycmd__menu_newlink (s_base + n);
      /*---(done)------------------------*/
   }
   DEBUG_YCMD   yLOG_value   ("newlink"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd__menu_base_load    (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*---(load)---------------------------*/
   for (i = 0; i < MAX_MENU; ++i) {
      DEBUG_YCMD   yLOG_complex ("checking"  , "%c %c %c %s", s_base [i].top, s_base [i].mid, s_base [i].bot, s_base [i].name);
      /*---(check for end)---------------*/
      if (s_base [i].name [0] == NULL) {
         DEBUG_YCMD   yLOG_note    ("name is null, break and stop");
         break;
      }
      if (strcmp (s_base [i].name, "-") == 0) {
         DEBUG_YCMD   yLOG_note    ("name is hyphen, break and stop");
         break;
      }
      if (s_base [i].top ==  0 )  break;
      if (s_base [i].top == G_CHAR_SPACE)  continue;
      if (s_base [i].mid == G_CHAR_SPACE && strchr ("123x" , myCMD.m_config) != NULL) {
         ycmd__menu_base_num (i);
         continue;
      }
      if (s_base [i].bot == G_CHAR_SPACE && strchr ("23x"  , myCMD.m_config) != NULL) {
         ycmd__menu_base_num (i);
         continue;
      }
      if (strchr ("3x"   , myCMD.m_config) != NULL) {
         ycmd__menu_base_num (i);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         menu display                         ----===*/
/*====================------------------------------------====================*/
static void  o___MENUS___________o () { return; }

char
ycmd_menu_reanchor      (char a_anchor)
{
   /*> return yvikeys_view_reanchor (YMAP_MENUS, a_anchor);                           <*/
}

char
ycmd_menu_final         (void)
{
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   /*> yVIKEYS_cmds_addX (YVIKEYS_M_VIEW  , "help"        , ""    , "c"    , yvikeys_help               , "" );   <*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     menu item placement                      ----===*/
/*====================------------------------------------====================*/
static void  o___PLACEMENT_______o () { return; }

char
ycmd__menu_place_clear  (void)
{
   int         i           =    0;
   for (i = 0; i < MAX_PLACE; ++i) {
      myCMD.m_places [i].item  = NULL;
      myCMD.m_places [i].align = '0';
      myCMD.m_places [i].x = myCMD.m_places [i].xo = 0;
      myCMD.m_places [i].y = myCMD.m_places [i].yo = 0;
   }
   myCMD.m_nplace = 0;
   return 0;
}

char
ycmd__menu_place_round  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tMLINK     *x_curr      = NULL;
   short       x_left, x_wide, x_bott, x_tall;
   short       x_off, y_off;
   short       x_pos, y_pos;
   short       x_cen, y_mid;
   char        x_env       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   x_env = yVIEW_env ();
   DEBUG_YCMD   yLOG_char    ("env"       , x_env);
   /*---(get sizes)----------------------*/
   if (x_env == YVIEW_CURSES) {
      yVIEW_size   (YVIEW_MENUS, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   } else {
      yVIEW_size   (YVIEW_MENUS, NULL, &x_left, &x_wide, &x_bott, &x_tall);
      /*> yVIEW_bounds (YVIEW_MENUS, NULL, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);   <*/
   }
   DEBUG_YCMD   yLOG_complex  ("size"      , "%3dl, %3dw, %3db, %3dt", x_left, x_wide, x_bott, x_tall);
   /*---(prepare)------------------------*/
   DEBUG_YCMD   yLOG_value   ("c_count"   , myCMD.m_head->c_count);
   x_curr = myCMD.m_head->c_first;
   x_cen  = x_left + (x_wide * 0.50);
   if (x_env == YVIEW_CURSES)  y_mid  = x_bott - (x_tall * 0.50);
   else                        y_mid  = x_bott + (x_tall * 0.50);
   ycmd__menu_place_clear ();
   DEBUG_YCMD   yLOG_complex  ("center"    , "%3dx, %3dy", x_cen, y_mid);
   /*---(walk children)------------------*/
   while (x_curr != NULL) {
      DEBUG_YCMD   yLOG_complex ("x_curr"    , "%2d  %c %c %c %-10.10s %c", myCMD.m_nplace, x_curr->data->top, x_curr->data->mid, x_curr->data->bot, x_curr->data->name, x_curr->active);
      /*---(alignment)---------*/
      switch (s_align [myCMD.m_nplace]) {
      case 1 :  x_off =   1;  y_off =  0;          break;
      case 2 :  x_off =   0;  y_off = s_abbr [myCMD.m_nplace];  break;
      case 3 :  x_off =  -1;  y_off =  0;          break;
      }
      /*---(position)----------*/
      x_pos = s_xpos [myCMD.m_nplace];
      y_pos = s_ypos [myCMD.m_nplace];
      DEBUG_YCMD   yLOG_complex  ("base xy"   , "%da, %2dxo, %3dx, %2dyo, %3dy", s_align [myCMD.m_nplace], x_off, x_pos, y_off, y_pos);
      if (x_env == YVIEW_CURSES) {
         y_off  *=  1.0;
         x_off  *=  2.0;
      } else if (s_type == YVIEW_FLAT) {
         x_pos  *=  6.0;
         y_pos  *= 12.0;
         y_off  *= 12.0;
         x_off  *= 20.0;
      } else {
         x_pos  *=  2.0;
         y_pos  *=  3.5;
         y_off  *=  3.0;
         x_off  *=  3.0;
      }
      DEBUG_YCMD   yLOG_complex  ("new xy"    , "%da, %2dxo, %3dx, %2dyo, %3dy", s_align [myCMD.m_nplace], x_off, x_pos, y_off, y_pos);
      /*---(alignment)---------*/
      if (x_off >  0)  myCMD.m_places [myCMD.m_nplace].align = YVIEW_BOTLEF;
      if (x_off == 0)  myCMD.m_places [myCMD.m_nplace].align = YVIEW_BOTCEN;
      if (x_off <  0)  myCMD.m_places [myCMD.m_nplace].align = YVIEW_BOTRIG;
      /*---(draw)--------------*/
      myCMD.m_places [myCMD.m_nplace].item = x_curr;
      myCMD.m_places [myCMD.m_nplace].x    = x_cen + x_pos;
      myCMD.m_places [myCMD.m_nplace].xo   = x_off;
      if (x_env == YVIEW_OPENGL) {
         myCMD.m_places [myCMD.m_nplace].y    = y_mid + y_pos;
         myCMD.m_places [myCMD.m_nplace].yo   = y_off;
      } else {
         myCMD.m_places [myCMD.m_nplace].y    = y_mid - y_pos;
         myCMD.m_places [myCMD.m_nplace].yo   = -y_off;
      }
      /*---(next)--------------*/
      x_curr = x_curr->s_next;
      ++myCMD.m_nplace;
      /*---(done)--------------*/
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
ycmd__menu_place_cols   (char a_level, tMLINK *a_curr)
{
   /*---(locals)-----------+-----+-----+-*/
   int         a           =   11;
   int         t           [LEN_LABEL];
   int         x_entry     =    0;
   int         x_group     =    0;
   short       x_left, x_wide, x_bott, x_tall;
   float       x_pos, y_pos;
   float       x_off;
   int         y_vert;
   tMLINK     *x_curr;
   char        x_env       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   x_env = yVIEW_env ();
   DEBUG_YCMD   yLOG_char    ("env"       , x_env);
   /*---(get sizes)----------------------*/
   if (x_env == YVIEW_CURSES) {
      yVIEW_size   (YVIEW_MENUS, NULL, &x_left, &x_wide, &x_bott, &x_tall);
   } else {
      yVIEW_size   (YVIEW_MENUS, NULL, &x_left, &x_wide, &x_bott, &x_tall);
      /*> yVIEW_bounds (YVIEW_MENUS, NULL, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);   <*/
   }
   DEBUG_YCMD   yLOG_complex  ("size"      , "%3dl, %3dw, %3db, %3dt", x_left, x_wide, x_bott, x_tall);
   /*---(col config)---------------------*/
   switch (a_curr->data->type) {
   case MENU_SINGLE :
      x_group = 3;
      break;
   case MENU_DOUBLE :
      x_group = 0;
      break;
   case MENU_TRIPLE :
      x_group = 2;
      break;
   default :
      a = a_curr->c_count;
      if (a <= 10) {
         x_group = 3;
      } else if (a <= 20) {
         x_group = 0;
         if (a % 2 == 0)  a = a / 2.0;
         else             a = a / 2.0 + 1;
      } else {
         x_group = 2;
         if (a % 3 == 0)  a = a / 3.0;
         else             a = a / 3.0 + 1;
      }
   }
   /*---(prepare)---------------------*/
   if (x_env == YVIEW_CURSES) {
      x_off  =  2.0;
      y_vert =  1;
   } else if (s_type == YVIEW_FLAT) {
      x_off  = 15.0;
      y_vert = 12;
   } else {
      x_off  =  3.0;
      y_vert = 12;
   }
   /*---(walk entries)-------------------*/
   x_curr = a_curr->c_first;
   ycmd__menu_place_clear ();
   while (x_curr != NULL) {
      DEBUG_YCMD   yLOG_complex ("x_curr"    , "%c %c %c %-10.10s %c %c", x_curr->data->top, x_curr->data->mid, x_curr->data->bot, x_curr->data->name, x_curr->active, x_curr->data->type);
      /*---(position)--------------------*/
      if (x_env == YVIEW_CURSES) {
         if (x_entry == 0)  y_pos  = x_bott + (x_tall * 0.15);
         else               y_pos += y_vert;
      } else {
         if (x_entry == 0)  y_pos  = x_bott + (x_tall * 0.80) - (x_tall * 0.14 * x_entry);
         else               y_pos -= y_vert;
      }
      switch (x_group) {
      case 0 : x_pos = x_left + x_wide * 0.20;   break;
      case 1 : x_pos = x_left + x_wide * 0.58;   break;
      case 2 : x_pos = x_left + x_wide * 0.05;   break;
      case 3 : x_pos = x_left + x_wide * 0.38;   break;
      case 4 : x_pos = x_left + x_wide * 0.70;   break;
      }
      /*---(alignment)---------*/
      if (x_off >  0)  myCMD.m_places [myCMD.m_nplace].align = YVIEW_BOTLEF;
      if (x_off == 0)  myCMD.m_places [myCMD.m_nplace].align = YVIEW_BOTCEN;
      if (x_off <  0)  myCMD.m_places [myCMD.m_nplace].align = YVIEW_BOTRIG;
      /*---(draw)--------------*/
      myCMD.m_places [myCMD.m_nplace].item = x_curr;
      myCMD.m_places [myCMD.m_nplace].x    = x_pos;
      myCMD.m_places [myCMD.m_nplace].xo   = x_off;
      if (x_env == YVIEW_OPENGL)  myCMD.m_places [myCMD.m_nplace].y    = y_pos;
      else                        myCMD.m_places [myCMD.m_nplace].y    = y_pos - x_tall + 1;
      myCMD.m_places [myCMD.m_nplace].yo   = 0;
      /*---(next)--------------*/
      ++myCMD.m_nplace;
      /*---(break handling)--------------*/
      if (a_curr->data->type != MENU_GROUP) {
         if (x_curr->data->type == MENU_BREAK) {
            DEBUG_YCMD   yLOG_note    ("found BREAK, continue to next group");
            ++x_group;
            x_entry = 0;
            x_curr = x_curr->s_next;
            continue;
         }
         if (x_curr->data->type == MENU_SKIP) {
            DEBUG_YCMD   yLOG_note    ("found SKIP, assign normally");
         }
         x_curr = x_curr->s_next;
         ++x_entry;
      } else {
         /*---(figure next)-----------------*/
         x_curr = x_curr->s_next;
         ++x_entry;
         if (myCMD.m_nplace != 0 && myCMD.m_nplace % a == 0) {
            DEBUG_YCMD   yLOG_note    ("too many for group add new column");
            ++x_group;
            x_entry = 0;
         }
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     external access                          ----===*/
/*====================------------------------------------====================*/
static void  o___EXTERNAL________o () { return; }

char
yCMD_menu_overall       (char *l, char *b, char *t)
{
   char        rce         =  -10;
   --rce;  if (myCMD.m_found == NULL)  return rce;
   if (l   != NULL)  *l  = myCMD.m_level;
   if (b   != NULL) {
      if (yKEYS_is_locked () == 0) {
         switch (myCMD.m_level) {
         case  0  :  sprintf (b, "");                       break;
         case  1  :  sprintf (b, "%c", myCMD.m_found->data->top);  break;
         case  2  :  sprintf (b, "%c%c", myCMD.m_found->data->top, myCMD.m_found->data->mid);  break;
         }
      } else {
         ystrlcpy (b, myCMD.m_path + 1, LEN_TERSE);
      }
   }
   if (t   != NULL)  ystrlcpy (t, myCMD.m_found->data->name, LEN_LABEL);
   return 0;
}

char
yCMD_menu_data          (char n, short *x, short *y, char *b, short *xo, short *yo, char *l, char *t, char *a, char *v)
{
   char        rce         =  -10;
   char        x_name      [LEN_LABEL] = "";
   --rce;  if (n < 0 || n >= myCMD.m_nplace)  return rce;
   if (x   != NULL)  *x  = myCMD.m_places [n].x;
   if (y   != NULL)  *y  = myCMD.m_places [n].y;
   if (b   != NULL) {
      switch (myCMD.m_level) {
      case 0  : sprintf (b, "%c", myCMD.m_places [n].item->data->top);   break;
      case 1  : sprintf (b, "%c", myCMD.m_places [n].item->data->mid);   break;
      case 2  : sprintf (b, "%c", myCMD.m_places [n].item->data->bot);   break;
      }
   }
   if (xo  != NULL)  *xo = myCMD.m_places [n].xo;
   if (yo  != NULL)  *yo = myCMD.m_places [n].yo;
   sprintf (x_name, "%.9s", myCMD.m_places [n].item->data->name);
   if (myCMD.m_level > 0) {
      switch (myCMD.m_places [n].item->data->type) {
      case MENU_GROUP  :
         ystrlcat (x_name, "+", LEN_LABEL);
         break;
      case MENU_SINGLE : case MENU_DOUBLE : case MENU_TRIPLE :
         ystrlcat (x_name, "+", LEN_LABEL);
         break;
      case MENU_MORE   :
         ystrlcat (x_name, "=", LEN_LABEL);
         break;
      }
   }
   if (l   != NULL)  *l = strlen (x_name);
   if (t   != NULL)  ystrlcpy (t, x_name, LEN_LABEL);
   if (a   != NULL)  *a = myCMD.m_places [n].align;
   if (v   != NULL)  *v = myCMD.m_places [n].item->active;
   return 0;
}




/*====================------------------------------------====================*/
/*===----                       adding/updating items                  ----===*/
/*====================------------------------------------====================*/
static void  o___UPDATING________o () { return; }

char
yVIKEYS_menu_alter      (uchar *a_path, char *a_keys)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                 <* 
    *> char        rce         =  -10;                                                          <* 
    *> char        rc          =    0;                                                          <* 
    *> int         n           =   -1;                                                          <* 
    *> int         x_len       =    0;                                                          <* 
    *> char        x_path      [LEN_LABEL];                                                     <* 
    *> char        x_dup       =    0;                                                          <* 
    *> int         x_level     =    0;                                                          <* 
    *> int         x_last      =    0;                                                          <* 
    *> int         i           =    0;                                                          <* 
    *> /+---(header)-------------------------+/                                                 <* 
    *> DEBUG_CMDS   yLOG_enter   (__FUNCTION__);                                                <* 
    *> /+---(defense)------------------------+/                                                 <* 
    *> DEBUG_CMDS   yLOG_note    ("before status check");                                       <* 
    *> --rce;  if (!STATUS_operational (MODE_COMMAND)) {                                        <* 
    *>    DEBUG_CMDS   yLOG_note    ("can not configure until operational");                    <* 
    *>    DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_CMDS   yLOG_note    ("after status check");                                        <* 
    *> /+---(defense)------------------------+/                                                 <* 
    *> DEBUG_CMDS   yLOG_point   ("a_path"    , a_path);                                        <* 
    *> --rce;  if (a_path == NULL) {                                                            <* 
    *>    DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_CMDS   yLOG_info    ("a_path"    , a_path);                                        <* 
    *> DEBUG_CMDS   yLOG_point   ("a_keys"    , a_keys);                                        <* 
    *> --rce;  if (a_keys == NULL) {                                                            <* 
    *>    DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_CMDS   yLOG_info    ("a_keys"    , a_keys);                                        <* 
    *> /+---(path)---------------------------+/                                                 <* 
    *> x_len = strlen (a_path);                                                                 <* 
    *> DEBUG_CMDS   yLOG_value   ("x_len"     , x_len);                                         <* 
    *> --rce;  if (x_len < 3 || x_len > 4) {                                                    <* 
    *>    DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> ystrlcpy (x_path, a_path, LEN_LABEL);                                                     <* 
    *> /+> n = yvikeys_menu_find (x_path, &x_level, &x_last);                             <+/   <* 
    *> DEBUG_CMDS   yLOG_value   ("find"      , n);                                             <* 
    *> --rce;  if (n < 0) {                                                                     <* 
    *>    DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> /+---(if making a group)--------------+/                                                 <* 
    *> --rce;  if (strcmp (a_keys, ">") == 0) {                                                 <* 
    *>    if (x_level != 2) {                                                                   <* 
    *>       DEBUG_CMDS   yLOG_exitr   (__FUNCTION__, rce);                                     <* 
    *>       return rce;                                                                        <* 
    *>    }                                                                                     <* 
    *>    s_base [n].type   = MENU_GROUP;                                                       <* 
    *>    ystrlcpy (s_base [n].keys, "-", LEN_TITLE );                                            <* 
    *>    s_base [n].active = MENU_ACTIVE;                                                      <* 
    *> }                                                                                        <* 
    *> /+---(if making a executable)---------+/                                                 <* 
    *> else {                                                                                   <* 
    *>    s_base [n].type   = '·';                                                              <* 
    *>    ystrlcpy (s_base [n].keys, a_keys, LEN_TITLE );                                         <* 
    *>    if (x_level == 2) {                                                                   <* 
    *>       s_base [n].active = MENU_ACTIVE;                                                   <* 
    *>       i = s_base [n].start;                                                              <* 
    *>       while (i >= 0) {                                                                   <* 
    *>          s_base [i].top    = '·';                                                        <* 
    *>          s_base [i].mid    = '·';                                                        <* 
    *>          s_base [i].bot    = '·';                                                        <* 
    *>          i = s_base [i].next;                                                            <* 
    *>       }                                                                                  <* 
    *>       yvikeys__menu_compress ();                                                         <* 
   *>    }                                                                                     <* 
      *> }                                                                                        <* 
      *> /+---(update count)-------------------+/                                                 <* 
      *> DEBUG_CMDS   yLOG_value   ("SUCCESS"   , myCMD.m_nmenu);                                       <* 
      *> yvikeys__menu_update (n);                                                                <* 
      *> /+---(complete)-----------------------+/                                                 <* 
      *> DEBUG_CMDS   yLOG_exit    (__FUNCTION__);                                                <* 
      *> return 0;                                                                                <*/
}

char
yCMD_menu_add           (uchar *a_path, char *a_name, char *a_keys)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =   -1;
   int         x_len       =    0;
   uchar       x_path      [LEN_LABEL];
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
   /*---(defense)------------------------*/
   rc = ycmd__menu_fix_path (a_path, &x_len, x_path);
   DEBUG_YCMD   yLOG_point   ("fix_path"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check in base)------------------*/
   rc = ycmd__menu_in_base (x_path);
   DEBUG_YCMD   yLOG_value   ("in_base"   , rc);
   /*---(add from base)------------------*/
   if (rc == 1) {
      rc = ycmd__menu_base_path (x_path);
      DEBUG_YCMD   yLOG_value   ("by_path"   , rc);
      --rce;  if (rc <  0) {
         DEBUG_YCMD   yLOG_note    ("adding failed, freeing menu item");
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = 0;
   }
   /*---(add wholly new)-----------------*/
   else {
      rc = ycmd__menu_new (x_path, a_name, a_keys);
      DEBUG_YCMD   yLOG_value   ("new"       , rc);
      --rce;  if (rc <  0) {
         DEBUG_YCMD   yLOG_note    ("adding failed, freeing menu item");
         DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = 1;
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                         mode handler                         ----===*/
/*====================------------------------------------====================*/
static void  o___SUBMODE_________o () { return; }

char
ycmd_menu_start         (void)
{
   int         n           =    0;
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   ystrlcpy (myCMD.m_path, "\\", LEN_LABEL);
   ystrlcpy (myCMD.m_keys, ""  , LEN_TITLE );
   n = ycmd_menu_find (myCMD.m_path);
   DEBUG_YCMD   yLOG_value   ("current"   , n);
   ycmd__menu_place_round ();
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> allow menu selection ---------------[ ------ [ge.TQ5.25#.F9]*/ /*-[03.0000.122.R]-*/ /*-[--.---.---.--]-*/
ycmd_menu_smode         (uchar a_major, uchar a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL];
   int         n           =    0;
   int         x_len       =    0;
   char        x_level     =    0;
   int         x_last      =    0;
   char        x_on        =    0;
   uchar       x_exec      [LEN_LABEL] = "·:=";
   tMLINK     *x_found     = NULL;
   char        x_lastp     [LEN_LABEL] = "";
   char        x_lastl     =    0;
   /*---(header)-------------------------*/
   DEBUG_YCMD   yLOG_enter   (__FUNCTION__);
   DEBUG_YCMD   yLOG_char    ("a_major"   , a_major);
   DEBUG_YCMD   yLOG_char    ("a_minor"   , chrvisible (a_minor));
   /*---(defenses)-----------------------*/
   DEBUG_YCMD   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (SMOD_MENUS  )) {
      DEBUG_YCMD   yLOG_note    ("not the correct mode");
      DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   if (a_minor == G_KEY_ESCAPE) {
      DEBUG_YCMD   yLOG_note    ("escape, return to map mode");
      yMODE_exit ();
      DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (a_minor == G_KEY_RETURN) {
      DEBUG_YCMD   yLOG_note    ("return, return to map mode");
      yMODE_exit ();
      DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   if (a_minor == G_KEY_SPACE || a_minor == G_CHAR_SPACE) {
      DEBUG_YCMD   yLOG_note    ("ignore spaces");
      DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(add to menu)--------------------*/
   ystrlcpy (x_lastp, myCMD.m_path, LEN_LABEL);
   x_found = myCMD.m_found;
   x_lastl = myCMD.m_level;
   sprintf (t, "%c", a_minor);
   ystrlcat (myCMD.m_path, t, LEN_LABEL);
   DEBUG_YCMD   yLOG_info    ("m_path"    , myCMD.m_path);
   /*---(find path)----------------------*/
   n = ycmd_menu_find (myCMD.m_path);
   DEBUG_YCMD   yLOG_value   ("n"         , n);
   --rce;  if (n <= 0) {
      DEBUG_YCMD   yLOG_note    ("menu failed to match, locked now");
      /*> ystrlcpy (myCMD.m_path, x_lastp, LEN_LABEL);                                 <*/
      myCMD.m_found = x_found;
      myCMD.m_level = x_lastl;
      yKEYS_set_lock ();
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YCMD   yLOG_value   ("m_level"   , myCMD.m_level);
   DEBUG_YCMD   yLOG_value   ("x_last"    , x_last);
   /*---(draw back)----------------------*/
   DEBUG_YCMD   yLOG_info    ("m_path"    , myCMD.m_path);
   x_len = strlen (myCMD.m_path);
   DEBUG_YCMD   yLOG_value   ("x_len"     , x_len);
   /*---(check exec)---------------------*/
   --rce;  if (n > 0 && x_len - 1 == myCMD.m_level) {
      DEBUG_YCMD   yLOG_char    ("type"      , myCMD.m_found->data->type);
      if (strchr (x_exec, myCMD.m_found->data->type) != NULL) {
         yMODE_exit ();
         DEBUG_YCMD   yLOG_info    ("keys"      , myCMD.m_found->data->keys);
         if (strlen (myCMD.m_found->data->keys) == 1 && myCMD.m_found->data->keys [0] == '-') {
            DEBUG_YCMD   yLOG_note    ("legal menu option, but action not set");
            yKEYS_set_error ();
            DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         /*> SOURCE_menu_prep ();                                                     <*/
         /*> ySRC_start ("µ");                                                        <*/
         ystrlcpy (myCMD.m_keys, myCMD.m_found->data->keys, LEN_TITLE);
         DEBUG_YCMD   yLOG_info    ("m_keys"    , myCMD.m_keys);
         yMACRO_menu_beg ();
         yKEYS_logging_off ();
         yKEYS_string (myCMD.m_keys);
         yKEYS_logging_on  ();
         yMACRO_menu_end ();
         DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
         return 0;
      } else if (strchr (MENU_GROUPING, myCMD.m_found->data->type) != NULL) {
         DEBUG_YCMD   yLOG_note    ("group/hand menu option, continue to next level");
         ycmd__menu_place_cols   (myCMD.m_level, myCMD.m_found);
      }
   }
   /*---(check exec)---------------------*/
   --rce;  if (n <= 0) {
      if (x_len - 1 >= 3) {
         DEBUG_YCMD   yLOG_note    ("menu failed to match in 3 levels, exiting");
         yKEYS_set_lock ();
      } else {
         DEBUG_YCMD   yLOG_note    ("illegal option selected, menu frozen");
         yKEYS_set_lock ();
      }
      DEBUG_YCMD   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   } else {
      ycmd__menu_place_cols   (myCMD.m_level, myCMD.m_found);
   }
   /*---(complete)-----------------------*/
   DEBUG_YCMD   yLOG_exit    (__FUNCTION__);
   return 0;
}


