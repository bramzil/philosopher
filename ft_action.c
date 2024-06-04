/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:28 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/04 23:02:31 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// void ft_destroy_mutexes(glb_t *glb)
// {
// 	int			i;

// 	i = -1;
// 	while (++i < glb->ph_nb)
// 	{
// 		pthread_mutex_destroy(&(glb->d_mtx[i]));
// 		pthread_mutex_destroy(&(glb->forks[i]));
// 		pthread_mutex_destroy(&(glb->meals_mtx[i]));
// 	}
// }

int	ft_sleeping(thr_t *thrd)
{
	if (ft_last_meal(thrd, ft_get_time(thrd->glb->start)) < 0)
		return (-1);
	if (ft_putevent(thrd, "sleeping\n"))
		return (-1);
	ft_usleep(thrd->glb->t_slp);
	return (0);
}
int	ft_putevent(thr_t *thrd, char *des)
{
	static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return(write(2, "thr fails to lock print mtx\n", 29));
	if (!ft_die(0))
		printf("%-15ld %-10d %s", ft_get_time(thrd->glb->start), thrd->id, des);
	if (des[0] == 'd')
		return (0);
	if (pthread_mutex_unlock(&mtx))
		return(write(2, "thr fails to lock print mtx\n", 29));
	return (0);
}

int	ft_eating(thr_t  *thrd)
{
	if (ft_putevent(thrd, "thinking\n"))
		return (-1);
	if (ft_lock_mutex(thrd) < 0)
		return (-1);
	if (ft_putevent(thrd, "eating\n"))
		return (-1);
	ft_usleep(thrd->glb->t_eat);
	if (ft_last_meal(thrd, ft_get_time(thrd->glb->start)) < 0)
		return (-1);
	if (ft_putevent(thrd, "sleeping\n"))
		return (-1);
	ft_usleep(thrd->glb->t_slp);
	if (ft_unlock_mutex(thrd) < 0)
		return (-1);
	ft_usleep(thrd->glb->t_eat);
	if (ft_last_meal(thrd, ft_get_time(thrd->glb->start)) < 0)
		return (ft_update_die(thrd));
	if (ft_unlock_mutex(thrd) < 0)
		return (ft_update_die(thrd));
	return (0);
}