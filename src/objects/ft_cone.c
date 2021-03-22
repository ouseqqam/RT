/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cone.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:02:39 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/18 17:43:06 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int	cone0(t_obj_var *var, t_object cone, t_ray ray, t_intersect *intersect)
{
	var->k = cone.angle;
	var->quadr.x = ft_sqr_vec(ray.direction) - ((1 + var->k * var->k) *
			(pow(ft_dot_vec(ray.direction, cone.normal), 2)));
	var->quadr.y = 2 * (ft_dot_vec(ray.direction, ray.origin) -
			((1 + var->k * var->k) * (ft_dot_vec(ray.direction, cone.normal) *
				ft_dot_vec(ray.origin, cone.normal))));
	var->quadr.z = ft_sqr_vec(ray.origin) - ((1 + var->k * var->k) *
			(pow(ft_dot_vec(ray.origin, cone.normal), 2)));
	if (!ft_calc_discriminant(var->quadr, &var->t))
		return (0);
	if ((var->t.x > RAY_T_MIN && var->t.x < intersect->t)
			&& (var->t.y > RAY_T_MIN && var->t.y < intersect->t))
		var->t_tmp = fmin(var->t.x, var->t.y);
	else if ((var->t.x > RAY_T_MIN && var->t.x < intersect->t)
			|| (var->t.y > RAY_T_MIN && var->t.y < intersect->t))
	{
		if (var->t.x > RAY_T_MIN && var->t.x < intersect->t)
			var->t_tmp = var->t.x;
		if (var->t.y > RAY_T_MIN && var->t.y < intersect->t)
			var->t_tmp = var->t.y;
	}
	else
		return (0);
	return (1);
}

int	cone_intersect(t_object cone, t_ray ray, t_intersect *intersect)
{
	t_obj_var var;

	if (cone0(&var, cone, ray, intersect) == 0)
		return (0);
	intersect->m = ft_dot_vec(ray.direction, cone.normal) *
		var.t_tmp + ft_dot_vec(ray.origin, cone.normal);
	intersect->t = var.t_tmp;
	intersect->object = cone;
	intersect->type = type_cone;
	ray.origin = ft_add_vec(ray.origin, cone.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	intersect->normal = ft_norm_vec(ft_sub_vec(
				ft_sub_vec(intersect->hitpoint, cone.position),
				ft_mult_vecs(ft_mult_vecs(cone.normal, intersect->m),
					(1 + var.k * var.k))));
	var.p = ft_sub_vec(intersect->hitpoint, cone.slice);
	if (ft_dot_vec(var.p, cone.slice_vec) > 0)
		return (0);
	return (1);
}
