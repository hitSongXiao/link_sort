#include <iostream>
#include <fstream>
#include <time.h>
#include <cstdlib>
#define MAX 50000
#define NUM 200
#define N 100000
int *num1;
int *num2;
int *num3;
int *sorted;
int Count;
int Max=0;
using namespace std;
void read();
void write();
void Write();
void count_sort(int A[],int B[]);
int main()
{
    write();
    read();
    count_sort(num1,sorted);
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
        //out<<i<<" "<<MAX-(rand()%(MAX/NUM)+(i/NUM)*(MAX/NUM))<<endl;
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
    num1=new int[Count];
    num2=new int[Count];
    num3=new int[Count];
    sorted=new int[Count];
    for(i=0;i<Count;i++)
    {
        in>>x;
        if(x!=i)
            cout<<"wrong"<<endl;
        in>>value;
        if(in.eof())
            break;
        num1[i]=value;
        num2[i]=value;
        num3[i]=value;
        if(value>Max)
            Max=value;
    }
    if(i<Count)
        cout<<"the nums wrong"<<endl;
    Count=i;
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
        out<<sorted[i]<<endl;
    out.close();
    return;
}
void count_sort(int A[],int B[])//¼ÆÊýÅÅÐò
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
