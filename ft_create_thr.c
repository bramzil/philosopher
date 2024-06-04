/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/04 10:38:12 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

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
        glb->die[i] = 0;
        thrds[i].glb = glb;
        thrds[i].id = i + 1;
		if (pthread_create(&t, NULL, ft_routing, \
            (void *)(&(thrds[i]))))
		    return (printf("thread_creation failure!\n"), -1);
		if (pthread_detach(t))
			return (printf("thread_detach failure!\n"), -1);
        i++;
	}
	return (0);
}