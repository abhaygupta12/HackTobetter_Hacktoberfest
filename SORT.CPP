
#include<stdio.h>
int sort(int a[],int n)
{
int temp,i,j;
 for(i=0;i<n;i++)
 {
 for(j=0;j<n-i;j++)
 {
    if(a[j]>a[j+1])
    temp=a[j];
    a[j+1]=a[j];
    a[j]=temp;
 }
 for(i=0;i<n;i++)
 printf("%d",a[i]);
}}
int main()
{
   int a[10],n,i,j;
   n=5;
   printf("enter numbers");
   for(i=0;i<n;i++)
   scanf("%d",&a[i]);
   sort(a,n);
   }
 
