/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:22 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/05 10:42:22 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>
# define PH_NB 200

//******************************* shared data *********************************//

typedef struct 		glb_s
{
	int				*die;
	int				ph_nb;
	long			t_die;
	long			t_eat;
	long			t_slp;
	long			meals;
	long			start;
}					glb_t;

//******************************** thread struct ******************************//

typedef struct 		thr_s
{
	int				id;
	int				die;
	pthread_t		thd;
	glb_t			*glb;
	long			meal;
	pthread_mutex_t	meal_mtx;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
}					thr_t;

//**************************** function prototypes ****************************//

int		ft_create_threads(thr_t **thrds, glb_t *glb);
int 	ft_intiate_mutexes(thr_t *thrds, int ph_nb);
int		ft_parsing(glb_t *glb, char **av, int ac);
long	ft_last_meal(thr_t *thrd, long value);
int		ft_putevent(thr_t *thrd, char *des);
int 	ft_unlock_mutex(thr_t *thrd);
int 	ft_lock_mutex(thr_t *thrd);
long	ft_get_time(long time);
void 	*ft_routing(void *par);
int		ft_cycle(thr_t *thrd);
void	ft_usleep(long vl);
int		ft_wait(int set);
int		ft_die(int set);

#endif