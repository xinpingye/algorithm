#include <stdio.h>

void print(int* map, int r, int c)
{
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
            printf("%d ",*(map + i * c + j));
        printf("\n");
    }
}

int two_point_compare(int* map, int r, int c, int i1, int j1, int i2, int j2)
{
    if(*(map + i1 * r + j1) > *(map + i2 * r + j2))
        return 1;
    else
        return 0;
}

int point_judge(int i, int j, int r, int c)
{
    if(i >= 0 && i < r && j >= 0 && j < c)
        return 1;
    else
        return 0;
}

int continue_judge(int* map, int r, int c, int i, int j, int i1, int j1)
{
    if(point_judge(i1, j1, r, c) && two_point_compare(map, r, c, i, j , i1, j1))
        return 1;
    else
        return 0;
}

int end_judge(int* map, int r, int c, int i, int j)
{
    int i1 = i - 1;
    int j1 = j;
    int i2 = i + 1;
    int j2 = j;
    int i3 = i;
    int j3 = j - 1;
    int i4 = i;
    int j4 = j + 1;
    if(continue_judge(map, r, c, i, j, i1, j1))
        return 0;
    if(continue_judge(map, r, c, i, j, i2, j2))
        return 0;
    if(continue_judge(map, r, c, i, j, i3, j3))
        return 0;
    if(continue_judge(map, r, c, i, j, i4, j4))
        return 0;
    return 1;
    
}

int find_max_result(int* results, int nums)
{
    int max = results[0];
    for(int i = 1; i < nums; i++)
        if(results[i] > max)
            max = results[i];
    return max;
}

int dfs(int* map, int r, int c, int i, int j)
{
    if(end_judge(map, r, c, i, j))
        return 1;

    int i1 = i - 1;
    int j1 = j;
    int i2 = i + 1;
    int j2 = j;
    int i3 = i;
    int j3 = j - 1;
    int i4 = i;
    int j4 = j + 1;

    int result1 = -1, result2 = -1, result3 = -1, result4 = -1;

    if(continue_judge(map, r, c, i, j, i1, j1))
        result1 = dfs(map, r, c, i1, j1);

    if(continue_judge(map, r, c, i, j, i2, j2))
        result2 = dfs(map, r, c, i2, j2);

    if(continue_judge(map, r, c, i, j, i3, j3))
        result3 = dfs(map, r, c, i3, j3);

    if(continue_judge(map, r, c, i, j, i4, j4))
        result4 = dfs(map, r, c, i4, j4);

    int results[4];
    int result_nums = 0;

    if(result1 != -1)
        results[result_nums++] = result1;

    if(result2 != -1)
        results[result_nums++] = result2;

    if(result3 != -1)
        results[result_nums++] = result3;

    if(result4 != -1)
        results[result_nums++] = result4;

    int max = find_max_result(results, result_nums);
    return max + 1;
}


int find_max(int* map, int r, int c)
{
    int max = -1;
    for(int i = 0; i < r; i++)
    {
        for(int j = 0; j < c; j++)
        {
            int result = dfs(map, r, c, i, j);
            if(result > max)
                max = result;
        }
    }
    return max;
}

int main()
{
    int r = 0, c = 0;
    scanf("%d %d\n", &r, &c);
    int map[r][c];
    for(int i = 0; i < r; i++)
        for(int j = 0; j < c; j++)
            scanf("%d", &map[i][j]);
    //print((int*)map, r, c);

    int max = find_max((int*)map, r, c);

    printf("max:%d\n", max);

    return 0;
}