/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:31 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/05 11:40:26 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int	ft_is_number(char *arg)
{
	int			i;

	i = -1;
	if (!arg)
		return (-1);
	else if ((arg[0] == '-') || (arg[0] == '+'))
		i += 1;
	while (arg && arg[++i])
		if ((arg[i] < '0') || ('9' < arg[i]))
			return (-1);
	return (0);
}

static long	ft_atoi(char *arg)
{
	int				sig;
	long			rslt;

	sig = 1;
	rslt = 0;
	if (!arg)
		return (0);
	else if ((*arg == '-') || (*arg == '+'))
	{
		if (*arg == '-')
			sig = -1;
		arg++;
	}
	while (arg && *arg)
	{
		rslt = rslt * 10 + (*arg - 48);
		if (2147483647 < rslt)
			break ;
		arg++;
	}
	return (sig * rslt);
}

int	ft_parsing(glb_t *glb, char **av, int ac)
{
	int				i;
	long			vl;

	i = 0;
	glb->meals = -1;
	if ((ac < 5) || (6 < ac))
		return (write(2, "Error: Invalid number of arguments!!!!!\n", 37));
	while ((++i < ac) && av && av[i])
	{
		if (ft_is_number(av[i]))
			return (write(2, "Error: A non numerical argument!!!!\n", 34));
		vl = ft_atoi(av[i]);
		if ((vl < 0) || (INT_MAX < vl))
			return (write(2, "Error: A number out valid range!!!!\n", 34));
		if ((i == 1) && (200 < vl))
			return (write(2, "Error: Thrds nmbr is too bigger!!!!\n", 34));
		(((i == 1) && (glb->ph_nb = vl)), ((i == 2) && (glb->t_die = vl)));
		(((i == 3) && (glb->t_eat = vl)), ((i == 4) && (glb->t_slp = vl)));
		((i == 5) && (glb->meals = vl));
	}
	return (0);
}
