/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:39:15 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/17 01:32:46 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @fn static ssize_t read_line(int fd, char *buffer, char **new_line)
 * @brief Reads data from the file descriptor into the static buffer.
 * @details Handles the `read` system call, ensuring the buffer is properly
 * null-terminated. If an error occurs during reading, it frees the partially
 * constructed line to prevent memory leaks.
 * @param fd The file descriptor to read from.
 * @param buffer The static character array storing residual read bytes.
 * @param new_line A double pointer to the dynamically allocated return string.
 * @return The number of bytes read, 0 if end-of-file (EOF) or invalid FD,
 * or -1 if a read error occurs.
 */
static ssize_t	read_line(int fd, char *buffer, char **new_line)
{
	ssize_t	n_bytes;

	if (fd < 0 || fd >= FD_SIZE || BUFFER_SIZE <= 0)
		return (0);
	if (*buffer)
		return (ft_strlen(buffer));
	n_bytes = read(fd, buffer, BUFFER_SIZE);
	if (n_bytes > 0)
		buffer[n_bytes] = '\0';
	if (n_bytes < 0 && *new_line)
	{
		free (*new_line);
		*new_line = NULL;
	}
	return (n_bytes);
}

/**
 * @fn char *get_next_line(int fd)
 * @brief Extracts the next line of text from a given file descriptor.
 * @details Repeatedly reads from the file descriptor and appends the characters
 * to a string until a newline character ('\n') or EOF is encountered. The
 * remaining bytes read past the newline are preserved in a static buffer
 * for the next function call.
 * @param fd The file descriptor to read from.
 * @return A dynamically allocated string containing the extracted line
 * (including the newline), or NULL if there is nothing else to read or an
 * error occurs.
 */
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*new_line;
	ssize_t		n_bytes;
	size_t		len;
	int			i;

	new_line = NULL;
	n_bytes = read_line(fd, buffer, &new_line);
	while (n_bytes > 0)
	{
		i = 0;
		while (i < n_bytes && buffer[i] && buffer[i++] != '\n')
			;
		new_line = ft_str_realloc(&new_line, i);
		if (!new_line)
			break ;
		len = ft_strlen(new_line);
		ft_copy_chars(new_line + len, buffer, i);
		ft_copy_chars(buffer, buffer + i, n_bytes - i);
		len += i;
		if (len > 0 && new_line[len - 1] == '\n')
			break ;
		n_bytes = read_line(fd, buffer, &new_line);
	}
	return (new_line);
}
