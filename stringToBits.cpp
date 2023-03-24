// Answered my SO question: https://stackoverflow.com/questions/75838092/how-can-i-convert-a-number-of-type-stdstring-to-its-binary-representation-in

#include <iostream>
#include <string>
#include <bitset>
#include <vector>


// Multiplies str1 and str2, and prints result.
std::string multiply(std::string num1, std::string num2)
{
    int len1 = num1.size();
    int len2 = num2.size();
    if (len1 == 0 || len2 == 0)
    return "0";
 
    // will keep the result number in vector
    // in reverse order
    std::vector<int> result(len1 + len2, 0);
 
    // Below two indexes are used to find positions
    // in result.
    int i_n1 = 0;
    int i_n2 = 0;
     
    // Go from right to left in num1
    for (int i=len1-1; i>=0; i--)
    {
        int carry = 0;
        int n1 = num1[i] - '0';
 
        // To shift position to left after every
        // multiplication of a digit in num2
        i_n2 = 0;
         
        // Go from right to left in num2            
        for (int j=len2-1; j>=0; j--)
        {
            // Take current digit of second number
            int n2 = num2[j] - '0';
 
            // Multiply with current digit of first number
            // and add result to previously stored result
            // at current position.
            int sum = n1*n2 + result[i_n1 + i_n2] + carry;
 
            // Carry for next iteration
            carry = sum/10;
 
            // Store result
            result[i_n1 + i_n2] = sum % 10;
 
            i_n2++;
        }
 
        // store carry in next cell
        if (carry > 0)
            result[i_n1 + i_n2] += carry;
 
        // To shift position to left after every
        // multiplication of a digit in num1.
        i_n1++;
    }
 
    // ignore '0's from the right
    int i = result.size() - 1;
    while (i>=0 && result[i] == 0)
    i--;
 
    // If all were '0's - means either both or
    // one of num1 or num2 were '0'
    if (i == -1)
    return "0";
 
    // generate the result string
    std::string s = "";
     
    while (i >= 0)
        s += std::to_string(result[i--]);
 
    return s;
}

// A function to perform division of large numbers
std::string longDivision(std::string number, int divisor)
{
    // As result can be very large store it in string
    std::string ans;
 
    // Find prefix of number that is larger
    // than divisor.
    int idx = 0;
    int temp = number[idx] - '0';
    while (temp < divisor)
        temp = temp * 10 + (number[++idx] - '0');
 
    // Repeatedly divide divisor with temp. After
    // every division, update temp to include one
    // more digit.
    while (number.size() > idx) {
        // Store result in answer i.e. temp / divisor
        ans += (temp / divisor) + '0';
 
        // Take next digit of number
        temp = (temp % divisor) * 10 + number[++idx] - '0';
    }
 
    // If divisor is greater than number
    if (ans.length() == 0)
        return "0";
 
    // else return ans
    return ans;
}

std::vector<bool> strToBits(std::string strNumber) {
    std::vector<bool> boolean;
    while (strNumber.size() > 0 && strNumber[0] != '0')
    {
        std::string temp = longDivision(strNumber, 2);
        if (multiply(temp, "2") == strNumber)    // if this is true there was no reminder on the division
            {boolean.push_back(0);}// std::cout << "0";}
        else 
            {boolean.push_back(1);}//std::cout << "1";}
        strNumber = temp;
    }
    std::reverse(boolean.begin(), boolean.end());
    return boolean;
}

void printBits(std::vector<bool> x) {
    for (int i = x.size()-1; i >= 0; i--)
    {
        std::cout << (int)x[i];
    }
    std::cout<< std::endl;
}

void padBits(std::vector<bool> &x, int size) {
    while (x.size() < size) {
        x.push_back(0);
    }
}

int equalSizes(std::vector<bool> &x, std::vector<bool> &y) {
    if (x.size() < y.size()) {
        padBits(x, y.size());
        return y.size();
    } else if (x.size() > y.size()) {
        padBits(y, x.size());
        return x.size();
    }
    return x.size();
}

int equalSizes(std::vector<bool> &x, std::vector<bool> &y, std::vector<bool> &z) {
    int m = std::max(x.size(), std::max(y.size(), z.size()));
    padBits(x, m);
    padBits(y, m);
    padBits(z, m);
    return m;
}

std::vector<bool> addBits(const std::vector<bool>& num1, const std::vector<bool>& num2) {
    std::vector<bool> result;

    bool carry = false;
    int i = num1.size() - 1, j = num2.size() - 1;

    while (i >= 0 || j >= 0 || carry) {
        bool bit1 = i >= 0 ? num1[i] : false;
        bool bit2 = j >= 0 ? num2[j] : false;

        bool sum = bit1 ^ bit2 ^ carry;
        carry = (bit1 & bit2) | (bit1 & carry) | (bit2 & carry);

        result.insert(result.begin(), sum);

        i--; j--;
    }

    return result;
}
std::vector<bool> shiftLeftOne(const std::vector<bool>& num) {
    std::vector<bool> result = num;
    //std::reverse(result.begin(), result.end());
    result.push_back(0);
    printBits(result);
    std::reverse(result.begin(), result.end());
    

    return result;
}
/*
std::vector<bool> fem(std::vector<bool> A, std::vector<bool> B, std::vector<bool> n) {
    int m = equalSizes(A, B, n);
    std::vector<std::vector<bool>> C;
    std::vector<std::vector<bool>> D;
    // Initial setup: C0 = 0; D0 = B
    for (int i = 0; i < m; i++) {
        C[0] = 0;
        D[0] = B[i];
    }

    for (int i = 1; i < m; i++) {
        std::vector<bool> Dtmp = D[i-1] << i;
        while (Dtmp <= n) {
            Dtmp = D[i-1] - n;
        }
        D[i-1] = Dtmp;
        if (A[i]) {
            C[i] = addBits(C[i-1], D[i-1]);
        } else {
            C[i] = C[i-1];
        }

    }

    return {0};
}
*/

int main()
{

    std::string A = "10"; 
    std::string B = "2"; 
    std::string n = "3"; 
    std::vector<bool> A_bits = strToBits(A);
    std::vector<bool> B_bits = strToBits(B);
    std::vector<bool> n_bits = strToBits(n);
    int m = equalSizes(A_bits, B_bits);
    for (auto it: A_bits) {
        std::cout << it;
    }
    std::cout << "+";
    for (auto it: B_bits) {
        std::cout << it;
    }
    std::cout << "=";
    std::vector<bool> tmp = addBits(A_bits, B_bits);
    for (auto it: tmp) {
        std::cout << it;
    }
    std::cout << std::endl;

    std::vector<bool> tmp2 = shiftLeftOne(A_bits);
    for (auto it: tmp2) {
        std::cout << it;
    }   
    std::cout << std::endl;


    
    return 0;
}