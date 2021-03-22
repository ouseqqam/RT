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

int	ft_xmllint_recusive2(t_env *env, t_parse *pa)
{
	if (pa->level < 4 &&
			(pa->index = ft_in_tags(env->tags[pa->level],
			pa->data + pa->i, 0)) > -1)
	{
		pa->i += ft_strlen(env->tags[pa->level][pa->index]) + 2;
		pa->j = -1;
		while (pa->data[pa->i + ++pa->j])
			if (pa->index == ft_in_tags(env->tags[pa->level],
						pa->data + pa->i + pa->j, 1))
				break ;
			else if (!pa->data[pa->i + pa->j + 1])
				return (ft_free_data(&pa->data, 0, TAG_CLOSE_E));
		if (!ft_check_mandatory(env, pa))
			return (ft_free_data(&pa->data, 0, TAG_POS_E));
		if (!ft_xmllint_recusive(
					ft_strsub(pa->data, pa->i, pa->j), env, pa->level
					+ 1, pa->index))
			return (ft_free_data(&pa->data, 0, 0));
		pa->i += ft_strlen(env->tags[pa->level][pa->index]) + 2 + pa->j;
	}
	else if (pa->level < 4 && ((!ft_isprint(pa->data[pa->i]))
	&& (!ft_isdigit(pa->data[pa->i]))) &&
			!ft_strchr(".-", pa->data[pa->i]))
		return (ft_free_data(&pa->data, 0, TAG_DATA_E));
	return (1);
}

int	ft_xmllint_recusive(char *data, t_env *env,
		int level, int parent)
{
	t_parse parse;

	parse.data = data;
	parse.level = level;
	parse.parent = parent;
	parse.i = -1;
	while (++parse.i < TAGS_NUM)
		parse.man[parse.i] = -1;
	parse.i = -1;
	while (parse.data[++parse.i])
	{
		if (!ft_strchr(" \t\n", parse.data[parse.i]))
		{
			if (!ft_xmllint_recusive2(env, &parse))
				return (0);
		}
	}
	if (level == 2 && !ft_parse(data, env, parent))
		return (ft_free_data(&data, 0, TAG_PARSE_E));
	return (ft_free_data(&data, 1, 0));
}
