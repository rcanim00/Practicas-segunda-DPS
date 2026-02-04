#include <stdio.h>
#include <string.h>

void vulnerable_function(char *str) {
    char buffer[512]; // Buffer mucho más amplio
    strcpy(buffer, str);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        vulnerable_function(argv[1]);
    } else {
        printf("Uso: %s <input>\n", argv[0]);
    }
    return 0;
}
