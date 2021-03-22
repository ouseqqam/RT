/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intersect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:56:17 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:56:18 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

int	ft_check_intersect(t_object_list ob, t_ray r, t_intersect *in)
{
	if (ob.type == type_sphere && sphere_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_plane && plane_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_cylinder && cylinder_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_cone && cone_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_ellipsoid && ellips_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_paraboloid && parab_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_triangle && trgle_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_cube && cube_intersect(ob.obj, r, in))
		return (1);
	else if (ob.type == type_disk && disk_intersect(ob.obj, r, in))
		return (1);
	return (0);
}

int	ft_apply_transformation(t_object_list object_list, t_intersect *intersect)
{
	t_ray rotated_ray;

	rotated_ray = intersect->ray;
	rotated_ray.origin = ft_sub_vec(rotated_ray.origin,
	object_list.obj.position);
	if (!ft_check_intersect(object_list, rotated_ray, intersect))
		return (0);
	if (intersect->type != type_cube)
		ft_set_face_normal(intersect, rotated_ray, intersect->normal);
	return (1);
}

int	ft_calc_intersect(t_object_list *object_list,
int id_ignore, t_intersect *intersect)
{
	int inter;

	inter = 0;
	while (object_list)
	{
		if (id_ignore == -1 || id_ignore != object_list->obj.id)
			inter |= ft_apply_transformation(*object_list, intersect);
		object_list = object_list->next;
	}
	return (inter);
}

int	*intersect_pixel(int *pix, int pixel)
{
	int i;

	i = 0;
	while (i < (WIN_HEIGHT * WIN_WIDTH))
	{
		if (pix[i] == 0)
			break ;
		i++;
	}
	pix[i] = pixel;
	return (pix);
}

int	ft_calc_discriminant(t_vec quadr, t_vec *t)
{
	double discriminant;

	discriminant = (quadr.y * quadr.y) - 4 * quadr.x * quadr.z;
	if (discriminant < 0.0f)
		return (0);
	t->x = (-quadr.y - sqrt(discriminant)) / (2 * quadr.x);
	t->y = (-quadr.y + sqrt(discriminant)) / (2 * quadr.x);
	return (1);
}
