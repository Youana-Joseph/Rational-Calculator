#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
using namespace std;
// File: CS112_A2_T3_S16_20230269_20231036_20230520
// Purpose: This is a rational numbers calculator, it provides summation, subtract, multiply, and divide for (integer/integer)
// Author: Omar Hani Tohami / S16
// Emails: otohami95@gmail.com (Omar's email)
//       : bassantelsherif80@gmail.com (Passant's email)
//       : youanajoseph8@gmail.com (Youana's email)
// Who did what:-
// 1. Omar Hani Tohami (20230269): [1- implement the gcd function ' to get the highest common factor ' .
//                                  2- handle the exit command .
//                                  3- split the inputs (num1, op, and num2).
//                                  4- made all the operations .
//                                  5- implement sliceRational function .]
//
// 2. Youana joesph (20230520):    [1- implement alphabet function ' to check if input contains alphabetical characters or not' .
//                                  2- implement simplifyFraction function ' to simplify fraction '
//                                  3- take the input from user and put it in variables (num1, op, and num2).
//                                  4- integrate the functions and combine the functions together .]
//
// 3. Passant shaaban (20231036):  [1- handle invalid input cases and print the error messages .
//                                  2- checking for alphabetical characters in num1 and num2.
//                                  3- implement the ConvertToRational function ' to check if the fraction has slashes or only whole number '  .
//                                  4- handle division by zero cases . ]


// Function to check if the input rational or whole number
string ConvertToRational(string input) {
    // a flag that indicates whether the input is rational or not
    bool has_slash = false;
    // Loop over each character of the string
    for (char c : input) {
        // If we found '/', set the flag to true and break the loop
        if (c == '/') {
            has_slash = true;
            break;
        }
    }
    // If  there was no slash in the string, return the original string appended by /1
    if (!has_slash){
        input += "/1";
    }
    return input;
}

// Function to check if a string contains alphabatical letters
bool alphabet(const string& str) {
    // Loop over the string
    for (char c : str) {
        // Return true if the character is an alphabetical
        if (isalpha(c)) {
            return true;
        }
    }
    // Return false if no alphabetical letter found
    return false;
}

// Function to check if a string contains digit
bool containDigit(const string& str){
    // Loop over the string
    for (char c : str) {
        // If the character is a digit return true
        if (isdigit(c)) {
            return true;
        }
    }
    // Return false if no digits found
    return false;
}

// Function to slice a string input
bool sliceRational(const string& input) {
    // Find the position of '/' in the input
    size_t slashPos = input.find('/');
    // If '/' is not found
    if (slashPos == string::npos) {
        // Return true to indicate that this is a whole number
        return true;
    }
    // Extract numerator
    string numerator = input.substr(0, slashPos);
    // Extract denomerator
    string denomerator = input.substr(slashPos + 1);
    // Check if either numerator or denominator contains non-digit chars
    if (!containDigit(numerator) || !containDigit(denomerator)) {
        // indicate an invalid rational number
        return false;
    }
   // indicate a valid rational number 
   return true;
}

// Function to find the greatest common divisor (GCD) using Euclid's algorithm
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to simplify the fraction
string simplifyFraction(int numerator, int denominator) {
    int divisor = gcd(numerator, denominator);
    numerator /= divisor;
    denominator /= divisor;
    // to check if the denominator = 1
    if (denominator == 1) {
        return to_string(numerator);
    // to check if numerator = 0
    } else if (numerator == 0) {
        return "0";
    // to check if denominator < 0
    } else if (denominator < 0) {
        // multiple numerator and denominator by -1
        numerator = -numerator;
        denominator = -denominator;
    }
    return to_string(numerator) + "/" + to_string(denominator);
}

