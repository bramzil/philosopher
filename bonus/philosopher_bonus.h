/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:22 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/11 18:00:22 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_BONUS_H
# define PHILOSOPHER_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <signal.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdatomic.h>

//******************************* shared data *********************************//

typedef struct 		glb_s
{
	int				ph_nb;
	long			t_die;
	long			t_eat;
	long			t_slp;
	long			start;
	int				meals_nbr;
	sem_t			*msg_smphr;
	sem_t			*prnt_smphr;
	sem_t			*forks_smphr;
	sem_t			*syn_die_smphr;
}					glb_t;

//******************************** thread struct ******************************//

typedef struct 		ph_s
{
	int				id;
	pid_t			pid;
	pthread_t		thd;
	glb_t			*glb;
	long			meal;
	long			start;
	int				meals_nbr;
	sem_t			*die_smphr;
	sem_t			*meal_smphr;
	sem_t			*meal_nbr_smphr;
	char			*die_sem_name;
	char			*meal_sem_name;
	char			*meal_nbr_sem_name;
}					ph_t;

//**************************** function prototypes ****************************//

int 	ft_destroy_smphrs(ph_t *phls, int nbr, int flg);
int 	ft_initiate_semaphores(ph_t *phls, glb_t *glb);
int		ft_free_names(ph_t *phls, int last, int flg);
int		ft_create_philos(ph_t **phls, glb_t *glb);
int		ft_parsing(glb_t *glb, char **av, int ac);
long	ft_last_meal(ph_t *phl, long value);
int		ft_putevent(ph_t *phl, char *des);
char 	*ft_generate_name(char *s1, int id);
int		ft_meals(ph_t *phl, int incr);
void	ft_usleep(ph_t *phl, long vl);
int 	ft_child_function(ph_t *phl);
int 	ft_unlock_smphr(ph_t *phl);
int		ft_die(ph_t *phl, int set);
int 	ft_lock_smphr(ph_t *phl);
int		ft_sleeping(ph_t  *phl);
int		ft_thinking(ph_t  *phl);
int		ft_clean_up(ph_t *phls);
int		ft_eating(ph_t *phl);
long	ft_get_time(long time);

#endif