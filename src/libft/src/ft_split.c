/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 13:27:29 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 13:27:30 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	buf;
	int	count;

	i = 0;
	buf = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			i++;
			buf++;
		}
		else if (s[i] == c && buf == 0)
			i++;
		else if (s[i] == c && buf > 0)
		{
			count++;
			buf = 0;
		}
	}
	if (buf > 0 && s[i] == '\0')
		count++;
	return (count);
}

static int	get_len(const char *s, char c, int *cur)
{
	int	buf;

	buf = 0;
	while (s[*cur] != '\0')
	{
		if (s[*cur] == c)
		{
			*cur += 1;
		}
		if (s[*cur] != c)
		{
			buf++;
			*cur += 1;
		}
		if (buf > 0 && s[*cur] == c)
			break ;
	}
	return (buf);
}

static void	write_word(const char *s, char *word, int buf, int cur)
{
	int	i;
	int	start;

	i = 0;
	start = cur - buf;
	while (i < buf)
	{
		word[i] = s[start];
		i++;
		start++;
	}
	word[i] = '\0';
}

static void	handle_leaks(char **arr, int index)
{
	while (index >= 0)
	{
		free(arr[index]);
		index--;
	}
	free(arr);
}

char	**ft_split(char const *s, char c)
{
	int		y;
	int		buf;
	int		cur;
	int		count;
	char	**arr;

	y = 0;
	cur = 0;
	if (!s)
		return (NULL);
	count = count_words(s, c);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	while (count-- > 0)
	{
		buf = get_len(s, c, &cur);
		arr[y] = malloc(sizeof(char) * (buf + 1));
		if (!arr[y])
			handle_leaks(arr, y);
		write_word(s, arr[y], buf, cur);
		y++;
	}
	arr[y] = NULL;
	return (arr);
}
