/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/04 23:01:30 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(long time)
{
	long			start;
	
	start = ft_get_time(0);
	while ((ft_get_time(0) - start) < time)
		usleep(10);
}

int ft_lock_mutex(thr_t *thrd)
{
	// printf("take thrd: %d left fork: %p\n", thrd->id, &thrd->left_fork);
	if (pthread_mutex_lock(&thrd->left_fork))
		return (write(2, "thrd fail to take left fork\n", 29));
	ft_putevent(thrd, "has take left fork\n");
	// printf("take thrd: %d right fork: %p\n", thrd->id, thrd->right_fork);
	if (pthread_mutex_lock(thrd->right_fork))
		return (write(2, "thrd fail to take right fork\n", 30));
	ft_putevent(thrd, "has take right fork\n");
	return (0);
}

int ft_unlock_mutex(thr_t *thrd)
{
	// printf("put thrd: %d right fork: %p\n", thrd->id, thrd->right_fork);
	if (pthread_mutex_unlock(thrd->right_fork))
		return (write(2, "thrd fail to putdown right fork\n", 33));
	// printf("put thrd: %d left fork: %p\n", thrd->id, &thrd->left_fork);
	if (pthread_mutex_unlock(&thrd->left_fork))
		return (write(2, "thrd fail to putdown left fork\n", 32));
	return (0);
}

int ft_intiate_mutexes(thr_t *thrds, int ph_nb)
{
	int				i;

	i = -1;
	while (++i  < ph_nb)
	{
		if (pthread_mutex_init(&thrds[i].left_fork, NULL) || \
			pthread_mutex_init(&thrds[i].meal_mtx, NULL))
			return (write(2, "issue in intiate of mtx!\n", 26));
		thrds[i].right_fork = &thrds[(i + 1) % ph_nb].left_fork;
		// printf("thrd: %d left_fork add: %p\n", (i + 1), &(thrds[i]).left_fork);
		// printf("thrd: %d right_fork add: %p\n", (i + 1), thrds[i].right_fork);
	}
	return (0);
}
