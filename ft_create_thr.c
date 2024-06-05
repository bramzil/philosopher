/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/05 10:33:13 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"


static void ft_initiate_data(thr_t *thrds, glb_t *glb)
{
    int         i;

    i = -1;
    while (++i < glb->ph_nb)
    {
        thrds[i].die = 0;
        thrds[i].meal = 0;
        thrds[i].glb = glb;
        thrds[i].id = i + 1;
    }
}

int	ft_create_threads(thr_t **thrds, glb_t *glb)
{
    int             i;

    i = 0;
    *thrds = malloc(sizeof(thr_t) * glb->ph_nb);
    if (!(*thrds))
        return (write(2, "thrds array's allocation fails\n", 32), -1);
    if (ft_intiate_mutexes(*thrds, glb->ph_nb))
        return (-1);
    ft_initiate_data(*thrds, glb);
    glb->start = ft_get_time(0);
    while (thrds && (i < glb->ph_nb))
	{
        if (pthread_create(&((*thrds)[i].thd), NULL, ft_routing, \
            (void *)(&((*thrds)[i]))))
		    return (write(2, "thread_creation failure!\n", 26), -1);
        if (pthread_detach((*thrds)[i].thd))
            return (write(2, "thread_detach failure!\n", 26), -1);
        i++;
	}
	return (0);
}