#include "ast.h"

static void	red_color(void)
{
	printf("\033[0;31m");
}

static void	yellow_color(void)
{
	printf("\033[0;33m");
}

static void	green_color(void)
{
	printf("\033[0;32m");
}

void	white_color(void)
{
	printf("\033[0;37m");
}

void	choose_color(int prefix_len)
{
	if (prefix_len % 3 == 0)
		green_color();
	else if (prefix_len % 3 == 1)
		red_color();
	else
		yellow_color();
}
