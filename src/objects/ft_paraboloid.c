/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_paraboloid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:04:30 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/16 16:15:48 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int		parabl(t_obj_var *var, t_object parab, t_ray ray, t_intersect *inter)
{
	var->quadr.x = ft_dot_vec(ray.direction, ray.direction) -
	ft_dot_vec(ray.direction, parab.normal) *
	ft_dot_vec(ray.direction, parab.normal);
	var->quadr.y = 2 * (ft_dot_vec(ray.direction, ray.origin) -
	ft_dot_vec(ray.direction, parab.normal) *
	(ft_dot_vec(ray.origin, parab.normal) + 2 * var->k));
	var->quadr.z = ft_dot_vec(ray.origin, ray.origin) -
	ft_dot_vec(ray.origin, parab.normal) *
	(ft_dot_vec(ray.origin, parab.normal) + 4 * var->k);
	if (!ft_calc_discriminant(var->quadr, &var->t))
		return (0);
	if ((var->t.x > RAY_T_MIN && var->t.x < inter->t)
	&& (var->t.y > RAY_T_MIN && var->t.y < inter->t))
		var->t_tmp = fmin(var->t.x, var->t.y);
	else if ((var->t.x > RAY_T_MIN && var->t.x < inter->t)
	|| (var->t.y > RAY_T_MIN && var->t.y < inter->t))
	{
		if (var->t.x > RAY_T_MIN && var->t.x < inter->t)
			var->t_tmp = var->t.x;
		if (var->t.y > RAY_T_MIN && var->t.y < inter->t)
			var->t_tmp = var->t.y;
	}
	else
		return (0);
	return (1);
}

int		parab_intersect(t_object parab, t_ray ray, t_intersect *inter)
{
	t_obj_var var;

	var.k = parab.angle;
	if (parabl(&var, parab, ray, inter) == 0)
		return (0);
	inter->t = var.t_tmp;
	inter->object = parab;
	inter->type = type_paraboloid;
	ray.origin = ft_add_vec(ray.origin, parab.position);
	inter->hitpoint = ft_ray_hitpoint(ray, inter->t);
	inter->normal = parab_normal(parab, inter, var.k);
	var.p = ft_sub_vec(inter->hitpoint, parab.slice);
	if (ft_dot_vec(var.p, parab.slice_vec) > 0)
		return (0);
	return (1);
}

t_vec	parab_normal(t_object parab, t_intersect *inter, double k)
{
	t_vec	n;
	double	m;

	m = ft_dot_vec(
		ft_sub_vec(inter->hitpoint, parab.position), parab.normal);
	n = ft_sub_vec(inter->hitpoint, parab.position);
	n = ft_sub_vec(n, ft_mult_vecs(parab.normal, m + k));
	n = ft_norm_vec(n);
	return (n);
}
