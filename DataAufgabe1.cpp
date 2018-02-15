template<class T>
class Data {
	struct Elem {
	    // Konstante Members   in der Initialisierungsliste gefüllt werden
	    // nicht-konstante members können, so wie hier, auch in der Initialiserungsliste gefüllt werden
		Elem(T t,Elem* pNext = 0) : m_Content(t),m_pNext(pNext) {}
		T m_Content;
		Elem* m_pNext;
	};
public:
    // sollte überall Data<T> stehen oder ist "Data" auch ausreichend?
	Data() : m_pHead(0) {
	     #if VERBOSE == 1
            cout << "Constructor called" << endl;
	     #endif
    }

	// Expliziter copy constructor
    // wichtig: const- Parameterübergabe
    Data(const Data &d) : m_pHead(0){
         #if VERBOSE == 1
            cout << "normal copy constructor" << endl;
	      #endif

	      copyList(d.m_pHead);
	}

//   Data(const Data& n) : m_pHead(n.m_pHead){}
    ~Data(){
        #if VERBOSE == 1
            cout<< "destructor called" << endl;
        #endif
        deleteList();
     }



    // crArg steht für "constant refrence argument"
    Data& operator=( const Data<T>& crArg ){
        //löscht alle vorhandenen Einträge, GAANZ wichtig;
        // explizit destruktor aufrufen
        deleteList();
        #if VERBOSE == 1
            cout << "Copy constructor called by = operator " << endl;
        #endif

        copyList(crArg.m_pHead);
        // ultra wichtig, fragen warum
        return *this;
	}

	void copyList(Elem* oHead){
        Elem** myTmp = &m_pHead;

	    for(Elem* tmp = oHead; tmp; tmp = tmp->m_pNext){
            *myTmp = new Elem(tmp->m_Content, tmp->m_pNext);
             myTmp = &((*myTmp)->m_pNext);
	    }
	}

	unsigned size() const {
		unsigned uiRes = 0;
		for(Elem* pTmp = m_pHead; pTmp; pTmp = pTmp->m_pNext,++uiRes);
		return uiRes;
	}

	void insert(T t) {
	    #if VERBOSE == 1
            cout << "inserting: " << t << endl;
        #endif

        Elem** pTmp = look4(t);
        *pTmp = new Elem(t, *pTmp);
	}

	void erase(T t) {
	     #if VERBOSE == 1
            cout << "Deleting: " << t << endl;
	    #endif // VERBOSE

	     Elem** pTmp = look4(t);
	     if(!(*pTmp) || (*pTmp)->m_Content != t){
            return;
	     }

	     Elem* pNext = (*pTmp)->m_pNext;
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

	void print(unsigned max) const{
		Elem* tmp;
		cout << "[";
		for(tmp = m_pHead; tmp && max > 0; tmp = tmp->m_pNext,--max)
			cout << tmp->m_Content << "\t";
		if (tmp)
			cout << "...";
		cout << "]" << endl;
	}
private:
	Elem** look4(T t) {
		Elem** pTmp = &m_pHead;
		while (*pTmp && (*pTmp)->m_Content < t)
			pTmp = &((*pTmp)->m_pNext);
		return pTmp;
	}

	 void deleteList(){
        for(Elem* pTmp = m_pHead; pTmp; pTmp = m_pHead ) {
            m_pHead = m_pHead->m_pNext;
            #if VERBOSE == 1
                cout << "deleting: " << pTmp->m_Content << " adr.:" << &(pTmp) << endl;
            #endif
            delete pTmp;
            // muss nicht im destruktor gesetzt werden?!
            pTmp = 0;
        }
    }

	Elem* m_pHead;
};
