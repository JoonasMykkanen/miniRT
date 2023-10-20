/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_line.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 14:27:19 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/20 15:40:20 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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
		return (ERROR);
	}
	return (OK);
}
