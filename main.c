
#include "fdf.h"
#include <stdio.h> //remove
t_mlx	*initialize_mlx_struct(void)
{
	t_mlx	*mlx;

	if (!(mlx = (t_mlx*)malloc(sizeof(*mlx))))
		return (NULL);
	mlx->x1 = 0;
	mlx->y1 = 0;
	mlx->y2 = 300;
	mlx->x2 = 300;
	mlx->color = 0xFFFF;
	return (mlx);
}

int	deal_key(int key, void *param)
{
	t_mlx	*mlx;
	mlx = param;
	if (key == 0)
	{
		draw_line(mlx->init, mlx->window, mlx->x1, mlx->y1, mlx->x2, mlx->y2, 0xFFFF);
		return (1);
	}
	else if (key == 126)
		mlx->y2--;
	else if (key == 125)
		mlx->y2++;
	else if (key == 123)
		mlx->x2--;
	else if (key == 124)
		mlx->x2++;
	draw_line(mlx->init, mlx->window, mlx->x1, mlx->y1, mlx->x2, mlx->y2, mlx->color++);
	return (1);
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
	printf("help");
	mlx->init = mlx_init();
	mlx->window = mlx_new_window(mlx->init, 500, 500, "Window");
	mlx->x1 = 200;
	mlx->y1 = 200;
	mlx->color = 0xFFFFFF;
	
	draw_map(mlx, s_map);
	//draw_line(mlx_ptr, win_ptr, 0, 0, 200, 200, 0xFFFFFF);
	mlx_hook(mlx->window, 2, 0, deal_key, mlx);
	mlx_loop(mlx->init);
	return (0);
}
