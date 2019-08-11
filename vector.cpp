#include<iostream>
#include<vector>

using namespace std;
int main()
{
 vector<vector<int> > array(4);
    for(int i=0;i<4;i++) {
        array[i].resize(5);
    }
    //输出二维数组的行和列 
    cout<<"Row:"<<array.size()<<"  Column:"<<array[0].size()<<endl;
    //输出二维数组 
    cout<<"["<<endl;
    for(int j=0;j<array.size();j++) {
        cout<<"["<<" ";
        for(int k=0;k<array[0].size();k++) {
            cout<<array[j][k]<<" ";
        }
        cout<<"]"<<endl;
    }
    cout<<"]"<<endl;
    
    
    vector<int>a;
    a(0)=1;
    cout<<a(0);
    return 0;
 } 
