/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_d_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:22:06 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:07:57 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_d_i(va_list *args, int count)
{
	char	*str;
	int		num;
	int		len;

	num = va_arg(*args, int);
	str = ft_itoa(num);
	ft_putstr_fd(str, 1);
	len = ft_strlen(str);
	free(str);
	return (count + len);
}
