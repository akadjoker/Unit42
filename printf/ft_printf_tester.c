#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "ft_printf.h"

#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define YELLOW "\033[0;33m"
#define RESET "\033[0m"

int test_count = 0;
int tests_passed = 0;

void print_result(int original_ret, int ft_ret, const char *test_name)
{
    test_count++;
    if (original_ret == ft_ret)
    {
        printf(GREEN "✓ %s" RESET " (returned %d)\n", test_name, ft_ret);
        tests_passed++;
    }
    else
        printf(RED "✗ %s" RESET " (printf: %d, ft_printf: %d)\n", 
               test_name, original_ret, ft_ret);
}

void test_mandatory(void)
{
    int ret1, ret2;

    printf(YELLOW "\n=== Testing Mandatory Part ===\n" RESET);

    // Test %c
    ret1 = printf("printf:    Hello %c World\n", 'A');
    ret2 = ft_printf("ft_printf: Hello %c World\n", 'A');
    print_result(ret1, ret2, "Basic char test");

    // Test %s
    ret1 = printf("printf:    %s\n", "Hello World");
    ret2 = ft_printf("ft_printf: %s\n", "Hello World");
    print_result(ret1, ret2, "Basic string test");

    ret1 = printf("printf:    %s\n", "");
    ret2 = ft_printf("ft_printf: %s\n", "");
    print_result(ret1, ret2, "Empty string test");

    // Test %p
    int num = 42;
    ret1 = printf("printf:    %p\n", (void *)&num);
    ret2 = ft_printf("ft_printf: %p\n", (void *)&num);
    print_result(ret1, ret2, "Pointer test");

    // Test %d and %i
    ret1 = printf("printf:    %d, %i\n", 42, -42);
    ret2 = ft_printf("ft_printf: %d, %i\n", 42, -42);
    print_result(ret1, ret2, "Integer test");

    ret1 = printf("printf:    %d\n", INT_MAX);
    ret2 = ft_printf("ft_printf: %d\n", INT_MAX);
    print_result(ret1, ret2, "INT_MAX test");

    ret1 = printf("printf:    %d\n", INT_MIN);
    ret2 = ft_printf("ft_printf: %d\n", INT_MIN);
    print_result(ret1, ret2, "INT_MIN test");

    // Test %u
    ret1 = printf("printf:    %u\n", UINT_MAX);
    ret2 = ft_printf("ft_printf: %u\n", UINT_MAX);
    print_result(ret1, ret2, "Unsigned int test");

    // Test %x and %X
    ret1 = printf("printf:    %x, %X\n", 42, 42);
    ret2 = ft_printf("ft_printf: %x, %X\n", 42, 42);
    print_result(ret1, ret2, "Hexadecimal test");

    // Test %%
    ret1 = printf("printf:    %%\n");
    ret2 = ft_printf("ft_printf: %%\n");
    print_result(ret1, ret2, "Percent sign test");

    // Test multiple conversions
    ret1 = printf("printf:    %c %s %p %d %i %u %x %X %%\n", 
                  'A', "test", (void *)&num, 42, -42, 42, 42, 42);
    ret2 = ft_printf("ft_printf: %c %s %p %d %i %u %x %X %%\n", 
                     'A', "test", (void *)&num, 42, -42, 42, 42, 42);
    print_result(ret1, ret2, "Multiple conversion test");
}

void test_bonus(void)
{
    int ret1, ret2;

    printf(YELLOW "\n=== Testing Bonus Part ===\n" RESET);

    // Test minimum field width
    ret1 = printf("printf:    |%10s|\n", "hello");
    ret2 = ft_printf("ft_printf: |%10s|\n", "hello");
    print_result(ret1, ret2, "Field width test");

    // Test left-justify flag (-)
    ret1 = printf("printf:    |%-10s|\n", "hello");
    ret2 = ft_printf("ft_printf: |%-10s|\n", "hello");
    print_result(ret1, ret2, "Left-justify test");

    // Test zero-padding flag (0)
    ret1 = printf("printf:    |%010d|\n", 42);
    ret2 = ft_printf("ft_printf: |%010d|\n", 42);
    print_result(ret1, ret2, "Zero-padding test");

    // Test precision (.)
    ret1 = printf("printf:    |%.5s|\n", "hello world");
    ret2 = ft_printf("ft_printf: |%.5s|\n", "hello world");
    print_result(ret1, ret2, "Precision test");

    // Test hash flag (#)
    ret1 = printf("printf:    |%#x| |%#X|\n", 42, 42);
    ret2 = ft_printf("ft_printf: |%#x| |%#X|\n", 42, 42);
    print_result(ret1, ret2, "Hash flag test");

    // Test space flag
    ret1 = printf("printf:    |% d|\n", 42);
    ret2 = ft_printf("ft_printf: |% d|\n", 42);
    print_result(ret1, ret2, "Space flag test");

    // Test plus flag (+)
    ret1 = printf("printf:    |%+d|\n", 42);
    ret2 = ft_printf("ft_printf: |%+d|\n", 42);
    print_result(ret1, ret2, "Plus flag test");

    // Test combinations
    ret1 = printf("printf:    |%+10.5d|\n", 42);
    ret2 = ft_printf("ft_printf: |%+10.5d|\n", 42);
    print_result(ret1, ret2, "Combined flags test");
}

int main(int argc, char **argv)
{
    printf(YELLOW "Starting ft_printf tests...\n" RESET);

    if (argc == 1 || strcmp(argv[1], "mandatory") == 0)
        test_mandatory();
    
    if (argc > 1 && strcmp(argv[1], "bonus") == 0)
    {
        test_mandatory();
        test_bonus();
    }

    printf(YELLOW "\nTest Summary:\n" RESET);
    printf("Tests passed: %d/%d (%.2f%%)\n", 
           tests_passed, test_count, 
           (float)tests_passed / test_count * 100);

    return (0);
}
