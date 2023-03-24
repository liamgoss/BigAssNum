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
        if (b.getValue()[0] == '-') {
            BigAssNum tmp(b.getValue().erase(0, 1)); // remove '-'
            return *this - tmp;
        }
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


    std::string operator - (BigAssNum &b) {
        if (getValue()[0] == '-' || b.getValue()[0] == '-') {
            std::cout << std::endl << "Negative subtraction is not supported yet!" << std::endl;
            return "X";
        }
        std::string result;
        bool is_negative = false;

        // If the second operand is greater than the first, swap them and mark the result as negative
        if (getValue().size() < b.getValue().size() || (getValue().size() == b.getValue().size() && getValue() < b.getValue())) {
            is_negative = true;
            std::string tmpVal = getValue();
            setValue(b.getValue());
            b.setValue(tmpVal);
        }

        int carry = 0;
        int i = getValue().size() - 1;
        int j = b.getValue().size() - 1;
        int x,y,diff;
        while (i >= 0 || j >= 0 || carry > 0) {
            x = (i >= 0) ? getValue()[i--] - '0' : 0;
            y = (j >= 0) ? b.getValue()[j--] - '0' : 0;
            diff = x - y - carry;
            if (diff < 0) {
                diff += 10;
                carry = 1;
            } else {
                carry = 0;
            }
            result.insert(0, std::to_string(diff));
        }

        // Remove leading zeros
        while (result.size() > 1 && result[0] == '0') {
            result.erase(0, 1);
        }

        // Add a minus sign if the result is negative
        if (is_negative) {
            result.insert(0, "-");
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

    std::string operator / (BigAssNum& b) {
        std::string result;
        std::vector<int> res(getValue().size() + b.getValue().size(), 0);




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

std::string BigToBin(BigAssNum num) {
    BigAssNum ret("0");
    BigAssNum temp("0");
    BigAssNum temp2("1");
    BigAssNum tempnum = num;
    BigAssNum sub("1");
    BigAssNum adds("1");
    BigAssNum tempadd("1");
    BigAssNum one("2");
    BigAssNum two("2");
    BigAssNum ten("10");

    while(tempnum.getValue()[0] != '0') {
        sub.setValue("1");
        adds.setValue("1");
        temp2.setValue("1");
        tempadd.setValue("1");
        temp = tempnum - sub;
        if(temp.getValue()[0] == '-'){
            ret = ret + tempadd;
            break;
        }

        while(temp.getValue()[0] != '-') {
            temp2 = sub;
            tempadd = adds;
            sub = sub * two;
            adds = adds * ten;
            temp = tempnum - sub;
        }
        tempnum = num;
        tempnum = tempnum - temp2;
        num = tempnum;
        ret = ret + tempadd;
    }
    return ret.getValue();
}


std::string modBig(BigAssNum num, BigAssNum mod) { //only working for small numbers
    std::string temp;
    std::string bigtemp;
    BigAssNum C("0");
    BigAssNum tempC("0");
    BigAssNum D("1");
    BigAssNum tempD("1");
    BigAssNum setD("1");
    BigAssNum tempmod("0");
    BigAssNum tempnum("0");
    BigAssNum two("2");
    temp = BigToBin(num);
    for(int i = temp.size() - 1; i >= 0; i--) {
        if(temp[i] == '1') {
            bigtemp = D.getValue();
            //setD = D;
            tempmod = mod;
            tempD = D - tempmod;
            while(tempD.getValue()[0] != '-') {
                bigtemp = tempD.getValue();
                tempmod = mod;
                tempD = tempD - tempmod;
            }
            D.setValue(bigtemp);
            tempnum = C + D;
            //D = setD;
            C = tempnum;
            bigtemp = C.getValue();
            tempmod = mod;
            tempC = tempnum - tempmod;
            while(tempC.getValue()[0] != '-'){
                bigtemp = tempC.getValue();
                tempmod = mod;
                tempC = tempC - tempmod;
            }
            C.setValue(bigtemp);
        }
        D = D * two;

    }
    return C.getValue();
}



int main() {

    BigAssNum test1("174981883239023362650696299580");
    BigAssNum test2("174981883239023362650696299580");
    BigAssNum test3("174981883239023362650696299580");
    BigAssNum modu("174981883239023362450696299581");

    BigAssNum product = test1 * test2;
    product.setValue(modBig(product, modu));
    std::string result = product * test3;
    product.setValue(result);
    result = modBig(product,modu);
    std::cout << prettyPrint(test1.getValue()) <<"^3" << " mod " << prettyPrint(modu.getValue()) << " = " << prettyPrint(result) << std::endl;

    return 0;

}
