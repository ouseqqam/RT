/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shader.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:57:11 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:57:12 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

void	ft_compute_light2(t_env *env,
t_intersect *intersect, t_vec *accum_color, t_light_var *var)
{
	var->light_intersect.t = RAY_T_MAX;
	ft_calc_intersect(env->object_list,
	var->object_list->obj.id, &var->light_intersect);
	if (var->light_intersect.t > ft_mag_vec(intersect->hitpoint))
	{
		*accum_color = ft_add_vec(*accum_color,
ft_diffuse(var->object_list->obj, var->light_intersect, intersect));
		*accum_color = ft_add_vec(*accum_color,
ft_mult_vec(intersect->object.main_color,
ft_mult_vecs(var->object_list->obj.main_color, var->lambert)));
		if (intersect->object.specular > 1)
		{
			var->specular =
			ft_get_specular_dot(env, *intersect, var->light_intersect);
			if (var->specular > 0)
			{
				var->specular = pow(var->specular, intersect->object.specular);
				*accum_color = ft_add_vec(*accum_color,
		ft_mult_vecs(var->object_list->obj.main_color, var->specular));
			}
		}
	}
}

void	ft_compute_light(t_env *env, t_intersect *intersect, t_vec *accum_color)
{
	t_light_var var;

	var.object_list = env->object_list;
	while (var.object_list)
	{
		if (var.object_list->type == type_light)
		{
			ft_get_light_ray(var.object_list->obj,
			&var.light_intersect, intersect);
			var.lambert = ft_dot_vec(intersect->normal,
			var.light_intersect.ray.direction);
			if (var.lambert > 0)
				ft_compute_light2(env, intersect, accum_color, &var);
		}
		var.object_list = var.object_list->next;
	}
}
