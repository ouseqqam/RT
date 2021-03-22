/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ellipsoid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:03:55 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/19 19:06:17 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int		ellips0(t_obj_var *var, t_object ellips, t_ray ray)
{
	var->a1 = ft_dot_vec(ray.direction, ellips.normal) * 2 * ellips.angle;
	var->a2 = ellips.radius * ellips.radius +
		ft_dot_vec(ray.origin, ellips.normal) * 2 *
		ellips.angle - ellips.angle;
	var->quadr.x = ft_dot_vec(ray.direction, ray.direction) *
		4 * ellips.radius * ellips.radius - var->a1 * var->a1;
	var->quadr.y = 2 * (ft_dot_vec(ray.direction, ray.origin) *
			4 * ellips.radius * ellips.radius - var->a1 * var->a2);
	var->quadr.z = ft_dot_vec(ray.origin, ray.origin) * 4 *
		ellips.radius * ellips.radius - var->a2 * var->a2;
	if (!ft_calc_discriminant(var->quadr, &var->t))
		return (0);
	return (1);
}

int		ellips_intersect(t_object ellips, t_ray ray, t_intersect *intersect)
{
	t_obj_var var;

	if (ellips0(&var, ellips, ray) == 0)
		return (0);
	if ((var.t.x > RAY_T_MIN && var.t.x < intersect->t)
			&& (var.t.y > RAY_T_MIN && var.t.y < intersect->t))
		intersect->t = fmin(var.t.x, var.t.y);
	else if ((var.t.x > RAY_T_MIN && var.t.x < intersect->t)
			|| (var.t.y > RAY_T_MIN && var.t.y < intersect->t))
	{
		if (var.t.x > RAY_T_MIN && var.t.x < intersect->t)
			intersect->t = var.t.x;
		if (var.t.y > RAY_T_MIN && var.t.y < intersect->t)
			intersect->t = var.t.y;
	}
	else
		return (0);
	intersect->object = ellips;
	intersect->type = type_ellipsoid;
	ray.origin = ft_add_vec(ray.origin, ellips.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	intersect->normal = elips_normal(ellips, intersect, var.quadr);
	return (1);
}

t_vec	elips_normal(t_object ellips, t_intersect *intr, t_vec quadr)
{
	t_vec cmid;
	t_vec r;
	t_vec n;

	cmid = ft_add_vec(ellips.position, ft_div_vecs(
				ft_mult_vecs(ellips.normal, ellips.angle), 2));
	r = ft_sub_vec(intr->hitpoint, cmid);
	n = ft_mult_vecs(ellips.normal,
			(1 - quadr.y * quadr.y / quadr.x * quadr.x) *
			ft_dot_vec(r, ellips.normal));
	n = ft_sub_vec(r, n);
	n = ft_norm_vec(n);
	return (n);
}
