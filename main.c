/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/05 10:40:39 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
	free(thrds);
	return (0);
}

