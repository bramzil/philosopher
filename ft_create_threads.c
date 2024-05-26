/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/27 20:45:59 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static void ft_intiate_par(par_t *par)
{
    par->die = NULL;
    par->forks = NULL;
    par->id_mtx = NULL;
    par->die_mtx = NULL;
    par->prnt_mtx = NULL;
}

int	ft_create_threads(par_t *par)
{
    int         i;
    pthread_t   t;

    i = -1;
    ft_intiate_par(par);
    par->die = (int *)malloc(sizeof(int));
    if (!par->die)
        return (printf("die alloc failure!\n"), -1);
    *(par->die) = 0;
    if (ft_intiate_mutex(par))
        return (-1);
    while (++i < par->ph_nb)
	{
        pthread_mutex_lock(par->id_mtx);
		par->id = i;
        pthread_mutex_unlock(par->id_mtx);
		if (pthread_create(&t, NULL, ft_routing, (void *)par))
		    return (printf("thread_creation failure!\n"), -1);
		if (pthread_detach(t))
			return (printf("thread_detach failure!\n"), -1);
        usleep(100);
	}
	return (0);
}