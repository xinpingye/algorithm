#include <stdio.h>

#define single_max_time 60
#define max_nums 20

struct mem_status
{
    int status[61];
    int value;
};

struct mem_status mem_all_status[10000];
int mem_status_nums = 0;

int action(int* status, int i, int j)
{

    if(status[i] == 0)
    {
        int result = status[j];
        status[j] = 0;
        return result;
    }

    if(status[j] == 0)
    {
        int result = status[i];
        status[i] = 0;
        return result;
    }

    if(status[i] < status[j])
    {
        int result = status[i];
        status[j] = status[j] - status[i];
        status[i] = status[i] - status[i];
        return result;
    }
    else if(status[i] == status[j])
    {
        int result = status[i];
        status[i] = 0;
        status[j] = 0;
        return result;
    }
    else
    {
        int result = status[j];
        status[i] = status[i] - status[j];
        status[j] = status[j] - status[j];
        return result;
    }
}

void action_undo(int* status, int i, int j, int v_i, int v_j)
{
    status[i] = v_i;
    status[j] = v_j;
    return;
}

int detect_wrong_action(int* status, int i, int j)
{
    if(status[i] == 0 && status[j] == 0)
        return 1;
    else
        return 0;
}

int detect_end(int* status, int nums)
{
    for(int i = 0; i < nums; i++)
        if(status[i] != 0)
            return 0;
    return 1;
}

int find_min(int* data, int nums)
{
    int min = data[0];
    for(int i = 1; i < nums; i++)
        if(data[i] < min)
            min = data[i];
    return min;
}

void print(int* status, int nums)
{
    for(int i = 0; i < nums; i++)
        printf("%d ", status[i]);
    printf("\n");
}

int two_array_compare(int status1[61], int status2[61])
{
    for(int i = 1; i < 61; i++)
        if(status1[i] != status2[i])
            return 0;
    return 1;;
}

int repeat_status(int status_general[61])
{
    for(int i = 0; i < mem_status_nums; i++)
        if(two_array_compare(status_general, mem_all_status[i].status))
            return  mem_all_status[i].value;
    return -1;
}

void two_array_copy(int status1[61], int status2[61])
{
    for(int i = 1; i < 61; i++)
        status1[i] = status2[i];
}

int dfs(int* status, int nums, int i, int j)
{

    int status_general[61];

    for(int i = 1; i < 61; i++)
        status_general[i] = 0;

    for(int i = 0; i < nums; i++)
        status_general[status[i]]++;

    int compare_result = repeat_status(status_general);
    if(compare_result != -1)
        return compare_result;
        
    //printf("here4\n");
    if(detect_end(status, nums))
        return 0;
    //printf("here5\n");
    if(detect_wrong_action(status, i, j))
        return -1;
    //printf("here6\n");

    //print(status, nums);

    int v_i = status[i];
    int v_j = status[j];
    int time = action(status, i, j);

    for(int i = 1; i < 61; i++)
        status_general[i] = 0;

    for(int i = 0; i < nums; i++)
        status_general[status[i]]++;

    //printf("here7\n");

    int select_i = -1;
    int select_j = -1;

    for(int i = 0; i < nums - 1; i++)
    {
        for(int j = i + 1; j < nums; j++)
        {
            if(status[i] == status[j] && status[i] != 0)
            {
                select_i = i;
                select_j = j;
                break;
            }
        }
    }
    
    int min;

    if(select_i != -1)
        min = dfs(status, nums, select_i, select_j);
    else
    {
        int results[max_nums * max_nums];
        int results_nums = 0;

        for(int i = 0; i < nums - 1; i++)
        {
            for(int j = i + 1; j < nums; j++)
            {
                int time = dfs(status, nums, i, j);
                if(time != -1)
                    results[results_nums++] = time;
            }
        }
        min = find_min(results, results_nums);
    }

    //printf("here8\n");

    action_undo(status, i, j, v_i, v_j);

    //printf("here time:%d\n", time);

    two_array_copy(mem_all_status[mem_status_nums].status, status_general);
    mem_all_status[mem_status_nums].value = min;
    mem_status_nums++;

    return time + min;

}

int min_times(int* status, int nums)
{
    int min_time = single_max_time * max_nums;
    if(nums == 1)
        return status[0];
    //printf("here1\n");

    int select_i = -1;
    int select_j = -1;


    for(int i = 0; i < nums - 1; i++)
    {
        for(int j = i + 1; j < nums; j++)
        {
            if(status[i] == status[j] && status[i] != 0)
            {
                select_i = i;
                select_j = j;
                break;
            }
        }
    }

    if(select_i != -1)
    {
        min_time = dfs(status, nums, select_i, select_j);
        //printf("here111\n");
    }
    else
    {
        //printf("here222\n");
        for(int i = 0; i < nums - 1; i++)
        {
            for(int j = i + 1; j < nums; j++)
            {
                //printf("here2\n");
                int time = dfs(status, nums, i, j);
                //printf("here time:%d i:%d j:%d\n", time, i, j);
                if(time < min_time)
                    min_time = time;
                //printf("here3\n");
            }
        }
    }
    return min_time;
}

int main()
{
    int s1, s2, s3, s4;
    scanf("%d", &s1);
    scanf("%d", &s2);
    scanf("%d", &s3);
    scanf("%d", &s4);

    int time = 0;

    int status[max_nums];

    for(int i = 0; i < s1; i++)
        scanf("%d", &status[i]);
    time += min_times(status,s1);

    //printf("time:%d\n", time);

    for(int i = 0; i < s2; i++)
        scanf("%d", &status[i]);
    time += min_times(status,s2);

    //printf("time:%d\n", time);

    for(int i = 0; i < s3; i++)
        scanf("%d", &status[i]);
    time += min_times(status,s3);

    //printf("time:%d\n", time);

    for(int i = 0; i < s4; i++)
        scanf("%d", &status[i]);
    time += min_times(status,s4);

    printf("%d", time);

    return 0;


        
}
