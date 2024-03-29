
typedef struct msgbuf_node {
    int id;
    char *pbuffer;
    struct msgbuf_node *next;
} msgbuf_node;

typedef struct proc_node {
    int user_who_p; /* the user process number in PM */
    int user_buf_size;
    char *user_buf_addr;
    int least_acceptable_msg_id;
    struct proc_node *next;
} proc_node;

typedef struct group_item {
    int grpnum;
    msgbuf_node *pbuflist;
    proc_node *pproclist;
} group_item;

#define MAX_NUM_OF_GROUPS   1024
#define KERN_MALLOC     malloc
#define KERN_FREE       free


