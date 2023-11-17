/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlira <jlira@student.42.rj>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 19:58:37 by jlira             #+#    #+#             */
/*   Updated: 2023/11/17 11:26:24 by jlira            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> 
#include <unistd.h> 
#include "get_next_line.h"

int	find_line(char *str)
{
	int	index;

	index = 0;
	if (str[0] == '\n')
		return (0);
	while (str[index] != '\0')
	{
		if (str[index] == '\n')
			return (index);
		index++;
	}
	return (0);
}

static char	*remain_line(char *content, int line)
{
	size_t	i;
	char	*new_remain;
	size_t	count;

	i = 0;
	while (content[i] && content[i] != '\n')
		i++;
	if (!(content[i]))
		return (NULL);
	if (content[i] == '\n')
		line = i++;
	new_remain = (char *)malloc(sizeof(char) * ft_strlen(content) - i + 1);
	if (!(new_remain))
		return (NULL);
	count = 0;
	while (content[i])
	{
		new_remain[count++] = content[i];
		i++;
	}
	new_remain[count] = '\0';
	if (line != -1)
		content[line + 1] = '\0';
	return (new_remain);
}

char	*ft_get_line(struct s_list **list, int i, int j)
{
	t_list	*current;
	char	*result;
	int		len;

	len = 0;
	current = *list;
	if (current->next->content == NULL)
		return (NULL);
	while (current->next != NULL)
	{
		len += ft_strlen(current->content);
		current = current->next;
	}
	len = len + find_line(current->content) + 1;
	result = (char *)malloc(len + 1);
	current = *list;
	while (i + 1 <= len)
	{
		j = 0;
		while (current->content[j] != '\0' && i + 1 <= len)
			result[i++] = current->content[j++];
		current = current->next;
	}
	result[i] = '\0';
	return (result);
}

int	read_file(t_list **list, int fd)
{
	t_list	*new;
	char	buffer[BUFFER_SIZE + 1];

	new = *list;
	if (new->content[0] == '\n' || find_line(new->content) > 0)
		return (-1);
	while (1)
	{
		new->bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (new->bytes_read == 0)
			return (-2);
		buffer[new->bytes_read] = '\0';
		if (find_line(buffer) > 0 || buffer[0] == '\n')
		{
			new->next = ft_lstnew(buffer, 0);
			break ;
		}
		new->next = ft_lstnew(buffer, 0);
		new = new->next;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	t_list		*head;
	char		*next_line;
	static char	*remain;
	t_list		*last;
	static int			check_error;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0 || check_error == -2 )
		return (NULL);
	head = ft_lstnew(remain, 1);
	check_error = read_file(&head, fd);
	last = ft_lstlast(head);
	if (check_error == -2)
	{
		ft_free(&head);
		return (NULL);
	}
	remain = remain_line(last->content, -1);
	if (check_error != 0)
		next_line = ft_strdup(last->content);
	else
		next_line = ft_get_line(&head, 0, 0);
	ft_free(&head);
	return (next_line);
}
