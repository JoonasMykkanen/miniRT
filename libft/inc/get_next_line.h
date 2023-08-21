/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:03:38 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/22 09:03:40 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h> 
# include <sys/uio.h>
# include <sys/types.h>

char	*get_next_line(int fd);
char	*gnl_strldup(char *src, int len);
size_t	gnl_strlen(char const *s, int mode);
void	*gnl_memchr(const void *s, int c, size_t n);
char	*gnl_strjoin(char const *s1, char const *s2);
void	*gnl_memcpy(void *dst, const void *src, size_t n);

#endif
