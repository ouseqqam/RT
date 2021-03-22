/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_colh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:55:05 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 15:24:54 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	colh_init(t_vec *colh)
{
	colh[0] = (t_vec){120, 40, 31};
	colh[1] = (t_vec){169, 50, 38};
	colh[2] = (t_vec){192, 57, 43};
	colh[3] = (t_vec){205, 97, 85};
	colh[4] = (t_vec){253, 237, 236};
	colh[5] = (t_vec){74, 35, 90};
	colh[6] = (t_vec){136, 78, 160};
	colh[7] = (t_vec){155, 89, 182};
	colh[8] = (t_vec){157, 122, 197};
	colh[9] = (t_vec){244, 236, 247};
	colh[10] = (t_vec){27, 79, 114};
	colh[11] = (t_vec){136, 78, 160};
	colh[12] = (t_vec){41, 128, 185};
	colh[13] = (t_vec){84, 153, 199};
	colh[14] = (t_vec){235, 245, 251};
	colh[15] = (t_vec){11, 83, 69};
	colh[16] = (t_vec){136, 78, 160};
	colh[17] = (t_vec){26, 188, 156};
	colh[18] = (t_vec){72, 201, 176};
	colh[19] = (t_vec){232, 246, 243};
	colh[20] = (t_vec){24, 106, 59};
	colh[21] = (t_vec){136, 78, 160};
	colh[22] = (t_vec){39, 174, 96};
	colh[23] = (t_vec){82, 190, 128};
	colh2_init(colh);
}

void	colh3_init(t_vec *colh)
{
	colh[46] = (t_vec){46, 64, 83};
	colh[47] = (t_vec){44, 62, 80};
	colh[48] = (t_vec){93, 109, 126};
	colh[49] = (t_vec){135, 206, 220};
	colh[50] = (t_vec){187, 196, 139};
	colh[51] = (t_vec){215, 196, 160};
	colh[52] = (t_vec){207, 214, 160};
	colh[53] = (t_vec){237, 204, 173};
}

void	colh2_init(t_vec *colh)
{
	colh[24] = (t_vec){234, 250, 241};
	colh[25] = (t_vec){254, 245, 231};
	colh[26] = (t_vec){212, 172, 13};
	colh[27] = (t_vec){241, 196, 15};
	colh[28] = (t_vec){244, 208, 63};
	colh[29] = (t_vec){126, 81, 9};
	colh[30] = (t_vec){251, 238, 230};
	colh[31] = (t_vec){202, 111, 30};
	colh[32] = (t_vec){230, 126, 34};
	colh[33] = (t_vec){235, 152, 78};
	colh[34] = (t_vec){110, 44, 0};
	colh[35] = (t_vec){248, 249, 249};
	colh[36] = (t_vec){208, 211, 212};
	colh[37] = (t_vec){236, 240, 241};
	colh[38] = (t_vec){240, 243, 244};
	colh[39] = (t_vec){98, 101, 103};
	colh[40] = (t_vec){242, 244, 244};
	colh[41] = (t_vec){131, 145, 146};
	colh[42] = (t_vec){149, 165, 166};
	colh[43] = (t_vec){170, 183, 184};
	colh[44] = (t_vec){66, 73, 73};
	colh[45] = (t_vec){234, 236, 238};
	colh3_init(colh);
}

void	ft_cb(t_vec *accum_color, t_vec uv)
{
	if (((int)(uv.x * 60) + (int)(uv.y * 60)) % 2 == 0)
	{
		accum_color->x = 0;
		accum_color->y = 0;
		accum_color->z = 0;
	}
	else
	{
		accum_color->x = 1;
		accum_color->y = 1;
		accum_color->z = 1;
	}
}
