#include <iostream>
#include <fstream>
//#include "Data.h"

template<class T>
class Data {
	struct Elem {
	    // Konstante Members MÜSSEN in der Initialisierungsliste gefüllt werden
	    // nicht-konstante members können, so wie hier, auch in der Initialiserungsliste gefüllt werden
		Elem(T t,Elem* pNext = 0) : m_Content(t),m_pNext(pNext) {}
		T m_Content;
		Elem* m_pNext;
	};
public:
    // sollte überall Data<T> stehen oder ist "Data" auch ausreichend?
	Data() : m_pHead(0) {
	     #if VERBOSE == 1
            std::cout << "Constructor called" << std::endl;
	     #endif
    }

	// Expliziter copy constructor
    // wichtig: const- Parameterübergabe
    Data(const Data &d) : m_pHead(0){
         #if VERBOSE == 1
            std::cout << "normal copy constructor" << std::endl;
	      #endif
	      for(Elem* tmp = d.m_pHead; tmp; tmp = tmp->m_pNext)
              insert(tmp->m_Content);
	}

//   Data(const Data& n) : m_pHead(n.m_pHead){}
    ~Data(){
            #if VERBOSE == 1
           std::cout<< "destructor called" << std::endl;
           #endif
            for(Elem* pTmp = m_pHead; pTmp; pTmp = m_pHead ) {
                m_pHead = m_pHead->m_pNext;
                #if VERBOSE == 1
                    std::cout << "deleting: " << pTmp->m_Content << " adr.:" << &(pTmp) << std::endl;
                #endif
                delete pTmp;
                // muss nicht im destruktor gesetzt werden?!
                pTmp = 0;
            }
    }



    // crArg steht für "constant refrence argument"
    Data& operator=( const Data<T>& crArg ){
        //löscht alle vorhandenen Einträge, GAANZ wichtig;
        // explizit destruktor aufrufen
        this->~Data();
        #if VERBOSE == 1
                std::cout << "Copy constructor called by = operator " << std::endl;
        #endif
	    for(Elem* tmp = crArg.m_pHead; tmp; tmp = tmp->m_pNext)
            insert(tmp->m_Content);

        // ultra wichtig, fragen warum
        return *this;
	}


	unsigned size() const {
		unsigned uiRes = 0;
		for(Elem* pTmp = m_pHead; pTmp; pTmp = pTmp->m_pNext,++uiRes);
		return uiRes;
	}

	void insert(T t) {
	    #if VERBOSE == 1
                std::cout << "inserting: " << t << std::endl;
        #endif

        Elem** pTmp = look4(t);
        *pTmp = new Elem(t, *pTmp);
	}
	void erase(T t) {
	     #if VERBOSE == 1
            std::cout << "Deleting: " << t << std::endl;
	    #endif // VERBOSE

	     Elem** pTmp = look4(t);
	     Elem* pNext = (*pTmp)->m_ pNext;

	     delete(*pTmp);
	    *pTmp = pNext;
	}
	bool find(T t) const {
		for(Elem* pTmp = m_pHead; pTmp && pTmp->m_Content <= t; pTmp =
		            pTmp->m_pNext)
			if (pTmp->m_Content == t)
				return true;
		return false;
	}

	Elem* findElem(T t) const{
        for(Elem* pTmp = m_pHead; pTmp && pTmp->m_Content <= t; pTmp =
		            pTmp->m_pNext)
			if (pTmp->m_pNext->m_Content == t)
                return pTmp;
        return 0;
	}

	void print(unsigned max) const{
		Elem* tmp;
		std::cout << "[";
		for(tmp = m_pHead; tmp && max > 0; tmp = tmp->m_pNext,--max)
			std::cout << tmp->m_Content << "\t";
		if (tmp)
			std::cout << "...";
		std::cout << "]" << std::endl;
	}
private:
	Elem** look4(T t) {
		Elem** pTmp = &m_pHead;
		while (*pTmp && (*pTmp)->m_Content < t)
			pTmp = &((*pTmp)->m_pNext);
		return pTmp;
	}

	Elem* m_pHead;
};

Data<int> readElems(const char* crFile) {
 	Data<int> res;
	std::ifstream s(crFile);
	while (s) {
		int i;
		s >> i;
		if (s)
			res.insert(i);

	}
	return res;
}

Data<int> deleteElems(const char* crFile,Data<int>& crRes) {
	std::ifstream s(crFile);
	Data<int> res(crRes);
	while (s) {
		int i;
		s >> i;
		if (s)
			if (res.find(i))
                res.erase(i);
	}
	return res;
}

