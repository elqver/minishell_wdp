#include "ast.h"

static void	print_tab(int pref_len)
{
	int	p;

	p = pref_len;
	white_color();
	write(1, "|", 1);
	while (pref_len--)
		write(1, "\t|", 2);
	choose_color(p);
}

static void	_print_ast(t_ast *root, int pref_len)
{
	if (root == NULL)
		return ;
	print_tab(pref_len);
	white_color();
	printf("Node data: %s\n", root->data);
	choose_color(pref_len);
	if (root->right != NULL)
	{
		print_tab(pref_len);
		printf("RIGHT {\n");
		_print_ast(root->right, pref_len + 1);
		print_tab(pref_len);
		printf("}\n");
	}
	choose_color(pref_len);
	if (root->left != NULL)
	{
		print_tab(pref_len);
		printf("LEFT {\n");
		_print_ast(root->left, pref_len + 1);
		print_tab(pref_len);
		printf("}\n");
	}
	white_color();
}

void	print_ast(t_ast *root)
{
	_print_ast(root, 0);
}
