
#include "main.h"

int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

class RESTAURANT_Gojo{
	class Tree_BST;
private:
	vector<Tree_BST> areaTable;
public:
	RESTAURANT_Gojo():areaTable(MAXSIZE + 1){}
	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result);
	}
	void remove_KOKUSEN()
	{
		for(int i = 1; i < MAXSIZE + 1; i++) areaTable[i].remove();		
 	}

	void print_LIMITLESS(int number)
	{
		if(number <= 0 || number > MAXSIZE) return;
		areaTable[number].print();
	}
private:
	class Tree_BST{
		class Node;
	private:
		Node* root;	
		queue<int> queueTime; 
	public:
		Tree_BST():root(nullptr){}
		~Tree_BST()
		{
			while(!queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 						
				root = remove_recursive(root ,temp);
			}
		}
		int size(){
			return queueTime.size();
		}
		Node *insert_recursive(Node *node, int result)
		{
			if (node == nullptr)
			{
				queueTime.push(result);
				Node *temp = new Node(result);
				return temp;
			}
			else
			{
				if (result >= node->result)
				{
					node->right = insert_recursive(node->right, result);
				}
				else
				{
					node->left = insert_recursive(node->left, result);
				}
			}
			return node;
		}
		void insert(int result)
		{
			root = insert_recursive(root, result);
		}
		Node *findMin(Node *node)
		{
			if (node == nullptr)
				return nullptr;
			while (node->left != nullptr)
			{
				node = node->left;
			}
			return node;
		}

		Node *findMax(Node *node)
		{
			while (node->right != nullptr)
			{
				node = node->right;
			}
			return node;
		}

		Node *remove_recursive(Node *node, int result)
		{
			if (node == nullptr)
			{
				return nullptr;
			}

			if (result > node->result)
			{
				node->right = remove_recursive(node->right, result);
			}
			else if (result < node->result)
			{
				node->left = remove_recursive(node->left, result);
			}
			else
			{
				if (node->left == nullptr && node->right == nullptr){
					node = nullptr;
				}
				else if (node->right == nullptr)
				{
					Node *temp = node;
					node = node->left;
					delete temp;
				}
				else if (node->left == nullptr)
				{
					Node *temp = node;
					node = node->right;
					delete temp;
				}
				else
				{
					Node *temp = findMin(node->right);
					node->result = temp->result;
					node->right = remove_recursive(node->right, temp->result);
				}
			}

			return node;
		}
		unsigned long long binomialCoefficient(unsigned long long x, unsigned long long n)
		{
			vector<vector<unsigned long long>> dp(n + 1, vector<unsigned long long>(x + 1, 0));

			for (unsigned long long i = 0; i <= n; i++)
			{
				for (unsigned long long j = 0; j <= x && j <= i; j++)
					(j == 0 || j == i) ? dp[i][j] = 1 : (dp[i][j] = (dp[i - 1][j - 1]%MAXSIZE + dp[i - 1][j]%MAXSIZE));
			}

			return dp[n][x]%MAXSIZE;
		}

		int CountNode(Node *node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}

		unsigned long long DFS(Node *node)
		{
			if (node == NULL) return 1;

			unsigned long long NodeRight = CountNode(node->right);
			unsigned long long NodeLeft = CountNode(node->left);

			return (DFS(node->left) * DFS(node->right) * binomialCoefficient(NodeLeft, NodeLeft + NodeRight)) % MAXSIZE;
		}
		void remove(){
			if(queueTime.empty()) return;
			
			unsigned long long number = DFS(root) % MAXSIZE;
			
			
			while(number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		
				queueTime.pop(); 					
				root = remove_recursive(root ,temp);
				number --;
			}
		}
		void print_recursive(Node* node)
		{
			if(node != NULL){
				print_recursive(node->left);
				cout << node->result << "\n";
				print_recursive(node->right);
			}
		}
		void print(){print_recursive(root);}
	private:
		class Node{
		private:
			int result;
			Node* left;
			Node* right;
			friend class Tree_BST;
		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};

};

class RESTAURANT_Sukuna{
	class Node;
private:
	vector<Node* > areaTable;
	list<Node* > LRU; 
private:
	int getIndex(Node *temp)
	{
		int result = 0;
		for (Node *tmp : LRU)
		{
			if (temp == tmp)
				break;
			++result;
		}
		return result;
	}

