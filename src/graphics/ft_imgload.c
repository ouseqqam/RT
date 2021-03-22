/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imgload.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:56:06 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:56:07 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

t_tex	*img_torgb(char *img_name)
{
	SDL_Surface		*img;
	unsigned char	*pixels;
	t_tex			*tex;
	int				i;

	i = 0;
	img = IMG_Load(img_name);
	if (!img)
	{
		ft_show_err(TAG_IMAGE_E);
		exit(0);
	}
	pixels = (unsigned char*)img->pixels;
	tex = malloc(sizeof(t_tex*));
	tex->rgbimg = malloc(sizeof(t_vec *) * img->h);
	while (i < img->h)
	{
		tex->rgbimg[i] = malloc(sizeof(t_vec) * img->w);
		i++;
	}
	return (img_torgb2(tex, pixels, img));
}

t_tex	*img_torgb2(t_tex *tex, unsigned char *pixels, SDL_Surface *img)
{
	int i;
	int j;
	int bpp;

	i = 0;
	j = 0;
	tex->i = img->h;
	tex->j = img->w;
	bpp = img->format->BytesPerPixel;
	while (i < img->h)
	{
		j = 0;
		while (j < img->w)
		{
			tex->rgbimg[i][j].x = pixels[(bpp * (i * img->w + j) + 2)];
			tex->rgbimg[i][j].x /= 255;
			tex->rgbimg[i][j].y = pixels[(bpp * (i * img->w + j) + 1)];
			tex->rgbimg[i][j].y /= 255;
			tex->rgbimg[i][j].z = pixels[(bpp * (i * img->w + j) + 0)];
			tex->rgbimg[i][j].z /= 255;
			j++;
		}
		i++;
	}
	return (tex);
}
