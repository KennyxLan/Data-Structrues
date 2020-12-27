#include <iostream>
#include <vector>
#include <iomanip>

class Node {
	friend class Tree;
public:
	explicit Node(int val)
		: data{ val }, parentPtr{ nullptr }, leftPtr{ nullptr }, rightPtr{ nullptr } {}

	int getData() const {
		return data;
	}

private:
	int data;
	Node* parentPtr;
	Node* leftPtr;
	Node* rightPtr;
};

class Tree {
public:
	void insert(int val) {
		Node* newNodePtr = new Node(val);
		if (rootPtr == nullptr) {
			rootPtr = newNodePtr;
			std::cout << '"' << std::setw(3) << val << "\" successfully inserted!\n";
			return;
		}
		Node* currentPtr = rootPtr;
		do {
			if (val < currentPtr->data) {
				if (currentPtr->leftPtr != nullptr)
					currentPtr = currentPtr->leftPtr;
				else {
					currentPtr->leftPtr = newNodePtr;
					newNodePtr->parentPtr = currentPtr;
					currentPtr = nullptr;
				}
			}else{ // val >= currentPtr->data
				if (currentPtr->rightPtr != nullptr)
					currentPtr = currentPtr->rightPtr;
				else {
					currentPtr->rightPtr = newNodePtr;
					newNodePtr->parentPtr = currentPtr;
					currentPtr = nullptr;
				}
			}
		} while (currentPtr != nullptr);
		std::cout << '"' << std::setw(3) << val << "\" successfully inserted!\n";
	}

	void print(int treeWidth = 64, int nodeWidth = 2, char placeHolder = '_') const {
		if (rootPtr == nullptr) {
			std::cout << "The tree is empty.\n";
			return;
		}
		else {
			std::vector<Node*> v;
			v.push_back(rootPtr);
			bool allNullptrThisLevel = false;
			while (allNullptrThisLevel == false) {
				allNullptrThisLevel = true;
				printChar(' ', treeWidth / 2 - nodeWidth / 2);
				std::vector<Node*> w;
				for (int i{ 0 }; i < v.size(); i++) {
					if (v[i] == nullptr) {
						w.push_back(nullptr);
						w.push_back(nullptr);
						printChar(placeHolder, nodeWidth);
					}else {
						allNullptrThisLevel = false;
						w.push_back(v[i]->leftPtr);
						w.push_back(v[i]->rightPtr);
						std::cout << std::setw(nodeWidth) << v[i]->getData();
					}
					printChar(' ', treeWidth - nodeWidth);
				}
				v.clear();
				v = w;
				w.clear();
				std::cout << std::endl;
				treeWidth = treeWidth / 2;
			}
		}
	} // end print()

	bool remove(int value) {
		Node* p = find(value);
		bool result = false;
		if (p == nullptr) {
			std::cout << "cannot find \"" << value << "\" in the tree, removal failed! \n";
			return false;
		}else if (p->parentPtr == nullptr) { // remove at root
			if (p->rightPtr != nullptr) {
				p->data = successor(p)->getData();
				result = removeNonRoot(successor(p));
			}else {
				rootPtr = p->leftPtr;
				if (p->leftPtr != nullptr)
					p->leftPtr->parentPtr = nullptr;
				delete p;
				result = true;
			}
		}else if(p->rightPtr != nullptr){
			p->data = successor(p)->getData();
			result = removeNonRoot(successor(p));
		}else{  // p->rightPtr == nullptr
			if (p->parentPtr->leftPtr == p)
				p->parentPtr->leftPtr = p->leftPtr;
			else
				p->parentPtr->rightPtr = p->leftPtr;
			if (p->leftPtr != nullptr)
				p->leftPtr->parentPtr = p->parentPtr;
			delete p;
			result = true;
		}
		if (result == true) {
			std::cout << '"' << std::setw(3) << value << "\" successfully removed\n";
		}else {
			std::cout << '"' << std::setw(3) << value << "\" FAILED TO BE REMOVED!!!!!!!!!!!\n";
		}
		return result;
	}

	bool removeNonRoot(Node* removePtr) {
		if (removePtr == nullptr || removePtr->parentPtr == nullptr) {
			return false;
		}else{
			if (removePtr->parentPtr->leftPtr == removePtr)
				removePtr->parentPtr->leftPtr = removePtr->rightPtr;
			else
				removePtr->parentPtr->rightPtr = removePtr->rightPtr;
			if(removePtr->rightPtr != nullptr)
				removePtr->rightPtr->parentPtr = removePtr->parentPtr;
			delete removePtr;
			return true;
		}
	}

	void printChar(char c, int n) const{
		for (int j{ 0 }; j < n; j++) {
			std::cout << c;
		}
	}

	Node* find(int val) const {
		if (rootPtr == nullptr) {
			return nullptr;
		}else {
			Node* currentPtr = rootPtr;
			while (currentPtr != nullptr) {
				if (val == currentPtr->getData()) {
					return currentPtr;
				}
				else if (val < currentPtr->getData())
					currentPtr = currentPtr->leftPtr;
				else // val > currentPtr->getData()
					currentPtr = currentPtr->rightPtr;
			}
			return currentPtr;
		}
	}

	Node* successor(Node* x) {
		if (x == nullptr) {
			return nullptr;
		}
		else if (x->rightPtr != nullptr) {
			Node* y = x->rightPtr;
			while (y->leftPtr != nullptr) {
				y = y->leftPtr;
			}
			return y;
		}else{
			while (x->parentPtr != nullptr) {
				if (x->parentPtr->leftPtr == x)
					return x->parentPtr;
				x = x->parentPtr;
			}
			return nullptr;
		}
	}

private:
	Node* rootPtr{ nullptr };
};

int main() {
	Tree myTree;
   // A minus sign indicates removal of the value.
	std::vector<int> inputVector = { 11, 9, 13, 18, 7, 17, 4, 3, 12, 6, -13, 15, -4, 16, -18, -13, 4, 18 };
	std::cout << "inputVector.size() = " << inputVector.size() << " ;\n";
	for (int i{ 0 }; i < inputVector.size(); i++) {
		if (inputVector[i] >= 0)
			myTree.insert(inputVector[i]);
		else if (inputVector[i] < 0)
			myTree.remove(-inputVector[i]);
	}
	std::cout << "\n";
	myTree.print(64, 2, '_');
	return 0;
}



//// for manual input
//	int inputNumber = 0;
//	while (std::cin >> inputNumber) {
//		if (inputNumber >= 0)
//			myTree.insert(inputNumber);
//		else
//			myTree.remove(-inputNumber);
//		myTree.print();
//	}


