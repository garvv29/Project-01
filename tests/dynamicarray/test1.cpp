#include <DynamicArray>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    DynamicArray<int> d;
    DynamicArray<string> e;
    d.append(1);
    d.append(2);
    d.append(3);
    d.insert(1,10);
    d.print();
}