/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_disk.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouseqqam <ouseqqam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:58:00 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/18 17:58:26 by ouseqqam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

double	distance(t_vec a, t_vec b)
{
	double d;
	double x;
	double y;
	double z;

	x = (b.x - a.x) * (b.x - a.x);
	y = (b.y - a.y) * (b.y - a.y);
	z = (b.z - a.z) * (b.z - a.z);
	d = sqrt(x + y + z);
	return (d);
}

int		disk_intersect(t_object disk, t_ray ray, t_intersect *intersect)
{
	double	d_dot_n;
	double	t;
	t_vec	p;
	double	d;

	disk.normal = (t_vec){0, 0, 1};
	d_dot_n = ft_dot_vec(ray.direction, disk.normal);
	if (d_dot_n == 0.0f)
		return (0);
	t = ft_dot_vec(ft_neg_vec(ray.origin), disk.normal) / d_dot_n;
	if (t <= RAY_T_MIN || t >= intersect->t)
		return (0);
	intersect->t = t;
	intersect->object = disk;
	intersect->type = type_disk;
	ray.origin = ft_add_vec(ray.origin, disk.position);
	intersect->hitpoint = ft_ray_hitpoint(ray, intersect->t);
	d = fabs(distance(intersect->hitpoint, disk.position));
	if (d > disk.radius)
		return (0);
	intersect->normal = ft_norm_vec(disk.normal);
	p = ft_sub_vec(intersect->hitpoint, disk.slice);
	if (ft_dot_vec(p, disk.slice_vec) > 0)
		return (0);
	return (1);
}
