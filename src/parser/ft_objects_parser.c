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

int	ft_sphere(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*sphere;

	sphere = ft_new_object();
	sphere->type = type_sphere;
	sphere->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_value(data, "<radius>", "</radius>",
			&(sphere->obj.radius));
	ret |= !ft_standard(data, &(sphere->obj));
	if (ret)
	{
		free(sphere);
		return (0);
	}
	ft_object_push_back(object_list, sphere);
	return (1);
}

int	ft_cylinder(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*cylinder;

	cylinder = ft_new_object();
	cylinder->type = type_cylinder;
	cylinder->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_value(data, "<radius>", "</radius>",
			&(cylinder->obj.radius));
	ret |= !ft_standard(data, &(cylinder->obj));
	if (ret)
	{
		free(cylinder);
		return (0);
	}
	ft_object_push_back(object_list, cylinder);
	return (1);
}

int	ft_cone(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*cone;

	cone = ft_new_object();
	cone->type = type_cone;
	cone->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_value(data, "<angle>", "</angle>", &(cone->obj.angle));
	ret |= !ft_standard(data, &(cone->obj));
	if (ret)
	{
		free(cone);
		return (0);
	}
	ft_object_push_back(object_list, cone);
	return (1);
}

int	ft_paraboloid(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*paraboloid;

	paraboloid = ft_new_object();
	paraboloid->type = type_paraboloid;
	paraboloid->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_value(data, "<angle>",
	"</angle>", &(paraboloid->obj.angle));
	ret |= !ft_standard(data, &(paraboloid->obj));
	if (ret)
	{
		free(paraboloid);
		return (0);
	}
	ft_object_push_back(object_list, paraboloid);
	return (1);
}

int	ft_ellipsoid(char *data, t_object_list **object_list, int *count)
{
	int				ret;
	t_object_list	*ellipsoid;

	ellipsoid = ft_new_object();
	ellipsoid->type = type_ellipsoid;
	ellipsoid->obj.id = (*count)++;
	ret = 0;
	ret |= !ft_parse_value(data, "<radius>", "</radius>",
			&(ellipsoid->obj.radius));
	ret |= !ft_parse_value(data, "<angle>",
	"</angle>", &(ellipsoid->obj.angle));
	ret |= !ft_standard(data, &(ellipsoid->obj));
	if (ret)
	{
		free(ellipsoid);
		return (0);
	}
	ft_object_push_back(object_list, ellipsoid);
	return (1);
}
