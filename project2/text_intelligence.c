#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


struct wordStat {
    char name[40];
    int count;
};

char *text_buf = NULL;
char **words = NULL;
int word_count = 0;
struct wordStat *stats = NULL;
int stat_count = 0;

/* sample paragraph */
char *sample = "It was the best of times it was the worst of times "
               "it was the age of wisdom it was the age of foolishness "
               "it was the epoch of belief it was the epoch of incredulity "
               "it was the season of Light it was the season of Darkness "
               "it was the spring of hope it was the winter of despair "
               "we had everything before us we had nothing before us "
               "we were all going direct to Heaven we were all going direct the other way";

void load_text() {
    int len = strlen(sample);
    int i, wcount = 0;


    text_buf = malloc(len + 1);
    strcpy(text_buf, sample);
    printf("Text buffer stored at memory address: %p\n", (void*)text_buf);

 
    char temp[2000];
    strcpy(temp, text_buf);
    char *tok = strtok(temp, " ");
    while (tok != NULL) {
        wcount++;
        tok = strtok(NULL, " ");
    }

  
    words = malloc(wcount * sizeof(char*));
    printf("Word array stored at memory address: %p\n", (void*)words);

    stats = malloc(wcount * sizeof(struct wordStat));
    printf("Stats array stored at memory address: %p\n", (void*)stats);

  
    char *ptr = text_buf;
    char *end = text_buf + len;
    word_count = 0;

    while (ptr < end) {
        while (ptr < end && !isalpha(*ptr)) ptr++;
        if (ptr >= end) break;

        char *start = ptr;
        while (ptr < end && isalpha(*ptr)) ptr++;

        int wlen = ptr - start;
        char *word = malloc(wlen + 1);
        int j;
        for (j = 0; j < wlen; j++) {
            word[j] = tolower(start[j]);
        }
        word[wlen] = '\0';

        *(words + word_count) = word;
        word_count++;
    }
 
    stat_count = 0;
    for (i = 0; i < word_count; i++) {
        char *w = *(words + i);
        int found = 0;
        int j;
        for (j = 0; j < stat_count; j++) {
            if (strcmp((stats + j)->name, w) == 0) {
                (stats + j)->count++;
                found = 1;
                break;
            }
        }
        if (!found) {
            strcpy((stats + stat_count)->name, w);
            (stats + stat_count)->count = 1;
            stat_count++;
        }
    }

    printf("\nSample Text:\n\"%s\"\n", sample);
    printf("\nWords: %d total, %d unique\n", word_count, stat_count);
}

/* count total and unique words */
void count_words() {
    printf("\nTotal words: %d\n", word_count);
    printf("Unique words: %d\n", stat_count);
}

/* longest word  */
void longest_word() {
    int i;
    char *longest = *(words);
    for (i = 1; i < word_count; i++) {
        if (strlen(*(words + i)) > strlen(longest)) {
            longest = *(words + i);
        }
    }
    printf("\nLongest word: \"%s\" (%d letters)\n", longest, (int)strlen(longest));
}

/* frequent word */
void most_frequent() {
    int i;
    struct wordStat *top = stats;
    for (i = 1; i < stat_count; i++) {
        if ((stats + i)->count > top->count) {
            top = stats + i;
        }
    }
    printf("\nMost frequent word: \"%s\" (appears %d times)\n", top->name, top->count);
}

/* average word length */
void average_word_length() {
    int i, total = 0;
    for (i = 0; i < word_count; i++) {
        total += strlen(*(words + i));
    }
    float avg = (float)total / word_count;
    printf("\n--- Average Word Length ---\n");
    printf("Total characters: %d\n", total);
    printf("Total words: %d\n", word_count);
    printf("Average word length: %.2f characters\n", avg);
    if (avg < 4.0)
        printf("Classification: Short word text\n");
    else if (avg < 6.0)
        printf("Classification: Average complexity\n");
    else
        printf("Classification: Complex vocabulary\n");
}

/* function pointer type */
typedef void (*AnalysisFunc)();

int main() {
  
    printf("  Adaptive Text Intelligence Tool\n");
    printf("  Student ID: 1005698443\n");
    printf("  Custom Analysis: Avg Word Length\n");

    load_text();

    AnalysisFunc options[4] = {
        count_words,
        longest_word,
        most_frequent,
        average_word_length
    };

    char *labels[4] = {
        "Count Words",
        "Find Longest Word",
        "Find Most Frequent Word",
        "Average Word Length (custom)"
    };

    int choice;
    do {
        printf("\n--- Menu ---\n");
        int i;
        for (i = 0; i < 4; i++) {
            printf("%d. %s\n", i + 1, labels[i]);
        }
        printf("5. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 4) {
            options[choice - 1]();
        } else if (choice != 5) {
            printf("Invalid choice.\n");
        }

    } while (choice != 5);

    /* free all dynamically allocated memory */
    int i;
    for (i = 0; i < word_count; i++) {
        free(*(words + i));
    }
    free(words);
    free(text_buf);
    free(stats);

    printf("Goodbye!\n");
    return 0;
}
