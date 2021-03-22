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

int		check_close_tag(char *str, char *orig)
{
	char	*end;
	int		i;
	int		e;

	end = (char *)malloc(sizeof(char) * ft_strlen(orig));
	i = 0;
	e = 0;
	while (orig[i])
	{
		if (i == 1)
		{
			end[e] = '/';
			e++;
		}
		end[e] = orig[i];
		e++;
		i++;
	}
	if (!ft_strcmp(end, str))
		return (1);
	return (0);
}

double	ft_get_value(char *str, int e, int i, int *ret)
{
	double	y;
	char	*num;

	y = 0;
	while (str[e] && str[e - 1] != '>')
		e++;
	num = ft_strsub(str, e, i - e);
	if (ft_strlen(num) > 0)
	{
		if (!isnumb(num))
			*ret |= 1;
		y = ft_atod(num);
		free(num);
		return (y);
	}
	free(num);
	return (0);
}

int		ft_parse_value(char *data, char *start, char *close, double *val)
{
	int ret;
	int flag;

	flag = 0;
	if ((ret = ft_strstr_index(data, start)) == -1)
		return (0);
	*val = ft_get_value(data, ret, ft_strstr_index(data, close), &flag);
	return (!flag);
}

char	*ft_get_string(char *str, int e, int i)
{
	char	*path;

	while (str[e] && str[e - 1] != '>')
		e++;
	path = ft_strsub(str, e, i - e);
	if (ft_strlen(path) > 0)
		return (path);
	free(path);
	return (NULL);
}
