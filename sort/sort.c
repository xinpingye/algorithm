#include <stdio.h>

#define MAX_SIZE 100

void print(int* data, int nums)
{
    for(int i = 0; i < nums; i++)
        printf("%d ", data[i]);
    printf("\n");
}

void bubble_sort(int* data, int nums)
{
    for(int i = 0; i < nums - 1; i++)
    {
        for(int j = 0;j < nums - 1 - i; j++)
        {
            if(data[j] > data[j + 1])
            {
                int tmp = data[j];
                data[j] = data[j + 1];
                data[j + 1] = tmp;
            }
        }
    }
}

int main()
{
    freopen("test.txt", "r", stdin);
    int data[MAX_SIZE];
    int nums = 0;
    int item = 0;
    while(scanf("%d ", &item) != EOF)
    {
        data[nums] = item;
        nums++;
    }
    print(data, nums);
    bubble_sort(data, nums);
    print(data, nums);
    return 0;
}