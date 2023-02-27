/*
Examples:
Exprtk, http://www.partow.net/programming/exprtk/index.html
GitExample, https://github.com/ArashPartow/exprtk/blob/master/readme.txt

/*
* how can the code be written to see these levels explicitly?  AJY
Levels
Level 1: Comments

Comments are used to provide information about the code and are ignored by the compiler or interpreter.
Examples: Single-line comments starting with //, multi-line comments starting with /* and ending with * / <-with no space

Level 2: Variables and Functions

Variables are used to store data values that can be used in the program.
Functions are used to encapsulate reusable blocks of code.
Examples : variable declarations, function definitions, and function calls.

Level 3 : Control Structures

Control structures are used to control the flow of execution in a program.
Examples : if / else statements, for loops, while loops, switch statements.

Level 4 : Statements

Statements are complete instructions that perform some action:
* assignment statements, 
* method calls, and 
* return statements.

Level 5 : Expressions

Expressions are combinations of variables, literals, and operators that can be evaluated to produce a value:
* arithmetic expressions(e.g., 2 + 3)
* boolean expressions(e.g., x > y), and 
* method invocations that return a value.

It's important to note that this breakdown is not exhaustive, and some elements may not fit neatly into a single level. 
Additionally, the specific examples of elements may vary depending on the programming language and the context of the 
program. The most important thing is to understand the purpose and role of each level and to follow the rules and 
conventions of the language to ensure that the program is well-formed and can be executed correctly.

*/
#include <iostream>
#include <string>
#include <deque>
#include <sstream>
#include <cmath>
#include <cstring>
#include <memory>
#include <unordered_map>


//AJY I don't get how the data structures "the struct s" relate and how they are constructed
//      are the data structures in order of .... ???
//
const double PI = 3.141592653589793238463;  // constant Pi
enum class TokenType {
    Ident, // Indentifier / String
    NumLit, // Numeric literal
    LPar, // Left parenthesis
    RPar, // Right parenthesis
    Add, // Addition operator +
    Sub, // Subtraction operator -
    Mul, // Multiplication operator *
    Div, // Division operator /
    Exp, // Exponentiation operator ^

    // AJY where to add these?? ---> eval, lex, op_binding_power
    NotEqual, // != Not Equal
    GreaterThanOrEqual, // >= Greater Than or Equal to
    GreaterThan, // > Greater Than Equal
    LessThanOrEqual, // <= Less Than Than or Equal to
    LessThan, // < Less Than
    EqualityCheck, // == Check Equality
    And, // && And Logic
    Or, // || Or
    Nor, // !| Nor
    Nand, //!& Nand
    XOr, // $$ XOr
    XNor, // !$ XNNor
    RSFF, // RS Flip Flop
    DFF, // D Flop Flop
    JKFF, // JK Flop Flop
    MOD, // % Modulus X with respedt to y e.g.x % y
    Declare, // : = assign x to y
    Increment, // += Increment x by the value of the expression on the right side
    Decrement, // -= Decrement x by the value of the expression on the right side
    MultiplyUpdate, // *= Assign the multiplication of x by the value of the expression on the righthand side to x.
    DivByUpdate, // /= Assign the division of x by the value of the expression | on the right - hand side to x.
    Comments // # Comments 
             // *
    // 
};

//
// what levels are these??? AJY
//
// how do you make the map ordered?
//
const std::unordered_map<std::string, double(*)(double)>& get_function_def_table() {
    static std::unordered_map<std::string, double(*)(double)> map{
        {
            "Log",
            [](double n) { return std::log(n); }
        },
        {
            "Ln",
            [](double n) { return std::log(n) / std::log(10.0); }
        },
        {
            "Sin",
            [](double n) { return std::sin(n); }
        },
        {
            "Cos",
            [](double n) { return std::cos(n); }
        },
        {
            "Tan",
            [](double n) { return std::tan(n); }
        },
        {
            "ASin",
            [](double n) { return std::asin(n); }
        },
        {
            "ACos",
            [](double n) { return std::acos(n); }
        },
        {
            "ATan",
            [](double n) { return std::atan(n); }
        },
        {
            "DegToRad",
            [](double n) { return n * (PI / 180); }
        },
        {
            "RadToDeg",
            [](double n) { return n * (180 / PI); }
        },
    };
    return map;
}


