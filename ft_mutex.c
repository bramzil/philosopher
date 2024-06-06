/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/06 10:49:23 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void	ft_usleep(long time)
{
	long			start;
	
	start = ft_get_time(0);
	while ((ft_get_time(0) - start) < time)
		usleep(500);
}

int ft_lock_mutex(thr_t *thrd)
{
	if (pthread_mutex_lock(&(thrd->left_fork)))
		return (-1);
	ft_putevent(thrd, "has take left fork\n");
	if (pthread_mutex_lock(thrd->right_fork))
		return (-1);
	ft_putevent(thrd, "has take right fork\n");
	return (0);
}

int ft_unlock_mutex(thr_t *thrd)
{
	if (pthread_mutex_unlock(&(thrd->left_fork)))
		return (-1);
	if (pthread_mutex_unlock(thrd->right_fork))
		return (-1);
	return (0);
}

int	ft_meals(thr_t *thrd, int incr)
{
	int			tmp;
	
	if (pthread_mutex_lock(&(thrd->meal_nbr_mtx)))
		return (-1);
	if (incr)
		thrd->meals_nbr += 1;
	tmp = thrd->meals_nbr;
	if (pthread_mutex_unlock(&(thrd->meal_nbr_mtx)))
		return (-1);
	return (tmp);
}

int ft_intiate_mutexes(thr_t *thrds, int ph_nb)
{
	int				i;

	i = -1;
	if (!thrds)
		return (-1);
	while (++i  < ph_nb)
	{
		if (pthread_mutex_init(&(thrds[i].left_fork), NULL) || \
			pthread_mutex_init(&(thrds[i].meal_mtx), NULL))
			return (write(2, "issue in intiate of mtx!\n", 26));
		thrds[i].right_fork = &(thrds[(i + 1) % ph_nb].left_fork);
	}
	if (pthread_mutex_init(&((thrds[0]).glb->prnt_mtx), NULL) || \
		pthread_mutex_init(&((thrds[0]).meal_nbr_mtx), NULL))
		return (write(2, "issue in intiate of mtx!\n", 26));
	return (0);
}
