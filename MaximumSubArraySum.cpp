#include <bits/stdc++.h> 
long long maxSubarraySum(int arr[], int n)
{
    long long curSum[n];
    long long maxSum = 0;

    for(int i=0; i<n; i++)
    {
        if(i == 0)
        {
            curSum[i] = max(0, arr[i]);
        }
        else
        {
            curSum[i] = max(0ll, curSum[i-1] + arr[i]);    
        }
    
        maxSum = max(maxSum, curSum[i]);
    }

    return maxSum;
}
