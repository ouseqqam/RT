/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:57:48 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:57:49 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	ft_loadtex(t_env *env)
{
	t_object_list *objl;

	objl = env->object_list;
	while (objl)
	{
		if (objl->obj.image != NULL)
		{
			if (ft_strncmp(objl->obj.image, "cb", 2)
			&& ft_strncmp(objl->obj.image, "sin", 3))
				objl->obj.tex = img_torgb(objl->obj.image);
		}
		objl->obj.tex_ev.x = 1;
		objl->obj.tex_ev.y = 0;
		objl->obj.tex_ev.z = 0;
		objl = objl->next;
	}
}

t_vec	sphere_map(t_vec inp, double r)
{
	t_vec	tx;
	double	phi;
	double	theta;

	theta = atan2(inp.x, inp.z);
	phi = acos(inp.y / r);
	tx.x = ((theta / (2 * M_PI)) + 0.5);
	tx.y = (phi / M_PI);
	return (tx);
}

t_vec	cone_map(t_vec inp)
{
	t_vec	tx;
	double	theta;

	theta = atan2(inp.x, inp.z);
	tx.x = ((theta / (2 * M_PI)) + 0.5);
	tx.y = inp.y - (int)inp.y;
	if (tx.y < 0 && tx.y > -1)
		tx.y *= -1;
	return (tx);
}

t_vec	plane_map(t_vec inp)
{
	t_vec	tx;

	tx.x = inp.x - (int)inp.x;
	if (tx.x < 0 && tx.x > -1)
		tx.x *= -1;
	tx.y = inp.z - (int)inp.z;
	if (tx.y < 0 && tx.y > -1)
		tx.y *= -1;
	return (tx);
}
