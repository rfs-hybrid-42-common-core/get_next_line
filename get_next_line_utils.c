/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:39:26 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/20 15:23:36 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @fn char *free_memory(char **ptr)
 * @brief Helper function to safely free a pointer and set it to NULL.
 * @details Consolidates deallocation logic to prevent dangling pointers 
 * and memory leaks across multiple error-handling branches.
 * @param ptr Double pointer to the memory to be freed.
 * @return Always returns NULL.
 */
char	*free_memory(char **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	return (NULL);
}

/**
 * @fn size_t ft_strlen(const char *s)
 * @brief Calculates the length of a string.
 * @details Iterates through the string to find the terminating null byte 
 * ('\0').
 * @param s The string to measure.
 * @return  The number of characters preceding the terminating null byte.
 */
size_t	ft_strlen(const char *s)
{
	const char	*ptr;

	ptr = s;
	while (*ptr)
		ptr++;
	return (ptr - s);
}

/**
 * @fn size_t ft_strlcpy(char *dst, const char *src, size_t size)
 * @brief Size-bounded string copying.
 * @details Copies up to size - 1 characters from the NUL-terminated string src 
 * to dst, NUL-terminating the result.
 * @param dst  Destination buffer.
 * @param src  Source string.
 * @param size Size of the destination buffer.
 * @return     The total length of the string it tried to create (length of src).
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	i = 0;
	while (src[i] && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

/**
 * @fn char *ft_strchr(const char *s, int c)
 * @brief Locates the first occurrence of c (converted to a char) in the 
 * string s.
 * @details The terminating null character is considered to be part of the 
 * string; therefore if c is '\0', the functions locate the terminating '\0'.
 * @param s The string to search.
 * @param c The character to find.
 * @return  A pointer to the located character, or NULL if the character does 
 * not appear in the string.
 */
char	*ft_strchr(const char *s, int c)
{
	while (*s != (char)c)
	{
		if (!*s)
			return (NULL);
		s++;
	}
	return ((char *)s);
}

/**
 * @fn char *ft_str_realloc(char **s, size_t size)
 * @brief Dynamically expands a string to accommodate more characters.
 * @details If the string is NULL, it allocates a new buffer of the given size.
 * If the string exists, it allocates a larger buffer, copies the old contents,
 * and frees the previous memory location.
 * @param s    A double pointer to the dynamically allocated string to expand.
 * @param size The additional number of characters the string needs to hold.
 * @return A pointer to the newly allocated and expanded string, or NULL
 * if memory allocation fails.
 */
char	*ft_str_realloc(char **s, size_t size)
{
	char	*new;
	size_t	len;

	if (!s || !*s)
	{
		new = (char *) malloc(sizeof(char) * (size + 1));
		if (!new)
			return (free_memory(s));
		*new = '\0';
		return (new);
	}
	len = ft_strlen(*s);
	new = (char *) malloc(sizeof(char) * (len + size + 1));
	if (!new)
		return (free_memory(s));
	ft_strlcpy(new, *s, len + 1);
	free_memory(s);
	return (new);
}
