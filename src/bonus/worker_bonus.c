/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   worker_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 07:19:34 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/27 13:57:26 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

// Function to delete workers after program is done
int	kill_workers(t_data *data)
{
	t_worker	*workers;
	int	idx;

	idx = -1;
	workers = data->pool.workers;
	pthread_cond_broadcast(&data->pool.cond);
	pthread_mutex_lock(&data->pool.alive);
	data->pool.done = true;
	pthread_mutex_unlock(&data->pool.alive);
	while (++idx < WORKERS)
	{
		if (pthread_join(workers[idx].employee, 0) != OK)
			return (ERROR);
	}
	if (pthread_cond_destroy(&data->pool.cond) != OK)
		return (ERROR);
	if (pthread_mutex_destroy(&data->pool.alive) != OK)
		return (ERROR);
	if (pthread_mutex_destroy(&data->pool.queue) != OK)
		return (ERROR);
	if (pthread_mutex_destroy(&data->pool.write) != OK)
		return (ERROR);
	return (OK);
}

static int	init_mutexes(t_data *data)
{
	data->pool.done = false;
	if (pthread_cond_init(&data->pool.cond, 0) != OK)
		return (ERROR);
	if (pthread_mutex_init(&data->pool.alive, 0) != OK)
		return (ERROR);
	if (pthread_mutex_init(&data->pool.queue, 0) != OK)
		return (ERROR);
	if (pthread_mutex_init(&data->pool.write, 0) != OK)
		return (ERROR);
	return (OK);
}

// init worker threads inside the pool
int	wakeup_workers(t_data *data)
{
	t_worker	*workers;
	int			status;
	int			idx;

	idx = -1;
	status = OK;
	workers = data->pool.workers;
	if (init_mutexes(data) != OK)
		status = ERROR;
	while (++idx < WORKERS)
	{
		workers[idx].index = idx;
		workers[idx].data = data;
		if (pthread_create(&data->pool.workers[idx].employee, 0, &routine, &workers[idx]) != OK)
			status = ERROR;
	}
	if (status == ERROR)
		ft_putstr_fd("Error: Threadpool could not be created\n", 2);
	return (status);
}
