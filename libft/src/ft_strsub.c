/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 17:39:49 by youarzaz          #+#    #+#             */
/*   Updated: 2019/03/30 21:31:41 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (s)
	{
		tmp = ft_strnew(len);
		if (tmp)
		{
			s += start;
			tmp = ft_strncpy(tmp, s, len);
			tmp[len] = '\0';
			return (tmp);
		}
	}
	return (NULL);
}
