#include <iostream>
#include <fstream>

#define AUFG 1
#define VERBOSE 1


#if AUFG == 1
    #include "DataAufgabe1.cpp"
    #define maData "data.txt"
    #define maData_rm "data_remove.txt"
#endif // AUFG

#if AUFG == 2
    #include "DataAufgabe2.cpp"
    #define maData "data_big.txt"
    #define maData_rm "data_big_remove.txt"
#endif // AUFG

int main() {
	Data<int> l1,l2;
	#if VERBOSE == 1
        std::cout << "READING " << maData << std::endl;
	#endif
	l1 = readElems(maData);
	#if VERBOSE == 1
        std::cout << "L1:" << std::endl;
    #endif
	l1.print(100);
	#if VERBOSE == 1
        std::cout << "L2:" << std::endl;
    #endif
	l2.print(100);
	std::cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          std::endl;
    #if VERBOSE == 1
        std::cout << "L1 = L2" << std::endl;
    #endif
	l2 = l1;
	#if VERBOSE == 1
        std::cout << "L1:" << std::endl;
    #endif
	l1.print(100);
	#if VERBOSE == 1
        std::cout << "L2" << std::endl;
    #endif
	l2.print(100);
	std::cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          std::endl;
    #if VERBOSE == 1
        std::cout << "DELETEING from " << maData_rm << std::endl;
    #endif
	l1 = deleteElems(maData_rm,l1);
	#if VERBOSE == 1
        std::cout << "L1:" << std::endl;
    #endif
	l1.print(100);
	#if VERBOSE == 1
        std::cout << "L2:" << std::endl;
    #endif
	l2.print(100);
	std::cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          std::endl;
	return 0;
}
