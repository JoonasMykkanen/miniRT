/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:07:30 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:08:29 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	dir_check(char *file)
{
	int		fd;
	char	buf[1];

	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(-1);
	if (read(fd, buf, 1) == -1)
	{
		close(fd);
		perror("dir check");
		exit(-1);
	}
	close(fd);
}
