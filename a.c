#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long long int fibo(int n);
int find_nth_term(int n, int len);

int main()
{
    {

        char line[306];  //stores line from stdin
        char first[102], second[102], n[102], *end;  //3 numbers from line, *end for strtoll
        int num_line, result_line = 1;
        unsigned long long len_first = 0, len_second = 0, len_next = 0, len_line, pos;
        unsigned long long int int_n;

        scanf("%d", &num_line);
        for(; num_line > 0; num_line--)
        {
            scanf("%s %s %s", first, second, n);
            int_n = strtoll(n, &end, 10);
            len_first = strlen(first);
            len_second = strlen(second);
            result_line = 0;
            while((fibo(result_line) * len_first) <= int_n)
            {
                result_line++;
            }
            pos = (int_n/len_first);    //position of string in line <result_line>
            if(int_n % len_first != 0)
                pos++;
            unsigned long long int pos_w = int_n - (len_first * (pos-1)); //position of nth character in string
            if (num_line != 1)
            {
                if(find_nth_term(result_line, pos) == 1)
                printf("%c\n", second[pos_w - 1]);       //
            else
                printf("%c\n", first[pos_w - 1]);
            }
            else
            {
               if(find_nth_term(result_line, pos) == 1)
                printf("%c", second[pos_w - 1]);       //
            else
                printf("%c", first[pos_w - 1]); 
            }
            
        }
        return 0;
    }

}

unsigned long long int fibo(int n)
{
    unsigned long long int c = n;
    static unsigned long long int fib_arr[20000] = {0,1};


    if(n ==0 || n == 1)
        return c;
    else
        {
            if (fib_arr[n-1] == 0)
            {
                fib_arr[n-1] = fibo(n-1);
            }
            if (fib_arr[n] == 0)
            {
                fib_arr[n] = fib_arr[n-1] + fib_arr[n-2];
            }
            return (fib_arr[n]);
        }
}

int find_nth_term(int line, int pos)
{
    if(pos == 1)
    {
        if(line % 2 == 0)
            return 1;
        else
            return 0;
    }
    if (pos == 2)
    {
        if (line % 2 == 0)
            return 0;
        else
            return 1;
    }
    if (pos <= fibo(line-1))
        return find_nth_term(line-1, pos);
    else
        return find_nth_term(line - 1, pos - fibo(line-2));
}
