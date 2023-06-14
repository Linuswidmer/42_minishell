#imclude "minishell.h"




static char *ft_status(char *word)                                                
{                                                                                 
        char *status;                                                             
        char *temp;                                                               
        temp = ft_itoa(g_status);                                                 
        status = ft_strjoin(temp, word);                                          
        min_free(&temp);                                                          
        return (status);                                                          
} 



int      min_check_word(char *word, char **result)                          
{                                                                                 
        *result = NULL;                                                           
        if (!word)                                                                
                return (0);                                                       
        else if (ft_isdigit(word[0]))                                             
                *result = ft_strdup(++word);                                      
        else if (ft_isalpha(word[0]))                                             
        {                                                                         
                *result = ft_strdup(word);                                        
                return (1);                                                       
        }                                                                         
        else if (word[0] == QUESTION)                                             
                *result = ft_status(++word);                                      
        else                                                                      
        {                                                                         
                if (word[0] == SUB)                                               
                        ft_putstr_fd(ERR_SUB, 2);                                 
                *result = ft_strjoin(DOLLAR, word);                               
        }                                                                         
        return (0);                                                               
}   
