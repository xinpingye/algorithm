#include <stdio.h>

#define MAX_LINE 8
#define MAX_COLUMN 8

int a[MAX_LINE][MAX_COLUMN];

struct point
{
    int l;
    int c;
    int path_map[MAX_LINE][MAX_COLUMN];
};

void print(int data[MAX_LINE][MAX_COLUMN], int lines, int columns)
{
    for(int i = 0; i < lines; i++)
    {
        for(int j = 0; j < columns; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}

void two_dimension_array_copy(int path_map1[MAX_LINE][MAX_COLUMN], int path_map2[MAX_LINE][MAX_COLUMN])
{
    for(int i = 0; i < MAX_LINE; i++)
        for(int j = 0; j < MAX_COLUMN; j++)
            path_map1[i][j] = path_map2[i][j];
}

int min_steps(struct point* bfs, int nums)
{
    printf("234\n");
    struct point next_bfs[nums * 4];
    printf("345\n");
    int next_nums = 0;
    for(int i = 0; i < nums; i++)
    {
        int l = bfs[i].l;
        int c = bfs[i].c;
        if(!((0 <= l && l < MAX_LINE) && (0 <= c && c < MAX_COLUMN)))
            continue;
        if(bfs[i].path_map[l][c] == 1)
            continue;
        if(a[l][c] == 1)
            continue;
        if(l == (MAX_LINE - 1) && c == (MAX_COLUMN - 1))
            return 1;

        bfs[i].path_map[l][c] = 1;

        next_bfs[next_nums].l = l + 1;
        next_bfs[next_nums].c = c;
        //p1.path_map = bfs[i].path_map;
        two_dimension_array_copy(next_bfs[next_nums].path_map, bfs[i].path_map);
        next_nums++;

        next_bfs[next_nums].l = l - 1;
        next_bfs[next_nums].c = c;
        //p2.path_map = bfs[i].path_map;
        two_dimension_array_copy(next_bfs[next_nums].path_map, bfs[i].path_map);
        next_nums++;

        next_bfs[next_nums].l = l;
        next_bfs[next_nums].c = c + 1;
        //p3.path_map = bfs[i].path_map;
        two_dimension_array_copy(next_bfs[next_nums].path_map, bfs[i].path_map);
        next_nums++;

        next_bfs[next_nums].l = l;
        next_bfs[next_nums].c = c - 1;
        //p4.path_map = bfs[i].path_map;
        two_dimension_array_copy(next_bfs[next_nums].path_map, bfs[i].path_map);
        next_nums++;

        bfs[i].path_map[l][c] = 0;
    }
    printf("123\n");
    if (nums == 1 && bfs[0].l == 0 && bfs[0].c == 0)
        return min_steps(next_bfs, next_nums);
    else
        return min_steps(next_bfs, next_nums) + 1;
}

int  main()
{
    freopen("p3.txt", "r", stdin);
    for(int i = 0; i < MAX_LINE; i++)
        for(int j = 0; j < MAX_COLUMN; j++)
            scanf("%d ",&a[i][j]);
    //print(a, MAX_LINE, MAX_COLUMN);

    int path_map[MAX_LINE][MAX_COLUMN];

    for(int i = 0; i < MAX_LINE; i++)
        for(int j = 0; j < MAX_COLUMN; j++)
            path_map[i][j] = 0;
    
    struct point bfs[1];
    bfs[0].l = 0;
    bfs[0].c = 0;
    //p.path_map = path_map;
    two_dimension_array_copy(bfs[0].path_map, path_map);

    int steps = min_steps(bfs, 1);

    printf("min steps:%d\n",steps);
    return 0;
}