#include <iostream>
#include <fstream>

using namespace std;

#include "BinarySearchTree.cpp"
#include "FileHelper.cpp"

int main() {
    Data<int> l1, l2;
    l1 = readElems("data_big.txt");
    l1.print(100);
    l2.print(100);
    cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() << endl;
    l2 = l1;
    l1.print(100);
    l2.print(100);
    cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() << endl;
    l1 = deleteElems("data_big_remove.txt", l1);
    l1.print(100);
    l2.print(100);
    cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() << endl;
    return 0;
}
