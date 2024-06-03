/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/03 03:41:15 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_die(thr_t *thrd)
{
	int			tmp;
	
	if (pthread_mutex_lock(&(thrd->glb->d_mtx[thrd->id - 1])))
				return (printf("fials to lock die mtx\n"));
	tmp = thrd->die;
	if (pthread_mutex_unlock(&(thrd->glb->d_mtx[thrd->id - 1])))
		return (printf("fials to unlock die mtx\n"));
	return (tmp);
}

int	ft_update_die(thr_t *thrd)
{
	int				i;
	int				tmp;
	
	i = -1;
	if (ft_die(thrd))
		return(1);
	while (++i < thrd->glb->ph_nb)
	{
		if (pthread_mutex_lock(&(thrd->glb->d_mtx[i])))
			return (printf("fials to lock die mtx\n"));
		thrd->die = 1;
		if (pthread_mutex_unlock(&(thrd->glb->d_mtx[i])))
			return (printf("fials to unlock die mtx\n"));
	}
	printf("%-15ld %-10d died\n", \
		ft_get_time(thrd->glb->start), thrd->id);
	return (0);
}

int main(int ac, char **av)
{
	int					i;
	glb_t				glb;
	thr_t				thrds[PH_NB];
	pthread_mutex_t		forks[PH_NB];
	pthread_mutex_t		d_mtx[PH_NB];
	pthread_mutex_t		meals_mtx[PH_NB];

	i = 0;
	glb.forks = forks;
	glb.d_mtx = d_mtx;
	glb.meals_mtx = meals_mtx;
	if (ft_parsing(&glb, av, ac) || \
		ft_create_threads(thrds, &glb))
		return (-1);
	while ((i < glb.ph_nb) && !ft_die(&(thrds[i])))
	{
		if ((ft_last_meal(&(thrds[i]), -1) + \
			glb.t_die) <= ft_get_time(thrds[i].glb->start))
		{
			ft_update_die(&(thrds[i]));
			break ;
		}
		(i++ && (i = (i % glb.ph_nb)));
	}
	return (0);
}

