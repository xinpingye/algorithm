#include <stdio.h>

#define MAX_STATUS 1000

#define MAX_STEPS 1000

#define MAX_CUP_1 8
#define MAX_CUP_2 5
#define MAX_CUP_3 3

#define INIT_CUP_1 8
#define INIT_CUP_2 0
#define INIT_CUP_3 0

struct item
{
    int c1;
    int c2;
    int c3;
    int status[MAX_STATUS];
};

void action(int* p_s, int* p_d, int max_dst)
{
    int s = *p_s;
    int d = *p_d;

    if(s == 0 || d == max_dst)
        return;
    if(s > (max_dst - d))
    {
        s = s - (max_dst - d);
        d = d + (max_dst - d);
    }
    else
    {
        d = d + s;
        s = s - s;
    }

    *p_s = s;
    *p_d = d;

    return;
}

int detect_success(int c1, int c2, int c3)
{
    if(c1 == 4 || c2 == 4 || c3 == 4)
        return 1;
    else
        return 0;
}

int detect_repect(int c1, int c2, int c3, int status[MAX_STATUS])
{
    if(status[c1 * 100 + c2 * 10 + c3] != 0)
        return 1;
    else
        return 0;
}

int detect_init_status(int c1, int c2, int c3)
{
    if(c1 == INIT_CUP_1 && c2 == INIT_CUP_2 && c3 == INIT_CUP_3)
        return 1;
    else
        return 0;
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

void one_dimension_array_copy(int dst[MAX_STATUS], int src[MAX_STATUS])
{
    for(int i = 0; i < MAX_STATUS; i++)
        dst[i] = src[i];
}

int min_steps(struct item* bfs, int nums)
{

    struct item next_bfs[nums * 6];
    int next_nums = 0;

    for(int i = 0; i < nums; i++)
    {
        int c1 = bfs[i].c1;
        int c2 = bfs[i].c2;
        int c3 = bfs[i].c3;

        if(detect_repect(c1, c2, c3, bfs[i].status))
            continue;
        if(detect_success(c1, c2, c3))
            return 1;

        bfs[i].status[c1 * 100 + c2 * 10 + c3] = 1;

        action(&c1, &c2, MAX_CUP_2);
        next_bfs[next_nums].c1 = c1;
        next_bfs[next_nums].c2 = c2;
        next_bfs[next_nums].c3 = c3;
        one_dimension_array_copy(next_bfs[next_nums].status, bfs[i].status);
        next_nums++;

        c1 = bfs[i].c1;
        c2 = bfs[i].c2;
        c3 = bfs[i].c3;

        action(&c1, &c3, MAX_CUP_3);
        next_bfs[next_nums].c1 = c1;
        next_bfs[next_nums].c2 = c2;
        next_bfs[next_nums].c3 = c3;
        one_dimension_array_copy(next_bfs[next_nums].status, bfs[i].status);
        next_nums++;

        c1 = bfs[i].c1;
        c2 = bfs[i].c2;
        c3 = bfs[i].c3;

        action(&c2, &c3, MAX_CUP_3);
        next_bfs[next_nums].c1 = c1;
        next_bfs[next_nums].c2 = c2;
        next_bfs[next_nums].c3 = c3;
        one_dimension_array_copy(next_bfs[next_nums].status, bfs[i].status);
        next_nums++;

        c1 = bfs[i].c1;
        c2 = bfs[i].c2;
        c3 = bfs[i].c3;

        action(&c3, &c1, MAX_CUP_1);
        next_bfs[next_nums].c1 = c1;
        next_bfs[next_nums].c2 = c2;
        next_bfs[next_nums].c3 = c3;
        one_dimension_array_copy(next_bfs[next_nums].status, bfs[i].status);
        next_nums++;

        c1 = bfs[i].c1;
        c2 = bfs[i].c2;
        c3 = bfs[i].c3;

        action(&c3, &c2, MAX_CUP_2);
        next_bfs[next_nums].c1 = c1;
        next_bfs[next_nums].c2 = c2;
        next_bfs[next_nums].c3 = c3;
        one_dimension_array_copy(next_bfs[next_nums].status, bfs[i].status);
        next_nums++;

        c1 = bfs[i].c1;
        c2 = bfs[i].c2;
        c3 = bfs[i].c3;

        action(&c2, &c1, MAX_CUP_1);
        next_bfs[next_nums].c1 = c1;
        next_bfs[next_nums].c2 = c2;
        next_bfs[next_nums].c3 = c3;
        one_dimension_array_copy(next_bfs[next_nums].status, bfs[i].status);
        next_nums++;

        c1 = bfs[i].c1;
        c2 = bfs[i].c2;
        c3 = bfs[i].c3;

    }

    if(nums == 1 && detect_init_status(bfs[0].c1, bfs[0].c2, bfs[0].c3))
        return min_steps(next_bfs, next_nums);
    else
        return min_steps(next_bfs, next_nums) + 1;

}

int main()
{

    struct item bfs[1];
    bfs[0].c1 = INIT_CUP_1;
    bfs[0].c2 = INIT_CUP_2;
    bfs[0].c3 = INIT_CUP_3;

    for(int i = 0; i < MAX_STATUS; i++)
        bfs[0].status[i] = 0;

    int nums = 1;

    int result = min_steps(bfs, nums);

    printf("result:%d\n", result);

}