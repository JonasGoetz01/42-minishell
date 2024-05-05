#include "../../inc/minishell.h"


/// @param token the token to be added to the garbage collector
/// @param mode 0 to add to the garbage collector, 1 to free all the tokens in the garbage collector
/// tracks all the tokens that have been malloced
void    garbage_collector(t_token *token, int mode)
{
    static t_token *garbage = NULL;
    t_token *tmp;

    if (mode == 0)
    {
        if (garbage == NULL)
            garbage = token;
        else
        {
            tmp = garbage;
            while (tmp)
                tmp = tmp->next;
            tmp = token;
        }
    }
    else if (mode == 1)
    {
        while (garbage)
        {
            tmp = garbage;
            garbage = garbage->next;
            free(tmp->value);
            free(tmp);
        }
    }
}
