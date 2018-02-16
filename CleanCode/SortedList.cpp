template<class T>
class Data {
    struct Elem {
        Elem(T t, Elem* pNext = 0) : m_Content(t), m_pNext(pNext) {}

        T m_Content;
        Elem* m_pNext;
    };

public:
    Data() : m_pHead(0) {}

    Data(const Data &d) : m_pHead(0) {
        copyList(d.m_pHead);
    }

    ~Data() {
        deleteList();
    }

    Data &operator=(const Data<T> &crArg) {
        deleteList();
        copyList(crArg.m_pHead);
        return *this;
    }

    void copyList(Elem* oHead) {
        Elem** myTmp = &m_pHead;
        for (Elem* tmp = oHead; tmp; tmp = tmp->m_pNext) {
            *myTmp = new Elem(tmp->m_Content, tmp->m_pNext);
            myTmp = &((*myTmp)->m_pNext);
        }
    }

    unsigned size() const {
        unsigned uiRes = 0;
        for (Elem* pTmp = m_pHead; pTmp; pTmp = pTmp->m_pNext, ++uiRes);
        return uiRes;
    }

    void insert(T t) {
        Elem** pTmp = look4(t);
        *pTmp = new Elem(t, *pTmp);
    }

    void erase(T t) {
        Elem** pTmp = look4(t);
        if (!(*pTmp) || (*pTmp)->m_Content != t) {
            return;
        }
        Elem* pNext = (*pTmp)->m_pNext;
        delete (*pTmp);
        *pTmp = pNext;
    }

    bool find(T t) const {
        for (Elem* pTmp = m_pHead; pTmp && pTmp->m_Content <= t; pTmp = pTmp->m_pNext)
            if (pTmp->m_Content == t) return true;
        return false;
    }

    void print(unsigned max) const {
        Elem* tmp;
        cout << "[";
        for (tmp = m_pHead; tmp && max > 0; tmp = tmp->m_pNext, --max)
            cout << tmp->m_Content << "\t";
        if (tmp) cout << "...";
        cout << "]" << endl;
    }

private:
    Elem** look4(T t) {
        Elem** pTmp = &m_pHead;
        while (*pTmp && (*pTmp)->m_Content < t) pTmp = &((*pTmp)->m_pNext);
        return pTmp;
    }

    void deleteList() {
        for (Elem* pTmp = m_pHead; pTmp; pTmp = m_pHead) {
            m_pHead = m_pHead->m_pNext;
            delete pTmp;
            pTmp = 0;
        }
    }

    Elem* m_pHead;
};
