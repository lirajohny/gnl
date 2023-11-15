#ifndef	GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
typedef struct s_list
{
	char *content;
	int	bytes_read;
	struct s_list *next;
}	t_list;
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif
#ifndef POINT
# define POINT 10
#endif

#define RESET   "\x1B[0m"
#define RED     "\x1B[31m"
#define GREEN   "\x1B[32m"
#define YELLOW  "\x1B[33m"
#define BLUE    "\x1B[34m"
#define MAGENTA "\x1B[35m"
#define CYAN    "\x1B[36m"
#define WHITE   "\x1B[37m"


char *get_next_line(int fd);
size_t	ft_strlen(char *s);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(char *content);
void ft_free(t_list **list);
char	*ft_strdup(char *s1);
#endif
