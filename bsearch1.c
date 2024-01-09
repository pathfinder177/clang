#include <stdio.h>

#define LIM 11
#define X 11

int arr_length(int arr[]);
int bs(int l, int i[]);

int main(){
    int i[LIM];
    i[0] = 2;
    i[1] = 3;
    i[2] = 4;
    i[3] = 5;
    i[4] = 6;
    i[5] = 7;
    i[6] = 8;
    i[7] = 9;
    i[8] = 10;
    i[9] = 11;
    i[10] = '\0';

    int l = arr_length(i);

    if (l > 1) {
        if (X == (i[l - 1])) {
            printf("%d\n", l - 1);
        }
        else {
            printf("%d\n", bs(l, i));
        }
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
    int min = 0;
    int max = l-1;
    int mid = max / 2;

    while (mid != 0) {
        if (X == i[mid]) {
            return mid;
        }
        else if (X > i[mid]) {
            min = mid;
            mid = (max + min) / 2;
        }
        else {
            max = mid;
            mid = (max - min) / 2;
        }
    }

    if (X == i[mid]) {
        return mid;
    }
    else {
        return -1;
    }
}
