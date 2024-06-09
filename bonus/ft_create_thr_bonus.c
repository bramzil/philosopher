/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_thr_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/09 15:24:34 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	ft_clean_up(thr_t *thrds)
{
	int				i;

	i = -1;
	if (!thrds)
		return (-1);
    printf("hello before\n");
	while (++i  < thrds[0].glb->ph_nb)
		pthread_join(thrds[i].thd, NULL);
	ft_destroy_smphr(thrds, thrds[0].glb->ph_nb, 2);
	free(thrds);
	return (0);
}

static int ft_initiate_data(thr_t *thrds, glb_t *glb)
{
    int         i;

    i = -1;
    glb->die = 0;
    while (++i < glb->ph_nb)
    {
        thrds[i].meals_nbr = 0;
        thrds[i].id = i + 1;
        thrds[i].glb = glb;
        thrds[i].meal = 0;
        thrds[i].meal_sem_name = \
            ft_generate_name("meal_sem_", (i + 1));
        if (!thrds[i].meal_sem_name)
            return (ft_free_names(thrds, (i + 1), 0), -1);
        thrds[i].meal_nbr_sem_name = \
            ft_generate_name("meal_nbr_sem_", (i + 1));
         if (!thrds[i].meal_nbr_sem_name)
            return (ft_free_names(thrds, (i + 1), 1), -1);
        thrds[i].syn_sem_name = \
            ft_generate_name("syn_sem_", (i + 1));
         if (!thrds[i].syn_sem_name)
            return (ft_free_names(thrds, (i + 1), 2), -1);
    }
    return (ft_initiate_semaphores(thrds, glb));
}

int	ft_threads(thr_t **thrds, glb_t *glb)
{
    int             i;

    i = 0;
    (*thrds) = malloc(sizeof(thr_t) * glb->ph_nb);
    if (!(*thrds))
        return (write(2, "thrds malloc issue\n", 20), -1);
    if (ft_initiate_data(*thrds, glb))
        return (free(*thrds), -1);
    glb->start = ft_get_time(0);
    while (thrds && (i < glb->ph_nb))
	{
        (*thrds)[i].start = ft_get_time(0);
        if (pthread_create(&((*thrds)[i].thd), NULL, ft_routing, \
            (void *)(&((*thrds)[i]))))
        {
            ft_die((*thrds)[i].glb, 1);
            ft_clean_up(*thrds);
		    return (write(2, "thread_creation fails!\n", 24), -1);
        }
        i++;
	}
	return (0);
}
