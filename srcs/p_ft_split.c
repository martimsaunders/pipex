/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ft_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprazere <mprazere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 10:36:48 by mprazere          #+#    #+#             */
/*   Updated: 2025/06/26 15:12:55 by mprazere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_words(char const *s, char c)
{
	int		count;
	int		i;
	int		in_quotes;
	char	quote_char;

	count = 0;
	i = 0;
	in_quotes = 0;
	quote_char = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c && !in_quotes)
			i++;
		if (!s[i])
			break ;
		count++;
		while (s[i] && (s[i] != c || in_quotes))
		{
			in_quotes = toggle_quotes(in_quotes, s[i], &quote_char);
			i++;
		}
	}
	return (count);
}

static int	word_len(char const *s, char c)
{
	int		len;
	int		in_quotes;
	char	quote_char;

	len = 0;
	in_quotes = 0;
	quote_char = 0;
	while (s[len] && (s[len] != c || in_quotes))
	{
		in_quotes = toggle_quotes(in_quotes, s[len], &quote_char);
		len++;
	}
	return (len);
}

static char	*extract_word(char const *s, int len, int i)
{
	char	*word;
	int		j;

	if ((s[0] == '\'' || s[0] == '\"') && len >= 2 && s[len - 1] == s[0])
	{
		word = malloc(len - 1);
		if (!word)
			return (NULL);
		j = 0;
		while (i < len - 1)
			word[j++] = s[i++];
		word[j] = '\0';
	}
	else
	{
		word = malloc(len + 1);
		if (!word)
			return (NULL);
		i = -1;
		while (++i < len)
			word[i] = s[i];
		word[i] = '\0';
	}
	return (word);
}

static char	*refine_word(char *s1, int count, int len)
{
	char	*new_str;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	count = count_plicas(s1);
	if (count == -1)
		return (s1);
	len = ft_strlen(s1) - count;
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (free(s1), NULL);
	i = 0;
	count = 0;
	while (i < len)
	{
		while (s1[i] == '\'' || s1[i] == '\"')
			i++;
		new_str[count++] = s1[i++];
	}
	new_str[count] = '\0';
	return (free(s1), new_str);
}

char	**ft_split_with_quotes(char const *s, char c, int i, int j)
{
	char	**result;
	int		words;
	int		len;

	if (!s)
		return (NULL);
	if (count_plicas(s) == -1)
		return (NULL);
	words = count_words(s, c);
	result = malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	while (++i < words)
	{
		while (s[j] && s[j] == c)
			j++;
		len = word_len(&s[j], c);
		result[i] = extract_word(&s[j], len, i);
		result[i] = refine_word(result[i], 0, 0);
		if (!result[i])
			return (free_split(result, i), NULL);
		j += len;
	}
	result[i] = NULL;
	return (result);
}

/* int	main(void)
{
	char *c = "grep '2'";
	char set = ' ';
	char **s = ft_split_with_quotes(c, set, -1, 0);
	int a = 0;

	if (!s)
	{
		printf("Erro");
		return (1);
	}
	while (s[a])
	{
		printf("Resultado: %s\n", s[a]);
		a++;
	}
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (0);
} */