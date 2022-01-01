/*============================----beg-of-source---============================*/
#ifndef yCMD
#define yCMD yes


typedef  unsigned char        uchar;


/*---(primary menus)------------------*//* microsoft, google, gnu, apple */
#define      YCMD_M_FILE        'f'
#define      YCMD_M_EDIT        'e'
#define      YCMD_M_VIEW        'v'
#define      YCMD_M_INSERT      'i'
#define      YCMD_M_FORMAT      'o'
/*---(extended menus)-----------------*//* microsoft, google, gnu, apple */
#define      YCMD_M_BUFFERS     'b'   /* replaces window */
#define      YCMD_M_DATASET     'd'   /* includes filters menu */
#define      YCMD_M_TOOLS       't'
/*---(more advanced)------------------*/
#define      YCMD_M_LAYERS      'l'   /* gimp  */
#define      YCMD_M_SELECT      's'   /* gimp  */
#define      YCMD_M_MODIFY      'm'
#define      YCMD_M_PALETTE     'p'
#define      YCMD_M_LANG        'g'
#define      YCMD_M_AUDIT       'a'
#define      YCMD_M_EXECUTE     'x'   /* build, test, and execute (use) */
#define      YCMD_M_CONFIG      'c'
/*---(perhaps useful)-----------------*/
#define      YCMD_M_SCRIPT      'r'   /* keyboard macros and scripts      */
#define      YCMD_M_SHOW        'h'   /* slideshow, present, printing     */
/*---(default)------------------------*/
#define      YCMD_M_NONE        ' '
/*---(done)---------------------------*/




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(internal)-------------*/
char*       yCMD_version            (void);
char        yCMD_init               (void);
char        yCMD_wrap               (void);
/*---(interface)------------*/
char        yCMD_add                (uchar a_menu, uchar *a_name, uchar *a_abbr, uchar *a_terms, void *a_func, uchar *a_desc);
char        yCMD_exec               (uchar *a_command, char *a_rc);
char        yCMD_direct             (uchar *a_command);
/*---(unittest)-------------*/
char*       yCMD__unit              (char *a_question, int n);


#endif
/*============================----end-of-source---============================*/
