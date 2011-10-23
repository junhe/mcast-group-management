#include <stdio.h>
#include "group.h"


int main()
{
    int i; 
    
    init_group();
    display_group();

    /* add a pid to each group */
    for ( i = 0; i < 10; i++ ) {
        addproc(i,i*10);
        addproc(i,i*10+1);
    }
    display_group();
    
    /* delete one pid from one group */
    for ( i = 5; i < 10; i++ ) {
        delproc(i,i*10+1);
    }
    display_group();
   
    /* delete group 99 */
    delgroup(4);
    display_group();

    delgroup(55);
    free_group();
    printf("Goodbye Dennis!\n");
    return 0;    
}

