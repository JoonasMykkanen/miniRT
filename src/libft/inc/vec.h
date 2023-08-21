/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 16:04:54 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC_H
# define VEC_H

# include "libft.h"
# include <stdbool.h>

typedef struct s_vec
{
	unsigned char	*memory;
	size_t			elem_size;
	size_t			alloc_size;
	size_t			len;
}	t_vec;

int		vec_free(t_vec *src);
int		vec_pop(void *dst, t_vec *src);
int		vec_push(t_vec *dst, void *src);
int		vec_copy(t_vec *dst, t_vec *src);
void	*vec_get(t_vec *src, size_t index);
int		vec_append(t_vec *dst, t_vec *src);
int		vec_prepend(t_vec *dst, t_vec *src);
int		vec_remove(t_vec *src, size_t index);
int		vec_iter(t_vec *src, void (*f) (void *));
int		vec_resize(t_vec *src, size_t target_size);
int		vec_insert(t_vec *dst, void *src, size_t index);
int		vec_map(t_vec *dst, t_vec *src, void (*f) (void *));
int		vec_filter(t_vec *dst, t_vec *src, bool (*f) (void *));
int		vec_new(t_vec *dst, size_t init_len, size_t elem_size);
int		vec_from(t_vec *dst, void *src, size_t len, size_t elem_size);

#endif