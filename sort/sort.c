#include <stdio.h>

#define MAX_SIZE 100
#define HASH_MAX_VALUE 1000

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

void select_sort(int* data, int nums)
{
    for(int i = 0; i < nums - 1; i++)
    {
        int min_value = data[i];
        int min_value_pos = i;
        for(int j = i + 1; j < nums; j++)
        {
            if(data[j] < min_value)
            {
                min_value = data[j];
                min_value_pos = j;
            }
        }
        int tmp = data[i];
        data[i] = data[min_value_pos];
        data[min_value_pos] = tmp;
    }
}

void quick_sort(int* data, int nums)
{
    if(nums == 1 || nums == 0)
        return;
    int left[nums], right[nums];
    int mid = nums/2;
    int left_nums = 0,right_nums = 0;
    for(int i = 0; i < nums; i++)
    {
        if(i != mid)
        {
            if(data[i] >= data[mid])
                right[right_nums++] = data[i];
            else
                left[left_nums++] = data[i];
        }
    }
    quick_sort(left, left_nums);
    quick_sort(right, right_nums);
    int mid_value = data[mid];
    for(int i = 0; i < nums; i++)
    {
        if(i < left_nums)
            data[i] = left[i];
        else if(i == left_nums)
            data[i] = mid_value;
        else if(i > left_nums)
            data[i] = right[i - (left_nums + 1)];
    }
    return;
}

void hash_sort(int* data, int nums)
{
    int hash_data[HASH_MAX_VALUE];
    for(int i = 0; i < HASH_MAX_VALUE; i++)
        hash_data[i] = 0;
    int pos = 0;
    for(int i = 0; i < nums; i++)
    {
        hash_data[data[i]] = 1;
    }
    for(int i = 0; i < HASH_MAX_VALUE; i++)
    {
        if(hash_data[i] == 1)
            data[pos++] = i;
        if(pos == nums)
            break;
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
    //insert_sort(data, nums);
    //select_sort(data, nums);
    //quick_sort(data, nums);
    hash_sort(data, nums);
    print(data, nums);
    return 0;
}