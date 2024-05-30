/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/28 18:32:18 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int main()
{
	int					i;
	par_t				par;

	i = -1;
	par.ph_nb = 2;
	par.t_die	= 410;
	par.t_slp = 200;
	par.t_teat = 200;
	ft_get_time();
	if (ft_create_threads(&par))
		return (-1);
	while (++i <= par.ph_nb)
	{
		if ((ft_meal(&par, -1, i) + par.t_die) < ft_get_time())
		{
			ft_putevent("died\n", ft_get_time(), i);
			ft_die(i, 1);
			break ;
		}
		else if (i == par.ph_nb)
			i = -1;
	}
	ft_free_par(&par);
	return (0);
}