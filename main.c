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
	par_t				par;

	par.ph_nb = 3;
	par.t_die	= 500;
	par.t_slp = 200;
	par.t_teat = 300;
	if (ft_create_threads(&par))
		return (-1);
	while (1)
		if (ft_die(0, 0))
			break ;
	ft_free_par(&par);
	return (0);
}