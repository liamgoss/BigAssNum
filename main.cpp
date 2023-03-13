#include <iostream>
#include <vector>
#include <string>
#include <cmath>
// 174981883239023362650696299580 ^ 3 mod 174981883239023362450696299581 = 3280075090892117215879456260

class BigAssNum {
private:
    std::string value;
public:

    std::string operator + (BigAssNum &b) {
        std::string result;
        int carry = 0;
        int i = value.size() - 1;
        int j = b.getValue().size() - 1;
        int x,y,sum;
        while (i >= 0 || j >= 0 || carry > 0) {
            x = (i >= 0) ? value[i--] - '0' : 0;
            y = (j >= 0) ? b.value[j--] - '0' : 0;
            sum = x + y + carry;
            result.insert(0, std::to_string(sum % 10));
            carry = sum / 10;
        }
        return result;
    }
    

    

    std::string getValue() {
        return value;
    }
    void setValue(std::string val) {
        value = val;
    }
    
    BigAssNum(std::string val) {
        // Preferred constructor
        setValue(val);
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