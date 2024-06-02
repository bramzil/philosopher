/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 12:03:53 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(long time)
{
	long			t;
	
	t = ft_get_time();
	while (1)
	{
		if (time <= (ft_get_time() - t))
			break ;
		usleep(50);
	}
}

int ft_lock_mutex(thr_t *thrd)
{
	if (!ft_die(0) && pthread_mutex_lock(thrd->left_fork))
		return (write(2, "thrd fail to take left fork\n", 29));
	printf("%-15ld %-10d has take left fork\n", ft_get_time(), thrd->id);
	if (!ft_die(0) && pthread_mutex_lock(thrd->right_fork))
		return (write(2, "thrd fail to take right fork\n", 30));
	printf("%-15ld %-10d has take right fork\n", ft_get_time(), thrd->id);
	return (0);
}

int ft_unlock_mutex(thr_t *thrd)
{
	if (!ft_die(0) && pthread_mutex_unlock(thrd->right_fork))
		return (write(2, "thrd fail to putdown right fork\n", 33));
	if (!ft_die(0) && pthread_mutex_unlock(thrd->left_fork))
		return (write(2, "thrd fail to putdown left fork\n", 32));
	return (0);
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
