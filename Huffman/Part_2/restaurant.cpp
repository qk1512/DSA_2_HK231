/*
! Võ Tiến ..............
* Võ Tiến ..............
~ Võ Tiến ..............
& Võ Tiến ..............
TODO Võ Tiến ..............
*/

#include "main.h"


int MAXSIZE = 0;

class JJK_RESTAURANT_OPERATIONS;
class RESTAURANT_Gojo;
class RESTAURANT_Sukuna;
class HuffTree_AVL;

//* nhà hàng của sư phụ GOJO
class RESTAURANT_Sukuna
{
	class Node;

private:
	vector<Node *> areaTable; //! nơi lưu trữ các khu vực
	list<Node *> LRU;		  //!  Least Recently Used này là cơ chế khu vực nào có khác vào nhà hàng lâu nhất
private:
	//* hàm gợi ý của anh thôi dùng hay không thì tùy các bạn nha -> nên suy nghĩ khác
	bool Compere(int index1, int index2)
	{
	}

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
		// TODO: với giá trị xét là areaTable[index].size()
		// TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		// TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khác vào gần nhất dùng list<Node* > LRU;
		// TODO: ví dụ khu A và khu B có số khách bằng nhau nếu khu A mới có khách vào thì so sánh min heap thì khu B đang nhỏ hơn khu A nên ở trên khu A
		int leftChild = 2 * index + 1;
		int rightChild = 2 * index + 2;
		int largest = index;

		if (leftChild < areaTable.size())
		{
			if (areaTable[leftChild]->size() < areaTable[largest]->size())
				largest = leftChild;
			else if (areaTable[leftChild]->size() == areaTable[largest]->size())
			{
				if (getIndex(areaTable[leftChild]) > getIndex(areaTable[largest]))
					largest = leftChild;
			}
		}

		if (rightChild < areaTable.size())
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
		// TODO: với giá trị xét là areaTable[index].size()
		// TODO: này là min heap nên areaTable[index].size() nào bé hơn thì ở trên
		// TODO: nếu 2 thằng bằng nhau thì chọn ra khu nào có khách vào gần nhất
		// TODO: này xử lí tương tự reheap_down
		int parentIndex = (index - 1) / 2;

