/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_plane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:18:12 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/16 16:59:04 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int	plane_intersect(t_object plane, t_ray ray, t_intersect *intersect)
{
	double	d_dot_n;
	double	t;
	t_vec	p;

	d_dot_n = ft_dot_vec(ray.direction, plane.normal);
	if (d_dot_n == 0.0f)
		return (0);
	t = ft_dot_vec(ft_neg_vec(ray.origin), plane.normal) / d_dot_n;
	if (t <= RAY_T_MIN || t >= intersect->t)
		return (0);
	intersect->t = t;
	intersect->object = plane;
	intersect->type = type_plane;
	ray.origin = ft_add_vec(ray.origin, plane.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	intersect->normal = ft_norm_vec(plane.normal);
	p = ft_sub_vec(intersect->hitpoint, plane.slice);
	if (ft_dot_vec(p, plane.slice_vec) > 0)
		return (0);
	return (1);
}
