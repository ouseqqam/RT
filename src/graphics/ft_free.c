/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:55:43 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:55:44 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	ft_free_2d_table(char ***tab)
{
	char	**tmp;
	int		i;

	tmp = *tab;
	i = -1;
	while (tmp[++i])
		free(tmp[i]);
	free(tmp);
}

void	ft_free_tags(char ***tags)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (tags[i][++j])
			free(tags[i][j]);
		free(tags[i]);
	}
}

void	ft_show_err(char *error)
{
	ft_putstr_fd(C_RED, 2);
	ft_putstr_fd(error, 2);
	ft_putendl_fd(C_RESET, 2);
	ft_putstr_fd("\a", 2);
}

int		ft_free_data(char **data, int ret, char *error)
{
	if (data)
		ft_strdel(data);
	if (error)
	{
		ft_show_err(error);
	}
	return (ret);
}

void	ft_free_object_list(t_object_list **head)
{
	t_object_list	*tmp;
	t_object_list	*swap;

	tmp = *head;
	while (tmp)
	{
		swap = tmp->next;
		ft_strdel(&(tmp->obj.image));
		free(tmp);
		tmp = swap;
	}
}
