#include <iostream>
#include <fstream>

#include "DataAufgabe2.cpp"

int main() {
	Data<int> l1,l2;
	std::cout << "READING data.txt" << std::endl;
	l1 = readElems("data_big.txt");
	std::cout << "L1:" << std::endl;
	l1.print(100);
	std::cout << "L2:" << std::endl;
	l2.print(100);
	std::cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          std::endl;
    std::cout << "L1 = L2" << std::endl;
	l2 = l1;
	std::cout << "L1:" << std::endl;
	l1.print(100);
	std::cout << "L2" << std::endl;
	l2.print(100);
	std::cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          std::endl;
    std::cout << "DELETEING from data_remove.txt" << std::endl;
	l1 = deleteElems("data_big_remove.txt",l1);
	std::cout << "L1:" << std::endl;
	l1.print(100);
	std::cout << "L2" << std::endl;
	l2.print(100);
	std::cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          std::endl;
	return 0;
}
