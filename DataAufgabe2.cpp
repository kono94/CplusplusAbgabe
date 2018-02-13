#include <iostream>
#include <fstream>

//Binärbaum

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
	Data() : m_pRoot(0), m_iSize(0) {std::cout << "Constructor called" << std::endl;}

  ~Data(){
           std::cout<< "destructor called" << std::endl;
           destroyTree(m_pRoot);
	}


	Data(const Data &d) : m_pRoot(0), m_iSize(0){
	      std::cout << "normal copy constructor" << std::endl;
	       m_pRoot = copyTree(d.m_pRoot);
	}


    Data& operator=( const Data& d ){
        //löscht alle vorhandenen Einträge, GAANZ wichrig;
        // explizit destruktor aufrufen

        this->~Data();
        m_iSize = 0;
	    std::cout << "Copy constructor called by = operator " << std::endl;
        m_pRoot =  copyTree(d.m_pRoot);
        // ultra wichtig, fragen warum
        return *this;
	}


	unsigned size() const {
		return m_iSize;
	}


	void insert(T t) {
	   insert(m_pRoot,t);
	   ++m_iSize;
	}

	void insert(Node*& n, T t){
        if (n == 0)
            n = new Node(t);
        else if (n->m_Content > t)
            insert(n->m_pLeft, t);
        else if(n->m_Content < t)
            insert(n->m_pRight, t);
        else
            n->m_iCount = n->m_iCount + 1;
    }


	void erase(T t) {
            //std::cout << "Deleting: " << t << std::endl;
            m_pRoot = eraseNode(m_pRoot,t);
    }

    Node*  eraseNode(Node* n, T t){
        // base case
        if (n == NULL) return n;

        // If the key to be deleted is smaller than the n's key,
        // then it lies in left subtree
        if (t < n->m_Content)
            n->m_pLeft = eraseNode(n->m_pLeft, t);

        // If the key to be deleted is greater than the n's key,
        // then it lies in right subtree
        else if (t > n->m_Content)
            n->m_pRight = eraseNode(n->m_pRight, t);

        // if key is same as n's key, then This is the node
        // to be deleted
        else {
            if(n->m_iCount > 1){
                n->m_iCount -= 1;
                --m_iSize;
                return n;
            }
            // node with only one child or no child
            if (n->m_pLeft == NULL) {
                Node* temp = n->m_pRight;
                delete n;
                --m_iSize;
                // sollte auf nullpointer gesetzt werden?
                n = 0;
                return temp;
            }else if (n->m_pRight == NULL) {
                Node* temp = n->m_pLeft;
                delete n;
                --m_iSize;
                // sollte auf nullpointer gesetzt werden?
                n = 0;
                return temp;
            }

            // node with two children: Get the inorder successor (smallest
            // in the right subtree)
            Node* temp = n->m_pRight;
            while (temp->m_pLeft != NULL)
                    temp = temp->m_pLeft;

            // Copy the inorder successor's content to this node
            n->m_Content = temp->m_Content;

            // Delete the inorder successor
            n->m_pRight = eraseNode(n->m_pRight, temp->m_Content);
        }
        return n;
    }

	bool find(T t) const {
		return findHelper(m_pRoot, t);
	}

	void print(unsigned max) {
	    std::cout << "[";
	    if(m_pRoot){
            if(printHelper(m_pRoot, max) >= max)
            std::cout << "...";
	    }
        std::cout << "]" << std::endl;
	}
private:

    unsigned int printHelper(Node* n, unsigned int max){
        unsigned c = 0;
            if(n->m_pLeft)
                c = printHelper(n->m_pLeft, max);

            if(max > c){
                for(unsigned i = 0; i< n->m_iCount && max > c; ++i){
                    std::cout << n->m_Content << " ";
                    ++c;
                }
                if(n->m_pRight && max > c)
                    c = printHelper(n->m_pRight, max);
            }
        return c;
    }

    bool findHelper(Node* n, T t){
        if(n){
            if(n->m_Content == t){
                return true;
            }else{
                find_helper(n->m_pLeft, t);
                find_helper(n->m_pRight, t);
            }
        }else{
            return false;
        }
    }

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

	void destroyTree(Node* n){
	  if(n){
            destroyTree(n->m_pLeft);
            destroyTree(n->m_pRight);
            delete n;
        }
	}
private:
	Node* m_pRoot;
	unsigned m_iSize;
};
Data<int> readElems(const char* crFile) {
 	Data<int> res;
	std::ifstream s(crFile);
	while (s) {
		int i;
		s >> i;
		if (s) {
			res.insert(i);
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
            res.erase(i);
	}
	return res;
}

