#include <stdio.h>

#define LIM 11
#define X 12

int arr_length(int arr[]);
int bs(int l, int i[]);

int main(){
    int i[LIM] = {2,3,4,5,6,7,8,9,10,11,'\0'};

    int l = arr_length(i);

    if (l > 1) {
        printf("%d\n", bs(l, i));
    }
    else if ((l == 1) && (X == i[0])) {
        return 0;
    }
    else {
        return -1;
    }

    return 0;
}

int arr_length(int arr[])
{
    int i;
    int count = 0;
    for(i=0; arr[i]!='\0'; i++)
    {
        count++;
    }
    return count;
}

int bs(int l, int i[])
{
    int min, max, mid;
    min = 0;
    max = l-1;

    while (min <= max) {
        mid = (max + min) / 2;

        if (X > i[mid]) {
            min = mid + 1;
        }
        else if(X < i[mid]) {
            max = mid - 1;
        }
        else {
            return mid;
        }
    }

    return -1;
}
