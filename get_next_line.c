/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:39:15 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/20 21:57:11 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @fn static ssize_t read_line(int fd, char **buffer, char **new_line)
 * @brief Reads data from the file descriptor into a dynamically allocated 
 * buffer.
 * @details Manages heap allocation for the specific file descriptor's buffer. 
 * If reading returns EOF or an error, it cleanly frees the buffer and the 
 * partial line to prevent memory leaks across multiple FDs.
 * @param fd The file descriptor to read from.
 * @param buffer Double pointer to the specific FD's residual buffer.
 * @param new_line A double pointer to the dynamically allocated return string.
 * @return The number of bytes read, 0 if EOF or invalid FD, or -1 on error.
 */
static ssize_t	read_line(int fd, char **buffer, char **new_line)
{
	ssize_t	n_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!*buffer)
	{
		*buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!*buffer)
			return (-1);
		**buffer = '\0';
	}
	if (**buffer)
		return (ft_strlen(*buffer));
	n_bytes = read(fd, *buffer, BUFFER_SIZE);
	if (n_bytes > 0)
	{
		(*buffer)[n_bytes] = '\0';
		return (n_bytes);
	}
	if (n_bytes < 0 && *new_line)
		free_memory(new_line);
	free_memory(buffer);
	return (n_bytes);
}

/**
 * @fn char *get_next_line(int fd)
 * @brief Extracts and returns the next line of text from a file descriptor.
 * @details Repeated calls to this function allow reading a text file pointed 
 * to by the file descriptor, one line at a time. It handles dynamic memory 
 * allocation to read in chunks based on the BUFFER_SIZE macro. The function 
 * seamlessly shifts unparsed residual data and properly frees memory upon 
 * reaching EOF or encountering a read error to prevent leaks.
 * @param fd The file descriptor to read from.
 * @return A dynamically allocated string containing the extracted line, 
 * or NULL if there is nothing else to read or an error occurs.
 */
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*new_line;
	ssize_t		n_bytes;
	int			i;

	new_line = NULL;
	n_bytes = read_line(fd, &buffer, &new_line);
	while (n_bytes > 0)
	{
		i = 0;
		while (i < n_bytes && buffer[i] && buffer[i++] != '\n')
			;
		new_line = ft_str_realloc(&new_line, i);
		if (!new_line)
			return (free_memory(&buffer));
		ft_strlcpy(new_line + ft_strlen(new_line), buffer, i + 1);
		ft_strlcpy(buffer, buffer + i, n_bytes - i + 1);
		if (ft_strchr(new_line, '\n'))
			break ;
		n_bytes = read_line(fd, &buffer, &new_line);
	}
	if (buffer && buffer[0] == '\0')
		free_memory(&buffer);
	return (new_line);
}
