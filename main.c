
#include "fdf.h"
#include <stdio.h> //remove
t_mlx	*initialize_mlx_struct(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(*mlx))))
		return (NULL);
	mlx->color = 0xFFFF;
	mlx->height = WINDOW_HEIGHT;
	mlx->width = WINDOW_WIDTH;
	mlx->zoom = 5;
	return (mlx);
}

int	deal_key(int key, void *param)
{
	t_mlx	*mlx;
	mlx = param;
	if (key == 53)
	{
		exit(0);
	}
	return (0);
}

int	mouse_event(int button, int x, int y, void *param)
{
	t_mlx	*mlx;
	mlx = param;

	(void)x;
	(void)y;
	if (button == 4)
	{
		mlx->zoom--;
		mlx_clear_window(mlx->init, mlx->window);
		draw_map(mlx, mlx->s_map);
		printf("%d\n", mlx->zoom);
	}
	if (button == 5)
	{
		mlx->zoom++;
		mlx_clear_window(mlx->init, mlx->window);
		draw_map(mlx, mlx->s_map);
	}
	return (0);
}



int	main(int argc, char **argv)
{

	t_mlx	*mlx;
	t_map	*s_map;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (argc == 2)
	{
		s_map = (t_map *)malloc(sizeof(*s_map));
		make_map(argv[1], s_map);
	}
	else 
	{
		exit(0);
	}
	
	i = 0;
	j = 0;
	while (i < s_map->rows)
	{
		
		j = 0;
		while (j < s_map->cols)
		{
			printf("%3d", s_map->map[i][j]);
			j++;
		}
		printf("\n");
		i++;
		
	}
	
	mlx = initialize_mlx_struct();
	if (mlx == NULL)
		return (0);
	mlx->init = mlx_init();
	mlx->window = mlx_new_window(mlx->init, mlx->width, mlx->height, "Window");
	mlx->color = 0xFFFFFF;
	mlx->s_map = s_map;
	
	draw_map(mlx, mlx->s_map);
	//draw_line(mlx_ptr, win_ptr, 0, 0, 200, 200, 0xFFFFFF);
	mlx_hook(mlx->window, 2, 0, deal_key, mlx);
	mlx_hook(mlx->window, 4, 0, mouse_event, mlx);
	mlx_loop(mlx->init);
	return (0);
}
