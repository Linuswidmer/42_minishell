/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 09:58:09 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/20 10:09:27 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int global_var = 0;

void modify_global_var() {
    global_var += 10;
}

int main() {
    printf("The initial value of the global variable is: %d\n", global_var);

	int pid1;
	//int pid2;

	pid1 = fork();
	if (pid1 == 0)
    	modify_global_var();
		
	//pid2 = fork();

    printf("The value of the global variable after modification is: %d\n", global_var);

    return 0;
}