		while (index > 0 && areaTable[index]->size() < areaTable[parentIndex]->size())
		{
			swap(areaTable[index], areaTable[parentIndex]);
			index = parentIndex;
			parentIndex = (index - 1) / 2;
		}
	}

	//* nếu node chưa tồn tại trong LRU thì thêm vô nếu tồn tại thì dịch nó lên đầu danh sách
	void moveTop(Node *node)
	{
		// TODO: BƯỚC 1 Tìm vị trí của node trong danh sách
		bool check = false;
		for (Node *temp : LRU)
		{
			if (temp == node)
				check = true;
		}
		// TODO: BƯỚC 2 nếu nó tồn tại thì dịch nó lên đầu danh sách, nếu không thì insert ở đầu danh sách
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

	//* xóa một node ra khỏi danh sách liên kết không gần gọi delete nha vì đã dùng bên dưới hàm xóa
	void removeNode(Node *node)
	{
		// TODO:
		LRU.remove(node);
	}

public:
	RESTAURANT_Sukuna() {}

	void insertAreaTable(int result)
	{
		int ID = result % MAXSIZE + 1;
		//*bước 1: kiểm tra xem heap có đang quản lí khu ID hay không nếu chưa quản lí thì phải thêm ở bước sau
		int index = -1;
		// TODO TODO TODO TODO TODO bước 1

		for (int i = 0; i < areaTable.size(); i++)
		{
			if (ID == areaTable[i]->ID)
			{
				index = i;
			}
		}

		//*bước 2: xem thử có khu này trong heap chưa để thêm vô
		if (index == -1)
		{
			areaTable.push_back(new Node(ID));
			index = areaTable.size() - 1;
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_up(index);
		}
		//*bước 3: thêm khách hàng mới vào khu khách hàng muốn thêm vào và tiến hàn reheap down bàn này xuống vì có số khách đông hơn
		else
		{
			areaTable[index]->insert(result);
			this->moveTop(areaTable[index]);
			this->ReHeap_down(index);
		}
	}

	void remove_KEITEIKEN(int number)
	{
		if (areaTable.size() <= 0)
			return;

		//* đuổi num khách hàng tại num khu vực
		int numberRemove = number;
		while (areaTable.size() != 0 && number != 0)
		{
			//* lấy ra khu đang ở đầu đầu heap xóa number khách hàng đầu linklist
			solution << "remove customers in the area ID = " << areaTable[0]->ID << ": ";
			areaTable[0]->remove(numberRemove);
			solution << "\n";

			//* trường hợp xóa hết thì xóa nó trong heap sau đó reheap down khu xuống vì đang ở đầu hàng
			if (areaTable[0]->size() == 0)
			{
				swap(areaTable[0], areaTable[areaTable.size() - 1]);
				//! xóa nó khỏi danh sách liên kết
				this->removeNode(areaTable[areaTable.size() - 1]);
				delete areaTable[areaTable.size() - 1];

				//! xóa trong heap nữa
				areaTable.pop_back();
			}
			this->ReHeap_down(0);
			number--;
		}
	}
	//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	void print_pre_order(int index, int number)
	{
		if (index >= this->areaTable.size())
			return;

		this->areaTable[index]->print(number);
		print_pre_order(index * 2 + 1, number);
		print_pre_order(index * 2 + 2, number);
	}
	void print_CLEAVE(int number)
	{
		if (number <= 0)
			return;

		solution << "Heap : ";
		for (auto it : this->areaTable)
		{
			int order = 0;
			for (auto ix : LRU)
			{
				if (ix == it)
					break;
				++order;
			}
			solution << it->ID << "(len=" << it->size() << ",index=" << order << ")"
					 << " ";
		}
		solution << "\n";

		solution << "Heap : ";
		for (auto it : this->areaTable)
			solution << it->ID << " ";
		solution << "\n";

		solution << "list LRU : ";
		for (auto it : LRU)
			solution << it->ID << " ";
		solution << "\n";

		print_pre_order(0, number);
	}
	//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	class Node
	{
	private:
		int ID;			//! ID của bàn đó
		list<int> head; //! lưu danh sách các result của khách hàng
		friend class RESTAURANT_Sukuna;

	public:
		Node(int ID) : ID(ID) {}
		int size() const { return head.size(); }
		//* thêm vô đầu danh sách
		void insert(int result) { head.push_front(result); }
		//* xóa ở cuối với số lượng là number cơ chế FIFO vô sớm thì cút sớm
		void remove(int number)
		{
			// TODO: xóa number khác hàng ở cuối danh sách tương ứng với vô sớm nhất
			//^ gợi ý dùng hàm của linklist có sẵn
			//* thêm solution << head.back() << " "; để in ra

			int length;
			if (number > head.size())
			{
				length = head.size();
			}
			else
			{
				length = number;
			}
			for (int i = 0; i < length; i++)
			{
				solution << head.back() << " ";
				head.pop_back();
			}
		}
		//* print ra number khách hàng mới đến gần nhất theo cơ chế LIFO các khách hàng gần nhất
		void print(int number)
		{
			solution << "customers in the area ID = " << ID << ": ";
			for (list<int>::iterator it = head.begin(); number > 0 && it != head.end(); ++it, --number)
			{
				solution << *it << " ";
			}
			solution << "\n";
		}
	};
};
//* nhà hàng su cờ na
class RESTAURANT_Gojo
{
	class Tree_BST;

private:
	//* cứ hiểu mỗi phần tử areaTable là các khu ăn trong đó sẽ có 1 nhân viên quản lí thêm vào và xóa ra chủ không cần quản lí mấy này
	vector<Tree_BST> areaTable;

public:
	RESTAURANT_Gojo() : areaTable(MAXSIZE + 1) {}
	void insertAreaTable(int result)
	{
		//* khách mới vô thích chọn khu có ID = result % MAXSIZE + 1 dắt nó tới chỗ đó rồi nén vô cho nhân viên khu đó xử lí
		int ID = result % MAXSIZE + 1;
		areaTable[ID].insert(result);
	}

