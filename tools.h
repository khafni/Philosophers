#ifndef TOOLS_H
# define TOOLS_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);
void	*ft_mem_grow(void *addr, size_t old_size, size_t new_size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		strstr_modified(const char *haystack, const char *needle);
int		ft_atoi(const char *str);
void	ft_putnbr_fd(int n, int fd);
#endif