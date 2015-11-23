#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>

const size_t MAX_LINE = 2048;
const int MAX_SWAP_PER_WORD = 2;
const float SWAP_PROBABILITY = 0.2;
const float MAX_REMOVE_PER_WORD = 0.2;
const float MAX_REMOVE_VOCAL = 0.05;
const float MAX_REMOVE_CONSONANT = 0.10;
const float MAX_REMOVE_DOUBLE = 0.40;
const float H_PROBABILITY = 0.3;

bool rnd(float probability);
void swap(char*a, char*b);
bool isvocal(char c);

void process(char* str);
void capitalize(char* str, size_t len);
void swap_letters(char* str, size_t len);
size_t remove_letters(char* str, size_t len);
size_t add_h(char* str, size_t len);

int main(int argc, char* argv[]) {
    if (argc > 1)
        freopen(argv[1], "r", stdin);


    char line[MAX_LINE];
    while (fgets(line, MAX_LINE, stdin) != NULL) {
        process(line);
        printf("%s", line);
    }

    return EXIT_SUCCESS;
}

bool rnd(float probability) {
    return (float)(rand()) / RAND_MAX < probability;
}

void process(char* str) {
    size_t len = strlen(str);
    capitalize(str, len);
    swap_letters(str, len);
    len = remove_letters(str, len);
    len = add_h(str, len);
}

void capitalize(char* str, size_t len) {
    int i;
    for (i = 0; i < len; i++)
        str[i] = toupper(str[i]);
}

void swap(char*a, char*b) {
    char t = *a;
    *a = *b;
    *b = t;
}

void swap_letters(char* str, size_t len) {
    int i;
    int perWord = 0;
    for (i = 0; i < len-1; i++) {
        char c = str[i];
        if (isspace(c)) { perWord = 0; continue; }
        if (isalpha(c) && isalpha(str[i+1]) && perWord < MAX_SWAP_PER_WORD && rnd(SWAP_PROBABILITY)) {
            swap(&str[i], &str[i+1]);
            perWord++;
        }
    }
}

bool isvocal(char c) {
    if (c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
        return true;
    return false;
}

size_t remove_letters(char* str, size_t len) {
    int pos = 0;
    int perWord = 0;
    int wordLength = 0;
    int i;
    for (i = 0; i < len; i++) {
        char c = str[i];
        str[pos] = c;

        if (isspace(c) || i == 0) {
            perWord = wordLength = 0;
            int j;
            for (j = i?i+1:0; j < len && isalpha(str[j]); j++)
                wordLength++;
        }

        bool skip = false;
        if (isvocal(c) && rnd(MAX_REMOVE_VOCAL))
            skip = true;
        else if (c == str[i+1] && rnd(MAX_REMOVE_DOUBLE))
            skip = true;
        else if (isalpha(c) && !isvocal(c) && rnd(MAX_REMOVE_CONSONANT))
            skip = true;
        if (!skip || perWord >= wordLength*MAX_REMOVE_PER_WORD)
            pos++;
        else if (skip)
            perWord++, wordLength--;
    }
    str[pos] = 0;
    return pos;
}

size_t add_h(char* str, size_t len) {
    if (rnd(H_PROBABILITY) && len + 4 < MAX_LINE) {
        len--;
        str[len++] = ' ';
        str[len++] = 'H';
        str[len++] = '!';
        str[len++] = '?';
        str[len++] = '\n';
        str[len] = '\0';
    }
    return len-1;
}
