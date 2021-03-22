/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:22:46 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/19 15:24:05 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

void	cb_sin(t_intersect *inter, t_vec *accum_color)
{
	t_vec uv;
	t_vec hp;

	hp = ft_sub_vec(inter->hitpoint, inter->object.position);
	if (!ft_strncmp(inter->object.image, "cb", 2))
	{
		if (inter->type == type_sphere)
			uv = sphere_map(hp, inter->object.radius);
		else if (inter->type == type_cylinder)
			uv = cone_map(hp);
		else if (inter->type == type_cone)
			uv = cone_map(hp);
		else
			uv = plane_map(hp);
		ft_cb(accum_color, uv);
	}
	else
		ft_sin(inter, accum_color, hp);
}

void	ft_sin(t_intersect *inter, t_vec *accum_color, t_vec hp)
{
	t_vec	uv;
	double	a;
	int		r;

	if (inter->type == type_sphere)
		uv = sphere_map(hp, inter->object.radius);
	else if (inter->type == type_cylinder)
		uv = cone_map(hp);
	else if (inter->type == type_cone)
		uv = cone_map(hp);
	else
		uv = plane_map(hp);
	r = 2 * M_PI / uv.x * uv.y;
	a = (5 * M_PI * r / 3 * (2 * M_PI)) + M_PI / 2;
	accum_color->x = sin(a) * 192 + 128;
	accum_color->x = fmax(0, fmin(255, accum_color->x));
	accum_color->y = sin(a - 2 * M_PI / 3) * 192 + 128;
	accum_color->y = fmax(0, fmin(255, accum_color->y));
	accum_color->z = sin(a - 4 * M_PI / 3) * 192 + 128;
	accum_color->z = fmax(0, fmin(255, accum_color->z));
}

int		uv_checker(t_vec *uv, t_intersect *inter)
{
	if (isnan(uv->x))
		uv->x = 0;
	if (isnan(uv->y))
		uv->y = 0;
	if (uv->x > 1 || uv->x < 0)
		return (0);
	if (uv->y > 1 || uv->y < 0)
		return (0);
	uv->y /= inter->object.tex_ev.x;
	uv->y -= inter->object.tex_ev.y;
	uv->x += inter->object.tex_ev.z;
	if (uv->x > 1 || uv->x < 0)
		return (0);
	if (uv->y > 1 || uv->y < 0)
		return (0);
	return (1);
}

int		ft_texture(t_intersect *inter, t_vec *accum_color)
{
	t_vec	uv;
	t_vec	hp;

	hp = ft_sub_vec(inter->hitpoint, inter->object.position);
	if (!ft_strncmp(inter->object.image, "cb", 2)
	|| !ft_strncmp(inter->object.image, "sin", 3))
		cb_sin(inter, accum_color);
	else
	{
		if (inter->type == type_sphere)
			uv = sphere_map(hp, inter->object.radius);
		else if (inter->type == type_cylinder)
			uv = sphere_map(hp, inter->object.radius);
		else if (inter->type == type_cone)
			uv = cone_map(hp);
		else
			uv = plane_map(hp);
		if (!uv_checker(&uv, inter))
			return (0);
		ft_texture2(inter, accum_color, uv);
	}
	return (1);
}

void	ft_texture2(t_intersect *inter, t_vec *accum_color, t_vec uv)
{
	t_vec	cl;
	int		i;
	int		j;

	i = (int)(uv.y * inter->object.tex->i);
	j = (int)(uv.x * inter->object.tex->j);
	cl.x = inter->object.tex->rgbimg[i][j].x;
	cl.y = inter->object.tex->rgbimg[i][j].y;
	cl.z = inter->object.tex->rgbimg[i][j].z;
	*accum_color = cl;
}
