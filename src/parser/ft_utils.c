/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:36:31 by achatoua          #+#    #+#             */
/*   Updated: 2021/03/16 16:36:38 by achatoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

int		ft_strstr_index(const char *haystack, const char *needle)
{
	int	i;
	int	a;
	int	j;

	a = 0;
	if (!*needle)
		return (-1);
	while (haystack[a])
	{
		i = a;
		j = 0;
		while (haystack[i] && needle[j] && haystack[i] == needle[j])
		{
			i++;
			j++;
		}
		if (needle[j] == '\0')
			return (a);
		a++;
	}
	return (-1);
}

int		isnumb(char *str)
{
	int	i;
	int	lenght;

	i = 0;
	lenght = strlen(str);
	if (lenght > 1 && str[0] != '+' && str[0] != '-' && (str[i] < '0'
				|| str[i] > '9'))
		return (0);
	i++;
	while (i < lenght)
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else if (str[i] == '.')
			break ;
		else
			return (0);
	if (i < lenght && str[i] == '.')
		i++;
	while (i < lenght)
		if (str[i] >= '0' && str[i] <= '9')
			i++;
		else
			return (0);
	return (1);
}

void	ft_atod2(t_atod *at)
{
	if (at->abso[0][at->i] && at->abso[0][at->i] == '-')
	{
		at->i++;
		at->sign = -1;
	}
	else if (at->abso[0][at->i] && at->abso[0][at->i] == '+')
		at->i++;
	while (at->abso[0][at->i] && at->abso[0][at->i] >= '0'
			&& at->abso[0][at->i] <= '9')
	{
		at->act = 1;
		at->j = (at->j * 10) + (at->abso[0][at->i] - '0');
		at->i++;
	}
	if (at->abso[0][at->i] && at->abso[0][at->i] == '.' && at->act == 1)
	{
		at->i++;
		while (at->abso[0][at->i] && at->abso[0][at->i] >= '0'
				&& at->abso[0][at->i] <= '9')
		{
			at->f = (at->f * 10) + (at->abso[0][at->i] - '0');
			at->i++;
			at->len++;
		}
	}
}

double	ft_atod(char *str)
{
	t_atod atod;

	atod.f = 0;
	atod.act = 0;
	atod.len = 0;
	atod.s = 0;
	atod.abso = ft_split_whitespaces(str);
	atod.i = 0;
	atod.j = 0;
	atod.sign = 1;
	if (atod.abso[0])
	{
		ft_atod2(&atod);
		atod.len = atod.len * -1;
		atod.f = atod.f * pow(10, atod.len);
		atod.j = atod.f + atod.j;
		atod.j = atod.j * atod.sign;
	}
	ft_free_2d_table(&atod.abso);
	return (atod.j);
}

int		ft_tab_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
