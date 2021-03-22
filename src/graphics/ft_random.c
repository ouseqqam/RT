/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:34:51 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 14:34:52 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

double	frand(void)
{
	return ((double)rand() / (RAND_MAX + 1.0));
}

double	ft_random_range(double min, double max)
{
	return (min + (max - min) * frand());
}

t_vec	ft_random_in_unit_disk(void)
{
	t_vec p;

	while (1)
	{
		p = (t_vec){ft_random_range(-1, 1), ft_random_range(-1, 1), 0};
		if (ft_sqr_vec(p) >= 1)
			continue;
		return (p);
	}
}
