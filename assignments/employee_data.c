#include <stdio.h>
int main()
{
    int n, i, key;
    int low, high, mid, comparisons, found;
    printf("Enter number of employee IDs: ");
    scanf("%d", &n);
    int id[n];
    printf("Enter employee IDs in ascending order:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &id[i]);
    }
    printf("\nEnter employee ID to search: ");
    scanf("%d", &key);
    low = 0;
    high = n - 1;
    comparisons = 0;
    found = 0;
    while(low <= high)
    {
        mid = (low + high) / 2;
        comparisons++;
        if(id[mid] == key)
        {
            printf("\nEmployee ID %d found at position %d\n", key, mid + 1);
            found = 1;
            break;
        }
        else if(key < id[mid])
        {
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    if(found == 0)
    {
        printf("\nEmployee ID %d is absent\n", key);
    }
    printf("Number of comparisons = %d\n", comparisons);
    return 0;
}