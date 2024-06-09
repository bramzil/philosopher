/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_bonus.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:22 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/09 14:52:31 by bramzil          ###   ########.fr       */
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

//******************************* shared data *********************************//

typedef struct 		glb_s
{
	int				die;
	int				ph_nb;
	long			t_die;
	long			t_eat;
	long			t_slp;
	long			start;
	int				meals_nbr;
	sem_t			*die_smphr;
	sem_t			*prnt_smphr;
	sem_t			*forks_smphr;
	sem_t			*syn_die_smphr;
}					glb_t;

//******************************** thread struct ******************************//

typedef struct 		thr_s
{
	int				id;
	pid_t			pid;
	pthread_t		thd;
	glb_t			*glb;
	long			meal;
	long			start;
	int				meals_nbr;
	sem_t			*syn_smphr;
	sem_t			*meal_smphr;
	sem_t			*meal_nbr_smphr;
	char			*syn_sem_name;
	char			*meal_sem_name;
	char			*meal_nbr_sem_name;
}					thr_t;

//**************************** function prototypes ****************************//

int 	ft_initiate_semaphores(thr_t *thrds, glb_t *glb);
int 	ft_destroy_smphr(thr_t *thrds, int nbr, int flg);
int		ft_free_names(thr_t *thrds, int last, int flg);
int		ft_parsing(glb_t *glb, char **av, int ac);
long	ft_last_meal(thr_t *thrd, long value);
int		ft_threads(thr_t **thrds, glb_t *glb);
int		ft_putevent(thr_t *thrd, char *des);
char 	*ft_generate_name(char *s1, int id);
int		ft_meals(thr_t *thrd, int incr);
void	ft_usleep(glb_t *glb, long vl);
int 	ft_unlock_smphr(thr_t *thrd);
int		ft_die(glb_t *glb, int set);
int 	ft_lock_smphr(thr_t *thrd);
int		ft_sleeping(thr_t  *thrd);
int		ft_thinking(thr_t  *thrd);
int		ft_clean_up(thr_t *thrds);
int		ft_eating(thr_t *thrd);
long	ft_get_time(long time);
void 	*ft_routing(void *par);

#endif