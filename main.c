#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BORDER "-------------------------------------\n"

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


int main() {
    test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	test_strdup();
    return 0;
}

void test_strlen() {
    char *str1 = "Hello, World!";
    char *str2 = "";

	printf(BORDER);
	printf("Testing ft_strlen vs strlen:\n");
	printf(BORDER);
    printf("String: '%s', strlen: %zu, ft_strlen: %zu\n", str1, strlen(str1), ft_strlen(str1));
    printf("String: '%s', strlen: %zu, ft_strlen: %zu\n", str2, strlen(str2), ft_strlen(str2));
}


void test_strcpy() {
	char *src1 = "TESTING";
	char dest1[50];
	char dest2[50];

	printf("\n");
	printf(BORDER);
	printf("Testing ft_strcpy vs strcpy:\n");
	printf(BORDER);

	printf("Source string: '%s'\n", src1);
	strcpy(dest1, src1);
	ft_strcpy(dest2, src1);
	printf("Using strcpy: '%s'\n", dest1);
	printf("Using ft_strcpy: '%s'\n", dest2);
	printf("\n");

	char *src2 = "A";
	char dest3[50];
	char dest4[50];

	printf("Source string: '%s'\n", src2);
	ft_strcpy(dest3, src2);
	printf("Using ft_strcpy: '%s'\n", dest3);
	strcpy(dest4, src2);
	printf("Using strcpy: '%s'\n", dest4);
}

void test_strcmp() {
	char *str1 = "Hello";
	char *str2 = "Hello, World!";
	char *str3 = "";

	printf("\n");
	printf(BORDER);
	printf("Testing ft_strcmp vs strcmp:\n");
	printf(BORDER);

	printf("String: '%s' vs '%s', strcmp: %d, ft_strcmp: %d\n", str1, str1, strcmp(str1, str1), ft_strcmp(str1, str1));
	printf("String: '%s' vs '%s', strcmp: %d, ft_strcmp: %d\n", str1, str2, strcmp(str1, str2), ft_strcmp(str1, str2));
	printf("String: '%s' vs '%s', strcmp: %d, ft_strcmp: %d\n", str2, str1, strcmp(str2, str1), ft_strcmp(str2, str1));
	printf("String: '%s' vs '%s', strcmp: %d, ft_strcmp: %d\n", str3, str3, strcmp(str3, str3), ft_strcmp(str3, str3));
}
void test_write() {
	char *str1 = "Hello, World!\n";
	char *str2 = "";
	
	printf("\n");
	printf(BORDER);
	printf("Testing write vs ft_write:\n");
	printf(BORDER);

	ssize_t res1 = write(1, str1, strlen(str1));
	ssize_t res2 = ft_write(1, str1, ft_strlen(str1));
	printf("write returned: %zd\n", res1);
	printf("ft_write returned: %zd\n", res2);

	ssize_t res3 = write(1, str2, strlen(str2));
	ssize_t res4 = ft_write(1, str2, ft_strlen(str2));
	printf("write returned: %zd\n", res3);
	printf("ft_write returned: %zd\n", res4);

	ssize_t res5 = write(-1, str1, strlen(str1));
	ssize_t res6 = ft_write(-1, str1, ft_strlen(str1));
	printf("write with invalid fd returned: %zd\n", res5);
	printf("ft_write with invalid fd returned: %zd\n", res6);

	/* ssize_t res7 = write(1, NULL, 10); */
	/* ssize_t res8 = ft_write(1, NULL, 10); */
	/* printf("write with NULL buffer returned: %zd\n", res7); */
	/* printf("ft_write with NULL buffer returned: %zd\n", res8); */
	/**/
	/* ssize_t res9 = write(1, str1, -5); */
	/* ssize_t res10 = ft_write(1, str1, -5); */
	/* printf("write with negative count returned: %zd\n", res9); */
	/* printf("ft_write with negative count returned: %zd\n", res10); */
}

void test_read() {
	printf("\n");
	printf(BORDER);
	printf("Testing ft_read vs read:\n");
	printf(BORDER);
}

void test_strdup() {
	printf("\n");
	printf(BORDER);
	printf("Testing ft_strdup vs strdup:\n");
	printf(BORDER);
}
