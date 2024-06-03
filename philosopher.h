/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:22 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/03 03:23:20 by bramzil          ###   ########.fr       */
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
	int				ph_nb;
	int				t_die;
	int				t_slp;
	int				t_eat;
	long			start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*d_mtx;
	pthread_mutex_t	*meals_mtx;
}					glb_t;


//******************************** thread struct ******************************//

typedef struct 		thr_s
{
	int				id;
	int				die;
	glb_t			*glb;
}					thr_t;

//**************************** function prototypes ****************************//

int		ft_create_threads(thr_t *thrds, glb_t *glb);
int		ft_parsing(glb_t *glb, char **av, int ac);
long	ft_last_meal(thr_t *thrd, long value);
int		ft_putevent(thr_t *thrd, char *des);
int 	ft_intiate_mutexes(glb_t *glb);
int 	ft_unlock_mutex(thr_t *thrd);
int		ft_update_die(thr_t *thrd);
int 	ft_lock_mutex(thr_t *thrd);
int 	ft_sleeping(thr_t *thrd);
long	ft_get_time(long time);
void 	*ft_routing(void *par);
int		ft_eating(thr_t *thrd);
int		ft_die(thr_t *thrd);
void	ft_usleep(long vl);

#endif