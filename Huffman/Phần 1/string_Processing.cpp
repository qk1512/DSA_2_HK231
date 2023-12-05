#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include<vector>
#include<map>
#include<stack>
#include<queue>
#include<list>
#include <utility> 
#include <algorithm>

using namespace std;
bool compare(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b);
void print(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b);

//* đầu vào là 1 chuỗi -> đầu ra chuỗi name đã được mã hóa Caesar và trả về danh sách freq có thứ tự giảm dần

vector<pair<char,int>> getCharFrequency(const string &name){
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
    return freq_prev;
}

/* vector<pair<char,int>> caesarEncode(vector<pair<char,int>> freq_prev){
    vector<pair<char,int>> encodedFreq;

    for(const auto &pair : freq_prev){
        char originalChar = pair.first;
        int originalFreq = pair.second;

        char encodedChar = (originalChar + originalFreq) % 128;

        encodedFreq.push_back(make_pair(encodedChar, originalFreq));
    }

    return encodedFreq;
} */

char caesarEncode(char &originalChar, int originalFreq)
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

vector<pair<char, int>> accumulateFrequencies(const vector<pair<char, int>> freq_prev)
{
    vector<pair<char, int>> accumulatedFreq;

    for (const auto &pair : freq_prev)
    {
        char currentChar = pair.first;
        int currentFreq = pair.second;

        // Explicitly specify the iterator type
        vector<std::pair<char, int>>::iterator it = find_if(accumulatedFreq.begin(), accumulatedFreq.end(),
                                                            [currentChar](const std::pair<char, int> &element)
                                                            {
                                                                return element.first == currentChar;
                                                            });

        if (it != accumulatedFreq.end())
        {
            // If the character is found, update its frequency
            it->second += currentFreq;
        }
        else
        {
            // If the character is not found, add a new pair to the vector
            accumulatedFreq.push_back(make_pair(currentChar, currentFreq));
        }
    }

    return accumulatedFreq;
}

vector<pair<char, int>> string_Processing(string& name)
{
    //* bước 1: liệt kê tuần suất xuất hiện của các kí tự riêng biệt trong tên của khách hàng (phân biệt hoa và thường)
    //* tạo thành một danh sách theo vị trí của các kí tự vào trước và vào sau 
    //! VD : name = "aDdbaaabbb" -> kết quả bước này: freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
    //TODO
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

    //* bước 2: mã hóa Caesar chuỗi name thành chuỗi mới và mã hóa luôn freq_prev 
    //! VD : name = "aDdbaaabbb", freq_prev = [{a, 4}, {D,1}, {d,1}, {b,4}]
    //! kq : name = "eEefeeefff", freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}]
    //TODO

    for(auto &pair : freq_prev){
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

    for(char &c: name){
        int key;
        for(pair<char,int> pair:freq_prev){
            if(pair.first == c){
                key = pair.second;
                break;
            }
        }
        c = caesarEncode(c,key);
    }

    
    //* bước 3: công dồn freq_prev với các kí tự giống nhau sau khi mã hóa
    //^ chú ý cộng dồn lên phái đầu ví dụ dưới 'e' có 2 chỗ nên ta chọn đầu vector để giữ lại
    //! vd freq_prev = [{e,4}, {E,1}, {e,1}, {f,4}] -> kq:  freq = [{e,5}, {E,1}, {f,4}]
     //TODO
    vector<pair<char, int>> freq = accumulateFrequencies(freq_prev);
    

    //* bước 4: sort chuỗi freq mới tìm được phía trên theo chiều giảm dần
    //^ chú ý nếu tuần suất hiện bằng nhau thì kí tự nào lớn hơn thì lớn hơn, kí tự hoa lớn hơn kí tự thường
    //TODO



    return freq_prev;
}


int main()
{
    //! test 1: kiểm tra bước 1 bước 2
    string name = "aaa";
    cout << "test 1 - name = " << name << " : ";
    string nameResult = "ddd";
    std::vector<std::pair<char, int>> result = {{'d', 3}};
    std::vector<std::pair<char, int>> you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 2: kiểm tra bước 1 bước 2
    name = "zzz";
    cout << "test 2 - name = " << name << " : ";
    nameResult = "ccc";
    result = {{'c', 3}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }


    //! test 3: kiểm tra bước 3 và 4
    name = "aAzzAB";
    cout << "test 3 - name = " << name << " : ";
    nameResult = "bCbbCC";
    result = {{'C', 3}, {'b', 3}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }



    //! test 4: kiểm tra bước 3 và 4
    name = "azdbc";
    cout << "test 4 - name = " << name << " : ";
    nameResult = "baecd";
    result = {{'e',1}, {'d', 1}, {'c', 1}, {'b',1}, {'a', 1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }


    //! test 5: 
    name = "aAcc";
    cout << "test 5 - name = " << name << " : ";
    nameResult = "bBee";
    result = {{'e',2}, {'B', 1}, {'b', 1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 6: 
    name = "cac";
    cout << "test 6 - name = " << name << " : ";
    nameResult = "ebe";
    result = {{'e',2},  {'b', 1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }


    //! test 7: 
    name = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
    cout << "test 7 - name = " << name << " : ";
    nameResult = "aaaaaaaaaaaaaaaaaaaaaaaaaa";
    result = {{'a',26}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }

    //! test 8: 
    name = "aaaaaaaaaaaaaaaaaaaaaaaaab";
    cout << "test 8 - name = " << name << " : ";
    nameResult = "zzzzzzzzzzzzzzzzzzzzzzzzzc";
    result = {{'z',25}, {'c',1}};
    you = string_Processing(name);
    if(compare(result, you) && nameResult == name) cout << "pass" << endl;
    else
    {
        cout << "fail" << endl;
        cout << "nameResult: " << nameResult << endl;
        cout << "name_you  : " << name << endl;
        print(result, you);
        return 0;
    }
}

void print(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b){
    cout << "solution     : ";
    for (auto i : a) cout << "{" << i.first << ":" << i.second << "} -> ";
    cout << "\nsolution_you : ";
    for (auto i : b) cout << "{" << i.first << ":" << i.second << "} -> ";
    cout << "\n";
}

bool compare(const std::vector<std::pair<char, int>>& a, const std::vector<std::pair<char, int>>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}



