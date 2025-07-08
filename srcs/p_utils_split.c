/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_utils_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 13:08:28 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/26 15:13:08 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **newstr, size_t i)
{
	while (i > 0)
		free(newstr[--i]);
	free(newstr);
}

int	count_plicas(char const *s)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (-1);
	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '\"')
			count++;
		i++;
	}
	if (count % 2 != 0)
		return (-1);
	return (count);
}

int	toggle_quotes(int in_quotes, char c, char *quote_char)
{
	if ((c == '\'' || c == '\"'))
	{
		if (!in_quotes)
		{
			*quote_char = c;
			return (1);
		}
		else if (c == *quote_char)
			return (0);
	}
	return (in_quotes);
}
