/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:56:25 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:56:26 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	ft_build_rotation_matrix3in4_2(double c_th,
double s_th, t_mat *result, int axis)
{
	if (axis == 0)
	{
		result->m_5 = c_th;
		result->m_a = c_th;
		result->m_6 = s_th;
		result->m_9 = -s_th;
	}
	else if (axis == 1)
	{
		result->m_a = c_th;
		result->m_0 = c_th;
		result->m_8 = s_th;
		result->m_2 = -s_th;
	}
	else
	{
		result->m_0 = c_th;
		result->m_5 = c_th;
		result->m_1 = s_th;
		result->m_4 = -s_th;
	}
}

void	ft_build_rotation_matrix3in4(double theta, int axis, t_mat *mat)
{
	t_mat		result;
	double		c_th;
	double		s_th;

	ft_build_diagonal_matrix3in4((t_vec){1.f, 1.f, 1.f}, &(result));
	axis = axis % 3;
	s_th = sin(theta);
	c_th = cos(theta);
	ft_build_rotation_matrix3in4_2(c_th, s_th, &result, axis);
	*mat = result;
}

t_vec	ft_rotate_axis_z(t_vec axis, double angle)
{
	t_vec res;

	res.x = cos(angle) * axis.x - sin(angle) * axis.y;
	res.y = sin(angle) * axis.x + cos(angle) * axis.y;
	res.z = axis.z;
	return (res);
}
