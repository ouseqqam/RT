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

t_vec	ft_set_vecs(double s)
{
	t_vec v;

	v.x = s;
	v.y = s;
	v.z = s;
	return (v);
}

t_vec	ft_add_vec(t_vec u, t_vec w)
{
	t_vec v;

	v.x = u.x + w.x;
	v.y = u.y + w.y;
	v.z = u.z + w.z;
	return (v);
}

t_vec	ft_sub_vec(t_vec u, t_vec w)
{
	t_vec v;

	v.x = u.x - w.x;
	v.y = u.y - w.y;
	v.z = u.z - w.z;
	return (v);
}
