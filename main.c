/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/04 23:04:42 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_die(int set)
{
	int						tmp;
	static int				die;
	static pthread_mutex_t	mtx = PTHREAD_MUTEX_INITIALIZER;
	
	if (pthread_mutex_lock(&mtx))
		return (printf("fials to lock die mtx\n"));
	if (set)
		die = 1;
	tmp = die;
	if (pthread_mutex_unlock(&mtx))
		return (printf("fials to unlock die mtx\n"));
	return (tmp);
}

int main(int ac, char **av)
{
	int					i;
	glb_t				glb;
	thr_t				*thrds;

	i = 0;
	if (ft_parsing(&glb, av, ac) || \
		ft_create_threads(&thrds, &glb))
		return (-1);
	while ((i < glb.ph_nb) && !ft_die(0))
	{
		if ((ft_last_meal(&(thrds[i]), -1) + \
			glb.t_die) <= ft_get_time(thrds[i].glb->start))
		{
			ft_putevent(&(thrds[i]), "died\n");
			ft_die(0);
			break ;
		}
		(i++ && (i = (i % glb.ph_nb)));
	}
	return (0);
}

