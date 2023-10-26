/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:33:51 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/26 10:10:58 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

void	reset_job_list(t_job *start)
{
	while (start)
	{
   		start->done = false;
		start = start->next;
	}
}

void	free_job_list(t_job *start)
{
	t_job	*temp;

	while (start)
	{
		temp = start;
		start = start->next;
		free(temp);
	}
}

int	get_next_job(t_job *start)
{
	t_job	*current;

    if (!start)
        return (-1);
	current = start;
	while (current->next)
	{
		if (!current->done)
			break ;
		current = current->next;
	}
	if (current->done)
		return (-1);
    current->done = true;
	return (current->row);
}

int push_job_list(t_job **start, int data)
{
    t_job	*temp;
    t_job	*job;

	job = new_job(data);
    if (!job)
        return (ERROR);
    if (!*start)
    {
        *start = job;
        return (OK);
    }
    temp = *start;
    while (temp->next)
        temp = temp->next;
    temp->next = job;
	return (OK);
}

t_job	*new_job(int data)
{
	t_job	*job;

	job = malloc(sizeof(t_job));
	if (!job)
		return (NULL);
	job->next = NULL;
	job->row = data;
	job->done = false;
	return (job);
}
