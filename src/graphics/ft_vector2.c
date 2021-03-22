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

t_vec	ft_mult_vecs(t_vec u, double s)
{
	t_vec v;

	v.x = u.x * s;
	v.y = u.y * s;
	v.z = u.z * s;
	return (v);
}

t_vec	ft_mult_vec(t_vec u, t_vec w)
{
	t_vec v;

	v.x = u.x * w.x;
	v.y = u.y * w.y;
	v.z = u.z * w.z;
	return (v);
}

t_vec	ft_div_vecs(t_vec u, double s)
{
	t_vec v;

	v.x = u.x / s;
	v.y = u.y / s;
	v.z = u.z / s;
	return (v);
}

double	ft_dot_vec(t_vec v, t_vec u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

double	ft_dot_mat(t_mat4 v, t_mat4 u)
{
	return (v.m_0 * u.m_0 + v.m_1 * u.m_1 + v.m_2 * u.m_2 + v.m_3 * u.m_3);
}
