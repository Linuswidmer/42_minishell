
#include "parser.h"


t_ionode *min_last_ionode(t_ionode *node)
{
        while (node->next)
                node = node->next;
    return (node);
}
