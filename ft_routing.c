/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/31 03:42:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

long	ft_get_time()
{
	long			tmp;
	static long		start;
	struct timeval	stmp;

	gettimeofday(&stmp, NULL);
	tmp = ((stmp.tv_sec * 1000) + (stmp.tv_usec / 1000));
	if (!start)
		start = tmp;
	return (tmp - start);
}

static int	ft_get_id(void)
{
	static int				id;
	int						tmp;
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;

	if (pthread_mutex_lock(&mtx))
		return (printf("thr: %d fails to lock id mtx\n", 0));
	tmp = id;
	id += 1;
	if (pthread_mutex_unlock(&mtx))
		return (printf("thr: %d fails to unlock id mtx\n", 0));
	return (tmp);
}

long	ft_last_meal(par_t *par, long value, int id)
{
	long		tmp;
	
	if (ft_die(id, 0))
		return (0);
	if (pthread_mutex_lock(&(par->meals_mtx[id])))
		return (printf("thr: %d fails to lock meals mtx\n", id));
	if (0 <= value)
		par->meals[id] = value;
	tmp = par->meals[id];
	if (pthread_mutex_unlock(&(par->meals_mtx[id])))
		return (printf("thr: %d fails to unlock meals mtx\n", id));
	return (tmp);
}

void *ft_routing(void *par)
{
	int				i;
	int				id;
	par_t			*loc_par;
	long			stmp_ref;

	i = -1;
	id = ft_get_id();
	loc_par = ((par_t*)par);
	ft_last_meal(loc_par, ft_get_time(), id);
	while (!ft_die(id, 0))
	{
		printf("%-15ld %-10d thinking\n", ft_get_time(), id);
		if (ft_die(id, 0) || ft_eating(par, &stmp_ref, id))
			break ;
		if (ft_die(id, 0) || ft_sleeping(par, &stmp_ref, id))
			break ;
	}
	return (0);
}