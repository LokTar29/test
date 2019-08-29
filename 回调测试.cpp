#include<iostream>
#include<algorithm>  
#include<stdio.h>
using namespace std;  

int num=0;
bool cmp(const int& a, const int& b)
{
	num++;
	printf("%d %d %d\n",a,b,a<b);
    return a<b;
}

int main()
{ 
    int nums[10] = {4,5,3,2,3,4,6,8,9,10};
    sort(nums, nums+10, cmp);
    for (int i = 0; i < 10; i++);
   //     cout<<nums[i]<<' ';
   // cout<<endl;
   printf("%d\n",num);
    return 0;  
}  
 
