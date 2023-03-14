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
        int i = getValue().size() - 1;
        int j = b.getValue().size() - 1;
        int x,y,sum;
        while (i >= 0 || j >= 0 || carry > 0) {
            // char - '0' converts it to its corresponding integer value (see: ascii code)
            x = (i >= 0) ? getValue()[i--] - '0' : 0;
            y = (j >= 0) ? b.value[j--] - '0' : 0;
            sum = x + y + carry;
            result.insert(0, std::to_string(sum % 10));
            carry = sum / 10;
        }
        while (result.size() > 1 && result[0] == '0') {
            result.erase(0, 1); // Remove leading zeros
        }
        return result;
    }

    std::string operator * (BigAssNum &b) {
        std::string result;
        int product, carry, aDigit, bDigit;
        std::string tmpRes;
        std::vector<int> res;

        for (auto i: b.getValue()) { // for char in str
            carry = 0;
            for (auto j: getValue()) {
                aDigit = std::atoi(&i);
                bDigit = std::atoi(&j);
                product = (aDigit * bDigit) + carry;
                std::cout << aDigit << " * " << bDigit << " + " << carry << " = " << product << std::endl;
                carry = product / 10;
                res.push_back(product % 10);
            }
        }
        // Put the result digits into the string
        for (int i=res.size()-1; i>=0; i--) {
            result.insert(0, std::to_string(res[i]));
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
    }

};

int main() {
    //BigAssNum val1("174981883239023362650696299580");
    BigAssNum test1("1234");
    BigAssNum test2("2");
    std::string result = test1 * test2;
    std::cout << result <<  std::endl;
    /*
    //std::string product = val1 * val2 * val3;

    BigAssNum result(val1*val2);
    std::cout << result.getValue() << std::endl;

    // Check if 174981883239023362650696299580 ^ 3 mod 174981883239023362450696299581 gave the right answer
    bool correctAnswer = result.getValue() == "5357710694893265063503016372118087519550604651571638219891423134484499571299081885912000";
    std::string print = (correctAnswer) ? "Correct!" : "Incorrect!";
    std::cout << print << std::endl;
    */
    return 0;
}