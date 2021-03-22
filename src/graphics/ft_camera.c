/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youarzaz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 12:54:52 by youarzaz          #+#    #+#             */
/*   Updated: 2021/03/19 12:54:53 by youarzaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_rt.h"

void	ft_run_cam_builder(t_env *env)
{
	double theta;
	double viewport_height;
	double viewport_width;

	env->cam.normal = (t_vec){0, 1, 0};
	env->cam.aspect_ratio = (double)env->sdl.win_width
	/ (double)env->sdl.win_height;
	theta = env->cam.fov * (M_PI / 180);
	viewport_height = 2.0 * tan(theta / 2);
	viewport_width = env->cam.aspect_ratio * viewport_height;
	env->cam.normal = ft_rotate_axis_z(env->cam.normal,
	env->cam.angle * (M_PI / 180));
	env->cam.look_at.z += EPSILON;
	env->cam.w = ft_norm_vec(ft_sub_vec(env->cam.position, env->cam.look_at));
	env->cam.u = ft_norm_vec(ft_cross_vec(env->cam.normal, env->cam.w));
	env->cam.v = ft_cross_vec(env->cam.u, env->cam.w);
	env->cam.horizontal = ft_mult_vecs(ft_mult_vecs(env->cam.u,
	viewport_width), env->cam.focus_dist);
	env->cam.vertical = ft_mult_vecs(ft_mult_vecs(env->cam.v,
	viewport_height), env->cam.focus_dist);
	env->cam.lower_left_corner = ft_sub_vec(ft_sub_vec(
	ft_sub_vec(env->cam.position,
	ft_div_vecs(env->cam.horizontal, 2)), ft_div_vecs(env->cam.vertical, 2)),
	ft_mult_vecs(env->cam.w, env->cam.focus_dist));
	env->cam.lens_radius = env->cam.aperture / 2;
}

void	ft_make_camera_ray(t_ray *camera_ray,
t_camera camera, double u, double v)
{
	t_vec rd;
	t_vec offset;
	t_vec dir;

	rd = ft_mult_vecs(ft_random_in_unit_disk(), camera.lens_radius);
	offset = ft_add_vec(ft_mult_vecs(camera.u, rd.x),
	ft_mult_vecs(camera.v, rd.y));
	dir = ft_add_vec(camera.lower_left_corner,
	ft_add_vec(ft_mult_vecs(camera.horizontal, u),
	ft_mult_vecs(camera.vertical, v)));
	dir = ft_sub_vec(dir, camera.position);
	dir = ft_sub_vec(dir, offset);
	*camera_ray = (t_ray){ft_add_vec(camera.position, offset), dir};
}
