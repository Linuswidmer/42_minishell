/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macros.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwidmer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:34:16 by lwidmer           #+#    #+#             */
/*   Updated: 2023/05/05 17:47:42 by lwidmer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACROS_H

# define SET_EXIT_ON_ERROR(result) ((result) == - 1 ? (exit = 1) : 0)
# define UPDATE_EXIT(e, r) ((e) = ((e) == 0 && (r) != 0) ? (r) : (e))
# define CHECK_MALLOC(ptr, e) ((ptr) ? 0 : (UPDATE_EXIT((e), 1)))
#define ON_SUCCESS(exit_code, function) ((exit_code) == 0 ? (function) : 0)

# define MACROS_H
#endif
