/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:00 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/27 21:04:54 by bramzil          ###   ########.fr       */
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
	stmp_ref = (stmp.tv_usec / 1000);
	while (!ft_die(par, id, 0) && ++i < 3)
	{
		gettimeofday(&stmp, NULL);
		if (ft_putevent(par, "thinking\n", (stmp.tv_usec / 1000), id))
			break ;
		if (ft_die(par, id, 0) || ft_eating(par, &stmp_ref, id))
			break ;
		if (ft_die(par, id, 0) || ft_sleeping(par, &stmp_ref, id))
			break ;
	}
	ft_die(par, id, 1);
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
	return (0);
}