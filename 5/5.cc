#include <iostream>
#include <cstdio>
#include <cmath>

int main()
{
    int quantity;
    int a[100] = {0};
    int b[100] = {0};
    //int time[200][3] = {0};
    int a_quantity = 0;
    int b_quantity_processed = 1;
    scanf("%d", &quantity);
    for (int i = 0; i < quantity; i++)
    {
        int temp;
        scanf("%d", &temp);
        int indicator = temp % 2;
        if (indicator)
        {
            a[a_quantity] = temp;
            a_quantity++;
            continue;
        }
        b[b_quantity_processed] = temp;
        b_quantity_processed += 2;
    }
    if (a_quantity > b_quantity_processed)
    {
        for (int i = 0; i < a_quantity; i++)
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
        for (int i = 0; i < b_quantity_processed; i++)
        {
            if (i < a_quantity)
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