//
//Does this Token struct contain the order of execution of the tokens? or is this done here in this code?  AJY
// 
// Define a struct called Token
struct Token {
    TokenType type;
    double value = 0;
    std::string ident = "";

    // Constructor for a Token
    Token(TokenType type) : type(type) {
        // If our token is a NumLit with no attached number, or an Ident with no attached string,
        // then throw an exception warning about it
        if (type == TokenType::NumLit) {
            throw std::runtime_error("Incorrect token constructor used for number literal");
        }
        else if (type == TokenType::Ident) {
            throw std::runtime_error("Incorrect token constructor used for identifier");
        }
    }

    // Constructor for a NumLit (with attached number)
    Token(double value) : type(TokenType::NumLit), value(value) {}

    // Constructor for an Ident (with attached string)
    Token(std::string ident) : type(TokenType::Ident), ident(ident) {}
};

// What levels are Operators???? AJY
// what is an overloaded stream??? what is it used for AJY
// Define an overloaded stream insertion operator for Token objects
std::ostream& operator<<(std::ostream& os, Token t) {
    // Use a switch statement to determine how to output the Token
    switch (t.type) {
    case TokenType::NumLit: // if the Token is a numerical literal
        os << t.value;
        break;
    case TokenType::LPar: // if the Token is a left parenthesis
        os << "(";
        break;
    case TokenType::RPar: // if the Token is a right parenthesis
        os << ")";
        break;
    case TokenType::Add: // if the Token is an addition operator
        os << "+";
        break;
    case TokenType::Sub: // if the Token is a subtraction operator
        os << "-";
        break;
    case TokenType::Mul: // if the Token is a multiplication operator
        os << "*";
        break;
    case TokenType::Div: // if the Token is a division operator
        os << "/";
        break;
    case TokenType::Exp: // if the Token is an exponentiation operator
        os << "^";
        break;
    case TokenType::Ident:
        os << t.ident;
        break;
    default:
        throw std::runtime_error("Unimplemented token print");
    }
    return os; // return the output stream
}

// Abstract base class for expressions
struct Expr {
    // Pure virtual function to print expression
    virtual void print() = 0;
    // Pure virtual function to evaluate expression with given value of x
    virtual double eval(const std::unordered_map<std::string, double>& ctx) = 0;
};

// Expression class for parenthesized sub-expressions
struct ParenExpr : public Expr {
    // Pointer to the sub-expression in parentheses
    Expr* e;
    // Constructor to initialize sub-expression
    ParenExpr(Expr* e) : e(e) {}
    // Function to print expression
    void print() override {
        std::cout << "(";
        e->print();
        std::cout << ")";
    }
    // Function to evaluate expression with given value of x
    double eval(const std::unordered_map<std::string, double>& ctx) override {
        return e->eval(ctx);
    }
};

// Expression class for variable x
struct IdentExpr : public Expr {
    std::string ident;
    IdentExpr(std::string ident) : ident(std::move(ident)) {}
    // Function to print expression
    void print() override {
        std::cout << ident;
    }
    // Function to evaluate expression with given value of x
    double eval(const std::unordered_map<std::string, double>& ctx) override {
        auto it = ctx.find(ident);
        if (it == ctx.end()) {
            throw std::runtime_error("Unbound variable `" + ident + "`");
        }
        return it->second;
    }
};

// Expression class for numerical constants
struct NumExpr : public Expr {
    double value;
    // Constructor to initialize numerical constant
    NumExpr(double n) : value(n) {}
    // Function to print expression
    void print() override {
        std::cout << value;
    }
    // Function to evaluate expression with given value of x
    double eval(const std::unordered_map<std::string, double>& ctx) override {
        return value;
    }
};

// Why not use a class? instead of a struct with member functions
// 
struct UnOpExpr : public Expr {
    Token op; // Unary operator or function
    Expr* e; // Expression to evaluate
    
    UnOpExpr(Token op, Expr* e) : op(op), e(e) {}
    
    void print() override {
        std::cout << op;
        e->print();
    }
    
    double eval(const std::unordered_map<std::string, double>& ctx) override {
        if (op.type == TokenType::Add) {
            return e->eval(ctx);
        }
        else if (op.type == TokenType::Sub) {
            return -e->eval(ctx);
        }
        throw std::runtime_error("Invalid unary operation or function");
    }
};

struct BinOpExpr : public Expr {
    Expr* lhs; // Left-hand side of the binary operation
    Token op; // Binary operator
    Expr* rhs; // Right-hand side of the binary operation
    
