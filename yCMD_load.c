/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yCMD.h"
#include    "yCMD_priv.h"



/*---(true useful vars)---------------*/
static tLINK  *s_head   = NULL;              /* head of link chain            */
static tLINK  *s_tail   = NULL;              /* tail of link chain            */
/*---(menu grphics/unit testing)------*/
static tLINK  *s_found  = NULL;              /* result of last find           */
/*---(DEBUGGING FASTER)---------------*/
static short   s_ncmd   = 0;                 /* all menu items in list        */
static short   s_nbase  = 0;                 /* base menu items in list       */
/*---(done)---------------------------*/
