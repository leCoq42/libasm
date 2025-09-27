#include <stdio.h>

int main() {
    test_strlen();
    return 0;
}




void test_strlen() {
    char *str = "Hello, World!";
    size_t len = ft_strlen(str);
    printf("Length of '%s' is %zu\n", str, len);
}