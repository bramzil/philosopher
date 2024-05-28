/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/28 16:09:10 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void	ft_subroutine(par_t *par, int id)
{
	int					i;
	struct timeval		stmp;
	long				stmp_ref;
	
	i = -1;
	gettimeofday(&stmp, NULL);
	stmp_ref = (stmp.tv_sec);
	while (!ft_die(id, 0) && ++i < 3)
	{
		gettimeofday(&stmp, NULL);
		if (ft_die(id, 0) || ft_putevent("thinking\n", \
			(stmp.tv_sec), id))
			break ;
		if (ft_die(id, 0) || ft_eating(par, &stmp_ref, id))
			break ;
		if (ft_die(id, 0) || ft_sleeping(par, &stmp_ref, id))
			break ;
	}
}

void *ft_routing(void *par)
{
	int				id;
	par_t			*loc_par;

	loc_par = ((par_t*)par);
	pthread_mutex_lock(loc_par->id_mtx);
	id = loc_par->id;
    pthread_mutex_unlock(loc_par->id_mtx);
	ft_subroutine(loc_par, id);
	ft_die(id, 1);
	return (0);
}