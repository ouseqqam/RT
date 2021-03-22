/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:58:00 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:58:02 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

t_vec	ft_cross_vec(t_vec u, t_vec w)
{
	t_vec v;

	v.x = u.y * w.z - u.z * w.y;
	v.y = u.z * w.x - u.x * w.z;
	v.z = u.x * w.y - u.y * w.x;
	return (v);
}

t_vec	ft_norm_vec(t_vec v)
{
	double tmp;

	tmp = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	v.x /= tmp;
	v.y /= tmp;
	v.z /= tmp;
	return (v);
}

t_vec	ft_neg_vec(t_vec v)
{
	v.x = -v.x;
	v.y = -v.y;
	v.z = -v.z;
	return (v);
}

double	ft_sqr_vec(t_vec v)
{
	return ((v.x * v.x) + (v.y * v.y) + (v.z * v.z));
}

double	ft_mag_vec(t_vec vec)
{
	return (sqrt((vec.x * vec.x) + (vec.y * vec.y) + (vec.z * vec.z)));
}
