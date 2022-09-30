#include<bits/stdc++.h>
using namespace std;
int partition(int arr[],int low,int high);
void printt(int arr[])
{
    for(int i=0;i<6;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}
void quicksort(int arr[],int low,int high)
{
    if(low<high)
    {
        int pos=partition(arr,low,high);
        quicksort(arr,low,pos-1);
        quicksort(arr,pos+1,high);
    }
}
int partition(int arr[],int low,int high)
{
    int pivot=arr[low];
    int i=low,j=high;
    while(i<j)
    {
        while(arr[i]<=pivot)
            i++;
        while(arr[j]>pivot)
            j--;
        if(i<j)
            swap(arr[i],arr[j]);
        if(i>j)
            swap(arr[j],arr[low]);
    }
    return j;
}
int main()
{
    int arr[]={2,1,5,3,9,8};
    quicksort(arr,0,5);
    cout<<"Sorted Array : ";
    for(int i=0;i<6;i++)
        cout<<arr[i]<<" ";
}
