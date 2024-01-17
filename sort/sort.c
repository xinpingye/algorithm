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

void insert_sort(int* data, int nums)
{
    for(int i = 1; i < nums; i++)
    {
        int insert_pos = -1;
        for(int j = 0; j < i; j++)
        {
            if (data[i] <= data[j])
            {
                insert_pos = j;
                break;
            }
            
        }
        if (insert_pos != -1)
        {
            int tmp1 = data[i], tmp2 = 0;
            for (int j = insert_pos; j <= i; j++)
            {
                tmp2 = data[j];
                data[j] = tmp1;
                tmp1 = tmp2;
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
    //bubble_sort(data, nums);
    insert_sort(data, nums);
    print(data, nums);
    return 0;
}