    BinOpExpr(Expr* lhs, Token op, Expr* rhs) : lhs(lhs), op(op), rhs(rhs) {}
    void print() override {
        lhs->print();
        std::cout << " " << op << " ";
        rhs->print();
    }
    double eval(const std::unordered_map<std::string, double>& ctx) override {
        // Check which operator to apply
        if (op.type == TokenType::Add) { // Addition
            return lhs->eval(ctx) + rhs->eval(ctx);
        }
        else if (op.type == TokenType::Sub) { // Subtraction
            return lhs->eval(ctx) - rhs->eval(ctx);
        }
        else if (op.type == TokenType::Mul) { // Multiplication
            return lhs->eval(ctx) * rhs->eval(ctx);
        }
        else if (op.type == TokenType::Div) { // Division
            return lhs->eval(ctx) / rhs->eval(ctx);
        }
        else if (op.type == TokenType::Exp) { // Exponentiation
            return std::pow(lhs->eval(ctx), rhs->eval(ctx));
        }
        // Throw an exception if the operator is invalid
        throw std::runtime_error("Invalid binary operation");
    }
};

struct ApExpr : public Expr {
    Expr* fn;
    Expr* arg;
    ApExpr(Expr* fn, Expr* arg) : fn(fn), arg(arg) {}
    void print() override {
        fn->print();
        std::cout << "(";
        arg->print();
        std::cout << ")";
    }
    double eval(const std::unordered_map<std::string, double>& ctx) override {
        IdentExpr* var = dynamic_cast<IdentExpr*>(fn);
        if (!var) {
            throw std::runtime_error("Function in application expression failed to cast");
        }
        auto& table = get_function_def_table();
        auto it = table.find(var->ident);
        if (it == table.end()) {
            throw std::runtime_error("Identifier not found in function table");
        }
        return it->second(arg->eval(ctx));
    }
};


// What levels are these??? AJY
//
// don't understand the token stack.  are the tokens all the part broken up
// e.g. (x+1)*(x+2) - 1 
// would the tokens be: (,x,+,1,),*,(,x,+,2,),-,1
// //
// This function receives a string expression and returns a deque of Token objects ... AJY
std::deque<Token> lex(const std::string& eq) {
    std::deque<Token> tokens; // Initialize an empty deque of Token objects
    for (int i = 0; i < eq.size(); ++i) { // Loop through each character in the input string
        if (eq[i] == ' ') continue;
        if (eq[i] == '(') {
            // If the current character in the equation string is '(',
            // create a new Token of TokenType::LPar and add it to the tokens vector.
            tokens.push_back(Token(TokenType::LPar));
            continue; // Skip to the next iteration of the loop.
        }
        if (eq[i] == ')') {
            // If the current character in the equation string is ')',
            // create a new Token of TokenType::RPar and add it to the tokens vector.
            tokens.push_back(Token(TokenType::RPar));
            // Skip to the next iteration of the loop.
            continue; // Skip to the next iteration of the loop.
        }
        if (eq[i] == '+') {
            // If the current character in the equation string is '+',
            // create a new Token of TokenType::Add and add it to the tokens vector.
            tokens.push_back(Token(TokenType::Add));
            continue; // Skip to the next iteration of the loop.
        }
        if (eq[i] == '-') {
            // If the current character in the equation string is '-',
            // create a new Token of TokenType::Sub and add it to the tokens vector.
            tokens.push_back(Token(TokenType::Sub));
            continue; // Skip to the next iteration of the loop.
        }

        /* need to check for:
           *= Assign the multiplication of x by the value of the expression on the righthand side to x.
        */
        if (eq[i] == '*') {
            // If the current character in the equation string is '*',
            // create a new Token of TokenType::Mul and add it to the tokens vector.
            tokens.push_back(Token(TokenType::Mul));
            continue; // Skip to the next iteration of the loop.
        }
        if (eq[i] == '/') {
            // If the current character in the equation string is '/',
            // create a new Token of TokenType::Div and add it to the tokens vector.
            tokens.push_back(Token(TokenType::Div));
            continue; // Skip to the next iteration of the loop.
        }
        if (eq[i] == '^') { // Check if the current character is '^'
            tokens.push_back(Token(TokenType::Exp)); // Add a new Token with TokenType::Exp and a value of 0 to the tokens vector
            continue;  // Continue to the next iteration of the loop
        }
        
        //doese the following go here??? AJY

        /* need to check for:
        != Not Equal
        !| Nor
        !&Nand
        */

       /* need to check for:
            >= Greater Than or Equal to
            > Greater Than Equal
        */
        
        /* need to check for:
            <= Less Than Than or Equal to
            < Less Than
         */

        
         /* need to check for:
            == Check Equality
         */

         /* need to check for:
            && And Logic
         */
         /* need to check for:
            || Or
         */
         /* need to check for:
            % Modulus X with respedt to y e.g.x % y
         */
         /* need to check for:
            : = assign x to y
         */
         /* need to check for:
            += Increment x by the value of the expression on the right side
         */
         /* need to check for:
            -= Decrement x by the value of the expression on the right side
         */
         /* need to check for:
            /= Assign the division of x by the value of the expression | on the right - hand side to x.
        */

        if (eq[i] >= '0' && eq[i] <= '9' || eq[i] == '.') {
            std::ostringstream os;
            while (i < eq.size() && eq[i] >= '0' && eq[i] <= '9') {
                os << eq[i++];
            }
            if (eq[i] == '.') {
                os << eq[i++];
            }
            while (i < eq.size() && eq[i] >= '0' && eq[i] <= '9') {
                os << eq[i++];
            }
            if (eq[i] == 'e' || eq[i] == 'E') {
                os << eq[i++];
            }
            if (eq[i] == '+' || eq[i] == '-') {
                os << eq[i++];
            }
            while (i < eq.size() && eq[i] >= '0' && eq[i] <= '9') {
                os << eq[i++];
            }
            tokens.push_back(Token(std::stod(os.str())));
            --i;
            continue;
        }

        if (eq[i] >= 'a' && eq[i] <= 'z' || eq[i] >= 'A' && eq[i] <= 'Z') {
            std::ostringstream os;
            while (i < eq.size() && (eq[i] >= 'a' && eq[i] <= 'z' || eq[i] >= 'A' && eq[i] <= 'Z')) {
                os << eq[i++];
            }
            tokens.push_back(Token(os.str()));
            --i;
            continue;
        }
    }
    return tokens;
}

