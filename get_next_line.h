/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:38:46 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/22 05:40:12 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/* ========================================================================== */
/* INCLUDES                                                                   */
/* ========================================================================== */

/* --------------------------- Internal Libraries --------------------------- */
# include <unistd.h>
# include <stdlib.h>

/* ========================================================================== */
/* MACROS                                                                     */
/* ========================================================================== */

/**
 * @def BUFFER_SIZE
 * @brief Defines the number of bytes to read from the file descriptor per 
 * read() call. Can be overridden at compile time using the -D flag.
 */
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

/* ========================================================================== */
/* FUNCTIONS                                                                  */
/* ========================================================================== */

/* ----------------------------- Main Function ------------------------------ */
char	*get_next_line(int fd);

/* --------------------------- Utility Functions ---------------------------- */
char	*free_memory(char **ptr);
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_strchr(const char *s, int c);
char	*ft_str_realloc(char **s, size_t size);

#endif
