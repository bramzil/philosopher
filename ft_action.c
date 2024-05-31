/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/31 03:32:50 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

void ft_free_par(par_t *par)
{
	int			i;

	i = -1;
	while (++i < par->ph_nb)
	{
		pthread_mutex_destroy(&(par->forks[i]));
		pthread_mutex_destroy(&(par->meals_mtx[i]));
	}
	free(par->meals_mtx);
	free(par->meals);
	free(par->forks);
}

int	ft_sleeping(par_t *par, long *ref, int id)
{
	if (ft_die(id, 0))
		return (-1);
	printf("%-15ld %-10d sleeping\n", ft_get_time(), id);
	ft_usleep(par->t_slp * 1000);
	return (0);
}

int	ft_eating(par_t *par, long *ref, int id)
{
	if (ft_die(id, 0) || ft_lock_mutex(par, par->ph_nb, id))
		return (-1);
	printf("%-15ld %-10d eating\n", ft_get_time(), id);
	ft_usleep(par->t_eat * 1000);
	ft_last_meal(par, ft_get_time(), id);
	if (ft_die(id, 0) || ft_unlock_mutex(par, par->ph_nb, id))
		return (-1);
	return (0);
}