/*============================----beg-of-source---============================*/
#ifndef yCMD
#define yCMD yes


typedef  unsigned char        uchar;





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
