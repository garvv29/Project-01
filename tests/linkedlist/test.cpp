#include <iostream>
#include <SinglyList>

int main()
{
    SinglyList<int> l;
    l.insert(0,10);
    l.insert(0,11);
    l.insert(1,12);
    l.insert(3,13);
    l.print();
    l.clear();
    l.print();
}