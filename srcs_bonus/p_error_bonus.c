/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2025/06/17 13:25:38 by marvin            #+#    #+#             */
/*   Updated: 2025/06/17 13:25:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_error(char *msg, t_pipex *var)
{
	close_all(var);
	if (var->pipes)
		free_pipes(var);
	if (var->pid)
		free(var->pid);
	error_exit(msg);
}

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}
