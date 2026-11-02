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
    int in_block_comment = 0;
    while (fgets(buffer, sizeof(buffer), in) != NULL) {
        char clean_line[2048];
        int c_idx = 0;
        int i = 0;
        while (buffer[i] != '\0') {
            if (in_block_comment) {
                if (buffer[i] == '*' && buffer[i+1] == '/') {
                    in_block_comment = 0;
                    i += 2;
                } else {
                    i++;
                }
            } else {
                if (buffer[i] == '/' && buffer[i+1] == '*') {
                    in_block_comment = 1;
                    i += 2;
                }
                else if (buffer[i] == '/' && buffer[i+1] == '/') {
                    break;
                }
                else {
                    clean_line[c_idx++] = buffer[i];
                    i++;
                }
            }
        }
        clean_line[c_idx] = '\0';
        char *p = clean_line;
        int only_whitespace = 1;
        while (*p != '\0') {
            if (!isspace((unsigned char)*p)) {
                only_whitespace = 0;
                break;
            }
            p++;
        }
        if (!only_whitespace) {
            size_t len = strlen(clean_line);
            while (len > 0 && (clean_line[len-1] == ' ' || clean_line[len-1] == '\t' || clean_line[len-1] == '\r' || clean_line[len-1] == '\n')) {
                clean_line[--len] = '\0';
            }
            fprintf(out, "%s\n", clean_line);
        }
    }
    fclose(in);
    fclose(out);
    printf("Done! The cleansed version is named clean.c in the same directory.\n");
    return 0;
}