// Main function
int main() {
    string inputs;
    cout << "Please enter rational numbers operation (or exit)\n";
    while (true){
        getline(cin, inputs);
        // Get the problem in one line
        istringstream problem(inputs);
        string num1, op, num2, result;
        if (!(problem >> num1 >> op >> num2) || (problem >> result) || !containDigit(num1) || !containDigit(num2) ) {
            if (num1 == "EXIT" || num1 == "exit" || num1 == "Exit") {
                cout << "Thanks for using rational calculator!";
                break;
            } else {
                cout << "Invalid inputs, Try again!\n";
                continue;
            }
        }
        // Check if num1 or num2 contain alphabatical letters
        if (alphabet(num1) || alphabet(num2)){
            cout << "No letters allowed, Try agin!\n";
            continue;
        }
        // Slice num1 and num2 and check if numerator or denomerator of each contains non-digit chars
        if (!sliceRational(num1) || !sliceRational(num2)) {
            cout << "Invalid inputs, Try again!\n";
            continue;
        }
        // Convert num1 and num2 into rational if they are whole numbers 
        string R1 = ConvertToRational(num1);
        string R2 = ConvertToRational(num2);
        // Declare numerator 1,2 and denominator 1,2
        int num1_num, num1_den, num2_num, num2_den;
        // Seperate R1 and R2 into (upper / lower) parts to help in results and operations
        sscanf(R1.c_str(), "%d/%d", &num1_num, &num1_den);
        sscanf(R2.c_str(), "%d/%d", &num2_num, &num2_den);
        // Check if denom 1,2 contain zeros
        if (num1_den == 0 || num2_den == 0){
            cout << "Denom can't be zero, Try again!\n";
            continue;
        }
        // Check if operator has multiple operators
        if(op.length() > 1){
            cout << "Invalid operation, Try again\n";
            continue;
        }
        // Switch over operator index zero (String op)
        switch (op[0]){
            case '+':
                // Result of summation
                result = simplifyFraction(num1_num * num2_den + num2_num * num1_den, num1_den * num2_den);
                break;
            case '-':
                // Result of subtraction
                result = simplifyFraction(num1_num * num2_den - num2_num * num1_den, num1_den * num2_den);
                break;
            case '*':
                // Result of multiplication
                result = simplifyFraction(num1_num * num2_num, num1_den * num2_den);
                break;
            case '/':
                // If second numerator (numerator of second number) == 0
                if(num2_num == 0){
                    // Print can't divide by zero
                    cout << "Can't divide over zero, Try again!\n";
                    continue;
                }
                // Result of division
                result = simplifyFraction(num1_num * num2_den, num1_den * num2_num);
                break;
            default:
                // Other operator
                cout << "Invalid operation, Try again!\n";
                continue;
        }
        cout << result << endl;
    }
    return 0;
}


// Pseudocode :-
/*
1.  Define functions ConvertToRational, alphabet, gcd, sliceRational, containDigit, and simplifyFraction.
2.  In the main function, initialize a string problem and print a prompt for the user to enter a rational numbers operation or "exit".
3.  Enter a while loop that runs until the user enters "exit" or "Exit" or "EXIT".
4.  Get the user's input as a single line and store it in problem.
5.  Parse the input using an istringstream object to extract the first number (num1), the operator (op), and the second number (num2).
6.  Check if num1 or num2 contain alphabetical letters using the alphabet function. If they do, print an error message and continue to the next iteration of the loop.
7.  Slice num1 and num2 using the function sliceRational.
8.  Check whether num1 or num2 contains non-digit chars using the function containDigit.
9.  Check if num1 or num2 contain spaces using the isValidFraction function. If they do, print an error message and continue to the next iteration of the loop.
10. Extract the numerators and denominators of num1 and num2 using sscanf.
11. Check if the denominators of num1 and num2 are zero. If they are, print an error message and continue to the next iteration of the loop.
12. Check if the operator contains multiple inputs. If it does, print an error message and continue to the next iteration of the loop.
13. Use a switch statement to perform the appropriate operation based on the operator.
14. Simplify the result using the simplifyFraction function.
15. Print the result.
16. Exit the loop if the user entered "exit".
*/