	void remove_KOKUSEN()
	{
		//* tới từng khu ăn kêu nhân viên tìm thằng nào gián điệp đấm nó rồi đuổi cổ nó đi
		for (int i = 1; i < MAXSIZE + 1; i++)
			areaTable[i].remove();
	}

	void print_LIMITLESS(int number)
	{
		//* tới khu number kêu nhân viên liệt kê tất cả khách hàng ra
		if (number <= 0 || number > MAXSIZE)
			return; //! quá kí tự
		areaTable[number].print();
	}

private:
	//* Tree_BST giống như các nhân viên
	class Tree_BST
	{
		class Node;

	private:
		Node *root;			  //! cây của khách hàng vị trí khách hàng
		queue<int> queueTime; //! thời gian khách hàng đến có thể hiểu như là sổ ghi thông tin khách hàng
	public:
		Tree_BST() : root(nullptr) {}
		int size()
		{
			return queueTime.size();
		}

		//^hàm thêm ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên được chủ giao cho bố trí khách hàng có result
		Node *insert_recursive(Node *node, int result)
		{
			// TODO TODO TODO  TODO TODO TODO
			if (node == nullptr)
			{
				queueTime.push(result);
				return new Node(result);
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
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//^hàm xóa ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* nhân viên sẽ tới tận nơi đuổi cổ khách hàng gián điệp ra khỏi nhà hàng với result là khách hàng gián điệp
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
				Node *nodeDelete = node;
				if (node->left == nullptr && node->right == nullptr)
					node = nullptr;
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
				// delete nodeDelete;
			}

			return node;
		}

		int CountNode(Node *node)
		{
			return node == NULL ? 0 : 1 + CountNode(node->left) + CountNode(node->right);
		}

		vector<int> convertToPostorderArray(Node *root)
		{
			vector<int> postorderArray;
			stack<Node *> nodeStack;

			if (root == nullptr)
			{
				return postorderArray;
			}

			nodeStack.push(root);

			while (!nodeStack.empty())
			{
				Node *current = nodeStack.top();
				nodeStack.pop();

				postorderArray.insert(postorderArray.begin(), current->result); // Chèn giá trị vào đầu mảng

				// Duyệt qua cây theo thứ tự: left -> right -> root
				if (current->left != nullptr)
				{
					nodeStack.push(current->left);
				}
				if (current->right != nullptr)
				{
					nodeStack.push(current->right);
				}
			}

			return postorderArray;
		}

