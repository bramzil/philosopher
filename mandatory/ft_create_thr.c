/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/08 16:41:29 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int ft_destroy_mtx(thr_t *thrds, int nbr, int flg)
{
    int         i;

    i = -1;
    if (!thrds)
        return (-1);
    while (++i < nbr)
	{
        if (((i + 1) != nbr) || (0 < flg))
		    pthread_mutex_destroy(&(thrds[i].meal_mtx));
        if (((i + 1) != nbr) || (1 < flg))
		    pthread_mutex_destroy(&(thrds[i].left_fork));
        if (((i + 1) != nbr) || (2 < flg))
		    pthread_mutex_destroy(&(thrds[i].meal_nbr_mtx));
	}
	pthread_mutex_destroy(&(thrds[0].glb->die_mtx));
	pthread_mutex_destroy(&(thrds[0].glb->prnt_mtx));
    return (0);
}

static int ft_initiate_data(thr_t **thrds, glb_t *glb)
{
    int         i;

    i = -1;
    glb->die = 0;
    *thrds = malloc(sizeof(thr_t) * glb->ph_nb);
    if (!(*thrds))
        return (write(2, "thrds array's malloc issue\n", 28), -1);
    while (++i < glb->ph_nb)
    {
        (*thrds)[i].meal = 0;
        (*thrds)[i].glb = glb;
        (*thrds)[i].id = i + 1;
        (*thrds)[i].meals_nbr = 0;
    }
    if (ft_intiate_mutexes(*thrds, glb->ph_nb))
        return (free(*thrds), -1);
    return (0);
}

int	ft_threads(thr_t **thrds, glb_t *glb)
{
    int             i;

    i = 0;
    if (!glb->meals_nbr)
        return (-1);
    glb->start = ft_get_time(0);
    if (ft_initiate_data(thrds, glb))
        return (-1);
    while (thrds && (i < glb->ph_nb))
	{
        (*thrds)[i].start = ft_get_time(0);
        if (pthread_create(&((*thrds)[i].thd), NULL, ft_routing, \
            (void *)(&((*thrds)[i]))))
		    return (write(2, "thread_creation failure!\n", 26), \
                free(*thrds), ft_die((*thrds)[i].glb, 1), -1);
        i++;
	}
	return (0);
}