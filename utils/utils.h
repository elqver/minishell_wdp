#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>

char		**ft_split(char const *s, char c);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isdigit(int c);
char		*ft_strdup(const char *s1);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlen(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
void		*ft_memcpy(void *dst, const void *src, size_t n);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
void		*ft_memmove(void *dst, const void *src, size_t len);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strchr(const char *s, int c);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strndup(const char *s, size_t n);

#endif 
