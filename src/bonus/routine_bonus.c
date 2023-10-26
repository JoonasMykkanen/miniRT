/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 08:05:01 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/26 12:10:57 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

static int	check_alive(t_data *data)
{
	pthread_mutex_lock(&data->pool.alive);
	if (data->pool.done)
	{
		pthread_mutex_unlock(&data->pool.alive);
		return (ERROR);
	}
	pthread_mutex_unlock(&data->pool.alive);
	return (OK);
}

static void	do_job(t_data *data, int y)
{
	int	pixel;
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		pixel = render_pixel(data, x, y);
		pthread_mutex_lock(&data->pool.write);
		mlx_put_pixel(data->img, x, y, pixel);
		pthread_mutex_unlock(&data->pool.write);
	}
}

// Routine that each worker loops trough
void	*routine(void *param)
{
	t_worker	*worker;
	t_data		*data;
	int			row;

	worker = (t_worker *)param;
	data = worker->data;
	while (42)
	{
		if (check_alive(data) != OK)
			break ;
		pthread_mutex_lock(&data->pool.queue);
		row = get_next_job(data->pool.job_list);
		if (row < 0)
		{
			pthread_cond_wait(&data->pool.cond, &data->pool.queue);
			pthread_mutex_unlock(&data->pool.queue);
			continue ;
		}
		pthread_mutex_unlock(&data->pool.queue);
		do_job(data, row);
	}
	return (data);
}
