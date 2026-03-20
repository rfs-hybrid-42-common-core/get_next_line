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

This specific implementation goes beyond the standard requirements by implementing rigorous optimizations to prevent Time Limit Exceeded (TLE) errors and drastically reduce static memory consumption.

---

## 🚀 Features & Optimizations

### 🔹 Core Capabilities
* **Iterative Reading:** Repeatedly calling the function on the same file descriptor reads the text file one line at a time until the end-of-file (EOF) is reached.
* **Custom Buffer Sizes:** Functions correctly regardless of the `BUFFER_SIZE` defined at compile time (from as small as 1 byte to massive 10MB buffers).

### 🌟 Bonus Features
* **Multiple File Descriptors:** Can manage and read from multiple FDs simultaneously without losing the reading thread of each descriptor.
* **Dynamic Pointer Management (Memory Optimization):** Instead of using a static 2D array (`static char buffer[1024][BUFFER_SIZE]`) which can cause gigabytes of BSS memory allocation on large buffer sizes, the bonus implementation uses a static array of pointers (`static char *buffer[FD_SIZE]`). The actual buffers are dynamically allocated on the heap only when an FD is actively being read from, resulting in a microscopic static memory footprint.

### ⚡ Performance Optimization
* **Fast Buffer Copying:** Standard implementations often rely on `ft_strlcpy`, which calculates the full length of the source string on every call, causing massive O(N²) slowdowns on large buffers. This project implements a custom `ft_copy_chars` function that safely copies only the required bytes, resulting in blazing-fast execution times that easily pass strict evaluation timeout tests.

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
You can define the `BUFFER_SIZE` macro dynamically during compilation:

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

    // Read line 1 from file 1
    line = get_next_line(fd1);
    printf("FD1 - Line 1: %s", line);
    free(line);

    // Read line 1 from file 2
    line = get_next_line(fd2);
    printf("FD2 - Line 1: %s", line);
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

## 📚 Resources & References
* `man 2 read`
* `man 3 malloc`
* `man 3 free`
* [Static Variables in C](https://en.wikipedia.org/wiki/Static_variable)

### 🤖 AI Usage Guidelines
*Per the subject requirements:*
* **Tasks:** AI tools were used to generate portfolio-ready Doxygen comments, structure the README template, and identify optimization bottlenecks (such as O(N²) timeouts and static memory limits).
* **Code:** The core iterative reading logic and buffer management were originally manually coded. AI assistance was utilized to refactor the bonus architecture (implementing a dynamic array of pointers to resolve strict BSS memory limits) and to integrate the `ft_copy_chars` utility for strict Moulinette timeout compliance.
