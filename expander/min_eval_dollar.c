#include "minishell.h"
static char ft_dollar_split_extra(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help)
{                                                                                 
        help.splitvalue = min_delimiter_split(value, &help.space, E_SPACE);        
        min_free(&help.value);                                                    
        if (!help.splitvalue)                                                     
                return (min_add_value_to_expander(token, word, NULL, help.space)); 
        help.space = min_eval_splitvalue(word, extra, help, help.splitvalue);      
        if (help.space == 3)                                                      
                help.space = min_add_to_asterisk(word, ft_asterisk_splitvalue(     
                        help.splitvalue[ft_len_split(help.splitvalue)             
                        -1]), NULL);                                              
        if (help.space == 4)                                                      
                help.space = min_asterisk(token, extra, ft_asterisk_splitvalue    
                        (help.splitvalue[ft_len_split(help.splitvalue) -1]),      
                        min_init_exphelp(help.dict, 0, 1));                       
        //min_doublefree(&help.splitvalue);                                       
        if (*token)                                                               
                *token = (*token)->next;                                          
        return (help.space);                                                      
}                       

static char     ft_dollar_split(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help)
{                                                                                 
        if (extra)                                                                
                return (ft_dollar_split_extra(token, word, extra, help);          
        help.splitvalue = min_delimiter_split(value, &help.space, E_SPACE);        
        min_free(&help.value);                                                    
        if (!help.splitvalue)                                                     
                return (min_add_value_to_expander(token, word, NULL, help.space)); 
        help.space = min_eval_splitvalue(word, extra, help, splitvalue);           
        if (help.space == 3)                                                      
                help.space = min_asterisk(token, word, ft_asterisk_splitvalue(    
                        help.splitvalue[ft_len_split(help.splitvalue) -1]),       
                        min_init_exphelp(help.dict, 1, 0));                       
        if (help.space == 4)                                                      
                help.space = min_asterisk(token, word, ft_asterisk_splitvalue(    
                        help.splitvalue[ft_len_split(help.splitvalue) -1]),       
                                min_init_exphelp(help.dict, 0, 1));               
        //min_doublefree(&dhelp.splitvalue);                                      
        if (*token)                                                               
                *token = (*token)->next;                                          
        return (help.space);                                                      
}                                                                                 
                                                                                  
static char ft_add_asterisk_free(t_expander **word, char **va, t_lexer **token)   
{                                                                                 
        t_expander *new;                                                          
                                                                                  
        if (!*va)                                                                 
                min_free_expander(word);                                          
        new = min_init_expander(l_word, *va);                                     
        min_to_aste(word, new, token);                                     
        min_free(va);                                                             
        return (0);                                                                  
}                                                                                    
                                                                                     
                                                                                     
char     min_eval_dollar(t_lexer **token, t_expander **word, t_expander **extra, t_exphelp help)
{                                                                                    
        if (!min_check_word((*token)->value, &help.dollar_value))                     
        {                                                                            
                if (extra)                                                           
                        return (ft_add_asterisk_free(word, &help.dollar_value, token));
                return (ft_add_value_to_expander(token, word, &help.dollar_value, help.space));
        }                                                                            
        if (!min_check_dict(&help.dollar_value, &help.value, help.dict))              
        {                                                                            
                *token = (*token)->next;                                             
                return (help.space);                                                 
        }                                                                            
        if (help.export)                                                             
        {                                                                            
                if (extra)                                                           
                        return (return (ft_add_asterisk_free(word, &help.value, token));    
                return(ft_add_value_to_expander(token, word, &help.value, help.space)); 
        }                                                                            
        return (ft_dollar_splitt(token, word, extra, help);                          
}                         
