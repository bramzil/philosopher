/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/06 19:04:48 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_clean_up(thr_t *thrds, int ph_nb)
{
	int				i;

	i = -1;
	if (!thrds)
		return (-1);
	while (++i  < ph_nb)
	{
		pthread_mutex_destroy(&(thrds[i].left_fork));
		pthread_mutex_destroy(&(thrds[i].meal_mtx));
		pthread_mutex_destroy(&(thrds[i].meal_nbr_mtx));
	}
	pthread_mutex_destroy(&(thrds[0].glb->prnt_mtx));
	free(thrds);
	return (0);
}

void f()
{
	system("leaks	a.out");
}

int main(int ac, char **av)
{
	int					i;
	glb_t				glb;
	int					fnsh; 
	thr_t				*thrds;

	i = 0;
	fnsh = 0;
	if (ft_parsing(&glb, av, ac) || ft_threads(&thrds, &glb))
		return (-1);
	while ((i < glb.ph_nb) && (fnsh < glb.ph_nb))
	{
		((i == 0) && (fnsh = 0));
		if ((ft_last_meal(&(thrds[i]), -1) + \
			glb.t_die) < ft_get_time((thrds[i].start)))
		{
			ft_putevent(&(thrds[i]), "died\n");
			break ;
		}
		((0 < glb.meals_nbr) && (ft_meals(&(thrds[i]), 0) == \
			glb.meals_nbr) && fnsh++);
		if (glb.ph_nb != 1)
			(i++ && (i = (i % glb.ph_nb)));
	}
	(usleep(1000), ft_clean_up(thrds, glb.ph_nb));
	return (0);
}