		unsigned long long binomialCoefficient(int n, int k)
		{
			if (k == 0 || k == n)
			{
				return 1;
			}

			vector<vector<unsigned long long>> triangle(n + 1, vector<unsigned long long>(n + 1, 0));

			// Populate Pascal's Triangle
			for (int i = 0; i <= n; ++i)
			{
				triangle[i][0] = 1;
				for (int j = 1; j <= i; ++j)
				{
					triangle[i][j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
				}
			}

			return triangle[n][k];
		}

		// Function to calculate the number of ways to form a BST from a given postorder array
		unsigned long long countBSTPermutations(const vector<int> &postorder, int start, int end)
		{
			if (start >= end)
			{
				return 1;
			}

			int rootValue = postorder[end];
			int i = start;

			while (i < end && postorder[i] < rootValue)
			{
				i++;
			}

			int leftSize = i - start;
			int rightSize = end - i;

			// Calculate the total number of permutations for the current root using Pascal's Triangle
			unsigned long long result = (binomialCoefficient(leftSize + rightSize, leftSize)) *
										(countBSTPermutations(postorder, start, i - 1)) *
										(countBSTPermutations(postorder, i, end - 1));

			return result;
		}

		// Function to calculate the total number of permutations for the postorder array
		unsigned long long totalPermutations(const vector<int> &postorder)
		{
			if (postorder.empty())
			{
				return 0;
			}

			int n = postorder.size();
			return countBSTPermutations(postorder, 0, n - 1);
		}

		unsigned long long DFS(Node *node)
		{
			if (node == NULL)
				return 1;
			// TODO TODO TODO  TODO TODO TODO  đệ quy

			vector<int> BST_array = convertToPostorderArray(node);
			unsigned long long result = totalPermutations(BST_array);

			return result;
		}

		//* nhân viên sẽ liệt kê ra các khách hàng gián điệp để dễ dàng đuổi
		void remove()
		{
			if (this->size() == 0)
				return; //! trường hợp rỗng bỏ qua
			//* bước 1: đếm số lượng node cần xóa
			//^ tìm hiểu : https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/
			// TODO: tính số lượng number
			unsigned long long number = DFS(root);
			// cout << number << " ";
			//*: trường hợp mà postoder cũng tạo ra một cây giống đó thì chỉ có 1 node -> nên không tính
			if (this->size() == 1)
				return;

			//* bước 2: xóa node trong cây với số lượng đã tính trên
			//* kiểm tra xem đã xóa đủ số lượng chưa hay cây đã hết node để xóa
			// cout << root -> result << " ";
			while (number != 0 && !queueTime.empty())
			{
				int temp = queueTime.front();		 //! tìm khách hàng đầu tiên được lưu trong sổ và lấy được vị trí nó rồi
				queueTime.pop();					 //! xóa nó khỏi sổ
				root = remove_recursive(root, temp); //! tới chỗ nó cho nó cút khỏi nhà hàng
				number--;
			}
		}
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//^hàm in ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//* hàm này theo trung thứ tự (in-order) thôi không gì khó hết
		string print_recursive(Node *node)
		{
			if (node == nullptr)
				return "NULL"; //! trường hợp dừng print
			string left = print_recursive(node->left);
			solution << node->result << " ";
			string right = print_recursive(node->right);

			if (node->left == nullptr && node->right == nullptr)
				return to_string(node->result); //! tr
			return to_string(node->result) + "(" + left + "," + right + ")";
		}
		void print()
		{
			//! trường hợp rỗng bỏ qua
			if (this->size() == 0)
			{
				solution << "EMPTY";
				return;
			}
			solution << "inoder: ";
			string s = print_recursive(root);
			solution << "\nTree: " << s;
			std::queue<int> tempQueue = queueTime;
			solution << "\nQueue: ";
			while (!tempQueue.empty())
			{
				solution << tempQueue.front() << " ";
				tempQueue.pop();
			}
		}
		//^ ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	private:
		class Node
		{
		private:
			int result;
			Node *left;
			Node *right;
			friend class Tree_BST;

		public:
			Node(int result) : result(result), left(NULL), right(NULL) {}
		};
	};
};

class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
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

	bool comparePairs(pair<char, int> a, pair<char, int> b)
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

	static bool comparePairsWrapper(const pair<char, int> &a, const pair<char, int> &b, HuffTree_AVL *instance)
	{
		return instance->comparePairs(a, b);
	}

	// Function to sort using member function as comparator
	void sortPairs(std::vector<std::pair<char, int>> &pairs)
	{
		std::sort(pairs.begin(), pairs.end(), [this](const pair<char, int> &a, const pair<char, int> &b)
				  { return comparePairsWrapper(a, b, this); });
	}

	vector<pair<char, int>> string_Processing(string &name)
	{
		// TODO: implement string_Processing
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

		// sort(freq.begin(),freq.end(),comparePairs);
		sortPairs(freq);
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

		// Perform rotation
		x->right = y;
		y->left = T2;

		// Update heights
		updateHeight(y);
		updateHeight(x);

		return x;
	}

