/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_wrappers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:46:00 by lwidmer           #+#    #+#             */
/*   Updated: 2023/04/12 12:48:19 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int export_wrapper(void** args)
{
    Commands* commands = (Commands*)args[0];
    t_dict* dict = (t_dict*)args[1];
    char* arg = (char*)args[2];

    return (commands->export(dict, arg));
}

int cd_wrapper(void** args) {
    Commands* commands = (Commands*)args[0];
    char* argv = (char*)args[1];

    return (commands->cd(argv));
}

