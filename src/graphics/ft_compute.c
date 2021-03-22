/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_compute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-aza <moel-aza@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:22:16 by ouseqqam          #+#    #+#             */
/*   Updated: 2021/03/19 18:15:14 by moel-aza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_rt.h"

void	ft_compute(t_env *env)
{
	ft_run_cam_builder(env);
	ft_putendl("Camera Build Complet !");
	ft_run_builder(env->object_list);
	ft_putendl("Build Complet !");
	ft_run_raytracer(env);
	ft_putendl("Computed !");
}

t_vec	ft_compute_color(t_thread_param *data, t_intersect *intersect)
{
	t_vec accum_color;

	intersect->t = RAY_T_MAX;
	if (!ft_calc_intersect(data->env->object_list, -1, intersect))
		return (ft_mult_vecs(data->env->bg.main_color, data->env->bg.ambient));
	accum_color = intersect->object.main_color;
	if (intersect->object.image != NULL)
	{
		if (ft_texture(intersect, &accum_color))
			intersect->object.main_color = accum_color;
	}
	accum_color = ft_mult_vecs(accum_color, data->env->bg.ambient);
	if (intersect->object.blur && data->s == 0)
		intersect->object.pix =
		intersect_pixel(intersect->object.pix, data->res);
	if (intersect->object.reflect > 0)
		accum_color = ft_add_vec(accum_color,
		ft_compute_reflect(data, intersect, accum_color));
	if (intersect->object.refract > 0)
		accum_color = ft_add_vec(accum_color,
		ft_compute_refract(data, intersect, accum_color));
	ft_compute_light(data->env, intersect, &accum_color);
	return (accum_color);
}

void	ft_run_raytracer_thread2(t_thread_param *data, t_vec *render_color)
{
	float			u;
	float			v;
	t_intersect		intersect;

	u = (((double)data->j) + frand()) / (data->env->sdl.win_width - 1);
	v = (((double)data->i) + frand()) / (data->env->sdl.win_height - 1);
	ft_make_camera_ray(&intersect.ray, data->env->cam, u, v);
	data->u = u;
	data->v = v;
	data->res = data->env->sdl.win_width * data->i + data->j;
	data->depth = DEPTH;
	data->refract_depth = DEPTH;
	*render_color = ft_add_vec(*render_color,
	ft_compute_color(data, &intersect));
}

void	*ft_run_raytracer_thread(void *param)
{
	t_vec			render_color;
	t_thread_param	*data;

	data = (t_thread_param*)param;
	data->i = -1;
	while (++data->i < data->env->sdl.win_height)
	{
		data->j = data->offset - 1;
		while (++data->j < data->offset + data->env->sdl.win_width / NUM_THD)
		{
			render_color = (t_vec){0, 0, 0};
			data->s = -1;
			while (++data->s < data->env->samples)
				ft_run_raytracer_thread2(data, &render_color);
			data->data_out[data->env->sdl.win_width * data->i + data->j] =
			ft_correct_color(render_color, data->env->samples);
		}
	}
	pthread_exit(0);
}

void	ft_run_raytracer(t_env *env)
{
	int				id;
	pthread_t		tid[NUM_THD];
	t_thread_param	param[NUM_THD];

	id = -1;
	while (++id < NUM_THD)
	{
		param[id].env = env;
		param[id].data_out = env->data_out;
		param[id].offset = env->sdl.win_width / NUM_THD * id;
		pthread_create(&tid[id], NULL,
		ft_run_raytracer_thread, (void *)&param[id]);
	}
	while (--id >= 0)
		pthread_join(tid[id], NULL);
}
