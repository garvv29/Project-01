#include "HashMap.h"

int main()
{
    HashMap<int,int> h;
    h.insert(1,2);
    h.insert(2,3);
    h.insert(3,4);
    h.print();
}