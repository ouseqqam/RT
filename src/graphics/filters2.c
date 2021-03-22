/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 14:59:07 by moel-aza          #+#    #+#             */
/*   Updated: 2021/03/19 16:35:44 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

double	color_distence(t_vec col1, t_vec col2)
{
	double i;

	col2.x *= 255;
	col2.y *= 255;
	col2.z *= 255;
	i = sqrt(((col1.x - col2.x) * (col1.x - col2.x)) + ((col1.y - col2.y) *
				(col1.y - col2.y)) + ((col1.z - col2.z) * (col1.z - col2.z)));
	return (i);
}

void	cartoon(t_vec *pixels, int res)
{
	t_vec	*colh;
	double	c;
	int		i;
	int		k;
	int		j;

	colh = malloc(sizeof(t_vec) * 54);
	colh_init(colh);
	i = 0;
	while (++i < res)
	{
		j = 0;
		c = INFINITY;
		while (++j < 54)
			if (color_distence(colh[j], pixels[i]) < c)
			{
				c = color_distence(colh[j], pixels[i]);
				k = j;
			}
		pixels[i].x = colh[k].x / 255;
		pixels[i].y = colh[k].y / 255;
		pixels[i].z = colh[k].z / 255;
	}
	free(colh);
}

void	sepia(t_vec *pixels, int res)
{
	int i;

	i = 0;
	while (i < res)
	{
		pixels[i].x = (pixels[i].x * .393) + (pixels[i].y * .769) +
			(pixels[i].z * .189);
		pixels[i].y = (pixels[i].x * .349) + (pixels[i].y * .686) +
			(pixels[i].z * .168);
		pixels[i].z = (pixels[i].x * .272) + (pixels[i].y * .534) +
			(pixels[i].z * .131);
		if (pixels[i].x > 1)
			pixels[i].x = 1;
		if (pixels[i].y > 1)
			pixels[i].y = 1;
		if (pixels[i].z > 1)
			pixels[i].z = 1;
		i++;
	}
}

void	blure_one_object3(t_vec *pixels, int j, int i, t_object_list *obj)
{
	pixels[obj->obj.pix[i] + j].x = (pixels[obj->obj.pix[i]].x
		* 0.03 + pixels[obj->obj.pix[i] + j].x * 0.97);
	pixels[obj->obj.pix[i] + j].y = (pixels[obj->obj.pix[i]].y
		* 0.03 + pixels[obj->obj.pix[i] + j].y * 0.97);
	pixels[obj->obj.pix[i] + j].z = (pixels[obj->obj.pix[i]].z
		* 0.03 + pixels[obj->obj.pix[i] + j].z * 0.97);
	pixels[obj->obj.pix[i] - j].x = (pixels[obj->obj.pix[i]].x
		* 0.03 + pixels[obj->obj.pix[i] - j].x * 0.97);
	pixels[obj->obj.pix[i] - j].y = (pixels[obj->obj.pix[i]].y
		* 0.03 + pixels[obj->obj.pix[i] - j].y * 0.97);
	pixels[obj->obj.pix[i] - j].z = (pixels[obj->obj.pix[i]].z
		* 0.03 + pixels[obj->obj.pix[i] - j].z * 0.97);
}
