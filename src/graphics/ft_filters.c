/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:55:31 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 14:33:56 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	noise(t_vec *pixels, int res)
{
	int i;

	i = 0;
	while (i < res)
	{
		if (rand() < (RAND_MAX / 3))
		{
			pixels[i].x = (pixels[i].x * .3)
				+ (pixels[i].y * .59) + (pixels[i].z * .11);
			pixels[i].y = (pixels[i].x * .3)
				+ (pixels[i].y * .59) + (pixels[i].z * .11);
			pixels[i].z = (pixels[i].x * .3)
				+ (pixels[i].y * .59) + (pixels[i].z * .11);
		}
		if (rand() > (RAND_MAX / 1.5))
		{
			pixels[i].x = (pixels[i].x * .59)
			+ (pixels[i].y * .1) + (pixels[i].z * .1);
			pixels[i].y = (pixels[i].x * .59)
			+ (pixels[i].y * .1) + (pixels[i].z * .1);
			pixels[i].z = (pixels[i].x * .59)
			+ (pixels[i].y * .1) + (pixels[i].z * .1);
		}
		i++;
	}
}

void	blure(t_vec *pixels, int res)
{
	int i;
	int j;
	int k;

	i = 0;
	while (i < res)
	{
		j = 1;
		k = 1;
		while (j < 70)
		{
			if (i + j < res)
			{
				pixels[i].x += pixels[i + j].x;
				pixels[i].y += pixels[i + j].y;
				pixels[i].z += pixels[i + j].z;
				k++;
			}
			j++;
		}
		pixels[i].x /= k;
		pixels[i].y /= k;
		pixels[i].z /= k;
		i++;
	}
}

void	blure_one_object2(t_vec *pixels, int res, t_object_list *obj, int i)
{
	int j;

	j = 0;
	while (++j < obj->obj.blur * 3 && obj->obj.blur != 0)
		if (obj->obj.pix[i] + j < res)
		{
			if ((j > 30 || j < 10) && rand() > (RAND_MAX / 3))
			{
				pixels[obj->obj.pix[i]].x = (pixels[obj->obj.pix[i]].x
					* 0.97 + pixels[obj->obj.pix[i] + j].x * 0.03);
				pixels[obj->obj.pix[i]].y = (pixels[obj->obj.pix[i]].y
					* 0.97 + pixels[obj->obj.pix[i] + j].y * 0.03);
				pixels[obj->obj.pix[i]].z = (pixels[obj->obj.pix[i]].z
					* 0.97 + pixels[obj->obj.pix[i] + j].z * 0.03);
				pixels[obj->obj.pix[i]].x = (pixels[obj->obj.pix[i]].x
					* 0.97 + pixels[obj->obj.pix[i] - j].x * 0.03);
				pixels[obj->obj.pix[i]].y = (pixels[obj->obj.pix[i]].y
					* 0.97 + pixels[obj->obj.pix[i] - j].y * 0.03);
				pixels[obj->obj.pix[i]].z = (pixels[obj->obj.pix[i]].z
					* 0.97 + pixels[obj->obj.pix[i] - j].z * 0.03);
			}
			blure_one_object3(pixels, j, i, obj);
		}
}

void	blure_one_object(t_vec *pixels, int res, t_object_list *obj)
{
	int i;

	while (obj)
	{
		if (obj->obj.blur != 0)
		{
			i = 0;
			while (obj->obj.pix[i] != 0)
			{
				blure_one_object2(pixels, res, obj, i);
				i++;
			}
		}
		obj = obj->next;
	}
}

void	filters(int flag, t_vec *pixels, int res, t_object_list *obj)
{
	if (flag == 1)
		sepia(pixels, res);
	if (flag == 2)
		noise(pixels, res);
	if (flag == 3)
		blure(pixels, res);
	if (flag == 4)
		blure_one_object(pixels, res, obj);
	if (flag == 5)
		cartoon(pixels, res);
}
