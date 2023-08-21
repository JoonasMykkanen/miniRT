/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:21:19 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/29 19:21:21 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_s(va_list *args, int count)
{
	char	*str;
	int		len;

	str = va_arg(*args, char *);
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (count + 6);
	}
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	return (count + len);
}
