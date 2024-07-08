#include <iostream>
#include <cmath>
#include <map>
#include <sstream>

using namespace std;

const int varArrSize = 2;  // Maximum size of the array
int intArrs[varArrSize] = {0L}; // save values
string varArrs[varArrSize] = {""}; // save variables

class PostfixVariable {
private:
    int initialVar;
    string varStack[varArrSize];

    map<string, int> variables;

public:
    PostfixVariable() : initialVar(-1) {}

    void pushVar(const string& value) {
        if (initialVar < varArrSize - 1) {
            varStack[++initialVar] = value;
        } else {
            cerr << "Not enough memory!" << endl;
            exit(1);
        }
    }

    string popVar() {
        if (initialVar >= 0) {
            return varStack[initialVar--];
        } else {
            cerr << "Not enough memory!" << endl;
            exit(1);
        }
    }

    void processVariable(const string& input) {
        istringstream iss(input);
        string token;

        while (iss >> token) {
            // If the token is an operator
            if (token == "=") {
                // If it's an assignment operator, pop the variable and number, then store the value
                int value = stoi(popVar());

                string variable = popVar();

                variables[variable] = value;

                /** Stores the value and variable */
                if(intArrs[0] == 0L)
                {
                    intArrs[0] = variables[variable];
                }
                else if(intArrs[0] != 0L && intArrs[1] == 0L)
                {
                    intArrs[1] =  variables[variable];
                }

                if(varArrs[0] == "")
                {
                    varArrs[0] = variable;
                }
                else if(varArrs[0] != "" && varArrs[1] == "")
                {
                    varArrs[1] = variable;
                }
            } else {
                // Otherwise, push the variable onto the stack
                pushVar(token);
            }
                
        }
    }
    
    void printVariableAssignments() const {
        // Output the variable assignments
        for (const auto& pair : variables) {
            cout << pair.first << " = " << pair.second << endl;
        }
    }
};


bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%' || c == 'M' || c == 'm' || c == '&' || c == 'h');
}

int performOperation(int operand1, int operand2, char operation) {
    switch (operation) {
        case '+':
            return operand1 + operand2;
        case '-':
            return operand1 - operand2;
        case '*':
            return operand1 * operand2;
        case '/':
            if (operand2 != 0) {
                return operand1 / operand2;
            } else {
                cerr << "Error : Denominator is zero !" << endl;
                exit(1);
            }
        case '^':
            return pow(operand1, operand2);
        case '%':
            return operand1 % operand2;
        case 'M':
            return fmax(operand1, operand2);
        case 'm':
            return fmin(operand1, operand2);
        case '&':
            return (operand1 + operand2)/2;
        case 'h':
            return hypot(operand1, operand2);
        default:
            cerr << "Error : Invalid operator" << endl;
            exit(1);
    }
}

int evaluatePostfix(const string& postfix) {
    int arrayResult[1]; // We only need one element to store the result
    int resultIndex = -1; // Initialize for the index of the array

    for (char c : postfix) {
        if (isdigit(c)) {
            // A digit can't be an operator
            cerr << "Error: A digit is NOT an operator!" << endl;
        } else if (isOperator(c)) {
            // Push the result to arrayResult after the calculation
            int operand2 = intArrs[1];
            int operand1 = intArrs[0];

            int result = performOperation(operand1, operand2, c);
            arrayResult[++resultIndex] = result;
        }
    }

    if (resultIndex == 0) {
        return arrayResult[resultIndex];
    } else {
        cerr << "Error: Invalid postfix expression!" << endl;
        exit(EXIT_FAILURE);
    }
}

int main() {
    PostfixVariable setVariables;

    cout << "-------------------------------------------------------------" << endl;
    cout << "NOTICE : This algorithm only works for the integer values." << endl;
    cout << "-------------------------------------------------------------" << endl;

    cout << "Set the first variable in postfix notation without comma (e.g., 'A 3 ='): ";
    string var1;
    getline(cin, var1);

    setVariables.processVariable(var1);
    setVariables.printVariableAssignments();

    cout << "Set the second variable in postfix notation without comma (e.g., 'B 3 ='): ";
    string var2;
    getline(cin, var2);

    setVariables.processVariable(var2);
    setVariables.printVariableAssignments();
    cout << "" << endl;

    string postfixExpression;

    cout << "-------------------------------------------------------------" << endl;
    cout << "NOTICE : Here is the operator table." << endl;
    cout << "" << endl;
    cout << "* The calculator will print out the floor value if it is positive and ceiling value if it is negative" << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << "" << endl;
    cout << "[    Operator Table    ]" << endl;
    cout << "" << endl;
    cout << "---------------------------------" << endl;
    cout << "| Operator |      Function     |" << endl;
    cout << "|----------|-------------------|" << endl;
    cout << "|    +     |        add        |" << endl;
    cout << "|    -     |      subtract     |" << endl;
    cout << "|    *     |      multiply     |" << endl;
    cout << "|    /     |       divide      |" << endl;
    cout << "|    ^     |       power       |" << endl;
    cout << "|    %     |      modulus      |" << endl;
    cout << "|    M     |      maximum      |" << endl;
    cout << "|    m     |      minimum      |" << endl;
    cout << "|    &     |      average      |" << endl;
    cout << "|    h     |     hypotenuse    |" << endl;
    cout << "--------------------------------" << endl;
    cout << "" << endl;
    cout << "-------------------------------------------------------------" << endl;

    cout << "Reminder : " << varArrs[0] << " = " << intArrs[0] << " and " << varArrs[1] << " = " << intArrs[1] << endl;
    cout << "Enter a postfix expression with comma ',' (e.g., 'A,B,+') : ";
    getline(cin, postfixExpression);

    /////////////////////////
    istringstream issp(postfixExpression);
    string a, b;
    int result;
    if(getline(issp, a, ',') && getline(issp, b, ','))
    {
        if(a == varArrs[0] && b == varArrs[1])
        {
            cout << "" << endl;
            cout << ".....CALCULATING....." << endl;
            result = evaluatePostfix(postfixExpression);
        }
        else{
            cerr << "Wrong input : Terminating the program" << endl;
            exit(1);
        }
    }

    cout << "Result: " << result << endl;

    return 0;
}