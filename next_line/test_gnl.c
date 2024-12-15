#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "get_next_line.h"

void test_basic_file(void) {
    printf("\n=== Test 1: Basic file reading ===\n");
    int fd = open("test1.txt", O_RDONLY);
    if (fd < 0) {
        printf("Error opening file\n");
        return;
    }

    char *line;
    int line_count = 0;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Line %d: %s", ++line_count, line);
        free(line);
    }
    close(fd);
}

void test_empty_file(void) {
    printf("\n=== Test 2: Empty file ===\n");
    int fd = open("empty.txt", O_RDONLY);
    if (fd < 0) {
        printf("Error opening file\n");
        return;
    }

    char *line = get_next_line(fd);
    if (line == NULL)
        printf("Successfully handled empty file\n");
    else {
        printf("Failed: got content from empty file\n");
        free(line);
    }
    close(fd);
}

void test_no_newline(void) {
    printf("\n=== Test 3: File without newline at end ===\n");
    int fd = open("no_newline.txt", O_RDONLY);
    if (fd < 0) {
        printf("Error opening file\n");
        return;
    }

    char *line;
    while ((line = get_next_line(fd)) != NULL) {
        printf("Read: %s", line);
        free(line);
    }
    close(fd);
}

void test_long_line(void) {
    printf("\n=== Test 4: Long line ===\n");
    // Create a file with a very long line
    FILE *fp = fopen("long_line.txt", "w");
    for (int i = 0; i < 1000; i++)
        fprintf(fp, "abcdefghij");
    fprintf(fp, "\n");
    fclose(fp);

    int fd = open("long_line.txt", O_RDONLY);
    char *line = get_next_line(fd);
    if (line) {
        printf("Successfully read long line of length: %lu\n", strlen(line));
        free(line);
    }
    close(fd);
}

void test_multiple_fd(void) {
    printf("\n=== Test 5: Multiple file descriptors ===\n");
    int fd1 = open("test1.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_RDONLY);
    
    char *line1 = get_next_line(fd1);
    printf("FD1 - Line 1: %s", line1);
    free(line1);

    char *line2 = get_next_line(fd2);
    printf("FD2 - Line 1: %s", line2);
    free(line2);

    line1 = get_next_line(fd1);
    printf("FD1 - Line 2: %s", line1);
    free(line1);

    close(fd1);
    close(fd2);
}

void test_invalid_fd(void) {
    printf("\n=== Test 6: Invalid file descriptor ===\n");
    char *line = get_next_line(-1);
    if (line == NULL)
        printf("Successfully handled invalid fd\n");
    else {
        printf("Failed: got content from invalid fd\n");
        free(line);
    }
}

void create_test_files(void) {
    // Create test1.txt
    FILE *fp = fopen("test1.txt", "w");
    fprintf(fp, "First line\nSecond line\nThird line\n");
    fclose(fp);

    // Create test2.txt
    fp = fopen("test2.txt", "w");
    fprintf(fp, "File 2 - Line 1\nFile 2 - Line 2\n");
    fclose(fp);

    // Create empty.txt
    fp = fopen("empty.txt", "w");
    fclose(fp);

    // Create no_newline.txt
    fp = fopen("no_newline.txt", "w");
    fprintf(fp, "This file ends without a newline");
    fclose(fp);
}

int main(void) {
    printf("Starting Get Next Line tests...\n");
    
    create_test_files();
    
    test_basic_file();
    test_empty_file();
    test_no_newline();
    test_long_line();
    test_multiple_fd();
    test_invalid_fd();

    printf("\nAll tests completed!\n");
    return 0;
}
