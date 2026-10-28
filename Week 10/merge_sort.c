/***************************************************************
 * Program to implement mergesort in and array in C            *
 * Author: SOORAJ                                              *
 * Date: 12-10-26                                               *
 * Version: 1                                                  *
 ***************************************************************/

#include <stdio.h>

void merge(int arr[], int low, int mid, int high) {
    int i=low, j=mid+1, k=0;
    int temp[high-low+1];
    while(i<=mid && j<=high){
        if(arr[i]<=arr[j])
            temp[k++]=arr[i++];
        else
            temp[k++]=arr[j++];
    }
    while(i<=mid)
        temp[k++]=arr[i++];
    while(j<=high)
        temp[k++]=arr[j++];
    for(i=low, k=0; i<=high; i++, k++)
        arr[i]=temp[k];
}

void mergesort(int arr[], int low, int high) {
    if(low<high){
        int mid=(low+high)/2;
        mergesort(arr, low, mid);
        mergesort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int n, i;
    printf("Enter no. of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter %d elements: ", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    mergesort(arr, 0, n - 1);
    printf("Sorted Array: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}