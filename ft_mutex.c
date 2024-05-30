/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:51 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/28 18:31:01 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_die(int id, int set)
{
	int						tmp;
	static int				die;
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return (ft_puterr("fail to lock die mtx!\n", id));
	if (set)
	{
		die += 1;
		if (die == 1)
			ft_putevent("died\n", ft_get_time(), id);
	}
	tmp = die;
	if (pthread_mutex_unlock(&mtx))
		return (ft_puterr("fail to unlock die mtx!\n", id));
	return (tmp);
}

int ft_lock_mutex(par_t *par, int ph_nb, int id)
{
	if (!par->forks)
		return (-1);
	if (pthread_mutex_lock(&par->forks[id]) || \
		pthread_mutex_lock(&par->forks[(id + 1) % ph_nb]))
		return (ft_puterr("fail to lock mutex\n", id));
	return (0);
}

int ft_unlock_mutex(par_t *par, int ph_nb, int id)
{
	if (!par->forks)
		return (-1);
	if (pthread_mutex_unlock(&par->forks[(id + 1) % ph_nb]) || \
		pthread_mutex_unlock(&par->forks[id]))
		return (ft_puterr("fail to unlock mutex\n", id));
	return (0);
}

int ft_intiate_forks(par_t *par)
{
	int				i;

	i = -1;
	par->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * par->ph_nb);
	if (!par->forks)
		return (printf("failure in allocation forks!\n"), -1);
	while (++i  < par->ph_nb)
		if (pthread_mutex_init(&(par->forks[i]), NULL))
			return (printf("issue in intiate of fork's mtx!\n"), -1);
	return (0);
}
