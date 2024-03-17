#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 20

void sortWords(char** wordsArr, int size);

int main() {
    FILE *strings = fopen("file1.txt", "w");
    const char text[] = "lorem ipsum dolor sit amet consectetur adipiscing elit\nquisque varius congue ex non mattis mauris vestibulum arcu ac\ndignissim tristique dolor nunc euismod ex scelerisque dictum libero velit a ipsum\ncurabitur condimentum urna at consectetur mollis";
    fprintf(strings, text);
    fclose(strings);
    fopen("file1.txt", "r");
    int wordsCounter = 1;
    int ch;
    while ((ch = getc(strings)) != EOF)
        if (ch == ' ' || ch == '\n')
            wordsCounter++;
    char **words = (char**)malloc(wordsCounter * sizeof (char*));
    if (words == NULL)
        return 1;
    for (int i = 0; i < wordsCounter; i++){
        words[i] = (char*)malloc(MAX_CHAR * sizeof (char));
        if (words[i] == NULL) {
            free(words);
            return 1;
        }
    }
    rewind(strings);
    int i = 0;
    char buffer[MAX_CHAR];
    while (fscanf(strings, "%s", buffer) != EOF) {
        strcpy(words[i], buffer);
        i++;
    }
    fclose(strings);
    sortWords(words, wordsCounter);
    FILE *fileOfWords = fopen("file2.txt", "w");
    for (i = 0; i < wordsCounter; i++) {
        fprintf(fileOfWords, "%s ", words[i]);
        free(words[i]);
    }
    free(words);
    fclose(fileOfWords);

    return 0;
}

void sortWords(char** wordsArr, int size)
{
    char temp[MAX_CHAR];
    for (int i = 1; i < size; i++) {
        strcpy(temp, wordsArr[i]);
        int j = i - 1;
        while (j >= 0 && strcmp(temp, wordsArr[j]) < 0){
            strcpy(wordsArr[j+1], wordsArr[j]);
            j--;
        }
        strcpy(wordsArr[j+1], temp);
    }
}