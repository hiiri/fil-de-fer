/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alcohen <alcohen@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 18:22:04 by alcohen           #+#    #+#             */
/*   Updated: 2020/02/27 16:13:25 by alcohen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_mlx			*initialize_mlx_struct(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(*mlx))))
		handle_error(ERROR_MALLOC);
	mlx->height = WINDOW_HEIGHT;
	mlx->width = WINDOW_WIDTH;
	mlx->zoom = ZOOM;
	mlx->x_offset = X_OFFSET;
	mlx->y_offset = Y_OFFSET;
	mlx->projection = 1;
	mlx->color = DEFAULT_COLOR;
	mlx->biggest_z = 0;
	mlx->smallest_z = 0;
	mlx->pitch = 0.1;
	mlx->mouse_x = 0;
	mlx->mouse_y = 0;
	mlx->mouse_pressed = 0;
	return (mlx);
}

int				deal_key(int key, void *param)
{
	t_mlx	*mlx;

	mlx = param;
	if (key == 53)
		exit(0);
	if (key == UP_ARROW)
		mlx->y_offset -= OFFSET_AMOUNT;
	else if (key == DOWN_ARROW)
		mlx->y_offset += OFFSET_AMOUNT;
	else if (key == LEFT_ARROW)
		mlx->x_offset -= OFFSET_AMOUNT;
	else if (key == RIGHT_ARROW)
		mlx->x_offset += OFFSET_AMOUNT;
	else if (key == CHANGE_PROJECTION)
		mlx->projection = !mlx->projection;
	else if (key == Q)
		mlx->pitch -= PITCH_CHANGE_AMOUNT;
	else if (key == W)
		mlx->pitch += PITCH_CHANGE_AMOUNT;
	mlx_clear_window(mlx->init, mlx->window);
	draw_map(mlx, mlx->s_map);
	return (0);
}

void			handle_error(int error)
{
	if (error == ERROR_ARGS)
		write(1, "Argument count must be 1\n", 25);
	else if (error == ERROR_MALLOC)
		write(1, "Malloc error\n", 13);
	else if (error == ERROR_READING_FILE)
		write(1, "Couldn't read file\n", 19);
	else if (error == ERROR_INVALID_MAP)
		write(1, "Invalid map\n", 12);
	exit(0);
}

static void		find_z_value_range(t_mlx *mlx, t_map *s_map)
{
	int	x;
	int y;

	x = 0;
	while (x < s_map->cols)
	{
		y = 0;
		while (y < s_map->rows)
		{
			if (s_map->map[y][x] < mlx->smallest_z)
				mlx->smallest_z = s_map->map[y][x];
			if (s_map->map[y][x] > mlx->biggest_z)
				mlx->biggest_z = s_map->map[y][x];
			y++;
		}
		x++;
	}
}

int				main(int argc, char **argv)
{
	t_mlx	*mlx;
	t_map	*s_map;

	if (argc != 2)
		handle_error(1);
	if (!(s_map = (t_map *)malloc(sizeof(*s_map))))
		handle_error(ERROR_MALLOC);
	make_map(argv[1], s_map);
	if (s_map->rows == 0)
		handle_error(ERROR_INVALID_MAP);
	mlx = initialize_mlx_struct();
	mlx->init = mlx_init();
	mlx->window = mlx_new_window(mlx->init, mlx->width, mlx->height, "Window");
	mlx->s_map = s_map;
	mlx->s_line = init_line();
	find_z_value_range(mlx, s_map);
	draw_map(mlx, mlx->s_map);
	mlx_hook(mlx->window, 2, 0, deal_key, mlx);
	mlx_hook(mlx->window, 4, 0, mouse_event, mlx);
	mlx_hook(mlx->window, 5, 0, mouse_release, mlx);
	mlx_hook(mlx->window, 6, 0, mouse_move, mlx);
	mlx_loop(mlx->init);
	return (0);
}
