/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:22 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/06 11:24:00 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <sys/time.h>

//******************************* shared data *********************************//

typedef struct 		glb_s
{
	int				ph_nb;
	long			t_die;
	long			t_eat;
	long			t_slp;
	long			start;
	int				meals_nbr;
	pthread_mutex_t	prnt_mtx;
}					glb_t;

//******************************** thread struct ******************************//

typedef struct 		thr_s
{
	int				id;
	pthread_t		thd;
	glb_t			*glb;
	long			meal;
	long			start;
	int				meals_nbr;
	pthread_mutex_t	meal_mtx;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	meal_nbr_mtx;
}					thr_t;

//**************************** function prototypes ****************************//

int 	ft_intiate_mutexes(thr_t *thrds, int ph_nb);
int		ft_parsing(glb_t *glb, char **av, int ac);
long	ft_last_meal(thr_t *thrd, long value);
int		ft_threads(thr_t **thrds, glb_t *glb);
int		ft_putevent(thr_t *thrd, char *des);
int		ft_meals(thr_t *thrd, int incr);
int 	ft_unlock_mutex(thr_t *thrd);
int 	ft_lock_mutex(thr_t *thrd);
int		ft_sleeping(thr_t  *thrd);
int		ft_thinking(thr_t  *thrd);
int		ft_eating(thr_t *thrd);
long	ft_get_time(long time);
void 	*ft_routing(void *par);
void	ft_usleep(long vl);

#endif