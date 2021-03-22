/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_checker.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achatoua <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 16:36:31 by achatoua          #+#    #+#             */
/*   Updated: 2021/03/16 17:26:38 by achatoua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

int	ft_scene(char *data, t_env *env)
{
	int		ret;

	ret = 0;
	ret |= !ft_parse_value(data, "<ambient>",
			"</ambient>", &(env->bg.ambient));
	ret |= !ft_color(data, &(env->bg.main_color), "<color>",
			"</color>");
	if (ret)
		return (0);
	env->xml_check.x++;
	return (1);
}

int	ft_plane(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*plane;

	ret = 0;
	plane = ft_new_object();
	plane->type = type_plane;
	plane->obj.id = (*count)++;
	ret |= !ft_standard(data, &(plane->obj));
	if (ret)
	{
		free(plane);
		return (0);
	}
	ft_object_push_back(object_list, plane);
	return (1);
}

int	ft_light2(char *data, t_object_list *light)
{
	int ret;

	ret = 0;
	ret |= !ft_parse_value(data, "<intensity>",
			"</intensity>", &(light->obj.intensity));
	ret |= !ft_parse_close(data, "<position>",
			"</position>", &(light->obj.position));
	ret |= !ft_parse_close(data, "<direction>",
			"</direction>", &(light->obj.direction));
	ret |= !ft_color(data, &(light->obj.main_color),
			"<color>", "</color>");
	return (ret);
}

int	ft_light(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	double			type;
	t_object_list	*light;

	light = ft_new_object();
	light->type = type_light;
	light->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_value(data, "<type>",
			"</type>", &(type));
	light->obj.type = (int)type;
	ret |= !ft_parse_value(data, "<attenuation>",
			"</attenuation>", &(light->obj.attenuation));
	ret = ft_light2(data, light);
	if (ret)
	{
		free(light);
		return (0);
	}
	ft_object_push_back(object_list, light);
	return (1);
}
