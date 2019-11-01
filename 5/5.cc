#include <iostream>
#include <cstdio>
#include <cmath>

int main()
{
    int quality;
    int a[100] = {0};
    int b[100] = {0};
    //int time[200][3] = {0};
    int a_quality = 0;
    int b_quality_processed = 1;
    scanf("%d", &quality);
    for (int i = 0; i < quality; i++)
    {
        int temp;
        scanf("%d", &temp);
        int indicator = temp % 2;
        if (indicator)
        {
            a[a_quality] = temp;
            a_quality++;
            continue;
        }
        b[b_quality_processed] = temp;
        b_quality_processed += 2;
    }
    if (a_quality > b_quality_processed)
    {
        for (int i = 0; i < a_quality; i++)
        {
            int indicator = i % 2;
            if (indicator)
            {
                printf("%d ", a[i]);
                if (b[i] != 0)
                {
                    printf("%d ", b[i]);
                }
                continue;
            }
            else
            {
                printf("%d ", a[i]);
            }
        }
    }
    else
    {
        for (int i = 0; i < b_quality_processed; i++)
        {
            if (i < a_quality)
            {
                int indicator = i % 2;
                if (indicator)
                {
                    printf("%d ", a[i]);
                    if (b[i] != 0)
                    {
                        printf("%d ", b[i]);
                    }
                    continue;
                }
                else
                {
                    printf("%d ", a[i]);
                    continue;
                }
            }
            else
            {
                if (b[i] != 0)
                {
                    printf("%d ", b[i]);
                }
            }
        }
    }
    return 0;
}