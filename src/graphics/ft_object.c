/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_object.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:56:46 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:56:47 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

t_object_list	*ft_new_object(void)
{
	t_object_list *node;

	if (!(node = (t_object_list *)ft_memalloc(sizeof(t_object_list))))
		return (0);
	node->next = NULL;
	node->obj.rotate.x = 0;
	node->obj.rotate.y = 0;
	node->obj.rotate.z = 0;
	node->obj.specular = 0;
	node->obj.reflect = 0;
	node->obj.refract = 0;
	node->obj.id = -1;
	return (node);
}

void			ft_object_push_back(t_object_list **head, t_object_list *new)
{
	t_object_list *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return ;
	}
	ft_object_push_back(&(tmp->next), new);
}

void			ft_run_builder(t_object_list *obl)
{
	t_builder_var var;

	while (obl)
	{
		var.position = obl->obj.position;
		var.scale = obl->obj.scale;
		var.rotate = ft_mult_vec(obl->obj.rotate, ft_set_vecs(M_PI / 180));
		ft_build_diagonal_matrix3in4(var.scale, &var.scale_mat);
		ft_build_rotation_matrix3in4(var.rotate.x, 0, &var.x_mat);
		ft_build_rotation_matrix3in4(var.rotate.y, 1, &var.y_mat);
		ft_build_rotation_matrix3in4(var.rotate.z, 2, &var.z_mat);
		ft_mult_matrix(var.x_mat, var.y_mat, &var.rot_mat);
		ft_mult_matrix(var.rot_mat, var.z_mat, &var.rot_mat);
		ft_mult_matrix(var.rot_mat, var.scale_mat, &var.rot_mat);
		obl->obj.matrix = var.rot_mat;
		obl->obj.matrix.m_c = var.position.x;
		obl->obj.matrix.m_d = var.position.y;
		obl->obj.matrix.m_e = var.position.z;
		obl->obj.normal = ft_apply_linear_matrix(obl->obj.matrix,
		obl->obj.normal);
		obl = obl->next;
	}
}
