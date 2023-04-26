/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:58:45 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/07 13:05:23 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    // Run the program in a loop
    while (1) {
        // Read input from the user using readline
        char *input = readline("Enter a command or type ctrl+d to quit: ");
        if (input == NULL) {
            printf("\nReceived Ctrl-D, exiting...\n");
            break;
        }
        // Add the input to the readline history
        add_history(input);
        // Process the input (in this case, just print it)
        printf("You entered: %s\n", input);
        free(input);
    }
    return 0;
}

