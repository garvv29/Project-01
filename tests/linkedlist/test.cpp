#include <iostream>
#include <SinglyList>
using namespace std;
int main()
{
    try{
    SinglyList<int> l;
    l.insert(0,10);
    l.insert(0,11);
    l.insert(1,12);
    l.insert(3,13);
    l.print();
    std::cout<<l.size()<<endl;
    l.remove(4);
    l.print();
    }
    catch(...){
        cout<<"Error : "<<"out of bound"<<endl;
    }

}