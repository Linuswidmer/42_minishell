typedef struct s_AST t_AST;
typedef struct s_ADD t_ADD;
typedef struct s_MIN t_MIN;
typedef struct s_MAX t_MAX;




typedef enum e_type
{
        ADD,
	MIN,
	MAX,
} e_type;

struct s_ADD
{
	int Number,
	t_AST *next;
	t_AST *last;
	t_AST *up;
	t_AST *down;
}		


struct s_Min
{
        int Number,
        t_AST *next;
        t_AST *last;
        t_AST *up;
	t_AST *left;
	t_AST *right;		
}


struct s_MAX
{
	char	key;
        int Number,
        t_AST *next;
        t_AST *last;
        t_AST *up;
        t_AST *down;
}

struct s_AST
{
	e_type key;
	union
	{
		t_ADD *add;
		t_MIN *min;
		t_MAX *max;
	}node;
}