	void ReHeap_down(int index)
	{
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int largest = index;

		if (leftChild < int(int(areaTable.size())))
		{
			if (areaTable[leftChild]->size() < areaTable[largest]->size())
				largest = leftChild;
			else if (areaTable[leftChild]->size() == areaTable[largest]->size())
			{
				if (getIndex(areaTable[leftChild]) > getIndex(areaTable[largest]))
					largest = leftChild;
			}
		}

		if (rightChild < int(int(areaTable.size())))
		{
			if (areaTable[rightChild]->size() < areaTable[largest]->size())
				largest = rightChild;
			else if (areaTable[rightChild]->size() == areaTable[largest]->size())
			{
				if (getIndex(areaTable[rightChild]) > getIndex(areaTable[largest]))
					largest = rightChild;
			}
		}

		if (largest != index)
		{
			swap(areaTable[index], areaTable[largest]);
			ReHeap_down(largest);
		}
	}

	void ReHeap_up(int index)
	{
		int parentIndex = (index - 1) / 2;

		while (index > 0 && areaTable[index]->size() < areaTable[parentIndex]->size())
		{
			swap(areaTable[index], areaTable[parentIndex]);
			index = parentIndex;
			parentIndex = (index - 1) / 2;
		}
	}

	void moveTop(Node *node)
	{
		bool check = false;
		for (Node *temp : LRU)
		{
			if (temp == node)
				check = true;
		}
		if (check)
		{
			LRU.remove(node);
			LRU.push_front(node);
		}
		else
		{
			LRU.push_front(node);
		}
	}

	void removeNode(Node *node)
	{
		LRU.remove(node);
	}

public:
	RESTAURANT_Sukuna(){}
	~RESTAURANT_Sukuna(){
		for(int i = 0; i < int(areaTable.size()); i++){
			delete areaTable[i];
		}
	}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		int index = -1;

		for (int i = 0; i < int(areaTable.size()); i++)
		{
			if (ID == areaTable[i]->ID)
			{
				index = i;
			}
		}

		if (index == -1)
		{
			areaTable.push_back(new Node(ID));

			index = int(areaTable.size()) - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		else
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}
	void remove_KEITEIKEN(int number)
	{
		if(int(areaTable.size()) <= 0) return;

		vector<Node* > areaTableNew(areaTable.begin(), areaTable.end());
		queue<Node* > listDelete;
		for(int i = 0;  int(areaTable.size()) && i < number; i++)
		{
			Node* nodeDelete = areaTable[0];
			swap(areaTable[0], areaTable[int(areaTable.size()) - 1]);
			areaTable.pop_back();
			this->ReHeap_down(0);


			listDelete.push(nodeDelete);
		}

		areaTable = areaTableNew;

		while(listDelete.size()){
			Node* nodeDelete = listDelete.front();
			listDelete.pop();

			nodeDelete->remove(number);

			int index = 0;
			while(areaTable[index] !=  nodeDelete) index++;

			if(nodeDelete->size() == 0)
			{
				swap(areaTable[index], areaTable[int(areaTable.size()) - 1]);
				this->removeNode(areaTable[int(areaTable.size()) - 1]);
				delete areaTable[int(areaTable.size()) - 1];

				areaTable.pop_back();
			}
			this->ReHeap_down(index);
		}
 	
	
	}

	void print_pre_order(int index, int number)
	{	
		if(index >= int(this->areaTable.size()) || number <= 0) return;
		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_LIMITLESS(int number){print_pre_order(0, number);}
private:
	class Node{
	private:
		int ID;					
		list<int> head; 	
		friend class RESTAURANT_Sukuna;
	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		void insert(int result){head.push_front(result);}
		void remove(int number)
		{
			while(number != 0 && !head.empty())
			{
				cout << head.back() << "-" <<ID << "\n";
				head.pop_back();
				number--;
			}
		}
		void print(int number)
		{
			for(list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				cout << ID << "-" << *it  << "\n";
			}
		}
	};
};



class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
	~HuffTree_AVL(){clear(root);}
	void clear(Node* node)
	{
		if(node)
		{
			clear(node->left);
			clear(node->right);
			delete node;
		}
	}

	char caesarEncode(char originalChar, int originalFreq)
	{
		if (isupper(originalChar))
		{
			originalChar = char(int(originalChar + originalFreq - 65) % 26 + 65);
		}
		else
		{
			originalChar = char(int(originalChar + originalFreq - 97) % 26 + 97);
		}
		return originalChar;
	}

	static bool comparePairs(pair<char, int> a, pair<char, int> b)
	{
		if (a.second != b.second)
		{
			return a.second > b.second;
		}
		else
		{
			if (isupper(a.first) && !isupper(b.first))
				return true;
			else if (!isupper(a.first) && isupper(b.first))
				return false;
			else
				return a.first > b.first;
		}
	}

