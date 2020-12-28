#include "mlx.h"
#include <unistd.h>

int main(void)
{
	void *mlx;
// 	void *window;
  
  	mlx = mlx_init();
	(void)mlx;
//  	window = mlx_new_window(mlx, 1000, 1000, "Title");
  
//  	mlx_loop(mlx);
	write(1, "1", 1);

  	return (0);
}
