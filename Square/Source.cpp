#include <iostream>
using namespace std;

struct node {
	int *numbers;
	node *nextNode;

	node() {
		numbers = new int[4];
		nextNode = NULL;
	}
	node(int a, int b, int c, int d) {
		numbers = new int[4];
		nextNode = NULL;
		setNumbers(a, b, c, d);
	}
	node(int *num) {
		numbers = new int[4];
		nextNode = NULL;
		numbers = num;
	}

	void setNumbers(int a, int b, int c, int d) {
		numbers[0] = a;
		numbers[1] = b;
		numbers[2] = c;
		numbers[3] = d;
	}

	void print() {
		cout << numbers[0] << ", \t"
			 << numbers[1] << ", \t"
			 << numbers[2] << ", \t"
			 << numbers[3] << endl;
	}

	bool contains(int searchTerm) {
		for (int i = 0; i < 4;i++) {
			if (numbers[i] == searchTerm) return true;
		}
		return false;
	}
};

struct priorityQueue {
	int *queue;
	int numItems;
	int maxSize;

	priorityQueue(int size) {
		maxSize = size;
		queue = new int[size];
		numItems = 0;
		//makes whole list zero.
		for (int i = 0; i < size; i++) {
			queue[i] = -1;
		}
	}

	void add(int newItem) {
		if (numItems < maxSize) {
			for (int i = 0; i < numItems; i++) {
				if (queue[i] > newItem) swap(queue[i], newItem);
				else if (queue[i] == newItem) return;
			}
			queue[numItems] = newItem;
			numItems++;
		}
		else {
			cout << "ERROR PQ: List is full\n";
		}
	}

	int pull() {
		if (numItems > 0) {
			numItems--;
			return queue[numItems];
		}
		else {
			cout << "ERROR PQ: List is empty\n";
			return -1;
		}
	}

	bool isEmpty() {
		return numItems == 0;
	}

	void read() {
		cout << "numItems: " << numItems << endl;
		for (int i = 0; i < maxSize; i++) {
			cout << i << ": " << queue[i] << endl;
		}
	}
};

struct numberLocalRec {
	priorityQueue **location;
	priorityQueue *mastList;
	int numItems[3];

	numberLocalRec (int listSize) {
		numItems[0] = numItems[1] = numItems[2] = 0;
		location = new priorityQueue*[3];
		mastList = new priorityQueue(3*listSize);

		for (int i = 0; i < 3; i++) {
			location[i] = new priorityQueue(listSize);
		}
	}

	void addLocal(int row, int local) {
		location[row]->add(local);
		numItems[row]++;
		mastList->add(local);
	}

	int pullMast() {
		return mastList->pull();
	}

	bool mastEmpty() {
		return mastList->numItems == 0;
	}

	void readMaster() {
		mastList->read();
	}

};

struct stack {
public:
	node *root;
	int numItems;

	stack() {
		root = new node;
		numItems = 0;
	}

	stack(int a, int b, int c, int d) {
		numItems = 1;
		root = new node;
		root->setNumbers(a, b, c, d);
	}

#pragma region Manipulation
	void removeAll() {
		this->numItems = 0;
		node *bus;
		node *follow;
		bus = new node;
		follow = new node;
		
		if (root != NULL) {
			while (root->nextNode != NULL) {
				bus->nextNode = root->nextNode;
				follow->nextNode = root;
				while (bus->nextNode->nextNode != NULL) {
					follow->nextNode = bus->nextNode;
					bus->nextNode = bus->nextNode->nextNode;
				}
				if (bus->nextNode != root) {
					delete bus->nextNode;
					follow->nextNode->nextNode = NULL;
				}
				else break;
			}
		}
		delete[] root;
		delete[] follow;
		delete[] bus;

		root = new node;
	}

	void removeNode(int nodeNumber) {
		if (nodeNumber == -1) return;
		else if (nodeNumber > numItems - 1) {
			cout << "ERROR: removeNode(nodeNumber) invalid\n";
			return;
		}
		else if (nodeNumber == 0) {
			node *buffer;
			buffer = new node;
			buffer->nextNode = root;
			root = root->nextNode;

			delete[] buffer->nextNode;
			delete[] buffer;
			
			
		}
		else if (nodeNumber == numItems - 1) {
			node *bus;
			bus = new node;

			bus->nextNode = root;

			for (int i = 0; i < numItems - 2; i++) {
				bus->nextNode = bus->nextNode->nextNode;
			}

			node *follow;
			follow = new node;
			follow->nextNode = bus->nextNode;
			bus->nextNode = bus->nextNode->nextNode;

			delete[] bus->nextNode;
			delete[] bus;
			follow->nextNode->nextNode = NULL;
			delete[] follow;

		}
		else {
			node *bus;
			bus = new node;

			bus->nextNode = root;

			for (int i = 0; i < nodeNumber - 1; i++) {
				bus->nextNode = bus->nextNode->nextNode;
			}

			node *follow;
			follow = new node;

			follow->nextNode = bus->nextNode;
			bus->nextNode = bus->nextNode->nextNode;
			//cout << "follow: ";
			//follow->nextNode->print();
			//cout << "bus   : ";
			//bus->nextNode->print();

			follow->nextNode->nextNode = bus->nextNode->nextNode;

			delete[] bus->nextNode;
			delete[] bus;
			delete[] follow;
		}

		numItems--;

	}

