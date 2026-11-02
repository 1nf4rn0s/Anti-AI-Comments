#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main() {
    char name[40];
    printf("what file do you want to clean? (yes, you have to use the file extension too): ");
    scanf("%39s", name);
    FILE *in = fopen(name, "r");
    FILE *out = fopen("clean.c", "w");
    if (!in || !out) {
        perror("File opening failed");
        return 1;
    }
    char buffer[2048];
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        char *comment = strstr(buffer, "//");
        if (comment != NULL) {
            *comment = '\0';
        }
        char *p = buffer;
        int only_whitespace = 1;
        while (*p != '\0') {
            if (!isspace((unsigned char)*p)) {
                only_whitespace = 0;
                break;
            }
            p++;
        }
        if (!only_whitespace) {
            size_t len = strlen(buffer);
            while (len > 0 && (buffer[len-1] == ' ' || buffer[len-1] == '\t' || buffer[len-1] == '\r' || buffer[len-1] == '\n')) {
                buffer[--len] = '\0';
            }
            fprintf(out, "%s\n", buffer);
        }
    }
    fclose(in);
    fclose(out);
    printf("Done! there should be the cleansed version named clean.c in the same directory as this file. check it out!\n");
    return 0;
}
