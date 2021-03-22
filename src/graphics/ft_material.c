/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_material.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:59:16 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 18:22:17 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

t_vec	ft_get_reflect(t_vec direction, t_vec normal)
{
	t_vec res;

	res = ft_mult_vecs(normal, -2.0 * ft_dot_vec(direction, normal));
	res = ft_add_vec(res, direction);
	return (res);
}

void	ft_get_refract(t_intersect *intersect)
{
	double	n;
	double	tmp1;
	double	tmp2;
	double	tmp3;
	t_vec	normal;

	normal = intersect->normal;
	intersect->ray.origin = intersect->hitpoint;
	tmp1 = ft_dot_vec(normal, intersect->ray.direction);
	if (tmp1 > 0.0)
	{
		n = intersect->object.refract / 1.0;
		normal = ft_mult_vecs(normal, -1.0);
	}
	else
	{
		n = 1.0 / intersect->object.refract;
		tmp1 = -tmp1;
	}
	tmp2 = n * n * (1.0 - tmp1 * tmp1);
	tmp3 = sqrt(1.0 - tmp2);
	intersect->ray.direction =
	ft_add_vec(ft_mult_vecs(intersect->ray.direction, n),
	ft_mult_vecs(normal, (n * tmp1 - tmp3)));
	intersect->ray.direction = ft_norm_vec(intersect->ray.direction);
}

t_vec	ft_compute_reflect(t_thread_param *data,
t_intersect *intersect, t_vec accum_color)
{
	if (data->depth)
	{
		data->depth--;
		intersect->ray.origin = intersect->hitpoint;
		intersect->ray.direction =
		ft_get_reflect(intersect->ray.direction, intersect->normal);
		accum_color = ft_add_vec(accum_color,
		ft_compute_color(data, intersect));
		accum_color = ft_mult_vecs(accum_color, intersect->object.reflect);
	}
	return (accum_color);
}

t_vec	ft_compute_refract(t_thread_param *data,
t_intersect *intersect, t_vec accum_color)
{
	if (data->refract_depth)
	{
		data->refract_depth--;
		ft_get_refract(intersect);
		accum_color = ft_add_vec(accum_color,
ft_mult_vecs(ft_compute_color(data, intersect), intersect->object.refract));
	}
	return (accum_color);
}
