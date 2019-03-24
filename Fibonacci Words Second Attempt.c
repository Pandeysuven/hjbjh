#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RESULT_LINE 300
#define LINE_SIZE 300


typedef struct obj
{
    struct obj *one;
    struct obj *two;
    char len[100];
    char string;
} OBJ;
OBJ result[RESULT_LINE];

char new_get_n(char*a, char*b, char*n);
int compareStrings(char *a, char *b);
char* addStrings(char *a, char *b);
char* subStrings(char* a, char*);

char new_get_n(char*a, char*b, char* char_n)
{
    unsigned long long int n;
    char len_a[100], len_b[100], *end;

    sprintf(len_a, "%lu", strlen(a));
    sprintf(len_b, "%lu", strlen(b));
    for (int i = 0; i < RESULT_LINE; i++)
    {
        result[i].len[0] = '\0';
        result[i].string = '\0';
        result[i].one = NULL;
        result[i].two = NULL;
    }
    result[1].string = 'a';
    strcpy(result[1].len, len_a);
    result[2].string = 'b';
    strcpy(result[2].len, len_b);
    int i = 3;
    while (1)
    {
        result[i].one = &result[i - 2];
        result[i].two = &result[i - 1];
        strcpy(result[i].len, addStrings(result[i - 1].len, result[i - 2].len));
        if (compareStrings(result[i].len, char_n) >= 0)
            break;
        i++;
    }
    OBJ *solution = &result[i];
    while (1)
    {
        if (solution->string == 'a')
        {
            n = strtoull(char_n, &end, 10);
            return a[n - 1];
        }
        if (solution->string == 'b')
        {
            n = strtoull(char_n, &end, 10);
            return b[n - 1];
        }
        if (compareStrings(solution->one->len, char_n) >= 0)
        { 
            solution = solution->one;
            i -= 2;
        }
        else
        {
            char_n = subStrings(char_n, solution->one->len); //n = char_n - solution->one->len
            solution = solution->two;
            i -= 1;
        }

    }
}



int main()
{
    char first[LINE_SIZE], second[LINE_SIZE], n[LINE_SIZE];  //3 numbers from line
    int num_line = 0;
    char c;
    for (scanf("%d", &num_line); num_line > 0; num_line--)
    {
        if (scanf("%s %s %s", first, second, n) != 3)
        {
            fprintf(stderr, "Error reading line %d.\n", num_line);
            exit(EXIT_FAILURE);
        }
        c = new_get_n(first, second, n);
        printf("%c\n", c);
    }
    return 0;
}



int compareStrings(char *a, char *b)
{
    if (strlen(a) > strlen(b))
        return 1;
    else if (strlen(a) < strlen(b))
        return -1;
    else
        return strcmp(a, b);
}

char* addStrings(char *a, char *b)
{
    unsigned int len_large = (strlen(a) > strlen(b)) ? strlen(a) : strlen(b);
    unsigned int len_small = (strlen(a) < strlen(b)) ? strlen(a) : strlen(b);
    char longer = (compareStrings(a, b) > 0) ? 'a' : 'b';
    char *sum = (char*)calloc(len_large + 2, sizeof(char));
    char *return_sum = (char*)calloc(len_large + 2, sizeof(char));;
    unsigned int i;

    for (i = 0; i < len_large + 1; i++)
    {
        sum[i] = '0';
        return_sum[i] = '0';
    }
    sum[len_large + 1] = '\0';
    for (i = 0; i < len_large; i++)
    {
        int t_sum = 0;
        if (i >= len_small)
        {
            if (longer == 'a')
                t_sum = (int)a[strlen(a) - i - 1] - '0';
            else if (longer == 'b')
                t_sum = (int)b[strlen(b) - i - 1] - '0';
        }
        else
            t_sum = (int)a[strlen(a) - i - 1] + (int)b[strlen(b) - i - 1] - 2 * '0';

        if (9 < t_sum)
        {
            sum[len_large - i - 1] = ((int)sum[len_large - i - 1] + 1);
            t_sum -= 10;
        }
        else if (9 == t_sum && sum[len_large - i] == '1')
        {
            sum[len_large - i - 1] = ((int)sum[len_large - i - 1] + 1);
            t_sum -= 10;
        }
        sum[len_large - i] = (char)((int)sum[len_large - i] + t_sum);
    }

    if (sum[0] == '0')
    {
        return_sum = (char*)calloc(len_large + 1, sizeof(char));
        for (unsigned int i = 0; i <= len_large; i++)
            return_sum[i] = sum[i + 1];
        free(sum);
        return return_sum;
    }

    int number_leading_zero = 0;
    for (unsigned int i = 0; sum[i] <= 0; i++)
    {
            number_leading_zero++;
    }
    for (unsigned int i = 0; i <= len_large+1; i++)
    {
        return_sum[i] = sum[i + number_leading_zero];
        if (return_sum[i] == '\0')
            break;
    }
    return sum;
}

char* subStrings(char* a, char* b)
{
    char *first = a;
    char *second = b;
    if (compareStrings(a, b) < 0)
    {
        first = b;
        second = a;
        
    }
    unsigned int len_large = strlen(first);
    char *diff = (char*)calloc(len_large + 1, sizeof(char));
    for (unsigned int i = 0; i < len_large; i++)
        diff[i] = '0';
    diff[len_large] = '\0';
    int burrow = 0, temp;
    for (unsigned int i = 0; i < len_large; i++)
    {
        if (i >= strlen(second))
            temp = first[strlen(first) - 1 - i] - '0';
        else
            temp = first[strlen(first) - 1 - i] - second[strlen(second)-1 - i];
        if (burrow)
        {
            temp--;
            burrow = 0;
        }
        if (temp < 0)
        {
            temp += 10;
            burrow = 1;
        }
        diff[strlen(diff)-1 - i] = (char)temp + '0';
            
    }
    
        char *return_diff = (char*)calloc(len_large, sizeof(char));
        int number_leading_zero = 0;
        for (unsigned int i = 0; i <= len_large; i++)
        {
            if (diff[i] == '0')
                number_leading_zero++;
            else if (diff[i] > '0')
                break;
        }
        for (unsigned int i = 0; i <= len_large; i++)
        {

            return_diff[i] = diff[i+number_leading_zero];
            if (return_diff[i] == '\0')
                break;
        }
        free(diff);
        return return_diff;
}
