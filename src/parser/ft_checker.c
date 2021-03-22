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

char	*ft_open_close_tag(char *tag, int toggle)
{
	char *tmp;
	char *out;

	tmp = ft_strjoin((toggle) ? "</" : "<", tag);
	out = ft_strjoin(tmp, ">");
	free(tmp);
	return (out);
}

int		ft_in_tags(char **arr, char *target, int toggle)
{
	int		i;
	int		len;
	char	*tmp;

	i = -1;
	while (arr[++i])
	{
		tmp = ft_open_close_tag(arr[i], toggle);
		len = ft_strlen(tmp);
		if (ft_strnequ(tmp, target, len))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
	}
	return (-1);
}

int		ft_check_tag_level(int index, int level)
{
	if (index == 1 && level == 0)
		return (1);
	else if (index >= 2 && index <= 7 && level == 1)
		return (1);
	else if (index >= 8 && index <= 12 && level == 2)
		return (1);
	else if (index >= 13 && level == 3)
		return (1);
	return (0);
}

int		ft_checker_xmllint(char *data, t_env *env)
{
	if (!ft_xmllint_recusive(data, env, 0, 0))
		return (0);
	if (env->xml_check.x != 1 || env->xml_check.y != 1)
	{
		ft_show_err(TAG_PARSE_E);
		return (0);
	}
	return (1);
}

int		ft_parse_file(t_env *env)
{
	char	*data;
	char	*tmp;
	char	*line;
	int		fd;

	env->tags[0] = ft_strsplit(TAG_0_L, ';');
	env->tags[1] = ft_strsplit(TAG_1_L_1""TAG_1_L_2, ';');
	env->tags[2] = ft_strsplit(TAG_2_L_1""TAG_2_L_2""\
	TAG_2_L_3""TAG_2_L_4""TAG_2_L_5, ';');
	env->tags[3] = ft_strsplit(TAG_3_L, ';');
	if ((fd = open(env->filename, O_RDONLY)) < 0)
		return (ft_free_data(0, 0, FD_E));
	data = ft_strdup("");
	while (get_next_line(fd, &line) > 0)
	{
		tmp = data;
		data = ft_strjoin(data, line);
		free(line);
		free(tmp);
	}
	free(line);
	if (!ft_checker_xmllint(data, env))
		return (0);
	return (!!env->o_count);
}
