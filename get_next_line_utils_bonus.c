/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:39:26 by maaugust          #+#    #+#             */
/*   Updated: 2026/02/17 01:34:35 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/**
 * @fn size_t ft_strlen(const char *s)
 * @brief Calculates the length of a string.
 * @details Iterates through the character array until the null-terminator
 * is found.
 * @param s The string to evaluate.
 * @return The number of characters in the string before the null-terminator.
 */
size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

/**
 * @fn void ft_copy_chars(char *dst, const char *src, size_t size)
 * @brief Performs a fast, bounded copy of characters.
 * @details Replaces standard string copy logic to prevent O(N^2) slowdowns
 * caused by calculating the full length of the source string. It only copies
 * up to the requested size and then null-terminates the destination.
 * @param dst The destination buffer.
 * @param src The source string to copy from.
 * @param size The maximum number of characters to copy.
 */
void	ft_copy_chars(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

/**
 * @fn char *ft_str_realloc(char **str, size_t size)
 * @brief Dynamically expands a string to accommodate more characters.
 * @details If the string is NULL, it allocates a new buffer of the given size.
 * If the string exists, it allocates a larger buffer, copies the old contents,
 * and frees the previous memory location.
 * @param str A double pointer to the dynamically allocated string to expand.
 * @param size The additional number of characters the string needs to hold.
 * @return A pointer to the newly allocated and expanded string, or NULL
 * if memory allocation fails.
 */
char	*ft_str_realloc(char **str, size_t size)
{
	char	*new;
	size_t	len;

	if (!str || !*str)
	{
		new = (char *) malloc(sizeof(char) * (size + 1));
		if (!new)
			return (free(*str), NULL);
		*new = '\0';
	}
	else
	{
		len = ft_strlen(*str);
		new = (char *) malloc(sizeof(char) * (len + size + 1));
		if (!new)
			return (free(*str), NULL);
		ft_copy_chars(new, *str, len);
		free(*str);
		str = NULL;
	}
	return (new);
}
