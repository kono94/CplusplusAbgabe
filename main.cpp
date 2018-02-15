#include <iostream>
#include <fstream>

using namespace std;

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

#include "FileHelper.cpp"

int main() {
	Data<int> l1,l2,l3;
	#if VERBOSE == 1
        cout << "READING " << maData << endl;
	#endif
	l1 = readElems(maData);
	#if VERBOSE == 1
        cout << "L1:" << endl;
    #endif
	l1.print(100);
	#if VERBOSE == 1
        cout << "L2:" << endl;
    #endif
	l2.print(100);
	cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          endl;
    #if VERBOSE == 1
        cout << "L1 = L2" << endl;
    #endif
	l2 = l1;
	#if VERBOSE == 1
        cout << "L1:" << endl;
    #endif
	l1.print(100);
	#if VERBOSE == 1
        cout << "L2" << endl;
    #endif
	l2.print(100);
	cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          endl;
    #if VERBOSE == 1
        cout << "DELETEING from " << maData_rm << endl;
    #endif
	l1 = deleteElems(maData_rm,l1);
	#if VERBOSE == 1
        cout << "L1:" << endl;
    #endif
	l1.print(100);
	#if VERBOSE == 1
        cout << "L2:" << endl;
    #endif
	l2.print(100);
	cout << "|l1| = " << l1.size() << " |l2| = " << l2.size() <<
	          endl;

	return 0;
}
