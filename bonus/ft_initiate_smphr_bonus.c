/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initiate_smphr_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 10:51:04 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 17:56:33 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int	ft_open_smphr(sem_t *ptr, char *name, int vl)
{
	ptr = sem_open(name, O_CREAT, 0666, vl);
	if (ptr == SEM_FAILED)
		return (-1);
	return (0);
}

static int	ft_smphr_unlink(ph_t *phls)
{
	int				i;

	i = -1;
	if (!phls)
		return (-1);
	while (phls && (++i < phls[0].glb->ph_nb))
	{
		sem_unlink(phls[i].die_sem_name);
		sem_unlink(phls[i].meal_sem_name);
		sem_unlink(phls[i].meal_nbr_sem_name);
	}
	(sem_unlink("/msg_smphr"), sem_unlink("/prnt_smphr"));
	(sem_unlink("/forks_smphr"), sem_unlink("/syn_die_smphr"));
	return (0);
}

static int ft_dstry_glb_smphr(glb_t *glb, int flg)
{
	(0 < flg) && (sem_close(glb->msg_smphr), \
		sem_unlink("/msg_smphr"));
	(1 < flg) && (sem_close(glb->prnt_smphr), \
		sem_unlink("/prnt_smphr"));
	(2 < flg) && (sem_close(glb->forks_smphr), \
		sem_unlink("/forks_smphr"));
	(3 < flg) && (sem_close(glb->syn_die_smphr), \
		sem_unlink("/syn_die_smphr"));
	return (0);
}

int	ft_destroy_smphrs(ph_t *phls, int nbr, int flg)
{
	int				i;

	i = -1;
	if (!phls)
		return (1);
	while (++i < nbr)
	{
		if (((i + 1) != nbr) || (0 < flg))
			(sem_close(phls[i].die_smphr), \
				sem_unlink(phls[i].die_sem_name));
		if (((i + 1) != nbr) || (1 < flg))
			(sem_close(phls[i].meal_smphr), \
				sem_unlink(phls[i].meal_sem_name));
		if (((i + 1) != nbr) || (2 <= flg))
			(sem_close(phls[i].meal_nbr_smphr), \
				sem_unlink(phls[i].meal_nbr_sem_name));
	}
	ft_dstry_glb_smphr(phls[0].glb, 5);
	return (ft_free_names(phls, phls[0].glb->ph_nb, flg));
}

static int  ft_initiate_phls_smphrs(ph_t *phls)
{
	int				i;

	i = -1;
	while (++i < phls[0].glb->ph_nb)
	{
		if (ft_open_smphr(phls[i].die_smphr, \
			phls[i].die_sem_name, 1) && \
				!ft_destroy_smphrs(phls, (i + 1), 0))
			return (write(2, "issue in init phl_smphr!\n", 27), -1);
		if (ft_open_smphr(phls[i].meal_smphr, \
			phls[i].meal_sem_name, 1) && \
				!ft_destroy_smphrs(phls, (i + 1), 1))
			return (write(2, "issue in init phl_smphr!\n", 27), -1);
		if (ft_open_smphr(phls[i].meal_nbr_smphr, \
			phls[i].meal_nbr_sem_name, 1) && \
				!ft_destroy_smphrs(phls, (i + 1), 2))
			return (write(2, "issue in init phl_smphr!\n", 27), -1);
	}
	return (0);
}


int ft_initiate_semaphores(ph_t *phls, glb_t *glb)
{
	ft_smphr_unlink(phls);
	if (ft_open_smphr(glb->msg_smphr, "/msg_smphr", 0))
		return (write(2, "issue in initiate of msg_smphr!\n", 33), -1);
	if (ft_open_smphr(glb->prnt_smphr, "/prnt_smphr", 1) && \
		!ft_dstry_glb_smphr(glb, 1))
		return (write(2, "issue in initiate of prnt_smphr!\n", 34), -1);
	if (ft_open_smphr(glb->forks_smphr, "/forks_smphr", glb->ph_nb) && \
		!ft_dstry_glb_smphr(glb, 2))
		return (write(2, "issue in initiate of forks_smphr!\n", 35), -1);
	if (ft_open_smphr(glb->syn_die_smphr, "/syn_die_smphr", 0)  && \
		!ft_dstry_glb_smphr(glb, 3))
		return (write(2, "issue in initiate of syn_die_smphr!\n", 37), -1);
	return (ft_initiate_phls_smphrs(phls));
}
