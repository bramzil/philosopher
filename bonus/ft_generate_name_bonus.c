/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generate_name_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bramzil <bramzil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:56:19 by bramzil           #+#    #+#             */
/*   Updated: 2024/06/09 12:12:09 by bramzil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

static int ft_char_nbr(char *s, unsigned int id)
{
    int           i;

    i = 0;
    while (s && s[i])
        i++;
    while (id && ++i)
        id = id / 10;
    return (i);
}

int	ft_free_names(thr_t *thrds, int last, int flg)
{
	int				i;

	i = -1;
	while (thrds && (++i < last))
	{
		if (((i + 1) != last) || (0 < flg))
			free(thrds[i].meal_sem_name);
		if (((i + 1) != last) || (1 <= flg))
			free(thrds[i].meal_nbr_sem_name);
		if (((i + 1) != last) || (2 <= flg))
			free(thrds[i].syn_sem_name);
	}
	return (0);
}

static char *ft_convert(unsigned int id)
{
    int         len;
    char        *str;

    str = NULL;
    len = ft_char_nbr(NULL, id);
    if (len)
    {
        str = malloc(sizeof(char) * (len + 1));
        if (!str)
            return (NULL);
        str[len] = '\0';
        while (0 <= --len)
        {
            str[len] = (id % 10) + 48;
            id = id / 10;
        }
    }
    return (str);
}

char *ft_generate_name(char *s1, int id)
{
    int             t[2];
    char            *s2;
    char            *str;

    t[0] = 0;
    t[1] = 0;
    s2 = ft_convert(id);
    if (!s1 || !s2)
        return (NULL);
    str = malloc(sizeof(char) * (ft_char_nbr(s1, 0) + \
        ft_char_nbr(s2, 0) + 1));
    if (!str)
        return (free(s2), NULL);
    while ((s1 && s1[t[0]]) || (s2 && s2[t[1]]))
    {
        if (s1 && s1[t[0]])
            (str[t[0]] = s1[t[0]], t[0]++);
        else if (s2 && s2[t[1]])
            (str[t[0] + t[1]] = s2[t[1]], t[1]++);
    }
    str[t[0] + t[1]] = '\0';
    return (free(s2), str);
}