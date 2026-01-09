#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

#define BORDER "-------------------------------------\n"

// ANSI Colors
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define BLUE    "\033[0;34m"
#define BOLD    "\033[1m"
#define RESET   "\033[0m"

// Test counters
static int g_tests_passed = 0;
static int g_tests_failed = 0;

size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);

void test_strlen();
void test_strcpy();
void test_strcmp();
void test_write();
void test_read();
void test_strdup();

// Helper functions
void print_header(const char *function_name) {
	printf("\n" BORDER);
	printf(BOLD BLUE "Testing %s" RESET "\n", function_name);
	printf(BORDER);
}

void check_size(size_t expected, size_t actual, const char *description) {
	if (expected == actual) {
		printf(GREEN "[PASS]" RESET " %s: expected %zu, got %zu\n", description, expected, actual);
		g_tests_passed++;
	} else {
		printf(RED "[FAIL]" RESET " %s: expected %zu, got %zu\n", description, expected, actual);
		g_tests_failed++;
	}
}

void check_int(int expected, int actual, const char *description) {
	if (expected == actual) {
		printf(GREEN "[PASS]" RESET " %s: expected %d, got %d\n", description, expected, actual);
		g_tests_passed++;
	} else {
		printf(RED "[FAIL]" RESET " %s: expected %d, got %d\n", description, expected, actual);
		g_tests_failed++;
	}
}

void check_str(const char *expected, const char *actual, const char *description) {
	if (strcmp(expected, actual) == 0) {
		printf(GREEN "[PASS]" RESET " %s: expected \"%s\", got \"%s\"\n", description, expected, actual);
		g_tests_passed++;
	} else {
		printf(RED "[FAIL]" RESET " %s: expected \"%s\", got \"%s\"\n", description, expected, actual);
		g_tests_failed++;
	}
}

void check_ssize(ssize_t expected, ssize_t actual, const char *description) {
	if (expected == actual) {
		printf(GREEN "[PASS]" RESET " %s: expected %zd, got %zd\n", description, expected, actual);
		g_tests_passed++;
	} else {
		printf(RED "[FAIL]" RESET " %s: expected %zd, got %zd\n", description, expected, actual);
		g_tests_failed++;
	}
}

void check_bool(int condition, const char *description) {
	if (condition) {
		printf(GREEN "[PASS]" RESET " %s\n", description);
		g_tests_passed++;
	} else {
		printf(RED "[FAIL]" RESET " %s\n", description);
		g_tests_failed++;
	}
}

void check_strcmp_sign(int std_result, int ft_result, const char *description) {
	int signs_match = (std_result == 0 && ft_result == 0) ||
	                  (std_result > 0 && ft_result > 0) ||
	                  (std_result < 0 && ft_result < 0);
	if (signs_match) {
		printf(GREEN "[PASS]" RESET " %s: strcmp=%d, ft_strcmp=%d (signs match)\n", 
		       description, std_result, ft_result);
		g_tests_passed++;
	} else {
		printf(RED "[FAIL]" RESET " %s: strcmp=%d, ft_strcmp=%d (signs differ!)\n", 
		       description, std_result, ft_result);
		g_tests_failed++;
	}
}

// Wrapper functions for register preservation tests
static char g_test_str[] = "test";
static char g_test_buf[50];

void wrapper_strlen(void) { ft_strlen(g_test_str); }
void wrapper_strcpy(void) { ft_strcpy(g_test_buf, g_test_str); }
void wrapper_strcmp(void) { ft_strcmp(g_test_str, g_test_str); }
void wrapper_write(void) { ft_write(1, "", 0); }
void wrapper_read(void) { ft_read(-1, g_test_buf, 0); }
void wrapper_strdup(void) { char *p = ft_strdup(g_test_str); if(p) free(p); }

