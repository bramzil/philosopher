/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/28 16:28:27 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"

int	ft_create_threads(par_t *par)
{
    int             i;
    pthread_t       t;

    i = -1;
    par->forks = NULL;
    par->meals = (long *)malloc(sizeof(long) * par->ph_nb);
    if (!par->meals || ft_intiate_forks(par))
        return (-1);
    while (++i < par->ph_nb)
	{
		if (pthread_create(&t, NULL, ft_routing, (void *)par))
		    return (printf("thread_creation failure!\n"), -1);
		if (pthread_detach(t))
			return (printf("thread_detach failure!\n"), -1);
        usleep(1000);
	}
	return (0);
}