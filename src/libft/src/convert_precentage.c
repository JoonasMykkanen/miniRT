/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_precentage.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 19:22:21 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:08:14 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	convert_precentage(int count)
{
	ft_putchar_fd('%', 1);
	return (++count);
}
