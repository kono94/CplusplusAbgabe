template<class T>
class Data {
	struct Elem {
	    // Konstante Members muessen in der Initialisierungsliste gefuellt werden
	    // nicht-konstante members koennen, so wie hier, auch in der Initialiserungsliste gefuellt werden
		Elem(T t,Elem* pNext = 0) : m_Content(t),m_pNext(pNext) {}
		T m_Content;
		Elem* m_pNext;
	};
public:
    // sollte ueberall Data<T> stehen oder ist "Data" auch ausreichend?
	Data() : m_pHead(0) {
	     #if VERBOSE == 1
            cout << "Constructor called" << endl;
	     #endif
    }

	// Expliziter, eigener copy constructor
    // wichtig: const- Parameterübergabe
    Data(const Data &d) : m_pHead(0){
         #if VERBOSE == 1
            cout << "normal copy constructor" << endl;
	      #endif

	      copyList(d.m_pHead);
	}

    ~Data(){
        #if VERBOSE == 1
            cout<< "destructor called" << endl;
        #endif
        deleteList();
     }



    // crArg steht fuer "constant refrence argument"
    Data& operator=( const Data<T>& crArg ){
        /* Zuerst muss die Liste auf der linken Seite
         des =-Operators korrekt geloescht und der Speicher
         freigegeben werden, da ansonsten die Liste einfach
         mit der Liste auf der rechten Seite ueberschrieben wird.
        */
        deleteList();
        #if VERBOSE == 1
            cout << "Copy constructor called by = operator " << endl;
        #endif

        copyList(crArg.m_pHead);
        return *this;
	}

	void copyList(Elem* oHead){
	    /*
            copyList erwartet den Head, der zu kopierenden Liste.
            Speichert sich dann den Pointer zum eigenen Head jeweils
            wieder in einem Pointer (Double Pointer), um diesen später
            wiederum zu dereferenzieren, um auf genau DIE pointer zuzugreifen,
            die auch die Liste verketten und nicht nur die Kopien von Pointern auf
             dem Stack umzubiegen (Diese sind bekanntlich temporaer und verschwinden
            am Ende der Funktion).
	    */
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
        /*
            Die look4-Methode liefert den Doppel-Pointer
            zurueck, der auf den Pointer zeigt, der
            auf das neue Elemt zeigen soll und quasi
            dazwischen eingehaengt wird.
        */
        Elem** pTmp = look4(t);
        *pTmp = new Elem(t, *pTmp);
	}

	void erase(T t) {
	     #if VERBOSE == 1
            cout << "Deleting: " << t << endl;
	    #endif // VERBOSE

	     Elem** pTmp = look4(t);
	     /*
            look4 sucht nur solange, bis das naechste Element
            groeßer ist, als t.
            Es muss noch zusaetzlich auf Gleichheit geprueft werden.
	     */
	     if(!(*pTmp) || (*pTmp)->m_Content != t){
            return;
	     }

         /*
            Pointer ueberspringt das zu loeschende Element.
            Element wird anschließend geloescht.
         */
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
            // muss eigentlich nicht im destruktor gesetzt werden
            pTmp = 0;
        }
    }

	Elem* m_pHead;
};
