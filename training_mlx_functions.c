#include "mlx.h"
#include <unistd.h>

int main(void)
{
	void *mlx;
	void *window;
  
	write(1, "124", 3);
  	mlx = mlx_init();
//	(void)mlx;
	window = mlx_new_window(mlx, 400, 400, "Title");
	mlx_loop(mlx);
	write(1, "1", 1);

//	free(mlx);
  	return (0);
}
