#include "input.h"
#include <term.h>
#include <unistd.h>

int			ft_putchar(int c)
{
	return (write(1, &c, 1));
}

void		ft_putstr(char *s)
{
	while (*s)
		ft_putchar(*s++);
}

void		print_prompt(void)
{
	ft_putstr("🚢💥 ");
}

int			read_escape_sequence(void)
{
	char	c;

	read(0, &c, 1);
	if (c != '[')
		return (0);
	read(0, &c, 1);
	return ((int)(c - 64));
}

void		execute_escape_sequence(t_history **history, t_backup **backup, t_string **editing, int eseq)
{
	if (eseq == UP && (*history)->older != NULL)
	{
		if ((*history)->newer != NULL)
			push_backup(backup, *history);
		*history = (*history)->older;
	}
	else if (eseq == DOWN && (*history)->newer != NULL)
	{
		push_backup(backup, *history);
		*history = (*history)->newer;
	}
	*editing = (*history)->data;
}

void		user_interface(t_history *history)
{
	t_backup	*backup;
	t_string	*editing;
	char 		c;

	editing = new_string();
	printf("before push history\n");
	push_history(&history, NULL);
	printf("after push history\n");
	backup = NULL;
	c = 0;
	print_prompt();
	while (c != '\n')
	{
		read(0, &c, 1);
		if (c == '\e')
			execute_escape_sequence(&history, &backup, &editing, read_escape_sequence());
		else
			append_string(editing, c);
		tputs(delete_line, 1, ft_putchar);
		tputs(restore_cursor, 1, ft_putchar);
		print_prompt();
		ft_putstr(editing->string);
	}
	history = get_newest_entry(history);
	pop_string(editing);
	history->data = editing;
	clear_backup_list(backup);
}

void		terminal(void)
{
	char		*line_to_execute;
	t_history	*input_history;

	input_history = NULL;
	while (0xDEFEC8EDFACE)
	{
		tputs(save_cursor, 1, ft_putchar);
		user_interface(input_history);
	}
}

int			main(void)
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
