/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:22 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/02 20:18:11 by bramzil          ###   ########.fr       */
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

//******************************** thread struct ******************************//

typedef struct 		thr_s
{
	int				id;
	int				t_slp;
	int				t_eat;
	int				ph_nb;
	long			start;
	pthread_mutex_t	*meal_mtx;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}					thr_t;

//****************************** define main struct ***************************//

typedef struct		par_s
{
	int				ph_nb;
	int				t_die;
	int				t_slp;
	int				t_eat;
	thr_t			*thrds;
	pthread_mutex_t	*meals;
	pthread_mutex_t	*forks;
}                   par_t;

//**************************** function prototypes ****************************//

int		ft_parsing(par_t *par, char **av, int ac);
long	ft_last_meal(thr_t *thrd, long value);
int 	ft_intiate_mutexes(par_t *par);
int		ft_putevent(thr_t *thrd, char *des, int id);
int		ft_create_threads(par_t *par);
int 	ft_unlock_mutex(thr_t *thrd);
int 	ft_lock_mutex(thr_t *thrd);
int 	ft_sleeping(thr_t *thrd);
int		ft_die(int set, int id);
void 	*ft_routing(void *par);
int		ft_eating(thr_t *thrd);
void	ft_usleep(long vl);
long	ft_get_time(long time);

#endif