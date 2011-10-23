#include "group.h"
#include <stdio.h>
#include <stdlib.h>

static group_item bcastgroup[MAX_NUM_OF_GROUPS];

void warning(char *msg) 
{
    fprintf(stderr, "%s\n", msg);
}


int init_group() 
{
    int i;
    printf("Initializing groups...\n");
    for ( i = 0; i < MAX_NUM_OF_GROUPS; i++ ) {
        bcastgroup[i].grpnum = -1;
        bcastgroup[i].pbuflist 
            = (msgbuf_node *)KERN_MALLOC(sizeof(msgbuf_node));
        (bcastgroup[i].pbuflist)->next = NULL;
        (bcastgroup[i].pbuflist)->pbuffer = NULL;

        bcastgroup[i].pproclist 
            = (proc_node *)KERN_MALLOC(sizeof(proc_node));
        (bcastgroup[i].pproclist)->next = NULL;
        (bcastgroup[i].pproclist)->pid = -1;
    }
    return 0;        
}

int display_group()
{
    int i;
    proc_node *cur;
   
    printf("Displaying group...\n");
    for ( i = 0; i < MAX_NUM_OF_GROUPS; i++ ) {
         cur = (bcastgroup[i].pproclist)->next;
         /* print if there are procs in this group */
         if ( cur != NULL ) {
             printf("GROUP %d:", i);
             while (cur != NULL) {
                 printf("->%d ", cur->pid);
                 cur = cur->next;
             }
             printf("\n");
         }
         
    }
}

void free_proclist(proc_node *p)
{
    if ( p == NULL ) {
        return;
    } else {
        free_proclist( p->next );
    }
    free(p);
}

void free_buflist(msgbuf_node *p)
{
    if ( p == NULL ) {
        return;
    } else {
        free_buflist( p->next );
    }
    free(p);
}

int free_group()
{
    int i;

    printf("Freeing group...\n");
    for ( i=0; i<MAX_NUM_OF_GROUPS; i++ ) {
        free_proclist(bcastgroup[i].pproclist);
        free_buflist(bcastgroup[i].pbuflist); 
    }
}


int addproc(int groupid, int pid)
{
    /* check if groupid is legal */
    if ( groupid >= MAX_NUM_OF_GROUPS 
            || groupid < 0 ) {
        warning("groupid is illegal.");
        return -1;
    }

    /* add this proc to the proc list */
    proc_node *pnewnode 
        = (proc_node *)KERN_MALLOC( sizeof(proc_node) );
    pnewnode->pid = pid;
    pnewnode->next = (bcastgroup[groupid].pproclist)->next;
    (bcastgroup[groupid].pproclist)->next = pnewnode;

    return 0;
}

int delproc(int groupid, int pid)
{
    /* check if groupid is legal */
    if ( groupid >= MAX_NUM_OF_GROUPS 
            || groupid < 0 ) {
        warning("groupid is illegal.");
        return -1;
    }

    proc_node *prev = bcastgroup[groupid].pproclist;
    proc_node *cur = (bcastgroup[groupid].pproclist)->next;
    
    if ( cur == NULL ) {
        /* this proc list is empty */
        warning("Trying to delete a proc from an empty list.");
        return -1;
    }
   

    while ( cur != NULL ) {
        if ( cur->pid == pid ) {
            /* found the proc, delete it */
            prev->next = cur->next;
            free(cur);
            cur = prev->next;
        } else {
            cur = cur->next;
            prev = prev->next;
        }

    }
    return 0;
}

int delgroup(int groupid)
{
    /* check if groupid is legal */
    if ( groupid >= MAX_NUM_OF_GROUPS 
            || groupid < 0 ) {
        warning("groupid is illegal.");
        return -1;
    }

    proc_node *prev = bcastgroup[groupid].pproclist;
    proc_node *cur = (bcastgroup[groupid].pproclist)->next;
    
    if ( cur == NULL ) {
        /* this proc list is empty */
        warning("The group is already empty.");
        return -1;
    }

    while ( cur != NULL ) {
        prev->next = cur->next;
        free(cur);
        cur = prev->next;
    }
    
}


