#include <stddef.h>
#include <stdio.h>
#include <string.h>

size_t ft_strlen(const char *s);
char *ft_strcpy(char *dst, const char *src);
int ft_strcmp(const char *s1, const char *s2);

void test_strlen();
void test_strcpy();
void test_strcmp();

#define BORDER "-------------------------------------\n"

int main() {
    test_strlen();
	test_strcpy();
	test_strcmp();
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
void test_strdup() {}
void test_write() {}
