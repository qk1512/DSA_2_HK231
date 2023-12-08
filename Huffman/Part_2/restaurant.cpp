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
class RESTAURANT_Gojo{
	//TODO: implement
};

//* nhà hàng su cờ na
class RESTAURANT_Sukuna{
	//TODO: implement
};

class HuffTree_AVL{
	class Node;
private:
	Node* root = nullptr;
public:
	vector<pair<char, int>> string_Processing(string& name)
	{
		//TODO: implement
	}


	Node* buildHuff(vector<pair<char, int>> freq)
	{
		//TODO: implement
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
		friend class HuffTree_AVL;
	public:
		Node(int weight, char c = '\0',Node* left = nullptr, Node* right = nullptr ): weight(weight), c(c), left(left), right(right) {}
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


