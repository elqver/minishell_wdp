#ifndef MAIN_HEADER_H
# define MAIN_HEADER_H

int		set_printing_flags(int new_val);
int		get_printing_flags(void);
void	main_loop(void);
void	print_help_message(void);
void	restore_original_file_descriptors(void);

#endif
