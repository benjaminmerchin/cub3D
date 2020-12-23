#include <stdio.h>

int		get_t(int trgb)
{
	return (trgb & (0xFF << 24));
}

int		get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

int		get_g(int trgb)
{
	int tmp;

	trgb = trgb >> 8;
	tmp = trgb >> 8;
	tmp *= 256;
//	printf("%d\n", trgb);
	trgb -= tmp;
	return (trgb);
}

int		get_b(int trgb)
{
	return (trgb & 0xFF);
}

int		create_trgb(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

int main(void)
{
	int couleur = 123456;
	printf("%d\n", create_trgb(50, 50, 50, 50));
	printf("%d\n", get_g(3289650));

	return (0);
}
