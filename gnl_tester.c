/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_tester.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 22:16:21 by maaugust          #+#    #+#             */
/*   Updated: 2026/03/20 22:16:27 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

/* Assuming the user compiles this with get_next_line.c or get_next_line_bonus.c */
char	*get_next_line(int fd);

/* ========================================================================== */
/* TOGGLE SWITCHES                                                            */
/* ========================================================================== */
#define TEST_MANDATORY
#define TEST_BONUS

/* ========================================================================== */
/* HELPER FUNCTIONS                                                           */
/* ========================================================================== */

/* Creates a temporary file with the given content */
static void	create_dummy_file(const char *filename, const char *content)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror("Error creating dummy file");
		return ;
	}
	if (content)
		write(fd, content, strlen(content));
	close(fd);
}

/* Runs a standard get_next_line loop on a single file descriptor */
static void	run_gnl_test(const char *test_name, const char *filename)
{
	int		fd;
	char	*line;
	int		line_count;

	printf("--- %s ---\n", test_name);
	fd = -1;
	if (filename)
		fd = open(filename, O_RDONLY);
	
	line_count = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: [%s]\n", line_count++, line);
		free(line);
	}
	printf("EOF or Error Reached. (Returned NULL)\n\n");
	
	if (fd >= 0)
		close(fd);
}

/* ========================================================================== */
/* MAIN FUNCTION                                                              */
/* ========================================================================== */
int	main(void)
{
	printf("============================================================\n");
	printf("                 GET_NEXT_LINE COMPREHENSIVE TESTER         \n");
	printf("============================================================\n\n");

#ifdef TEST_MANDATORY
	printf("======================= MANDATORY ==========================\n\n");

	/* Test 1: Normal Multiline File */
	create_dummy_file("test_normal.txt", "Hello World\nThis is 42\nPorto\n");
	run_gnl_test("Normal Multiline File", "test_normal.txt");

	/* Test 2: Empty File */
	create_dummy_file("test_empty.txt", "");
	run_gnl_test("Empty File", "test_empty.txt");

	/* Test 3: No Newline at EOF */
	create_dummy_file("test_no_nl.txt", "This line has no newline at the end");
	run_gnl_test("No Newline at EOF", "test_no_nl.txt");

	/* Test 4: Multiple Consecutive Newlines */
	create_dummy_file("test_nls.txt", "\n\nLine 3\n\n\nLine 6\n");
	run_gnl_test("Multiple Consecutive Newlines", "test_nls.txt");

	/* Test 5: Invalid File Descriptor */
	run_gnl_test("Invalid File Descriptor (-1)", NULL);

	/* Cleanup Dummy Files */
	unlink("test_normal.txt");
	unlink("test_empty.txt");
	unlink("test_no_nl.txt");
	unlink("test_nls.txt");
#endif

#ifdef TEST_BONUS
	printf("========================= BONUS ============================\n\n");

	/* Create 3 files for interleaving */
	create_dummy_file("bonus_1.txt", "File 1 - Line 1\nFile 1 - Line 2\nFile 1 - Line 3\n");
	create_dummy_file("bonus_2.txt", "File 2 - Line 1\nFile 2 - Line 2\n");
	create_dummy_file("bonus_3.txt", "File 3 - Line 1\nFile 3 - Line 2\nFile 3 - Line 3\nFile 3 - Line 4\n");

	printf("--- Interleaved File Descriptors ---\n");
	int fd1 = open("bonus_1.txt", O_RDONLY);
	int fd2 = open("bonus_2.txt", O_RDONLY);
	int fd3 = open("bonus_3.txt", O_RDONLY);
	char *l1, *l2, *l3;

	/* Interleave calls */
	l1 = get_next_line(fd1); printf("FD1: [%s]\n", l1 ? l1 : "NULL"); free(l1);
	l2 = get_next_line(fd2); printf("FD2: [%s]\n", l2 ? l2 : "NULL"); free(l2);
	l3 = get_next_line(fd3); printf("FD3: [%s]\n", l3 ? l3 : "NULL"); free(l3);
	
	l1 = get_next_line(fd1); printf("FD1: [%s]\n", l1 ? l1 : "NULL"); free(l1);
	l2 = get_next_line(fd2); printf("FD2: [%s]\n", l2 ? l2 : "NULL"); free(l2);
	l3 = get_next_line(fd3); printf("FD3: [%s]\n", l3 ? l3 : "NULL"); free(l3);
	
	l1 = get_next_line(fd1); printf("FD1: [%s]\n", l1 ? l1 : "NULL"); free(l1);
	l2 = get_next_line(fd2); printf("FD2: [%s]\n", l2 ? l2 : "NULL"); free(l2);
	l3 = get_next_line(fd3); printf("FD3: [%s]\n", l3 ? l3 : "NULL"); free(l3);
	
	l3 = get_next_line(fd3); printf("FD3: [%s]\n", l3 ? l3 : "NULL"); free(l3);

	close(fd1); close(fd2); close(fd3);

	/* Cleanup Dummy Files */
	unlink("bonus_1.txt");
	unlink("bonus_2.txt");
	unlink("bonus_3.txt");
	printf("\nDummy files cleaned up.\n");
#endif

	return (0);
}
