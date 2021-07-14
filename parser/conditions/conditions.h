#ifndef CONDITIONS_H
# define CONDITIONS_H

int	word_symbol_condition(char c);

int	single_quote_condition(char c);
int	not_single_quote_condition(char c);
int	double_quote_condition(char c);
int	not_double_quote_condition(char c);

int	left_redir_condition(char c);
int	right_redir_condition(char c);

int	pipe_condition(char c);

int	space_condition(char c);

int	dollar_condition(char c);
int	question_mark_condition(char c);
int	letter_underscore_condition(char c);
int	letter_digit_underscore_condition(char c);

#endif
