/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/31 03:33:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main()
{
	int					i;
	par_t				par;

	i = -1;
	par.ph_nb = 4;
	par.t_die = 410;
	par.t_slp = 200;
	par.t_eat = 200;
	ft_get_time();
	if (ft_create_threads(&par))
		return (-1);
	while (++i < par.ph_nb)
	{
		if ((ft_last_meal(&par, -1, i) + par.t_die) < ft_get_time())
		{
			printf("%-15ld %-10d died\n", ft_get_time(), i);
			printf("thread: %d last meal: %ld\n", i, ft_last_meal(&par, -1, i));
			ft_die(i, 1);
			
			break ;
		}
		else if ((i + 1) == par.ph_nb)
			i = -1;
	}
	ft_free_par(&par);
	return (0);
}