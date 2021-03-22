/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:55:13 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:55:14 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

t_vec	ft_color_clip(t_vec color)
{
	if (color.x < 0.0)
		color.x = 0.0;
	if (color.y < 0.0)
		color.y = 0.0;
	if (color.z < 0.0)
		color.z = 0.0;
	if (color.x > 0.999)
		color.x = 0.999;
	if (color.y > 0.999)
		color.y = 0.999;
	if (color.z > 0.999)
		color.z = 0.999;
	return (color);
}

t_vec	ft_correct_color(t_vec render_color, int samples)
{
	float scale;

	scale = 1.0 / samples;
	render_color = ft_mult_vecs(render_color, scale);
	render_color.x = sqrt(render_color.x);
	render_color.y = sqrt(render_color.y);
	render_color.z = sqrt(render_color.z);
	render_color = ft_color_clip(render_color);
	return (render_color);
}
