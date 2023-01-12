/*============================----beg-of-source---============================*/
#ifndef yCMD
#define yCMD yes


typedef  unsigned char        uchar;




/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(internal)-------------*/
char*       yCMD_version            (void);
char        yCMD_init               (void);
char        yCMD_init_after         (void);
char        yCMD_wrap               (void);
/*---(interface)------------*/
char        yCMD_add                (uchar a_menu, uchar *a_name, uchar *a_abbr, uchar *a_terms, void *a_func, uchar *a_desc);
char        yCMD_exec               (uchar *a_command, char *a_rc);
char        yCMD_direct             (uchar *a_command);
/*---(unittest)-------------*/
char*       yCMD__unit              (char *a_question, int n);
/*---(menu)-----------------*/
char        yCMD_menu_overall       (char *l, char *b, char *t);
char        yCMD_menu_data          (char n, short *x, short *y, char *b, short *xo, short *yo, char *l, char *t, char *a, char *v);



#endif
/*============================----end-of-source---============================*/
