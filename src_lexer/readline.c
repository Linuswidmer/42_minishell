/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 12:08:13 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/03 12:08:28 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

int main() {
    char *input;

    // Read a line of input using readline
    input = readline("Enter a line of input: ");

    // Print the input
    printf("You entered: %s\n", input);

    // Free the memory used by readline
    free(input);

    return 0;
}
