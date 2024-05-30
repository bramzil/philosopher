/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 22:43:22 by bramzil           #+#    #+#             */
/*   Updated: 2024/05/28 15:55:25 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <pthread.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdio.h>

//******************************** priority ***********************************//

typedef struct      priority_s
{
    
}                   priority_t;


//****************************** define main struct ***************************//

typedef struct		par_s
{
	int				ph_nb;
	long			t_die;
	long			t_slp;
	long			t_teat;
	pthread_mutex_t	*forks;
}                   par_t;

//**************************** function prototypes ****************************//

int 	ft_unlock_mutex(par_t *par, int ph_nb, int id);
int 	ft_lock_mutex(par_t *par, int ph_nb, int id);
int 	ft_sleeping(par_t *par, long *ref, int id);
int		ft_putevent(char *msg, long stmp, int id);
int		ft_eating(par_t *par, long *ref, int id);
int		ft_create_threads(par_t *par);
int		ft_puterr(char *msg, int id);
int 	ft_intiate_forks(par_t *par);
void	 ft_free_par(par_t *par);
int		ft_die(int id, int set);
void 	*ft_routing(void *par);
long	ft_get_time();

#endif