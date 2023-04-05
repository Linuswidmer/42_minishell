typedef struct s_cmdnode    t_cmdnode;
typedef struct s_ionode     t_ionode;



struct s_cmdnode
{
    char    *arg;
    char **args;
    t_cmdnode *next;
};

struct s_ionode
{
    char *value;
    char *file;
    t_ionode *next;
};

typedef union myunion
{ 
    t_cmdnode a;
 	t_ionode b;

} t_init;







t_init *min_last_ionode(t_init *node)
{
        while (node->next)
                node = node->next;
    return (node);
}



