/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 12:05:53 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

static thr_t   *ft_create_arr(par_t *par)
{
    int         i;
    thr_t       *arr;

    i = -1;
    arr = (thr_t *)malloc(sizeof(thr_t) * par->ph_nb);
    if (!arr)
        return (NULL);
    while (++i < par->ph_nb)
    {
        arr[i].id = i + 1;
        arr[i].ph_nb = par->ph_nb;
        arr[i].t_eat = par->t_eat;
        arr[i].t_slp = par->t_slp;
        arr[i].meal_mtx = &(par->meals[i]);
        if ((i + 2) % 2)
        {
            arr[i].left_fork = &(par->forks[i]);
            arr[i].right_fork = &(par->forks[(i + 1) % par->ph_nb]);
        }
        else
        {
            arr[i].left_fork = &(par->forks[(i + 1) % par->ph_nb]);
            arr[i].right_fork = &(par->forks[i]);
        } 
    }
    return (arr);
}

int	ft_create_threads(par_t *par)
{
    int             i;
    pthread_t       t;

    i = -1;
    if (ft_intiate_mutexes(par))
        return (-1);
    par->thrds= ft_create_arr(par);
    while (par->thrds && (++i < par->ph_nb))
	{
		if (pthread_create(&t, NULL, ft_routing, (void *)(&(par->thrds[i]))))
		    return (printf("thread_creation failure!\n"), -1);
		if (pthread_detach(t))
			return (printf("thread_detach failure!\n"), -1);
	}
	return (0);
}