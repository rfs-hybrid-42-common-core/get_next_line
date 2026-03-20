*This project has been created as part of the 42 curriculum by maaugust.*

<div align="center">
  <img src="https://raw.githubusercontent.com/rfs-hybrid/42-Common-Core/main/assets/covers/cover-get_next_line-bonus.png" alt="get_next_line Cover" width="100%" />
</div>

<div align="center">
  <h1>📖 get_next_line: Reading a File Line by Line</h1>
  <img src="https://img.shields.io/badge/Language-C-blue" />
  <img src="https://img.shields.io/badge/Grade-125%2F100-success" />
  <img src="https://img.shields.io/badge/Norminette-Passing-success" />
</div>

---

## 💡 Description
**get_next_line (GNL)** is a project in the 42 curriculum that requires writing a function capable of reading a single line from a file descriptor (FD), returning it, and saving the remaining read bytes for the next call.

The goal of this project is to learn about **static variables**, **file descriptors**, and efficient **memory allocation** in C. 

This specific implementation goes beyond the standard requirements by implementing rigorous optimizations to prevent Time Limit Exceeded (TLE) errors and drastically reduce static memory consumption, while remaining robust against extreme `BUFFER_SIZE` variations.

---

## 📑 Features

### 🔹 Mandatory Features
* **Iterative Reading:** Repeatedly calling the function on the same file descriptor reads the text file one line at a time until the end-of-file (EOF) is reached.
* **Custom Buffer Sizes:** Functions correctly regardless of the `BUFFER_SIZE` defined at compile time (from as small as 1 byte to massive 10MB buffers).
* **Memory Safety:** Completely frees all heap-allocated memory upon reaching EOF or encountering a read error, ensuring zero memory leaks.

### 🚀 Bonus Features
* **Multiple File Descriptors:** Can manage and read from multiple FDs simultaneously without losing the reading thread of each descriptor.
* **Dynamic Pointer Management (Memory Optimization):** Instead of using a static 2D array (`static char buffer[1024][BUFFER_SIZE]`) which can cause gigabytes of BSS memory allocation on large buffer sizes, the bonus implementation uses a static array of pointers (`static char *buffer[FD_SIZE]`).

---

## 🧠 Algorithm & Data Structure

*Per the subject requirements, here is the justification for the architecture used in this project.*

### Data Structure: Static Array of Pointers
To manage multiple file descriptors in the bonus part, I utilized a static array of pointers (`static char *buffer[FD_SIZE];`). Unlike a standard 2D static array, this approach ensures that memory is only allocated on the heap when an FD is actively being read from. If an FD is never opened, it consumes zero buffer memory, drastically reducing the program's static footprint.

### Algorithm: In-Place Buffer Shifting
Standard `get_next_line` implementations often rely heavily on `ft_strjoin` and temporary buffers, causing massive O(N²) slowdowns and continuous `malloc`/`free` cycles on every read. This project takes a highly optimized alternative route:
1. **Dynamic Expansion:** The function uses a custom `ft_str_realloc` to expand the return line exactly to the size needed for the new parsed characters.
2. **In-Place Shift:** Instead of allocating a new string to save the leftover characters (the text *after* the `\n`), the algorithm uses `ft_strlcpy` to seamlessly slide the unparsed residual bytes to the front of the existing allocated static buffer.
3. **Reduced Allocations:** By shifting the memory inside the pre-allocated static buffer, the function drastically reduces the number of heap allocations per call, resulting in blazing-fast execution times that easily pass strict timeout tests.

---

## 🛠️ Instructions

### 💻 Usage
To use `get_next_line` in your code, simply include the appropriate header and compile your program with the corresponding source files.

#### 1. Mandatory (Single File Descriptor)
The mandatory version is optimized for reading sequentially from a single open file.

**Include header & write your `main.c`:**
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("test.txt", O_RDONLY);
    char *line;

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

**Compile:**
You must define the `BUFFER_SIZE` macro dynamically during compilation:
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
```

#### 2. Bonus (Multiple File Descriptors)
The bonus version utilizes a static array of pointers, allowing you to seamlessly alternate reading from multiple files without losing your place in any of them.

**Include bonus header & write your `main.c`:**
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;

    if (fd1 < 0 || fd2 < 0)
        return (1);

    // Read alternately from both files
    line = get_next_line(fd1);
    printf("FD1: %s", line);
    free(line);

    line = get_next_line(fd2);
    printf("FD2: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

**Compile with bonus files:**
Make sure to compile using the `_bonus.c` source files and the `_bonus.h` header!
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bonus.c get_next_line_utils_bonus.c
```

### 🧪 Testing
The 42 subject highly encourages creating test programs to verify your work before peer evaluations. 

**1. Using the Custom Tester (`gnl_tester.c`)**
This repository includes a custom, comprehensive tester that automatically creates dummy files, tests edge cases (empty files, no newlines, interleaved FDs), and cleans up after itself.
* **Test Mandatory:**
  ```bash
  cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 gnl_tester.c get_next_line.c get_next_line_utils.c -o tester
  ./tester
  ```
* **Test Bonus:**
  ```bash
  cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 gnl_tester.c get_next_line_bonus.c get_next_line_utils_bonus.c -o tester
  ./tester
  ```
*(Note: Try compiling with extreme `-D BUFFER_SIZE` values like `1` or `10000000` to test the robustness of the algorithm!)*

**2. Third-Party Testers (Francinette)**
Francinette is a widely used testing framework within the 42 community that runs strict tests (including memory leak checks and edge cases) against your logic.
* **Installation:** Follow the instructions on the [Francinette GitHub Repository](https://github.com/xicodomingues/francinette).
* **Usage:** Inside your repository root, run:
  ```bash
  paco
  ```
*(Note: To enforce strict norm and timeout rules, use `paco -s`)*

### 🚨 The Norm
Moulinette relies on a program called `norminette` to check if your files comply with the 42 Norm. Every single `.c` and `.h` file must pass this check. If there is a norm error, you will receive a 0.

**The 42 Header:**
Before writing any code, every file must start with the standard 42 header. `norminette` will automatically fail any file missing this specific signature.
```c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maaugust <maaugust@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:39:15 by maaugust          #+#    #+#             */
/*   Updated: 2025/05/26 16:00:10 by maaugust         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
```
Run the following command in the root of your repository to check all your files at once:
```bash
norminette -R CheckForbiddenSourceHeader
```

---

## 📚 Resources & References
* `man 2 read`
* `man 3 malloc`
* `man 3 free`
* [Static Variables in C](https://en.wikipedia.org/wiki/Static_variable)
* [42 Norm V4](https://cdn.intra.42.fr/pdf/pdf/96987/en.norm.pdf) - The strict coding standard for 42 C projects.
* [Official 42 Norminette Repository](https://github.com/42School/norminette) - The open-source linter enforcing the strict 42 coding standard.

### 🤖 AI Usage Guidelines
*Per the subject requirements:*
* **Tasks:** AI tools were used exclusively for generating portfolio-ready Doxygen comments, structuring the README template, and identifying potential memory footprint trade-offs regarding extreme `BUFFER_SIZE` edge cases.
* **Code:** The core iterative reading logic, pointer arithmetic, and custom string manipulation algorithms were entirely manually coded to ensure a fundamental understanding of C, memory management, and file descriptor operations.
