#include <iostream>
using namespace std;

int pascal (int baris, int posisi)
{
    if ((posisi==0)||(posisi==baris))
        return 1;
    else
        return pascal (baris-1, posisi)+pascal(baris-1, posisi-1);
        
}
int main()
{
    cout<<"Segitiga pascal 3 tingkat"<<endl;
    cout<<" "<<endl;
    int tinggi=3;
    int spasi=tinggi;
    for(int i=0;i<tinggi;i++)
    
    {
    for (int j=1;j<spasi;j++)
        cout<<"";
    for (int j=0;j<=i;j++)
        cout<<" "<<pascal(i,j)<<" ";
    cout<<endl;
    spasi--;
    }
}