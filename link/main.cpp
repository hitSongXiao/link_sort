#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>
#include <queue>
#include <algorithm>
#define MAX 10000
#define NUM 200
#define N 50000
int *nums;
int *num1;
int *num2;
int *num3;
int *sorted_1;
int *sorted_2;
int Count;
int Max;
int maxSize;
int **num;
int all[10];
using namespace std;
void read();
void write();
void Write();
void Bucket(int A[],int B[]);
void count_sort(int A[],int B[]);
void sort_3(int A[],int m);
int num_bite(int x,int m);
int main()
{

    bool flag1,flag2,flag3;
    int start1,end1;
    int start2,end2;
    int start3,end3;
    for(int i=0;i<10;i++)
    {
        Max=0;
        flag1=false;
        flag2=false;
        flag3=false;
        write();
        read();
        num=new int *[10];
        for(int j=0;j<10;j++)
            num[j]=new int[Max];
        start1=clock();
        count_sort(num1,sorted_1);
        end1=clock();
        start2=clock();
        Bucket(num2,sorted_2);
        end2=clock();
        start3=clock();
        sort_3(num3,0);
        end3=clock();
        sort(nums,nums+Count);
        for(int i=0;i<Count;i++)
        {
            if(sorted_1[i]!=nums[i])
            {
                cout<<"count_sort wrong"<<endl;
                flag1=true;
            }
            if(sorted_2[i]!=nums[i])
            {
                cout<<"Bucket sort wrong"<<endl;
                flag2=true;
            }
            if(num3[i]!=nums[i])
            {
                cout<<"basic"<<endl;
                flag3=true;
            }
        }
        if(!flag1)
        {
            cout<<"the count_sort successfully"<<endl;
            cout<<"running time:"<<end1-start1<<"ms"<<endl;
        }
        if(!flag2)
        {
            cout<<"the Bucket sort successfully"<<endl;
            cout<<"running time:"<<end2-start2<<"ms"<<endl;
        }
        if(!flag3)
        {
            cout<<"basic sort"<<endl;
            cout<<"running time:"<<end3-start3<<"ms"<<endl;
        }
        for(int j=0;j<10;j++)
            delete(num[j]);
        delete(num);
    }
    Write();
}
void write()
{
    ofstream out("test.txt",iostream::out);
    if(!out.is_open())
    {
        cout<<"error!"<<endl;
        return;
    }
    out<<N<<endl;
    srand(time(NULL));
    for(int i=0;i<N;i++)
    {
        out<<i<<" "<<rand()%(MAX/NUM)+(i/(MAX/NUM))*(MAX/NUM)<<endl;
        //out<<i<<" "<<rand()%MAX<<endl;
    }
    out.close();
}
void read()
{
    ifstream in("test.txt",iostream::in);
    if(!in.is_open())
    {
        cout<<"error!"<<endl;
        return;
    }
    int i,value,x;
    in>>Count;
    nums=new int[Count];
    num1=new int[Count];
    num2=new int[Count];
    num3=new int[Count];
    sorted_1=new int[Count];
    sorted_2=new int[Count];
    for(i=0;i<Count;i++)
    {
        in>>x;
        if(x!=i)
            cout<<"wrong"<<endl;
        in>>value;
        if(in.eof())
            break;
        nums[i]=value;
        num1[i]=value;
        num2[i]=value;
        num3[i]=value;
        if(value>Max)
            Max=value;
    }
    if(i<Count)
        cout<<"the nums wrong"<<endl;
    Count=i;
    int t=Max;
    maxSize=0;
    while(t!=0)
    {
        t/=10;
        maxSize++;
    }
    in.close();
}
void Write()
{
    ofstream out("write.txt",iostream::out);
    if(!out.is_open())
    {
        cout<<"error!"<<endl;
        return;
    }
    for(int i=0;i<N;i++)
        out<<sorted_1[i]<<endl;
    out.close();
    return;
}
void count_sort(int A[],int B[])
{
    int *CountArr=new int[Max+1];
    for(int i=0;i<=Max;i++)
        CountArr[i]=0;
    for(int i=0;i<Count;i++)
    {
        CountArr[A[i]]++;
    }
    for(int i=1;i<=Max;i++)
    {
        CountArr[i]+=CountArr[i-1];
    }
    for(int i=0;i<Count;i++)
    {
        B[CountArr[A[i]]-1]=A[i];
        CountArr[A[i]]--;
    }
}
void Bucket(int A[],int B[])
{
    int *CountArr=new int[Max+1];
    int x=0;
    for(int i=0;i<Max;i++)
    {
        CountArr[i]=0;
    }
    for(int i=0;i<Count;i++)
    {
        CountArr[A[i]]++;
    }
    for(int i=0;i<=Max;i++)
    {
        while(CountArr[i])
        {
            B[x++]=i;
            CountArr[i]--;
        }
    }
}

void sort_3(int A[],int m)
{
    if(m>maxSize)
    {
        return;
    }
    else{
        for(int i=0;i<10;i++)
            all[i]=0;
        //queue<int>num[10];
        for(int i=0;i<Count;i++)
        {
            int x=num_bite(A[i],m);
        //    num[x].push(A[i]);
            num[x][all[x]++]=A[i];
        }
        int n=0;
        for(int i=0;i<10;i++)
        {
            /*while(!num[i].empty()all[i])
            {
            //    A[n++]=num[i].front();
             //   num[i].pop();
                A[n++]=num[i][--all[i]];
            }*/
            for(int j=0;j<all[i];j++)
            {
                A[n++]=num[i][j];
            }
        }
        sort_3(A,m+1);
        return;
    }
}
int num_bite(int x,int m)
{
    int sum;
    for(int i=0;i<=m;i++)
    {
        sum=x%10;
        x/=10;
    }
    return sum;
}
