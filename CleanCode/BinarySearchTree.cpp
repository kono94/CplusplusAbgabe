template<class T>
class Data {
	struct Node {
		Node(T t, unsigned iCount = 1, Node* pLeft = 0, Node* pRight = 0) : m_Content(t), m_iCount(iCount), m_pLeft(pLeft), m_pRight(pRight) {}
		T m_Content;
		unsigned m_iCount;
		Node* m_pLeft;
		Node* m_pRight;
	};
public:
	Data() : m_pRoot(0), m_iSize(0) {}

   ~Data(){
        destroyTree(m_pRoot);
	}

	Data(const Data &d) : m_pRoot(0), m_iSize(0){
	    m_pRoot = copyTree(d.m_pRoot);
	}

    Data& operator=( const Data& d ){
        destroyTree(m_pRoot);
        m_pRoot = copyTree(d.m_pRoot);
        return *this;
	}

	unsigned size() const {
		return m_iSize;
	}

	void insert(T t) {
	   Node** pTmp = look4(t);
	   if((*pTmp) == 0)
            (*pTmp) = new Node(t);
       else
            (*pTmp)->m_iCount += 1;
	   ++m_iSize;
	}

	void erase(T t) {
        Node** tmp = look4(t);
        if(!(*tmp)){
            return;
        }
        if((*tmp)->m_iCount > 1){
            (*tmp)->m_iCount -= 1;
            return;
        }
        //keine Söhne
        if((*tmp)->m_pLeft == 0 && (*tmp)->m_pRight == 0){
            delete (*tmp);
            (*tmp) = 0;
        }
        // Nur einen rechten Sohn
        else if((*tmp)->m_pLeft){
            Node* skipper = (*tmp)->m_pRight;
            delete (*tmp);
            (*tmp) = skipper;
        }
        // Nur einen linken Sohn
        else if((*tmp)->m_pRight){
            Node* skipper = (*tmp)->m_pLeft;
            delete (*tmp);
            (*tmp) = skipper;
        }
        // zwei Söhne
        else{
            // speicher verweis auf zu löschenden knoten
             Node* pDel = (*tmp);
             Node* pFa = (*tmp);
             Node* pSon = (*tmp)->m_pLeft;

            // finde den größten kleinsten Knoten zum ersetzen
             while(!(pSon->m_pRight)){
                pFa = pSon;
                pSon = pSon->m_pRight;
             }

             (*tmp) = pSon;

             if(pFa != pDel)
                pFa->m_pRight = pSon->m_pLeft;
             if(pSon != pDel->m_pLeft)
                pSon->m_pLeft = pDel->m_pLeft;
             if(pSon != pDel->m_pRight)
                pSon->m_pRight = pDel->m_pRight;

             delete pDel;
        }
    }

	bool find(T t) const {
	    return look4(t);
	}

	void print(unsigned max) {
	    cout << "[";
	    if(m_pRoot){
            if(printHelper(m_pRoot, max) >= max)
            cout << "...";
	    }
        cout << "]" << endl;
	}

private:
     Node* copyTree(Node* n){
        if(n){
            Node* newNode = new Node(n->m_Content, n->m_iCount);
            m_iSize += n->m_iCount;
            newNode->m_pLeft = copyTree(n->m_pLeft);
            newNode->m_pRight = copyTree(n->m_pRight);
            return newNode;
        }else{
            return 0;
        }
    }

    void destroyTree(Node*& n){
	  if(n){
            m_iSize = m_iSize - n->m_iCount;
            destroyTree(n->m_pLeft);
            destroyTree(n->m_pRight);
            delete n;
            n = 0;
        }
	}


    Node** look4(T t){
        Node** pTmp = &m_pRoot;
        while (*pTmp && (*pTmp)->m_Content != t){
            if((*pTmp)->m_Content > t)
               pTmp = &((*pTmp)->m_pLeft);
            else
                pTmp = &((*pTmp)->m_pRight);
        }
		return pTmp;
    }

    unsigned int printHelper(Node* n, unsigned int max){
        unsigned c = 0;
            if(n->m_pLeft)
                c = printHelper(n->m_pLeft, max);

            if(max > c){
                for(unsigned i = 0; i< n->m_iCount && max > c; ++i){
                    cout << n->m_Content << " ";
                    ++c;
                }
                if(n->m_pRight && max > c)
                    c = printHelper(n->m_pRight, max);
            }
        return c;
    }

    Node* m_pRoot;
    unsigned m_iSize;
};

