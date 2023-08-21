/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 10:06:12 by jmykkane          #+#    #+#             */
/*   Updated: 2023/07/05 12:07:25 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include "ft_printf.h"
# include "get_next_line.h"
# include "vec.h"

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int		ft_isnum(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
void	ft_free(void *ptr);
void	dir_check(char *file);
char	*ft_strdup(char *src);
char	*ft_itoa(long long n);
int		ft_lstsize(t_list *lst);
int		ft_atoi(const char *str);
size_t	ft_strlen(char const *s);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
void	ft_putnbr_fd(int n, int fd);
void	ft_bzero(void *s, size_t n);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
int		ft_hexlen(unsigned long long num);
char	*ft_strrchr(const char *s, int c);
char	**ft_split(char const *s, char c);
char	*ft_itoa_hex(unsigned long long num);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memrcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);
void	ft_puthex_lower_fd(unsigned long long num, int fd);
void	ft_puthex_upper_fd(unsigned long long num, int fd);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);

#endif
