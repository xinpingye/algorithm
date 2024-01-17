#include <stdio.h>

#define MAX_LINE 8
#define MAX_COLUMN 8

int a[MAX_LINE][MAX_COLUMN];
int path_map[MAX_LINE][MAX_COLUMN];

void print(int data[MAX_LINE][MAX_COLUMN], int lines, int columns)
{
    for(int i = 0; i < lines; i++)
    {
        for(int j = 0; j < columns; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

int find_min(int v[], int nums)
{
    int min = v[0];
    for(int i = 1; i < nums; i++)
    {
        if(v[i] < min)
            min = v[i];
    }
    return min;
}

int min_steps(int l, int c)
{
    if(!((l >= 0 && l < MAX_LINE) && (c >= 0 && c < MAX_COLUMN)))
        return -1;
    if(a[l][c] == 1)
        return -1;
    if(path_map[l][c] == 1)
        return -1;
    if(l == (MAX_LINE - 1) && c == (MAX_COLUMN - 1))
        return 1;

    path_map[l][c] = 1;

    int to_right_min_steps = min_steps((l + 1), c);
    int to_left_min_steps = min_steps((l - 1), c);
    int to_up_min_steps = min_steps(l, (c - 1));
    int to_down_min_steps = min_steps(l, (c + 1));

    int nums = 0;
    int v[4];
    if(to_right_min_steps != -1)
        v[nums++] = to_right_min_steps;
    if(to_left_min_steps != -1)
        v[nums++] = to_left_min_steps;
    if(to_up_min_steps != -1)
        v[nums++] = to_up_min_steps;
    if(to_down_min_steps != -1)
        v[nums++] = to_down_min_steps;

    if(nums == 0)
    {
        path_map[l][c] = 0;
        return -1;
    }

    int min = find_min(v, nums);

    if( l == 0 && c == 0)
    {
        path_map[l][c] = 0;
        return min;
    }
    else
    {
        path_map[l][c] = 0;
        return min + 1;
    }
}

int  main()
{
    freopen("p1.txt", "r", stdin);
    for(int i = 0; i < MAX_LINE; i++)
        for(int j = 0; j < MAX_COLUMN; j++)
            scanf("%d ",&a[i][j]);
    //print(a, MAX_LINE, MAX_COLUMN);

    for(int i = 0; i < MAX_LINE; i++)
        for(int j = 0; j < MAX_COLUMN; j++)
            path_map[i][j] = 0;
    int steps = min_steps(0, 0);
    printf("min steps:%d\n",steps);
    return 0;
}