void check_rbx_preserved(void (*func_ptr)(void), const char *description) {
	const unsigned long canary = 0xDEADBEEFCAFEBABE;
	unsigned long rbx_after;
	
	// Single asm block: set canary, call function, read result
	__asm__ volatile (
		"movq %[canary], %%rbx\n\t"
		"callq *%[func]\n\t"
		"movq %%rbx, %[after]"
		: [after] "=r" (rbx_after)
		: [canary] "r" (canary), [func] "r" (func_ptr)
		: "rbx", "rax", "rcx", "rdx", "rsi", "rdi", 
		  "r8", "r9", "r10", "r11", "memory", "cc"
	);
	
	if (rbx_after == canary) {
		printf(GREEN "[PASS]" RESET " %s: rbx preserved (0x%lx)\n", description, rbx_after);
		g_tests_passed++;
	} else {
		printf(RED "[FAIL]" RESET " %s: rbx corrupted (expected 0x%lx, got 0x%lx)\n", 
			description, canary, rbx_after);
		g_tests_failed++;
	}
}

void print_summary() {
	int total = g_tests_passed + g_tests_failed;
	printf("\n");
	printf("=====================================\n");
	printf(BOLD "        TEST SUMMARY" RESET "\n");
	printf("=====================================\n");
	printf(GREEN "  Passed: %d" RESET "\n", g_tests_passed);
	if (g_tests_failed > 0)
		printf(RED "  Failed: %d" RESET "\n", g_tests_failed);
	else
		printf("  Failed: 0\n");
	printf("  Total:  %d\n", total);
	printf("=====================================\n");
}

int main() {
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
	print_summary();
	return 0;
}

void test_strlen() {
	char *str1 = "Hello, World!";
	char *str2 = "";
	char *str3 = "This is a much longer string to test loop correctness and ensure the function handles strings with many characters without issues. 100+ chars!";
	char *str4 = "Tabs\tand\nnewlines\tand  spaces";

	print_header("ft_strlen");
	check_size(strlen(str1), ft_strlen(str1), "ft_strlen(\"Hello, World!\")");
	check_size(strlen(str2), ft_strlen(str2), "ft_strlen(\"\")");
	check_size(strlen(str3), ft_strlen(str3), "ft_strlen(long string)");
	check_size(strlen(str4), ft_strlen(str4), "ft_strlen(special chars)");
	
	// Register preservation test
	printf("\n  Register preservation test:\n");
	check_rbx_preserved(wrapper_strlen, "ft_strlen");
}


void test_strcpy() {
	char *src1 = "TESTING";
	char dest1[50];
	char dest2[50];

	print_header("ft_strcpy");

	strcpy(dest1, src1);
	ft_strcpy(dest2, src1);
	check_str(dest1, dest2, "ft_strcpy(dest, \"TESTING\")");

	char *src2 = "A";
	char dest3[50];
	char dest4[50];

	strcpy(dest3, src2);
	ft_strcpy(dest4, src2);
	check_str(dest3, dest4, "ft_strcpy(dest, \"A\")");
	
	// Empty string test
	char *src3 = "";
	char dest5[50];
	char dest6[50];
	
	strcpy(dest5, src3);
	ft_strcpy(dest6, src3);
	check_str(dest5, dest6, "ft_strcpy(dest, \"\")");
	
	// Return value test
	char dest7[50];
	char *ret = ft_strcpy(dest7, "Test");
	check_bool(ret == dest7, "ft_strcpy returns dst pointer");
	
	// Register preservation test
	printf("\n  Register preservation test:\n");
	check_rbx_preserved(wrapper_strcpy, "ft_strcpy");
}

