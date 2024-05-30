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

long	ft_get_time()
{
	long			tmp;
	struct timeval	stmp;

	gettimeofday(&stmp, NULL);
	tmp = ((stmp.tv_sec * 1000) + (stmp.tv_usec / 1000));
	return (tmp);
}

static int	ft_get_id(void)
{
	static int				id;
	int						tmp;

	tmp = id;
	id += 1;
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
	stmp_ref = ft_get_time();
	while (!ft_die(id, 0))
	{
		if (ft_die(id, 0) || ft_putevent("thinking\n", \
			ft_get_time(), id))
			break ;
		if (ft_die(id, 0) || ft_eating(par, &stmp_ref, id))
			break ;
		if (ft_die(id, 0) || ft_sleeping(par, &stmp_ref, id))
			break ;
	}
	ft_die(id, 1);
	return (0);
}