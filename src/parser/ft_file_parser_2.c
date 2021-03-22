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

int		ft_parse_close2(t_vec *pos,
		int counter, char *color_tag, int e)
{
	int	ret;

	ret = 0;
	counter = ft_strstr_index(color_tag, "</x>");
	if (counter == -1 || (e = ft_strstr_index(color_tag, "<x>")) == -1)
		return (0);
	pos->x = ft_get_value(color_tag, e, counter, &ret);
	counter = ft_strstr_index(color_tag, "</y>");
	if (counter == -1 || (e = ft_strstr_index(color_tag, "<y>")) == -1)
		return (0);
	pos->y = ft_get_value(color_tag, e, counter, &ret);
	counter = ft_strstr_index(color_tag, "</z>");
	if (counter == -1 || (e = ft_strstr_index(color_tag, "<z>")) == -1)
		return (0);
	pos->z = ft_get_value(color_tag, e, counter, &ret);
	return (!ret);
}

int		ft_parse_close(char *coor, char *open, char *close, t_vec *pos)
{
	int		e;
	int		i;
	int		counter;
	char	color_tag[ft_strlen(coor) + 1];

	i = -1;
	ft_bzero(color_tag, ft_strlen(coor));
	if ((e = ft_strstr_index(coor, open)) == -1 ||
			(counter = ft_strstr_index(coor, close)) == -1)
		return (0);
	while (e++ <= counter)
		color_tag[++i] = coor[e];
	if (e == counter || e <= 0)
		return (0);
	return (ft_parse_close2(pos, counter, color_tag, e));
}

int		ft_color2(t_vec *color,
		int counter, char *color_tag, int e)
{
	int	ret;

	ret = 0;
	counter = ft_strstr_index(color_tag, "</r>");
	if (counter == -1 || (e = ft_strstr_index(color_tag, "<r>")) == -1)
		return (0);
	color->x = ft_get_value(color_tag, e, counter, &ret);
	counter = ft_strstr_index(color_tag, "</g>");
	if (counter == -1 || (e = ft_strstr_index(color_tag, "<g>")) == -1)
		return (0);
	color->y = ft_get_value(color_tag, e, counter, &ret);
	counter = ft_strstr_index(color_tag, "</b>");
	if (counter == -1 || (e = ft_strstr_index(color_tag, "<b>")) == -1)
		return (0);
	color->z = ft_get_value(color_tag, e, counter, &ret);
	return (!ret);
}

int		ft_color(char *coor, t_vec *color, char *open, char *close)
{
	int		e;
	int		i;
	int		counter;
	char	color_tag[ft_strlen(coor)];

	i = -1;
	ft_bzero(color_tag, ft_strlen(coor));
	if ((e = ft_strstr_index(coor, open)) == -1 ||
			(counter = ft_strstr_index(coor, close)) == -1)
		return (0);
	while (e++ <= counter)
		color_tag[++i] = coor[e];
	if (e == counter || e <= 0)
		return (0);
	return (ft_color2(color, counter, color_tag, e));
}
