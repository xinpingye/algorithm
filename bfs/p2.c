#include <stdio.h>

#define MAX_STATUS 1000

#define MAX_STEPS 1000

#define MAX_CUP_1 8
#define MAX_CUP_2 5
#define MAX_CUP_3 3

#define INIT_CUP_1 8
#define INIT_CUP_2 0
#define INIT_CUP_3 0

struct mydata
{
    int c1;
    int c2;
    int c3;
};

//struct mydata actions[MAX_STEPS];
//int steps = 0;

int status[MAX_STATUS];


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

int detect_repect(int c1, int c2, int c3)
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

int dfs(int c1, int c2, int c3)
{
    if(detect_repect(c1,c2,c3))
        return -1;
    if(detect_success(c1,c2,c3))
    {
        //actions[steps].c1 = c1;
        //actions[steps].c2 = c2;
        //actions[steps].c3 = c3;
        //steps++;
        return 1;
    }

    //actions[steps].c1 = c1;
    //actions[steps].c2 = c2;
    //actions[steps].c3 = c3;
    
    //if(!detect_init_status(c1, c2, c3))
        //steps++;

    status[c1 * 100 + c2 * 10 + c3] = 1;

    int results[6];
    int result_nums = 0;

    int c1_bak = c1;
    int c2_bak = c2;
    int c3_bak = c3;

    action(&c1, &c2, MAX_CUP_2);
    int result1 = dfs(c1, c2, c3);
    if(result1 != -1)
        results[result_nums++] = result1;

    c1 = c1_bak;
    c2 = c2_bak;
    c3 = c3_bak;

    action(&c1, &c3, MAX_CUP_3);
    int result2 = dfs(c1, c2, c3);
    if(result2 != -1)
        results[result_nums++] = result2;

    c1 = c1_bak;
    c2 = c2_bak;
    c3 = c3_bak;

    action(&c2, &c3, MAX_CUP_3);
    int result3 = dfs(c1, c2, c3);
    if(result3 != -1)
        results[result_nums++] = result3;

    c1 = c1_bak;
    c2 = c2_bak;
    c3 = c3_bak;

    action(&c3, &c1, MAX_CUP_1);
    int result4 = dfs(c1, c2, c3);
    if(result4 != -1)
        results[result_nums++] = result4;

    c1 = c1_bak;
    c2 = c2_bak;
    c3 = c3_bak;

    action(&c3, &c2, MAX_CUP_2);
    int result5 = dfs(c1, c2, c3);
    if(result5 != -1)
        results[result_nums++] = result5;

    c1 = c1_bak;
    c2 = c2_bak;
    c3 = c3_bak;

    action(&c2, &c1, MAX_CUP_1);
    int result6 = dfs(c1, c2, c3);
    if(result6 != -1)
        results[result_nums++] = result6;

    c1 = c1_bak;
    c2 = c2_bak;
    c3 = c3_bak;

    status[c1 * 100 + c2 * 10 + c3] = 0;

    if(result_nums == 0)
        return -1;

    int min = find_min(results, result_nums);

    if(detect_init_status(c1, c2, c3))
        return min;
    else
        return min + 1;

}




int main()
{
    for(int i = 0; i < MAX_STATUS; i++)
        status[i] = 0;

    int c1 = INIT_CUP_1;
    int c2 = INIT_CUP_2;
    int c3 = INIT_CUP_3;

    int result = dfs(c1, c2, c3);

    printf("result:%d\n", result);

}