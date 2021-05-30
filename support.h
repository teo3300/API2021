#ifdef log
    #define LOG(msg)    printf("%4u: %s\n", __LINE__, msg)
#else
    #define LOG(msg) 
#endif

#ifdef print
    #define PRINT(msg)  printf("%4u: %4i\n", __LINE__, msg)
#else
    #define LOG(msg) 
#endif

/********** support.h **********/