void test_strcmp() {
	char *str1 = "Hello";
	char *str2 = "Hello, World!";
	char *str3 = "";
	char str4[] = {(char)0xff, '\0'};  // High ASCII
	char str5[] = {(char)0x01, '\0'};  // Low ASCII
	char *str6 = "abc";
	char *str7 = "bbc";

	print_header("ft_strcmp");
	check_strcmp_sign(strcmp(str1, str1), ft_strcmp(str1, str1), "ft_strcmp(\"Hello\", \"Hello\")");
	check_strcmp_sign(strcmp(str1, str2), ft_strcmp(str1, str2), "ft_strcmp(\"Hello\", \"Hello, World!\")");
	check_strcmp_sign(strcmp(str2, str1), ft_strcmp(str2, str1), "ft_strcmp(\"Hello, World!\", \"Hello\")");
	check_strcmp_sign(strcmp(str3, str3), ft_strcmp(str3, str3), "ft_strcmp(\"\", \"\")");
	
	// Unsigned comparison test (high ASCII)
	check_strcmp_sign(strcmp(str4, str5), ft_strcmp(str4, str5), "ft_strcmp(\"\\xff\", \"\\x01\") - unsigned");
	
	// First character difference
	check_strcmp_sign(strcmp(str6, str7), ft_strcmp(str6, str7), "ft_strcmp(\"abc\", \"bbc\") - first char diff");
	
	// Register preservation test
	printf("\n  Register preservation test:\n");
	check_rbx_preserved(wrapper_strcmp, "ft_strcmp");
}

void test_write() {
	char *str1 = "Hello, World!\n";
	char *str2 = "";
	
	print_header("ft_write");

	printf("  Test 1 - Writing \"Hello, World!\\n\":\n");
	ssize_t res1 = write(1, str1, strlen(str1));
	ssize_t res2 = ft_write(1, str1, strlen(str1));
	check_ssize(res1, res2, "ft_write(1, \"Hello, World!\\n\", 14)");

	printf("\n  Test 2 - Writing empty string:\n");
	ssize_t res3 = write(1, str2, strlen(str2));
	ssize_t res4 = ft_write(1, str2, strlen(str2));
	check_ssize(res3, res4, "ft_write(1, \"\", 0)");

	printf("\n  Test 3 - Invalid fd (-1) with errno:\n");
	errno = 0;
	ssize_t res5 = write(-1, str1, strlen(str1));
	int errno1 = errno;
	errno = 0;
	ssize_t res6 = ft_write(-1, str1, strlen(str1));
	int errno2 = errno;
	check_ssize(res5, res6, "ft_write(-1, \"Hello, World!\\n\", 14) return value");
	check_int(errno1, errno2, "ft_write(-1, \"Hello, World!\\n\", 14) errno");
	
	// Register preservation test
	printf("\n  Register preservation test:\n");
	check_rbx_preserved(wrapper_write, "ft_write");
}

