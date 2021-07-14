#include "ast.h"

static void	red_color(void)
{
	write(1, "\033[0;31m", 7);
}

static void	yellow_color(void)
{
	write(1, "\033[0;33m", 7);
}

static void	green_color(void)
{
	write(1, "\033[0;32m", 7);
}

void	white_color(void)
{
	write(1, "\033[0;37m", 7);
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