// I don't get this struct ... what is it used for/  AJY
//
//
struct BindingPower {
    int left_bp;
    int right_bp;
    BindingPower(int left_bp, int right_bp)
        : left_bp(left_bp), right_bp(right_bp) {}
};

//
//don't understand why Add, Mul, don't have a binding power AJY
//
std::unique_ptr<BindingPower> op_binding_power(TokenType token) {
    
    switch (token) {
        case TokenType::Add:
        case TokenType::Sub:
            return std::make_unique<BindingPower>(1, 2);
        case TokenType::Mul:
        case TokenType::Div:
            return std::make_unique<BindingPower>(3, 4);
        case TokenType::Exp:
            return std::make_unique<BindingPower>(5, 6);
        default:
            return nullptr;
        }
}

// 
//
//
// Function that parses a deque of tokens and returns an expression tree
// min_bp - minimum binding power of the operator
Expr* parse(std::deque<Token>& tokens, int min_bp = 0) {
    if (tokens.empty()) return nullptr;

    // Get the first token from the deque
    Token front = tokens.front();
    Expr* lhs;

    // Switch statement to determine the type of expression based on the first token
    switch (front.type) {
    case TokenType::Ident: {
        tokens.pop_front();
        lhs = new IdentExpr(front.ident);
        break;
    }
    case TokenType::NumLit: {
        tokens.pop_front();
        lhs = new NumExpr(front.value);
        break;
    }
    case TokenType::LPar: {
        tokens.pop_front();
        lhs = new ParenExpr(parse(tokens));
        // Check if there is a right parenthesis, throw an error if missing
        if (tokens.empty() || tokens.front().type != TokenType::RPar) {
            throw std::runtime_error("Missing right parenthesis");
        }
        tokens.pop_front();
        break;
    }
    case TokenType::Add:
    case TokenType::Sub: {
        tokens.pop_front();
        lhs = new UnOpExpr(front, parse(tokens, 1000)); ///? <------1000 ?????? AJY
        break;
    }
    default:
        return nullptr;
    }

    // parse binary operations
    while (true) {
        // If there are no tokens, exit the loop
        if (tokens.empty()) break;

        // Get the first token
        Token front = tokens.front();

        auto bp = op_binding_power(front.type);
        if (bp) {
            // If the left binding power is less than the minimum binding power, exit the loop
            if (bp->left_bp < min_bp) break;

            // Remove the first token from the list
            tokens.pop_front();

            // Parse the right-hand side expression
            Expr* rhs = parse(tokens, bp->right_bp);

            // Create a new binary operation expression with the left-hand side expression,
            // the first token, and the right-hand side expression
            lhs = new BinOpExpr(lhs, front, rhs);

            continue;
        }

        // Check for application expr
        auto expr = parse(tokens, 1000);
        if (expr) {
            lhs = new ApExpr(lhs, expr);
            continue;
        }
        break;
    }
    return lhs;
}

