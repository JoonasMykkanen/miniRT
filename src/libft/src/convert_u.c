/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:42:32 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/30 14:42:33 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_u(va_list *args, int count)
{
	char	*str;
	long	num;
	int		len;

	num = (unsigned int)va_arg(*args, int);
	str = ft_itoa(num);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (count + len);
}
