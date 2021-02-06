#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

// Prototypes.
int grader(string s);
int *counter(string t);

int main(void)
{
    // Collect text from terminal.
    string text = get_string("Text: ");

    // Generate a grade level.
    int grade_level = grader(text);

    // Determine what to print based on spec.
    if (grade_level < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade_level > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grade_level);
    }

    return 0;
}

int *counter(string t)
{
    // Array of letters, words, and sentences of text, t.
    static int arr[3];

    // If there's any text, make sure arr reads at least 1 word.
    if (t)
    {
        arr[1] = 1;
    }

    // Add up each letter, word, and sentence.
    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (isalpha(t[i]))
        {
            arr[0]++;
        }
        else if (isspace(t[i]))
        {
            arr[1]++;
        }
        else if (t[i] == 33 || t[i] == 46 || t[i] == 63)
        {
            arr[2]++;
        }
    }

    return arr;
}

int grader(string t)
{
    // Creation of pointer to store counter() arr.
    int *p = counter(t);

    // Abstraction of vars for use in index.
    // Hundred words per sentence.
    float hund_words = *(p + 1) / 100.0;
    // Letters per hundred words.
    float l = *p / hund_words;
    // Sentences per hundred words.
    float s = *(p + 2) / hund_words;

    // Coleman-Liau reading grade-level index.
    float index = 0.0588 * l - 0.296 * s - 15.8;
    int grade_level = round(index);

    return grade_level;
}