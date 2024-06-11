/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:10 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 19:06:27 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

void f()
{
	system("leaks	philo_bonus");
}

static void	*ft_catch_msg(void *glb)
{
	int			i;
	glb_t		*l_glb;

	i = 0;
	l_glb = (glb_t*)glb;
	while (i < (l_glb->ph_nb * l_glb->meals_nbr))
	{
		sem_wait(l_glb->msg_smphr);
		i++;
	}
	sem_post(l_glb->syn_die_smphr);
	return (0);
}

static int ft_are_finished(glb_t *glb)
{
	int					i;
	pthread_t			th;

	i = -1;
	if (0 < glb->meals_nbr)
	{
		if (pthread_create(&th, NULL, ft_catch_msg, \
			(void*)glb) || pthread_detach(th))
			return (write(2, "pthread_create fails\n", 22), -1);
	}
	return (0);
}


int main(int ac, char **av)
{
	int					i;
	glb_t				glb;
	ph_t				*phls;

	i = -1;
	// atexit(f);
	if (ft_parsing(&glb, av, ac))
		return (0);
	if (ft_create_philos(&phls, &glb))
		return (0);
	ft_are_finished(&glb);
	sem_wait(glb.syn_die_smphr);
	while (++i  < phls[0].glb->ph_nb)
        kill(phls[i].pid, SIGTERM);
	ft_destroy_smphrs (phls, phls[0].glb->ph_nb, 2);
	free(phls);
	return (0);
}

