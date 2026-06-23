#include <DynamicArray>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    DynamicArray<string> d;
    DynamicArray<string> e;
    cout<<d.size()<<" ";
    cout<<d.capacity();
    d.print();
    d.append("garv");
    d.append("garv1");
    d.append("garv2");
    d.append("garv3");
    d.append("garv4");
    d.append("garv5");
    d.print();
    cout<<d.size()<<" ";
    cout<<d.capacity();
    cout<<endl;
    e=d;
    e.print();
    DynamicArray<int> a(100);
    cout<<a.capacity();
    vector<int> v={1,2,3,4,5};
    DynamicArray<int> b(v);
    DynamicArray<int> c(v.begin(),v.end());
    a.print();
    b.print();
    c.print();
    c[100]=10;
    int y,z;
    c.get(1,y);
    cout<<y<<" "<<z;
    c.set(1,10);
    c.get(1,y);
    cout<<y;
    cout<<endl;
}