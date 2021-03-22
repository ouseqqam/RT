/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sphere.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:17:56 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/19 19:02:07 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int	spheres(t_obj_var *var, t_object sphere, t_ray ray, t_intersect *intersect)
{
	var->quadr.x = ft_sqr_vec(ray.direction);
	var->quadr.y = 2 * ft_dot_vec(ray.direction, ray.origin);
	var->quadr.z = ft_sqr_vec(ray.origin) - (sphere.radius * sphere.radius);
	if (!ft_calc_discriminant(var->quadr, &var->t))
		return (0);
	if ((var->t.x > RAY_T_MIN && var->t.x < intersect->t)
			&& (var->t.y > RAY_T_MIN && var->t.y < intersect->t))
		intersect->t = fmin(var->t.x, var->t.y);
	else if ((var->t.x > RAY_T_MIN && var->t.x < intersect->t)
			|| (var->t.y > RAY_T_MIN && var->t.y < intersect->t))
	{
		if (var->t.x > RAY_T_MIN && var->t.x < intersect->t)
			intersect->t = var->t.x;
		if (var->t.y > RAY_T_MIN && var->t.y < intersect->t)
			intersect->t = var->t.y;
	}
	else
		return (0);
	return (1);
}

int	sphere_intersect(t_object sphere, t_ray ray, t_intersect *intersect)
{
	t_obj_var	var;

	if (spheres(&var, sphere, ray, intersect) == 0)
		return (0);
	intersect->object = sphere;
	intersect->type = type_sphere;
	ray.origin = ft_add_vec(ray.origin, sphere.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	intersect->normal = ft_norm_vec(ft_div_vecs(
				ft_sub_vec(intersect->hitpoint, sphere.position),
				sphere.radius));
	var.p = ft_sub_vec(intersect->hitpoint, sphere.slice);
	if (ft_dot_vec(var.p, sphere.slice_vec) > 0)
		return (0);
	return (1);
}
