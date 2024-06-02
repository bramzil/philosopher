/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:53:31 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/01 23:18:52 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static int  ft_is_number(char *arg)
{
    int         i;

    i = -1;
    if (!arg)
        return (-1);
    else if (arg[0] == '-')
        i += 1;
    while (arg && arg[++i])
        if ((arg[i] < '0') || ('9' < arg[i]))
            return (-1);
    return (0);
}

static long  ft_atoi(char *arg)
{
    int             sig;
    long            rslt;

    sig = 1;
    rslt = 0;
    if (!arg)
        return (0);
    else if ((*arg == '-') && arg++)
        sig = -1;
    while (arg && *arg)
    {
        rslt = rslt * 10 + (*arg - 48);
        if (2147483647 < rslt)
            break ;
        arg++;   
    }
    return (sig * rslt);
}

int ft_parsing(par_t *par, char **av, int ac)
{
    int             i;
    long            vl;

    i = 0;
    while ((++i < ac) && av && av[i])
    {
        if (ft_is_number(av[i]))
            return (printf("Error: %s invalid number!", av[i]));
        vl = ft_atoi(av[i]);
        if ((vl < 0) || (INT_MAX < vl))
            return (printf("Error: %s out valid range!", av[i]));
        ((i == 1) && (par->ph_nb = vl));
        ((i == 2) && (par->t_die = vl));
        ((i == 3) && (par->t_eat = vl));
        ((i == 4) && (par->t_slp = vl));
    }
    return (0);
}