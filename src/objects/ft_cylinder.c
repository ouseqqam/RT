/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cylinder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:15:35 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/16 16:15:02 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int	cyldr(t_obj_var *var, t_object cylinder, t_ray ray, t_intersect *intersect)
{
	var->quadr.x = ft_sqr_vec(ray.direction)
		- (pow(ft_dot_vec(ray.direction, cylinder.normal), 2));
	var->quadr.y = 2 * (ft_dot_vec(ray.direction, ray.origin)
			- (ft_dot_vec(ray.direction, cylinder.normal)
				* ft_dot_vec(ray.origin, cylinder.normal)));
	var->quadr.z = ft_sqr_vec(ray.origin)
		- (pow(ft_dot_vec(ray.origin, cylinder.normal), 2))
		- (cylinder.radius * cylinder.radius);
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

int	cylinder_intersect(t_object cylinder, t_ray ray, t_intersect *intersect)
{
	t_obj_var var;

	if (cyldr(&var, cylinder, ray, intersect) == 0)
		return (0);
	intersect->m = ft_dot_vec(ray.direction, cylinder.normal) * var.t_tmp
		+ ft_dot_vec(ray.origin, cylinder.normal);
	intersect->t = var.t_tmp;
	intersect->object = cylinder;
	intersect->type = type_cylinder;
	ray.origin = ft_add_vec(ray.origin, cylinder.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	intersect->normal = ft_norm_vec(ft_sub_vec(
				ft_sub_vec(intersect->hitpoint, cylinder.position),
				ft_mult_vecs(cylinder.normal, intersect->m)));
	var.p = ft_sub_vec(intersect->hitpoint, cylinder.slice);
	if (ft_dot_vec(var.p, cylinder.slice_vec) > 0)
		return (0);
	return (1);
}