	void addNode(int a, int b, int c, int d) {

		if (numItems == 0) {
			root->setNumbers(a, b, c, d);
			numItems++;
			return;
		}
		node *bus, *newNode;
		bus = new node;
		newNode = new node();
		newNode->setNumbers(a, b, c, d);

		bus->nextNode = root;

		while (bus->nextNode->nextNode != NULL) {
			bus->nextNode = bus->nextNode->nextNode;
		}
		bus->nextNode->nextNode = newNode;

		numItems++;
		delete[] bus;

	}

	void pushBottom() {
		node *train;
		node *newNode;
		node *buffer;
		buffer = new node;
		newNode = new node(root->numbers);
		train = new node;
		train->nextNode = root;

		while (train->nextNode->nextNode != NULL) {
			train->nextNode = train->nextNode->nextNode;
		}

		train->nextNode->nextNode = newNode;

		train->nextNode = root->nextNode;
		buffer->nextNode = root;
		root = train->nextNode;

		delete[] train;
		delete[] buffer->nextNode;
		delete[] buffer;
	}
#pragma endregion

	
	void read() {
		node *bus;
		bus = new node;

		bus->nextNode = root;

		while (bus->nextNode->nextNode != NULL) {
			bus->nextNode->print();
			cout << "\n";
			bus->nextNode = bus->nextNode->nextNode;
		}
		bus->nextNode->print();
		cout << "\n";

		delete[] bus;
	}

	int *get(int nodeNumber) {
		if (nodeNumber > numItems - 1) {
			cout << "Out of bounds\n";
		}
		else if (nodeNumber == 0) {
			return root->numbers;
		}

		node *bus;
		bus = new node;
		bus->nextNode = root;
		for (int i = 0; i < nodeNumber; i++) {
			bus->nextNode = bus->nextNode->nextNode;
		}

		return bus->nextNode->numbers;
	}

	void simpleElimate(int rowToCheck) {
		int *numbers;
		int *buffer;
		numberLocalRec *locals;
		
		numbers		= new int(3);
		buffer		= new int(3);
		locals		= new numberLocalRec(numItems);

		numbers = get(rowToCheck);
		//starts at the first combo and works its way down.

		//start finding connection for said row. 
		for (int searchPos = rowToCheck + 1; searchPos < numItems; searchPos++) {
			//starts at next combo and works its way down.

			buffer = get(searchPos);

			for (int keyCol = 0; keyCol < 3; keyCol++) {
				for (int searchCol = 0; searchCol < 3; searchCol++) {

					//finds matches in each row, and adds them to a directory

					if (numbers[keyCol] == buffer[searchCol]) {
						locals->addLocal(keyCol, searchPos);
					}
				}
			}
		}
		//adding things to a directory is done...
		
		//Directory looks like
		//location = [[1,5,8],[4,6],[]]
		//numItems = [3		 ,3	   ,0 ]
			
		//remove all that do not pass.
		for (int pos = 0; pos < 3; pos++) {
			//removes all that only have 0
			
			if (locals->numItems[pos] == 0) {
				while (locals->mastEmpty() != true) {
					removeNode(locals->pullMast());
				}
				removeNode(0);
				return;
			}	
		}
		pushBottom();
		
	}

};

int main() {

	int dMc;

	stack *numberComboRecord;
	numberComboRecord = new stack;
	//a^2 + b^2 = d^2 - c^2;

	//I comfirmed that everything under:
	//380k and less is not possible
	//too long to test resonably.
	for (int i = 380*1000; i <= 385*1000; i++) {
		//Sets our d, increases evertime c hits d-1;
		//starts a new tally

		//in this for loop the next combinations are created and stored
		for (int j = 1; j < i-1; j++) {
			//sets our c, which will be 1 less than d. increases everytime b hits 1
			dMc = i - j*j;
			if (dMc < 1) break;
			for (int k = j; k >= 1; k--) {
				//sets our b which can be equal to c and decreases everytime a hits 1
				for (int l = k; l >= 1; l--) {
					//sets our a which can also equal c and decreases.
					if (l*l + k*k == dMc) {
						//log it and numItems goes up
						numberComboRecord->addNode(l, k, j, i);
					}
					else if (l*l + k*k < dMc) break;
					//a loop
				}
				//b loop
			}
			//c loop
		}		

		//cout << "n: " << numberComboRecord->numItems << endl;
		//numberComboRecord->read();

		//if there are more than 8 combos, check it.
		if (numberComboRecord->numItems >= 8) { 
			//cout << "n: " << numberComboRecord->numItems << endl;
			//numberComboRecord->read();
			//cout << "----------------------------------\n";
			for (int i = 0; i < numberComboRecord->numItems-2; i++) {
				numberComboRecord->simpleElimate(0);
			}
			if (numberComboRecord->numItems >= 8) {
				//FOOOR
				for (int i = 0; i < numberComboRecord->numItems - 2; i++) {
					numberComboRecord->simpleElimate(0);
				}
				if (numberComboRecord->numItems >= 8) {
					//FOOR
					for (int i = 0; i < numberComboRecord->numItems - 2; i++) {
						numberComboRecord->simpleElimate(0);
					}
					if (numberComboRecord->numItems >= 8) {
						//for
						for (int i = 0; i < numberComboRecord->numItems - 2; i++) {
							numberComboRecord->simpleElimate(0);
						}
						if (numberComboRecord->numItems >= 8) {
							cout << "n: " << numberComboRecord->numItems << endl;
							numberComboRecord->read();
							cout << "----------------------------------\n";
						}
					}
					
				}
			}
			//CHECK IT OUT!
		}
		
		//discard if it didnt make the cut
		numberComboRecord->removeAll();
		//d loop
	}
	
	cout << "end;\n";
	delete numberComboRecord;
	system("PAUSE");
	return 0;
}