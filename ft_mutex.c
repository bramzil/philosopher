/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 20:20:10 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(long time)
{
	long			t;
	
	t = ft_get_time(0);
	while (1)
	{
		if (time <= (ft_get_time(0) - t))
			break ;
		usleep(10);
	}
}

int ft_lock_mutex(thr_t *thrd)
{
	if (pthread_mutex_lock(thrd->left_fork))
		return (write(2, "thrd fail to take left fork\n", 29));
	ft_putevent(thrd, "has take left fork\n", thrd->id);
	if (pthread_mutex_lock(thrd->right_fork))
		return (write(2, "thrd fail to take right fork\n", 30));
	ft_putevent(thrd, "has take right fork\n", thrd->id);
	return (ft_die(0, thrd->id));
}

int ft_unlock_mutex(thr_t *thrd)
{
	if (pthread_mutex_unlock(thrd->right_fork))
		return (write(2, "thrd fail to putdown right fork\n", 33));
	if (pthread_mutex_unlock(thrd->left_fork))
		return (write(2, "thrd fail to putdown left fork\n", 32));
	return (ft_die(0, thrd->id));
}

int ft_intiate_mutexes(par_t *par)
{
	int				i;

	i = -1;
	while (++i  < par->ph_nb)
		if (pthread_mutex_init(&(par->forks[i]), NULL) || \
			pthread_mutex_init(&(par->meals[i]), NULL))
			return (write(2, "issue in intiate of mtx!\n", 26));
	return (0);
}
