/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 10:28:37 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_destroy_mutexes(par_t *par)
{
	int			i;

	i = -1;
	while (++i < par->ph_nb)
		pthread_mutex_destroy(&(par->forks[i]));
}

int	ft_sleeping(thr_t *thrd)
{
	if (ft_die(0))
		return (1);
	printf("%-15ld %-10d sleeping\n", ft_get_time(), thrd->id);
	ft_usleep(thrd->t_slp);
	return (0);
}

int	ft_eating(thr_t  *thrd)
{
	if (ft_lock_mutex(thrd) < 0)
		return (ft_die(1));
	printf("%-15ld %-10d eating\n", ft_get_time(), thrd->id);
	ft_usleep(thrd->t_eat);
	if (ft_last_meal(thrd, ft_get_time()) < 0)
		return (ft_die(1));
	if (ft_unlock_mutex(thrd) < 0)
		return (ft_die(1));
	return (0);
}