	vector<pair<char, int>> string_Processing(string& name)
	{
		vector<pair<char, int>> freq_prev;
		for (char c : name)
		{
			bool found = false;
			for (pair<char, int> &prev : freq_prev)
			{
				if (prev.first == c)
				{
					prev.second++;
					found = true;
					break;
				}
			}
			if (!found)
			{
				freq_prev.push_back(make_pair(c, 1));
			}
		}
		if(freq_prev.size() < 3) return {};

		for (char &c : name)
		{
			int key;
			for (pair<char, int> pair : freq_prev)
			{
				if (pair.first == c)
				{
					key = pair.second;
					break;
				}
			}
			c = caesarEncode(c, key);
		}

		for (pair<char, int> &pair : freq_prev)
		{
			char originalChar = pair.first;
			int originalFreq = pair.second;

			if (isupper(originalChar))
			{
				pair.first = char(int(originalChar + originalFreq - 65) % 26 + 65);
			}
			else
			{
				pair.first = char(int(originalChar + originalFreq - 97) % 26 + 97);
			}
		}
		if (freq_prev.size() < 3) return {};
		vector<pair<char, int>> freq;
		for (pair<char, int> pair : freq_prev)
		{
			char currentChar = pair.first;
			int currentFreq = pair.second;

			bool found = false;
			for (std::pair<char, int> &element : freq)
			{
				if (element.first == currentChar)
				{
					element.second += currentFreq;
					found = true;
					break;
				}
			}

			if (!found)
			{
				freq.push_back(make_pair(currentChar, currentFreq));
			}
		}

		sort(freq.begin(), freq.end(), comparePairs);
		return freq;
	}

	int height(Node *node)
	{
		if (node == nullptr)
		{
			return 0;
		}
		return 1 + max(height(node->left), height(node->right));
	}

	int balanceFactor(Node *node)
	{
		return (node == nullptr) ? 0 : height(node->left) - height(node->right);
	}

	void updateHeight(Node *node)
	{
		if (node != nullptr)
		{
			node->height = 1 + std::max(height(node->left), height(node->right));
		}
	}

	Node *rotateRight(Node *y)
	{
		Node *x = y->left;
		Node *T2 = x->right;

		x->right = y;
		y->left = T2;

		updateHeight(y);
		updateHeight(x);

		return x;
	}

	Node *rotateLeft(Node *x)
	{
		Node *y = x->right;
		Node *T2 = y->left;

		y->left = x;
		x->right = T2;

		updateHeight(x);
		updateHeight(y);

		return y;
	}

	Node *balance(Node *node, int &count)
	{
		updateHeight(node);

		int balance = balanceFactor(node);

		// Left Heavy
		if (balance > 1)
		{
			if (balanceFactor(node->left) >= 0)
			{
				// Left Left Case
				count++;
				return rotateRight(node);
			}
			else
			{
				// Left Right Case
				count++;
				node->left = rotateLeft(node->left);
				return rotateRight(node);
			}
		}

		// Right Heavy
		if (balance < -1)
		{
			if (balanceFactor(node->right) <= 0)
			{
				// Right Right Case
				count++;
				return rotateLeft(node);
			}
			else
			{
				// Right Left Case
				count++;
				node->right = rotateRight(node->right);
				return rotateLeft(node);
			}
		}

		// Node is still balanced
		return node;
	}
	Node* balanceTreeRecursive(Node* node, int count = 0)
	{
		if(node == nullptr  || count == 1) return node;
		node = balance(node, count);
		node->left = balanceTreeRecursive(node->left, count);
		node->right = balanceTreeRecursive(node->right, count);
		return node;
	}

	static bool compareNode(pair<Node *, int> temp_1, pair<Node *, int> temp_2)
	{
		if (temp_1.first->weight != temp_2.first->weight)
		{
			return temp_1.first->weight > temp_2.first->weight;
		}
		else
		{
			if (temp_1.first->c == '*')
				return true;
			else if (temp_2.first->c == '*')
				return false;
			else if (temp_1.first->c == '\0' && temp_2.first->c == '\0')
			{
				return temp_1.second > temp_2.second;
			}
			else if (temp_1.first->c == '\0' && temp_2.first->c != '\0')
				return true;
			else if (temp_2.first->c == '\0' && temp_1.first->c != '\0')
				return false;
			else if (isupper(temp_1.first->c) && !(isupper(temp_2.first->c)))
				return true;
			else if (!isupper(temp_1.first->c) && isupper(temp_2.first->c))
				return false;
			else
				return temp_1.first->c > temp_2.first->c;
		}
	}

