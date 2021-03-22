/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matrix.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:56:25 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:56:26 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

t_vec	ft_apply_linear_matrix(t_mat mat, t_vec vec3)
{
	t_vec		res;

	res.x = ft_dot_vec((t_vec){mat.m_0, mat.m_4, mat.m_8}, vec3);
	res.y = ft_dot_vec((t_vec){mat.m_1, mat.m_5, mat.m_6}, vec3);
	res.z = ft_dot_vec((t_vec){mat.m_2, mat.m_6, mat.m_a}, vec3);
	return (res);
}

void	ft_build_diagonal_matrix3in4(t_vec diag, t_mat *mat)
{
	ft_bzero(mat, sizeof(t_mat));
	mat->m_0 = diag.x;
	mat->m_5 = diag.y;
	mat->m_a = diag.z;
	mat->m_f = 1.f;
}

void	ft_mult_matrix2(t_mat q, t_mat r, t_mat *mat)
{
	mat->m_8 = ft_dot_mat((t_mat4){q.m_0, q.m_4, q.m_8, q.m_c},
	(t_mat4){r.m_8, r.m_9, r.m_a, r.m_b});
	mat->m_9 = ft_dot_mat((t_mat4){q.m_1, q.m_5, q.m_9, q.m_d},
	(t_mat4){r.m_8, r.m_9, r.m_a, r.m_b});
	mat->m_a = ft_dot_mat((t_mat4){q.m_2, q.m_6, q.m_a, q.m_e},
	(t_mat4){r.m_8, r.m_9, r.m_a, r.m_b});
	mat->m_b = ft_dot_mat((t_mat4){q.m_3, q.m_7, q.m_b, q.m_f},
	(t_mat4){r.m_8, r.m_9, r.m_a, r.m_b});
	mat->m_c = ft_dot_mat((t_mat4){q.m_0, q.m_4, q.m_8, q.m_c},
	(t_mat4){r.m_c, r.m_d, r.m_e, r.m_f});
	mat->m_d = ft_dot_mat((t_mat4){q.m_1, q.m_5, q.m_9, q.m_d},
	(t_mat4){r.m_c, r.m_d, r.m_e, r.m_f});
	mat->m_e = ft_dot_mat((t_mat4){q.m_2, q.m_6, q.m_a, q.m_e},
	(t_mat4){r.m_c, r.m_d, r.m_e, r.m_f});
	mat->m_f = ft_dot_mat((t_mat4){q.m_3, q.m_7, q.m_b, q.m_f},
	(t_mat4){r.m_c, r.m_d, r.m_e, r.m_f});
}

void	ft_mult_matrix(t_mat q, t_mat r, t_mat *mat)
{
	mat->m_0 = ft_dot_mat((t_mat4){q.m_0, q.m_4, q.m_8, q.m_c},
	(t_mat4){r.m_0, r.m_1, r.m_2, r.m_3});
	mat->m_1 = ft_dot_mat((t_mat4){q.m_1, q.m_5, q.m_9, q.m_d},
	(t_mat4){r.m_0, r.m_1, r.m_2, r.m_3});
	mat->m_2 = ft_dot_mat((t_mat4){q.m_2, q.m_6, q.m_a, q.m_e},
	(t_mat4){r.m_0, r.m_1, r.m_2, r.m_3});
	mat->m_3 = ft_dot_mat((t_mat4){q.m_3, q.m_7, q.m_b, q.m_f},
	(t_mat4){r.m_0, r.m_1, r.m_2, r.m_3});
	mat->m_4 = ft_dot_mat((t_mat4){q.m_0, q.m_4, q.m_8, q.m_c},
	(t_mat4){r.m_4, r.m_5, r.m_6, r.m_7});
	mat->m_5 = ft_dot_mat((t_mat4){q.m_1, q.m_5, q.m_9, q.m_d},
	(t_mat4){r.m_4, r.m_5, r.m_6, r.m_7});
	mat->m_6 = ft_dot_mat((t_mat4){q.m_2, q.m_6, q.m_a, q.m_e},
	(t_mat4){r.m_4, r.m_5, r.m_6, r.m_7});
	mat->m_7 = ft_dot_mat((t_mat4){q.m_3, q.m_7, q.m_b, q.m_f},
	(t_mat4){r.m_4, r.m_5, r.m_6, r.m_7});
	ft_mult_matrix2(q, r, mat);
}