	Node *rotateLeft(Node *x)
	{
		Node *y = x->right;
		Node *T2 = y->left;

		// Perform rotation
		y->left = x;
		x->right = T2;

		// Update heights
		updateHeight(x);
		updateHeight(y);

		return y;
	}

	Node *balance(Node *node, int &count)
	{
		// Update height of current node
		if(count >= 3) return node;
		updateHeight(node);

		// Get the balance factor to check if this node became unbalanced
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
				node->left = rotateLeft(node->left);
				count += 2;
				if (count >= 4)
					return node;
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
				node->right = rotateRight(node->right);
				count += 2;
				if (count >= 4)
					return node;
				return rotateLeft(node);
			}
		}

		// Node is still balanced
		return node;
	}

	Node *balanceTreeRecursive(Node *node, int &count)
	{
		// Base case: empty tree or leaf node
		if (node == nullptr)
		{
			return nullptr;
		}

		if (count >= 3) return node;

		node = balance(node, count);

		// Balance the left subtree
		node->left = balanceTreeRecursive(node->left, count);

		// Balance the right subtree
		node->right = balanceTreeRecursive(node->right, count);

		// Balance the current node
		return balance(node, count);
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
		//* bước 1 : chuyển freq thành build theo thứ tự 0 -> n
		vector<pair<Node *, int>> build;
		for (pair<char, int> pairs : freq)
		{
			build.push_back(make_pair(new Node(pairs.second, pairs.first), 0));
		}

		int order_pushing = 0;
		while (build.size() > 1)
		{
			int count = 0;
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

			newNode = balanceTreeRecursive(newNode, count);
			newNode->c = '*';
			build.push_back(make_pair(newNode, order_pushing));
			sort(build.begin(), build.end(), compareNode);
			newNode->c = '\0';

		}
		return build[0].first;
	}

	int encode(string name){

		if(name.length() < 3) return -1;

		//* bước 1 xử lí chuỗi thu được list để tới phần sau
		vector<pair<char, int>> freq = this->string_Processing(name);
		solution << "freq     : {";
    for (int i = 0; i <freq.size();i++){
		if(i == freq.size() - 1)  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "}";
		else  solution << "{" <<"'"<< freq[i].first <<"'" << "," << freq[i].second << "},";
	}
		solution << "}"<<endl;
		
		//* bước 2 xây dựng cây huff
		root = this->buildHuff(freq);
	
		if(root->left == nullptr && root->right == nullptr) return 0; //! trường hợp chỉ có 1 node
		this->print();
		return -1;
	}

	void rec_print(const Node* tree) {
		if (tree == nullptr) {
			return;
		}
		if(tree->c) solution << "[" << tree->weight << "," << tree->c << "]";
		else solution << "[" << tree->weight << "]";
		
		if (tree->left != nullptr || tree->right != nullptr) {
			solution << "(";
			rec_print(tree->left);
			solution << ",";
			rec_print(tree->right);
			solution << ")";
		}
	}
	
	void print()
	{	
		//* print theo chiều rộng anh có hướng dẫn rồi queue
		//* khi in chuyển từ cout << "char-freq/n" thành solution << "char-freq/n" cho anh dễ test
		solution << "root : ";
		rec_print(root);
		solution << '\n';
	}

private:
	class Node{
	public:
		int weight;
		char c;
		Node* left;
		Node* right;
		int height;
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0', Node *left = nullptr, Node *right = nullptr) : height(1), weight(weight), c(c), left(left), right(right) {}
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
		//* mã hóa HuffTree_AVL kết quả là 10 kí tự nhị phân cuối chuyển sang thập phân
		int result = New_customers_arrive.encode(name);
		return;
	}	

	//* xử lí nhà hàng gojo
	void KOKUSEN(){}
	void LIMITLESS(int num){}
	
	//* xử lí nhà hàng Sukuna
	void KEITEIKEN(int num){}
	void CLEAVE(int num){}

	//* xử lý HuffTree_AVL
	void HAND(){New_customers_arrive.print();}
};


