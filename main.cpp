#include <iostream>
#include <vector>
#include <string>
using namespace std;


// 174981883239023362650696299580 ^ 3 mod 174981883239023362450696299581 = 3280075090892117215879456260

class BigAssNum {
private:
    vector<int> value;
public:
    void printValue() {
        for (int i = 0; i < value.size(); i++) {
            cout << value[i] << " ";
        }
        cout << endl;
    }

    string getValue() {
        string output;
        for (int i=0; i<value.size(); i++) {
            output += to_string(value[i]);
        }
        return output;
    }
     
    BigAssNum(string val) {
        // Preferred constructor
        for (auto it: val) {
            value.push_back(atoi(&it)); // Convert digit character to int
        }
    }

    BigAssNum() {
        // Default Constructor
        throw invalid_argument("No arguments specified!");
    }


};

int main() {
    BigAssNum test("01234");
    return 0;
}