void test_read() {
	const char *test_file = "test_read.txt";
	const char *test_content = "Hello from file!";

	print_header("ft_read");
	
	// Create test file
	int fd_write = open(test_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_write < 0) {
		printf(RED "[SKIP]" RESET " Could not create test file for ft_read tests\n");
		return;
	}
	int res = write(fd_write, test_content, strlen(test_content));
	if (res < 0) {
		printf(RED "[SKIP]" RESET " Could not write to test file for ft_read tests\n");
		close(fd_write);
		return;
	}
	close(fd_write);
	
	// Test 1: Read from file
	printf("  Test 1 - Read from file:\n");
	char buf1[50] = {0};
	char buf2[50] = {0};
	int fd1 = open(test_file, O_RDONLY);
	int fd2 = open(test_file, O_RDONLY);
	
	if (fd1 != -1 && fd2 != -1) {
		ssize_t r1 = read(fd1, buf1, 16);
		ssize_t r2 = ft_read(fd2, buf2, 16);
		check_ssize(r1, r2, "ft_read(fd, buf, 16) return value");
		check_str(buf1, buf2, "ft_read(fd, buf, 16) buffer content");
		close(fd1);
		close(fd2);
	}
	
	// Test 2: Invalid file descriptor
	printf("\n  Test 2 - Invalid fd:\n");
	char buf3[10];
	errno = 0;
	ssize_t r3 = read(-1, buf3, 10);
	int errno1 = errno;
	errno = 0;
	ssize_t r4 = ft_read(-1, buf3, 10);
	int errno2 = errno;
	check_ssize(r3, r4, "ft_read(-1, buf, 10) return value");
	check_int(errno1, errno2, "ft_read(-1, buf, 10) errno");
	
	// Test 3: Read 0 bytes
	printf("\n  Test 3 - Read 0 bytes:\n");
	int fd3 = open(test_file, O_RDONLY);
	if (fd3 != -1) {
		char buf4[10];
		ssize_t r5 = read(fd3, buf4, 0);
		ssize_t r6 = ft_read(fd3, buf4, 0);
		check_ssize(r5, r6, "ft_read(fd, buf, 0)");
		close(fd3);
	}
	
	// Test 4: Read from /dev/zero
	printf("\n  Test 4 - Read from /dev/zero:\n");
	int fd_zero = open("/dev/zero", O_RDONLY);
	if (fd_zero != -1) {
		char buf5[10] = {0};
		ssize_t r7 = ft_read(fd_zero, buf5, 5);
		check_ssize(5, r7, "ft_read(/dev/zero) return value");
		int all_zeros = 1;
		for (int i = 0; i < 5; i++) {
			if (buf5[i] != 0) all_zeros = 0;
		}
		check_bool(all_zeros, "ft_read(/dev/zero) buffer contains zeros");
		close(fd_zero);
	}
	
	// Cleanup
	unlink(test_file);
	
	// Register preservation test
	printf("\n  Register preservation test:\n");
	check_rbx_preserved(wrapper_read, "ft_read");
}

void test_strdup() {
	print_header("ft_strdup");
	
	// Test 1: Basic string
	printf("  Test 1 - Basic string:\n");
	char *str1 = "Hello, World!";
	char *dup1 = strdup(str1);
	char *ft_dup1 = ft_strdup(str1);
	
	check_str(dup1, ft_dup1, "ft_strdup(\"Hello, World!\")");
	check_size(strlen(dup1), strlen(ft_dup1), "ft_strdup(\"Hello, World!\") length");
	
	free(dup1);
	free(ft_dup1);
	
	// Test 2: Empty string
	printf("\n  Test 2 - Empty string:\n");
	char *str2 = "";
	char *dup2 = strdup(str2);
	char *ft_dup2 = ft_strdup(str2);
	
	check_str(dup2, ft_dup2, "ft_strdup(\"\")");
	check_size(strlen(dup2), strlen(ft_dup2), "ft_strdup(\"\") length");
	
	free(dup2);
	free(ft_dup2);
	
	// Test 3: Single character
	printf("\n  Test 3 - Single character:\n");
	char *str3 = "A";
	char *dup3 = strdup(str3);
	char *ft_dup3 = ft_strdup(str3);
	
	check_str(dup3, ft_dup3, "ft_strdup(\"A\")");
	
	free(dup3);
	free(ft_dup3);
	
	// Test 4: Pointer independence
	printf("\n  Test 4 - Pointer independence:\n");
	char *str4 = "Testing independence";
	char *ft_dup4 = ft_strdup(str4);
	
	check_bool(ft_dup4 != str4, "ft_strdup returns different pointer");
	
	free(ft_dup4);
	
	// Test 5: Long string
	printf("\n  Test 5 - Long string:\n");
	char *str5 = "This is a very long string designed to test malloc and copy correctness with many characters. Over 100 chars here!";
	char *dup5 = strdup(str5);
	char *ft_dup5 = ft_strdup(str5);
	
	check_str(dup5, ft_dup5, "ft_strdup(long string)");
	check_size(strlen(dup5), strlen(ft_dup5), "ft_strdup(long string) length");
	
	free(dup5);
	free(ft_dup5);
	
	// Register preservation test
	printf("\n  Register preservation test:\n");
	check_rbx_preserved(wrapper_strdup, "ft_strdup");
}
