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

double	ft_get_specular_dot(t_env *env, t_intersect intersect,
t_intersect light_intersect)
{
	t_vec	h;
	double	specular;

	h = ft_add_vec(light_intersect.ray.direction,
	ft_norm_vec(ft_sub_vec(env->cam.position, intersect.hitpoint)));
	h = ft_norm_vec(h);
	specular = ft_dot_vec(intersect.normal, h);
	return (specular);
}

t_vec	ft_diffuse(t_object light,
t_intersect light_intersect, t_intersect *intersect)
{
	double	theta;
	double	res;

	theta = ft_clampf(ft_dot_vec(light_intersect.ray.direction,
	intersect->normal), 0, 1);
	res = intersect->object.diffuse * light.intensity
	* theta / light_intersect.dist_attenuation;
	return (ft_mult_vecs(light.main_color, res));
}

void	ft_get_light_ray(t_object light,
t_intersect *light_intersect, t_intersect *intersect)
{
	light_intersect->ray.origin = intersect->hitpoint;
	if (light.type == lgt_directional)
	{
		light_intersect->ray.direction = light.direction;
		light_intersect->dist_attenuation = 1.0;
	}
	else
	{
		light_intersect->ray.direction =
		ft_sub_vec(light.position, intersect->hitpoint);
		intersect->t = ft_mag_vec(light_intersect->ray.direction);
		light_intersect->dist_attenuation =
		(1.0 + intersect->t * intersect->t * light.attenuation);
	}
	light_intersect->ray.direction =
	ft_norm_vec(light_intersect->ray.direction);
}
