/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initiate_smphr_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:51:04 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/09 14:57:23 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	ft_sem_unlink(thr_t *thrds)
{
		int				i;

	i = -1;
	while (++i < thrds[0].glb->ph_nb)
	{
		sem_unlink(thrds[i].syn_sem_name);
		sem_unlink(thrds[i].meal_sem_name);
		sem_unlink(thrds[i].meal_nbr_sem_name);
	}
	sem_unlink("/syn_die_smphr");
	sem_unlink("/forks_smphr");
	sem_unlink("/prnt_smphr");
	sem_unlink("/die_smphr");
	return (0);
}

int	ft_destroy_smphr(thr_t *thrds, int nbr, int flg)
{
	int				i;

	i = -1;
	while (++i < nbr)
	{
		if (((i + 1) != nbr) || (0 < flg))
			(sem_close(thrds[i].meal_smphr), \
				sem_unlink(thrds[i].meal_sem_name));
		if (((i + 1) != nbr) || (1 <= flg))
			(sem_close(thrds[i].meal_nbr_smphr), \
				sem_unlink(thrds[i].meal_nbr_sem_name));
		if (((i + 1) != nbr) || (2 <= flg))
			(sem_close(thrds[i].syn_smphr), \
				sem_unlink(thrds[i].syn_sem_name));
	}
	(sem_close(thrds[0].glb->forks_smphr), \
		sem_unlink("/forks_smphr"));
	(sem_close(thrds[0].glb->prnt_smphr), \
		sem_unlink("/prnt_smphr"));
	(sem_close(thrds[0].glb->die_smphr), \
		sem_unlink("/die_smphr"));
	(sem_close(thrds[0].glb->syn_die_smphr), \
		sem_unlink("/syn_die_smphr"));
	return (ft_free_names(thrds, thrds[0].glb->ph_nb, flg));
}

static int  ft_initiate_thrds_smphrs(thr_t *thrds)
{
	int				i;

	i = -1;
	while (++i < thrds[0].glb->ph_nb)
	{
		thrds[i].meal_smphr = sem_open(thrds[i].meal_sem_name, \
			O_CREAT, 0666, 1);
		if ((thrds[i].meal_smphr == SEM_FAILED) && \
			!ft_destroy_smphr(thrds, (i + 1), 0))
			return (write(2, "issue in init of meal_smphr!\n", 29), -1);
		thrds[i].meal_nbr_smphr = sem_open(thrds[i].meal_nbr_sem_name, \
			O_CREAT, 0666, 1);
		if ((thrds[i].meal_nbr_smphr == SEM_FAILED) && \
			!ft_destroy_smphr(thrds, (i + 1), 1))
			return (write(2, "issue in init of meal_nbr_smphr!\n", 34), -1);
		thrds[i].syn_smphr = sem_open(thrds[i].syn_sem_name, \
			O_CREAT, 0666, 1);
		if ((thrds[i].syn_smphr == SEM_FAILED) && \
			!ft_destroy_smphr(thrds, (i + 1), 2))
			return (write(2, "issue in init of syn_smphr!\n", 34), -1);
	}
	return (0);
}

int ft_initiate_semaphores(thr_t *thrds, glb_t *glb)
{
	int				i;

	i = -1;
	ft_sem_unlink(thrds);
	glb->forks_smphr = sem_open("/forks_smphr", O_CREAT, 0666, \
		glb->ph_nb);
	if ((glb->forks_smphr == SEM_FAILED) && !ft_free_names(thrds, \
		glb->ph_nb, 2))
		return (write(2, "issue in initiate of forks_smphr!\n", 35), -1);
	glb->prnt_smphr = sem_open("/prnt_smphr", O_CREAT, 0666, 1);
	if ((glb->prnt_smphr == SEM_FAILED) && !ft_free_names(thrds, \
		glb->ph_nb, 2))
	{
		(sem_close(glb->forks_smphr), sem_unlink("/forks_smphr"));
		return (write(2, "issue in initiate of prnt_smphr!\n", 34), -1);
	}
	glb->die_smphr = sem_open("/die_smphr", O_CREAT, 0666, 1);
	if ((glb->die_smphr == SEM_FAILED) && !ft_free_names(thrds, \
		glb->ph_nb, 2))
	{
		(sem_close(glb->forks_smphr), sem_unlink("/forks_smphr"));
		(sem_close(glb->prnt_smphr), sem_unlink("/prnt_smphr"));
		return (write(2, "issue in initiate of die_smphr!\n", 34), -1);
	}
	glb->syn_die_smphr = sem_open("/syn_die_smphr", O_CREAT, 0666, 0);
	if ((glb->syn_die_smphr == SEM_FAILED) && !ft_free_names(thrds, \
		glb->ph_nb, 2))
	{
		(sem_close(glb->forks_smphr), sem_unlink("/forks_smphr"));
		(sem_close(glb->prnt_smphr), sem_unlink("/prnt_smphr"));
		(sem_close(glb->die_smphr), sem_unlink("/die_smphr"));
		return (write(2, "issue in initiate of die_smphr!\n", 34), -1);
	}
	return (ft_initiate_thrds_smphrs(thrds));
}