double eval(std::string eq, const std::unordered_map<std::string, double>& ctx = {}) {
    
    // Lex the equation string to get a list of tokens
    auto tokens = lex(eq);

    // Parse the tokens to create an expression tree
    auto expr = parse(tokens);

    // Print the function in human-readable form
    std::cout << "f(...) = ";
    expr->print();
    std::cout << "\n";

    // Evaluate the expression
    double result = expr->eval(ctx);

    // Pretty-print the result
    std::cout << "\tf(";
    bool first = true;
    for (auto& p : ctx) {
        if (!first) {
            std::cout << ", ";
        }
        first = false;
        std::cout << p.first << "=" << p.second;
    }
    std::cout << ") = " << result << std::endl;

    return result;
}


int main() {
    double x = eval("104.2 * 12");
    double y = eval("Log(x)", { {"x", x} });
    double z = eval("x + y", { {"x", x}, {"y", y} });

    return(0);
}

/*

// don't understand the levels
// not sure how to add a class with the following characteristics


Expression Classes
*Single Expression
*Expression Stack

Class Use Case #1: Single Expression

Expression Exp1("104.2 * 12");
cout <<  Exp1.Get() << Endl;
Expression Exp2("Log(x)", { {"x", x} });
cout <<  Exp2.Get() << Endl;

Class Use Case #2: Stack of Expression
ExpressionStack ExpStack();
 
ExpStack.DeclareVar("x:=1");
ExpStack.DeclareVar("y:=1");
ExpStack.AddExp("z := Log(x) + y");
ExpStack.CalculateAll();
cout << ExpStack.Get("x") << endl;
cout << ExpStack.Get("y") << endl;
cout << ExpStack.Get("z") << endl;

ExpStack.SetVar("x:=1");
ExpStack.SetVar("y:=1");

ExpStack.Set("y","22");
ExpStack.Calc("z");
cout << ExpStack.Get("z") << endl;
ExpStack.SetOutVariable("z");
cout << ExpStack.GetOutput() << endl;


Alternative Use Case #2:
ExpStack.AddVar("x","1");
ExpStack.AddVar("y","1");
ExpStack.AddExp("z","Log(x) + y");

*/

/*
Check and/or Add these:
Sqrt
InRange

Operands
!= Not Equal
>= Greater Than or Equal to
> Greater Than Equal
<= Less Than Than or Equal to
< Less Than
== Check Equality
&& And Logic
|| Or
!| Nor
!& Nand
% Modulus X with respedt to y e.g. x%y
:= assign x to y
+= Increment x by the value of the expression on the right side
-= Decrement x by the value of the expression on the right side
*= Assign the multiplication of x by the value of the expression on the righthand side to x.
/= Assign the division of x by the value of the expression |on the right-hand side to x.
+ Add


*/


/*



    Add, // Addition operator +
    Sub, // Subtraction operator -
    Mul, // Multiplication operator *
    Div, // Division operator /
    Exp, // Exponentiation operator ^
    Log, // Logarithm function Log()
    Sin, // Sine function Sin()
    Cos, // Cosine function Cos()
    Tan, // Tangent function Tan()
    ASin, // Inverse sine function InvTan()
    ACos, // Inverse cosine function Cos()
    ATan, // Inverse tangent function Tan()
    RadToDeg, // Radians to degrees conversion function RadToDeg
    DegToRad // Degrees to radians conversion function DegToRad

+-/*^()
log
sin
cos

Arithmetic operations:
Addition: +
Subtraction: -
Multiplication: *
Division: /
Exponentiation: ^

Trigonometric functions:
Sine: sin
Cosine: cos
Tangent: tan
Arcsine: asin
Arccosine: acos
Arctangent: atan

log
nlg
pi
https://www.mycompiler.io/new/cpp/

*/
