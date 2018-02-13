#include <iostream>
#include <fstream>
//#include "Data.h"

template<class T>
class Data {
	struct Elem {
		Elem(T t,Elem* pNext = 0) : m_Content(t),m_pNext(pNext) {}
		T m_Content;
		Elem* m_pNext;
	};
public:
	Data() : m_pHead(0) {std::cout << "Constructor called" << std::endl;}


//   Data(const Data& n) : m_pHead(n.m_pHead){}
  ~Data(){
           std::cout<< "destructor called" << std::endl;
            for(Elem* pTmp = m_pHead; pTmp; pTmp = m_pHead ) {
                m_pHead = m_pHead->m_pNext;
                std::cout << "deleting: " << pTmp->m_Content << " adr.:" << &(pTmp) << std::endl;
                delete pTmp;
                // muss nicht im destruktor gesetzt werden?!
                pTmp = 0;
            }
	}

	Data(const Data &d) : m_pHead(0){
	      std::cout << "normal copy constructor" << std::endl;
	      for(Elem* tmp = d.m_pHead; tmp; tmp = tmp->m_pNext)
            insert(tmp->m_Content);
	}


    Data& operator=( const Data& d ){
        //l�scht alle vorhandenen Eintr�ge, GAANZ wichrig;
        // explizit destruktor aufrufen
        this->~Data();
	    std::cout << "Copy constructor called by = operator " << std::endl;
	    for(Elem* tmp = d.m_pHead; tmp; tmp = tmp->m_pNext)
            insert(tmp->m_Content);

        // ultra wichtig, fragen warum
        return *this;
	}


	Data::unsigned size() const {
		unsigned uiRes = 0;
		for(Elem* pTmp = m_pHead; pTmp; pTmp = pTmp->m_pNext,++uiRes);
		return uiRes;
	}

	void insert(T t) {
	    if(m_pHead == 0){
            m_pHead = new Elem(t, 0);
	    }else{
            Elem** pTmp = look4(t);
            if(*pTmp == m_pHead){
                m_pHead = new Elem(t, m_pHead);
            }else{
                *pTmp = new Elem(t, *pTmp);
            }
        }
	}
	void erase(T t) {
	    std::cout << "Deleting: " << t << std::endl;
	    Elem* toDelete = 0;
	    if(m_pHead->m_Content == t){
             toDelete = m_pHead;
             m_pHead = m_pHead->m_pNext;
             delete toDelete;
             // hier sollte der Pointer zum nullpointer gesetzt werden
             toDelete = 0;
             std::cout << "head changed" << std::endl;
	    }else{
            Elem* prev = findElem(t);
           // std::cout << "tmp" << (*tmp)->m_Content << " "<< (*tmp)->m_Content << std::endl;
            if(prev != 0){
                 std::cout << "prev != 0" << std::endl;
                 toDelete = prev->m_pNext;
                 prev->m_pNext = prev->m_pNext->m_pNext;
                 delete toDelete;
                 toDelete = 0;
            }
	    }
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
private:
	Elem* m_pHead;
};
Data<int> readElems(const char* crFile) {
 	Data<int> res;
	std::ifstream s(crFile);
	while (s) {
		int i;
		s >> i;
		if (s) {
			res.insert(i);
			std::cout << "inserted: " << i << std::endl;
		}
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
