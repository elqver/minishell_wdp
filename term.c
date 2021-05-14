#include <term.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int		ft_putchar(int c)
{
	write(1, &c, 1);
	return (c);
}

int		ft_putstr(char *s)
{
	while (*s)
		ft_putchar(*s++);
	return (0);
}

typedef struct			s_history
{
	char				*str;
	struct s_history	*next;
}						t_history;

void	print_history(t_history *i)
{
	if (i == NULL)
		ft_putstr("Input list is empty\n");
	while (i != NULL)
	{
		ft_putstr(i->str);
		i = i->next;
	}
}

t_history	*new_history_node(char *s)
{
	t_history	*new;

	new = malloc(sizeof(t_history));
	new->str = strdup(s);
	new->next = NULL;
	return (new);
}

t_history	*append_history(t_history **start, char *s)
{
	t_history	*ptr;

	if (*start == NULL)
	{
		*start = new_history_node(s);
		return (*start);
	}
	ptr = *start;
	while (ptr->next != NULL)
		ptr = ptr->next;
	ptr->next = new_history_node(s);
	return (*start);
}

int		read_escape_sequence(void)
{
	char	c;

	read(0, &c, 1);
	if (c == '[')
	{
		read(0, &c, 1);
		if (c == 'A')
			return (1);
		if (c == 'B')
			return (2);
	}
	return (0);
}

void	print_prompt()
{
	ft_putstr("ඞ ");
}

void	execute_escape_sequence(void)
{
	int	arrow;

	arrow = read_escape_sequence();
	if (arrow == 1)
	{
		tputs(delete_line, 1, ft_putchar);
		tputs(restore_cursor, 1, ft_putchar);
		print_prompt();
		ft_putstr("prev");
	}
	if (arrow == 2)
	{
		tputs(delete_line, 1, ft_putchar);
		tputs(restore_cursor, 1, ft_putchar);
		print_prompt();
		ft_putstr("next");
	}
}

char	*read_line(void)
{
	char		*input;
	size_t		size;
	size_t		wr; // was read
	int			new_line;

	print_prompt();
	size = 10;
	input = calloc(sizeof(char), size);
	wr = 0;
	new_line = 0;
	while (!new_line)
	{
		if (wr == size)
			input = realloc(input, size *= 2);
		read(0, &input[wr], 1);
		ft_putchar(input[wr]);
		input[wr + 1] = '\0';
		if (input[wr] == '\e')
			execute_escape_sequence();
		new_line = input[wr] == '\n';
		wr++;
	}
	input[wr - 1] = '\0';
	return (input);
}

void	terminal(void) // t_token, ...
{
	t_history	*history;
	char		*input;

	history = NULL;
	while (1)
	{
		tputs(save_cursor, 1, ft_putchar);
		input = read_line();
		append_history(&history, input);
		free(input);
	}
}

int		main(int ac, char **av, char **env)
{
	struct termios	term;
	char			*term_name;

	term_name = "xterm-256color";
	tcgetattr(0, &term);
	term.c_lflag &= ~(ECHO);
	term.c_lflag &= ~(ICANON);
	tcsetattr(0, TCSANOW, &term);
	tgetent(NULL, term_name);

	terminal();
}
