/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/03 04:36:52 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

// static void ft_spread_forks(par_t *par, thr_t *arr, int i)
// {
//     arr[i].left_fork = &(par->forks[i]);
//     arr[i].right_fork = &(par->forks[(i + 1) % par->ph_nb]);
// }

// static thr_t   *ft_create_arr(thr_t *thrds, glb_t *glb)
// {
//     int         i;

//     i = -1;
//     glb->start = ft_get_time(0);
//     while (++i < glb->ph_nb)
//     {
//        thrds[i].glb = glb;
//     }
//     return (arr);
// }

int	ft_create_threads(thr_t *thrds, glb_t *glb)
{
    int             i;
    pthread_t       t;

    i = 0;
    glb->start = ft_get_time(0);
    if (ft_intiate_mutexes(glb))
        return (-1);
    while (thrds && (i < glb->ph_nb))
	{
        thrds[i].die = 0;
        thrds[i].glb = glb;
        thrds[i].id = i + 1;
        if (ft_last_meal(&(thrds[i]), (glb->start + 60)) < 0)
		    return (ft_update_die(&(thrds[i])));
		if (pthread_create(&t, NULL, ft_routing, \
            (void *)(&(thrds[i]))))
		    return (printf("thread_creation failure!\n"), -1);
		if (pthread_detach(t))
			return (printf("thread_detach failure!\n"), -1);
        usleep(30);
        i++;
	}
	return (0);
}