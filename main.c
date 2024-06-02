/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 20:24:13 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_die(int set, int id)
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
	par_t				par;
	pthread_mutex_t		forks[PH_NB];
	pthread_mutex_t		meals_mtx[PH_NB];

	i = -1;
	par.forks = forks;
	par.meals = meals_mtx;

	if (ft_parsing(&par, av, ac) || \
		ft_create_threads(&par))
		return (-1);
	while ((++i < par.ph_nb))
	{
		if ((ft_last_meal(&(par.thrds[i]), -1) + \
			par.t_die) <= ft_get_time(par.thrds[i].start))
		{
			ft_die(1, (i + 1));
			printf("%-15ld %-10d died\n", \
				ft_get_time(par.thrds[i].start), (i + 1));
			break ;
		}
		else if ((i + 1) == par.ph_nb)
			i = -1;
	}
	return (0);
}

