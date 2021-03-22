/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:22:28 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/12 18:22:30 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

t_vec	ft_ray_hitpoint(t_ray ray, double t)
{
	return (ft_add_vec(ray.origin, ft_mult_vecs(ray.direction, t)));
}

void	ft_set_face_normal(t_intersect *intersect,
t_ray ray, t_vec outward_normal)
{
	intersect->front_face =
	ft_dot_vec(ray.direction, outward_normal) < 0;
	intersect->normal = intersect->front_face ?
	outward_normal : ft_neg_vec(outward_normal);
}

void	ft_swap(double *a, double *b)
{
	double tmp_a;

	tmp_a = *a;
	*a = *b;
	*b = tmp_a;
}

double	ft_clampf(double value, double min, double max)
{
	value > max ? value = max : 0;
	value < min ? value = min : 0;
	return (value);
}
