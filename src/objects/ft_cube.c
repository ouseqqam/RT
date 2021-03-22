/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:15:28 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/16 16:14:11 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int		cube_intersect_0(t_cube_var *var, t_object cube, t_ray ray)
{
	var->tmin = (cube.b_min.x - ray.origin.x) / ray.direction.x;
	var->tmax = (cube.b_max.x - ray.origin.x) / ray.direction.x;
	if (var->tmin > var->tmax)
		ft_swap(&var->tmin, &var->tmax);
	var->tymin = (cube.b_min.y - ray.origin.y) / ray.direction.y;
	var->tymax = (cube.b_max.y - ray.origin.y) / ray.direction.y;
	if (var->tymin > var->tymax)
		ft_swap(&var->tymin, &var->tymax);
	if ((var->tmin > var->tymax) || (var->tymin > var->tmax))
		return (0);
	if (var->tymin > var->tmin)
		var->tmin = var->tymin;
	if (var->tymax < var->tmax)
		var->tmax = var->tymax;
	var->tzmin = (cube.b_min.z - ray.origin.z) / ray.direction.z;
	var->tzmax = (cube.b_max.z - ray.origin.z) / ray.direction.z;
	if (var->tzmin > var->tzmax)
		ft_swap(&var->tzmin, &var->tzmax);
	if ((var->tmin > var->tzmax) || (var->tzmin > var->tmax))
		return (0);
	return (1);
}

int		cube_intersect(t_object cube, t_ray ray, t_intersect *intersect)
{
	t_cube_var	var;
	t_vec		p;

	if (cube_intersect_0(&var, cube, ray) == 0)
		return (0);
	if (var.tzmin > var.tmin)
		var.tmin = var.tzmin;
	if (var.tzmax < var.tmax)
		var.tmax = var.tzmax;
	if (var.tmin > var.tmax)
		ft_swap(&var.tmin, &var.tmax);
	if (var.tmin > RAY_T_MIN && var.tmin < intersect->t)
		intersect->t = var.tmin;
	else
		return (0);
	intersect->object = cube;
	intersect->type = type_cube;
	ray.origin = ft_add_vec(ray.origin, cube.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	intersect->normal = cube_normal(cube, intersect);
	p = ft_sub_vec(intersect->hitpoint, cube.slice);
	if (ft_dot_vec(p, cube.slice_vec) > 0)
		return (0);
	return (1);
}

t_vec	cube_normal(t_object cube, t_intersect *intersect)
{
	t_vec	c;
	t_vec	d;
	t_vec	p;
	t_vec	n;
	double	bias;

	bias = 1.00001;
	c = ft_mult_vecs(ft_add_vec(cube.b_min, cube.b_max), 0.5);
	d = ft_mult_vecs(ft_sub_vec(cube.b_min, cube.b_max), 0.5);
	d.x = fabs(d.x) * bias;
	d.y = fabs(d.y) * bias;
	d.z = fabs(d.z) * bias;
	p = ft_sub_vec(intersect->hitpoint, c);
	n.x = p.x / d.x;
	n.y = p.y / d.y;
	n.z = p.z / d.z;
	return (ft_norm_vec(n));
}
