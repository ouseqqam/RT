/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_triangle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 16:06:24 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/16 16:57:27 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int		initial_trgle_var(t_triangle_var *var, t_object triangle, t_ray ray)
{
	var->a = ft_sub_vec(triangle.v1, triangle.v0);
	var->b = ft_sub_vec(triangle.v2, triangle.v0);
	var->p = ft_cross_vec(ray.direction, var->b);
	var->det = ft_dot_vec(var->a, var->p);
	if (fabs(var->det) < 0.0000000001)
		return (0);
	var->invdet = 1 / var->det;
	var->ov0 = ft_sub_vec(ray.origin, triangle.v0);
	var->u = ft_dot_vec(var->ov0, var->p) * var->invdet;
	if (var->u < 0 || var->u > 1)
		return (0);
	var->ov0 = ft_cross_vec(var->ov0, var->a);
	var->v = ft_dot_vec(ray.direction, var->ov0) * var->invdet;
	if (var->v < 0 || var->u + var->v > 1)
		return (0);
	var->t = ft_dot_vec(var->b, var->ov0) * var->invdet;
	return (1);
}

int		trgle_intersect(t_object triangle, t_ray ray, t_intersect *intersect)
{
	t_triangle_var	var;

	if (initial_trgle_var(&var, triangle, ray) == 0)
		return (0);
	if (var.t > RAY_T_MIN && var.t < intersect->t)
		intersect->t = var.t;
	else
		return (0);
	intersect->object = triangle;
	intersect->type = type_triangle;
	ray.origin = ft_add_vec(ray.origin, triangle.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	intersect->normal = triangle_normal(triangle);
	var.p = ft_sub_vec(intersect->hitpoint, triangle.slice);
	if (ft_dot_vec(var.p, triangle.slice_vec) > 0)
		return (0);
	return (1);
}

t_vec	triangle_normal(t_object triangle)
{
	t_vec n;
	t_vec a;
	t_vec b;

	a = ft_sub_vec(triangle.v1, triangle.v0);
	b = ft_sub_vec(triangle.v2, triangle.v0);
	n = ft_norm_vec(ft_cross_vec(a, b));
	return (n);
}
