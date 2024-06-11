/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_philos_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:42:41 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 19:20:11 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	ft_clean_up(ph_t *phls)
{
	int				i;

	i = -1;
	if (!phls)
		return (-1);
	while (++i  < phls[0].glb->ph_nb)
        kill(phls[i].pid, SIGTERM);
	ft_destroy_smphrs(phls, phls[0].glb->ph_nb, 2);
	free(phls);
	return (0);
}

static int ft_initiate_data(ph_t *phls, glb_t *glb)
{
    int         i;

    i = -1;
    while (++i < glb->ph_nb)
    {
        phls[i].meals_nbr = 0;
        phls[i].id = i + 1;
        phls[i].glb = glb;
        phls[i].meal = 0;
        phls[i].meal_sem_name = \
            ft_generate_name("meal_sem_", (i + 1));
        if (!phls[i].meal_sem_name)
            return (ft_free_names(phls, (i + 1), 0), -1);
        phls[i].meal_nbr_sem_name = \
            ft_generate_name("meal_nbr_sem_", (i + 1));
         if (!phls[i].meal_nbr_sem_name)
            return (ft_free_names(phls, (i + 1), 1), -1);
        phls[i].die_sem_name = \
            ft_generate_name("die_sem_", (i + 1));
         if (!phls[i].die_sem_name)
            return (ft_free_names(phls, (i + 1), 2), -1);
    }
    return (ft_initiate_semaphores(phls, glb));
}

int	ft_create_philos(ph_t **phls, glb_t *glb)
{
    int             i;

    i = 0;
    (*phls) = malloc(sizeof(ph_t) * glb->ph_nb);
    if (!(*phls))
        return (write(2, "phls malloc issue\n", 20), -1);
    if (ft_initiate_data((*phls), glb))
        return (free(*phls), -1);
    glb->start = ft_get_time(0);
    while ((*phls) && (i < glb->ph_nb))
	{
       (*phls)[i].pid = fork();
        if (((*phls)[i].pid == -1) && ft_die(&(*phls)[i], 1))
            return (write(2, "fork fails!\n", 13), -1);
       (*phls)[i].start = ft_get_time(0);
        if ((*phls)[i].pid == 0)
            ft_child_function(&(*phls)[i]);
        i++;
	}
	return (0);
}
