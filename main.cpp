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
        int counter = 0;
        int product, carry, aDigit, bDigit;
        std::string tmpRes;
        std::vector<int> res;
        for (int i = 0; i<b.getValue().size(); i++) {
            carry = 0;
            for (int j = 0; j<getValue().size(); j++) {
                aDigit = std::atoi(&getValue()[i]);
                bDigit = std::atoi(&b.getValue()[j]);
                product = (aDigit * bDigit) + carry;
                std::cout << aDigit << " * " << bDigit << " + " << carry << " = " << product << std::endl;
                carry = product / 10;
                res.push_back(aDigit & bDigit);
                //res[counter + i] = std::atoi(&getValue()[i]) % std::atoi(&b.getValue()[j]);
            }
            counter++; // current level of multiplication
            for (int k = 0; k < counter; k++){
                res.push_back(0);
            }
            
        }
        for (auto it: res) {
            result.insert(0, std::to_string(it));
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