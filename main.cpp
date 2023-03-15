#include <iostream>
#include <vector>
#include <string>
#include <cmath>
// 174981883239023362650696299580 ^ 3 mod 174981883239023362450696299581 = 3280075090892117215879456260


std::string prettyPrint(std::string ugly) {
    // Determine the position where the first comma should be inserted
    int first_comma_pos = ugly.length() % 3;
    if (first_comma_pos == 0) {
        first_comma_pos = 3;
    }
    
    // Insert commas after every three digits, starting from the first comma position
    for (int i = first_comma_pos; i < ugly.length(); i += 4) {
        ugly.insert(i, ",");
    }
    
    return ugly;
}

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


    std::string operator - (BigAssNum& b) {
        // Assumption:  a>=b>=0
        std::string result;
        int borrow = 0;
        int i = getValue().size() - 1;
        int j = b.getValue().size() - 1;
        int x,y,diff;
        while (i >= 0 || j >= 0) {
            x = (i >= 0) ? getValue()[i--] - '0' : 0;
            y = (j >= 0) ? b.value[j--] - '0' : 0;
            diff = x - y - borrow;
            borrow = 0;
            if (diff < 0) {
                diff += 10;
                borrow = 1;
            }
            result.insert(0, std::to_string(diff));
        }
        while (result.size() > 1 && result[0] == '0') {
            result.erase(0, 1); // Remove leading zeros
        }
        return result;
    }

    std::string operator * (BigAssNum& b) {
        std::string result;
        std::vector<int> res(getValue().size() + b.getValue().size(), 0);

        for (int i = getValue().size() - 1; i >= 0; --i) {
            int carry = 0;
            for (int j = b.getValue().size() - 1; j >= 0; --j) {
                int aDigit = getValue()[i] - '0';
                int bDigit = b.getValue()[j] - '0';
                int product = aDigit * bDigit + carry + res[i+j+1];
                carry = product / 10;
                res[i+j+1] = product % 10;
            }
            res[i] += carry;
        }

        // Skip leading zeros
        int i = 0;
        while (i < res.size() - 1 && res[i] == 0) {
            ++i;
        }

        // Convert to string
        while (i < res.size()) {
            result += std::to_string(res[i++]);
        }

        return result;
    }

    
    std::string string() {
        return getValue();
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
    BigAssNum sub1("1234");
    BigAssNum sub2("69");
    std::string result = sub1 - sub2;
    std::cout << prettyPrint(result) <<  std::endl;
    

    
    /*
    
    BigAssNum test1("174981883239023362650696299580");
    BigAssNum test2("174981883239023362650696299580");
    BigAssNum test3("174981883239023362650696299580");

    BigAssNum product = test1 * test2;
    std::string result = product * test3;
    std::cout << prettyPrint(result) <<  std::endl;
    
    //std::string product = val1 * val2 * val3;

    
    

    // Check if 174981883239023362650696299580 ^ 3 mod 174981883239023362450696299581 gave the right answer
    bool correctAnswer = result == "5357710694893265063503016372118087519550604651571638219891423134484499571299081885912000";
    std::string finalPrint = (correctAnswer) ? "Correct!" : "Incorrect!";
    std::cout << finalPrint << std::endl;
    */
    return 0;
    
}