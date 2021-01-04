#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "part1_helper.h"

void getRand(double *a, int n) //获取[0, 1]之间不重复的n个随机数保存到数组a中
{
    int i, j, m = 0, flag;
    double t = 0.0;
    for (i = 0; i < n; i++) //循环n次得到n个随机数
    {
        while (1)
        {
            flag = 0; //进入while(1)，标志位置0
            t = ((double)rand()) / RAND_MAX;
            // printf("%f\n", t);
            for (j = 0; j < m; j++) //第一次m = 0,不执行循环语句
            {
                if (a[j] == t) //新生成的随机数只要和数组中的元素重复
                {
                    flag = 1; // flag 置1
                    break;    //一旦找到一个重复的，直接跳出for循环
                }
            }
            if (flag == 0) //第一次flag = 0
            {
                a[m++] = t; //生成的随机数和数组中已有的元素不重复时，保存到数组中。
                break;      //跳出while循环，继续获得后面的随机数
            }
        }
    }
}
