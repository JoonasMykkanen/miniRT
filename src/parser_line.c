/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:27:19 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/25 09:25:49 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	more_checks(char *str, int i)
{
	if ((str[i] == ' ' || str[i] == ',') && (str[i + 1] == '.'))
		return (1);
	return (0);
}

int	check_line_chars(char *str, int len)
{
	int	i;

	i = -1;
	while (str[++i] != '\0' && i < len - 1)
	{
		if (ft_isdigit(str[i]))
			continue ;
		if (i < 3 && ft_isalpha(str[i]))
			continue ;
		if (str[i] == ' ' && (str[i + 1] == ' ' || ft_isdigit(str[i + 1])))
			continue ;
		if ((str[i] == ',' || str[i] == '.') && ft_isdigit(str[i + 1]))
			continue ;
		if ((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]))
			continue ;
		if (str[i] == ',' && (str[i + 1] == '+' || str[i + 1] == '-'))
			continue ;
		if (str[i] == ' ' && (str[i + 1] == '+' || str[i + 1] == '-'))
			continue ;
		if (more_checks(str, i))
			continue ;
		return (ERROR);
	}
	return (OK);
}