	Node *buildHuff(vector<pair<char, int>> freq)
	{
		vector<pair<Node *, int>> build;
		for (pair<char, int> pairs : freq)
		{
			build.push_back(make_pair(new Node(pairs.second, pairs.first), 0));
		}
		int order_pushing = 0;
		while (build.size() > 1)
		{
			Node *newNode = new Node(0);
			Node *temp_left = build.back().first;
			build.pop_back();
			Node *temp_right = build.back().first;
			build.pop_back();

			newNode->left = temp_left;
			newNode->right = temp_right;
			newNode->weight = temp_left->weight + temp_right->weight;
			newNode->height = height(newNode);
			order_pushing++;

			newNode = balanceTreeRecursive(newNode);
			newNode = balanceTreeRecursive(newNode);
			newNode = balanceTreeRecursive(newNode);

			newNode->c = '*';
			build.push_back(make_pair(newNode, order_pushing));
			sort(build.begin(), build.end(), compareNode);
			newNode->c = '\0';
		}
		return build[0].first;
	}
	void encodingHuffman_rec(vector<string> &encoding, Node *node, string s = "")
	{
		if (node == nullptr)
			return;

		if (node->left == nullptr && node->right == nullptr)
		{
			encoding[node->c] = s;
			return;
		}

		encodingHuffman_rec(encoding, node->left, s + '0');
		encodingHuffman_rec(encoding, node->right, s + '1');
	}
	int encodingHuffman(Node *root, string nameCaesar)
	{
		if (root->left == nullptr && root->right == nullptr) return 0;

		vector<string> encoding(256, "");
		encodingHuffman_rec(encoding, root);

		string nameCaesar_encode = "";
		for (char c : nameCaesar)
		{
			for (int i = 0; i < int(encoding.size()); i++)
			{
				if (char(i) == c)
					nameCaesar_encode += encoding[i];
			}
		}

		int result = 0;

		reverse(nameCaesar_encode.begin(), nameCaesar_encode.end());

		int size_encode = 10;
		if (nameCaesar_encode.size() <= 10)
			size_encode = nameCaesar_encode.size();

		for (int i = 0; i < size_encode; i++)
		{
			result += (nameCaesar_encode[i] - '0') * pow(2, size_encode - 1 - i);
		}

		return result;
	}

	int encode(string name){

		vector<pair<char, int>> freq  = this->string_Processing(name);
		if(freq.size() == 0) return -1;
		
		this->clear(root);
		root = this->buildHuff(freq);
		if(root->left == nullptr && root->right == nullptr) return 0; 
		int result = this->encodingHuffman(root ,name);
		
		return result;
	}

	


	void print_recursive(Node* node){
		if(node == nullptr) return;
		print_recursive(node->left);
		if(node->c == '\0') cout << node->weight << "\n";
		else cout << node->c << "\n";
		print_recursive(node->right);
	}
	void print_HAND(){print_recursive(root);}

private:
	class Node{
	public:
		int weight;
		char c;
		int height;
		Node* left;
		Node* right;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : weight(weight), c(c), height(1), left(left), right(right) {}
	};
};



class JJK_RESTAURANT_OPERATIONS
{
private:
	HuffTree_AVL New_customers_arrive;
	RESTAURANT_Gojo hash;
	RESTAURANT_Sukuna heap;
	
public:

	void LAPSE(string name)
	{
		int result = New_customers_arrive.encode(name);
		if(result == -1) return;

		if(result % 2 == 1) hash.insertAreaTable(result);
		else heap.insertAreaTable(result);
	}	

	void KOKUSEN(){
		hash.remove_KOKUSEN();
	}
	void LIMITLESS(int num){
		hash.print_LIMITLESS(num);
	}
	void KEITEIKEN(int num){
		heap.remove_KEITEIKEN(num);
	}
	void CLEAVE(int num){
		heap.print_LIMITLESS(num);
	}
	void HAND(){
		New_customers_arrive.print_HAND();
	}
};




void simulate(string filename)
{
	
	ifstream ss(filename);
	string str, name;
	int num;

	ss >> str; ss >> MAXSIZE; 

	JJK_RESTAURANT_OPERATIONS* MAYBE_RUN = new JJK_RESTAURANT_OPERATIONS();
	while (ss >> str)
	{
		if (str == "LAPSE") // LAPSE <NAME>
		{
			ss >> name;
			MAYBE_RUN->LAPSE(name);
		}
		else if (str == "KOKUSEN") // KOKUSEN
		{
			MAYBE_RUN->KOKUSEN();
		}
		else if (str == "KEITEIKEN") // KEITEIKEN <NUM>
		{
			ss >> num;
			MAYBE_RUN->KEITEIKEN(num);
		}
		else if (str == "HAND") // HAND
		{
			MAYBE_RUN->HAND();
		}		
		else if (str == "LIMITLESS") // LIMITLESS <NUM>
		{
			ss >> num;
			MAYBE_RUN->LIMITLESS(num);
		}		
		else if (str == "CLEAVE") // CLEAVE <NUM>
		{
			ss >> num;
			MAYBE_RUN->CLEAVE(num);
		}				
	}
	delete MAYBE_RUN;
}

