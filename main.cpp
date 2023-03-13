#include <iostream>
#include <vector>
#include <string>

// 174981883239023362650696299580 ^ 3 mod 174981883239023362450696299581 = 3280075090892117215879456260

class BigAssNum {
private:
    std::vector<int> value;
public:
    void printValue() {
        for (int i = 0; i < value.size(); i++) {
            std::cout << value[i] << " ";
        }
        std::cout << std::endl;
    }

    std::string exponentiate(int power) {
        std::string uwu = "uwu";
        return uwu;
    }


    std::string vecToString(std::vector<int> input) {
        std::string output;
        for (int i=0; i<input.size(); i++) {
            output += std::to_string(input[i]);
        }
        return output;
    }
    

    std::string getValue() {
        return vecToString(value);
    }
    
    BigAssNum(std::string val) {
        // Preferred constructor
        for (auto it: val) {
            value.push_back(atoi(&it)); // Convert digit character to int
        }
    }

    BigAssNum() {
        // Default Constructor
        throw std::invalid_argument("No arguments specified!");
    }

};

int main() {
    BigAssNum test("01234");
    return 0;
}