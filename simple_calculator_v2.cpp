/*
	simple_calculator_v2.cpp - Simple calculator (second version)

  This program implements a basic expression calculator.
  Input from cin, output from cout.
  The gramman for input is:

  Statement:
    Declaration 
    Expression
    Funtion
    Update
    Print
    Quit

  Print:
    ;
    
  Quit:
    quit

  Update:
    set Name = Expression

  Declaration:
    let Name = Expression

  Expression:
    Term
    Expression + Term
    Expression - Term

  Term:
    Primary
    Term * Primary
    Term % Primary
    Term / Primary

  Primary:
    Number
    Name
    ( Expression )
    - Primary
    + Primary


  Function :
    FunctionName ( Expression )
    pow ( Expression , Expression )

  FunctionName :
    sin
    cos
    tan
    asin
    acos
    atan
    exp
    ln
    log10
    log2

  Number:
    floating-point-literal

  Name:
    a string of letters and numbers
  
  Input comes from cin throuhg the Token_stream called ts.
*/

#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>
#include <cmath>
#include <math.h>
#include <map>

using namespace std;

bool flag_const = false;

const string prompt = "> ";
const string result = "= ";

enum keywords {

      let = 'L',
      set = 'S',
      funtion = 'F',
      quit = 'Q',
      print = ';',
      number = '8',
      name = 'a',
      help = 'H',
      constant = 'C'
};


struct Token;

inline void error(const string& s);
inline void error(const string& s, const string& s2);
void define_name(string s, double d);
void set_value(string s, double d);
double expression();
double FunctionName(Token f);
void help_command();



inline void error(const string& s)
{
	throw runtime_error(s);
}

inline void error(const string& s, const string& s2) { error(s+s2); }

struct Token 
{
  char kind;
  double value;
  string name;
  Token(char ch) :kind(ch), value(0) { }
  Token(char ch, double val) :kind(ch), value(val) { }
  Token(char ch, string val) :kind(ch), name(val) { }
};

class Token_stream 
{ 
  private:

    bool full; 
    Token buffer; 
    
  public: 
    
    Token_stream() :full(false), buffer(0) { } 
    Token get(); 
    void unget(Token t) { buffer=t; full=true; } 
    void ignore(char);
};


Token check_reserved_keyword(string s)
{

        if (s == "let")   return Token(let);	
        if (s == "set")   return Token(set);	
        if (s == "quit")  return Token(quit);
        if (s == "help")  return Token(help);
        if (s == "const") return Token(constant);

        if (s == "sin")   return Token(funtion, "sin");	
        if (s == "cos")   return Token(funtion, "cos");	
        if (s == "tan")   return Token(funtion, "tan");
        if (s == "asin")  return Token(funtion, "asin");	
        if (s == "acos")  return Token(funtion, "acos");	
        if (s == "atan")  return Token(funtion, "atan");
        if (s == "exp")   return Token(funtion, "exp");	
        if (s == "ln")    return Token(funtion, "ln");	
        if (s == "log10") return Token(funtion, "log10");
        if (s == "log2")  return Token(funtion, "log2");	
        if (s == "pow")   return Token(funtion, "pow");	

        return Token(name, s);
}


Token Token_stream::get()
{
  if (full) { full=false; return buffer; }
  char ch;
  do { cin.get(ch); } while(isspace(ch));
  switch (ch) 
  {
    case '(':
    case ',':
    case ')':
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case ';':
    case '=': 
      return Token(ch);

    case '.':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {	
      cin.unget();
      double val;
      cin>>val;
      return Token(number, val);
    }
    default:
    	if (isalpha(ch)) 
      {
        string s;
        s+=ch;
        while(cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
        cin.unget();
        return check_reserved_keyword(s);
    	}
    	error("Bad token");
  }
}


void Token_stream::ignore(char c)
{
  if (full && c==buffer.kind) 
  {
    full = false;
    return;
  }
  full = false;

  char ch;
  while (cin>>ch)
    if (ch==c) return;
}


struct Variable 
{
  string name;
  double value;
  bool constant;
};

map<string, Variable> names;


double get_value(string s)
{
  if (names[s].name == s) return names[s].value;
  error("get: undefined name ", s);
}

void set_value(string s, double d)
{
  if (names[s].name == s) 
  {
    if (names[s].constant)
      { 
        error("can not update constant variable");
        return;
      }
      names[s].value = d;
      return;
    }
  error("set: undefined name ", s);
}

bool is_declared(string s)
{
  if (names[s].name == s) return true;
  return false;
}

void define_name(string s, double d)
{
  names[s] = {s, d};
}

Token_stream ts;

double primary()
{
  Token t = ts.get();
  switch (t.kind) 
  {
    case funtion:
      return FunctionName(t);

    case '(':
    {	
      double d = expression();
      t = ts.get();
      if (t.kind != ')') error("'(' expected");
      return d;
    }
    case '-':
      return - primary();
    case '+':
      return primary();
    case number:
      return t.value;
    case name:
      return get_value(t.name);
    default:
      cout << t.name;
      error("primary expected"); 
  }
}

double term()
{
  double left = primary();
  while(true) 
  {
    Token t = ts.get();
    switch(t.kind) 
    {
      case '*':
        left *= primary();
        break;
      case '/':
        {	
          double d = primary();
          if (d == 0) error("divide by zero");
          left /= d;
          break;
        }
      case '%':
        {	
          double d = primary();

          if (d < 1) error("module less 1 is undefined");
          left = std::fmod(left, d);
          break;
        }
      default:
        ts.unget(t);
        return left;
    }
  }
}

double expression()
{
  double left = term();
  while(true) 
  {
    Token t = ts.get();
    switch(t.kind) 
    {
      case funtion:
        return FunctionName(t);
        break;

      case '+':
        left += term();
        break;
      case '-':
        left -= term();
        break;

      default:
        ts.unget(t);
        return left;
    }
  }
}

double declaration()
{
  Token t = ts.get();
  if (t.kind != name) error ("name expected in declaration");
  string name = t.name;
  if (is_declared(name)) error(name, " declared twice");
  Token t2 = ts.get();
  if (t2.kind != '=') error("= missing in declaration of " , name);
  double d = expression();

  if (flag_const) {
    names[name] = {name, d, true};
  } else {
    names[name] = {name, d};
  }

  return d;
}

double update()
{
  Token t = ts.get();
  if (t.kind != name) error ("name expected in declaration");
  string name = t.name;
  Token t2 = ts.get();
  if (t2.kind != '=') error("= missing in declaration of " , name);
  double d = expression();
  set_value(name, d);
  return d;
}


double FunctionName(Token f)
{

  if (f.name == "pow")
  {
      
    if (ts.get().kind != '(') error ("unexpected syntax pow");
    
    double a = expression();

    if (ts.get().kind != ',') error ("unexpected syntax pow");
    
    double b = expression();

    if (ts.get().kind != ')') error ("unexpected syntax pow");

    return pow(a, b);

  }

  double d = primary();

  if (f.name == "sin")  return sin(d);
  if (f.name == "cos")  return cos(d);
  if (f.name == "tan")  return tan(d);
  if (f.name == "atan") return atan(d);
  if (f.name == "exp")  return exp(d);

  if (f.name == "log10" && d >= 0) return log10(d);
  if (f.name == "log2" && d >= 0) return log2(d);
  if (f.name == "ln" && d >= 0) return log(d);

  if (f.name == "asin" && d >= -1 && d <= 1) return asin(d);
  if (f.name == "acos" && d >= -1 && d <= 1) return acos(d);

  error("operation not permitted");

  return -1;
}


double statement()
{
  Token t = ts.get();
  double d=0;

  switch(t.kind) 
  {
    case constant:
      flag_const = true;
      if (ts.get().kind != let) error("expected let keyword");

      d = declaration();
      flag_const = false;
      return d;

    case let:
      return declaration();

    case set:
      return update();

    case funtion:
      return FunctionName(t);
      
    default:
      ts.unget(t);
      return expression();
  }
}

void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
  while(true) 
  try 
  {
    cout << prompt;
    Token t = ts.get();
    while (t.kind == print) t=ts.get();
    
    if (t.kind == help)
    {
      help_command();
      continue;
    }
    
    if (t.kind == quit) return;
    ts.unget(t);

    auto the_result=statement();
    cout << result << the_result << endl;
  }
  catch(runtime_error& e) 
  {
    clean_up_mess();
    cerr << e.what() << endl;
  }
}

int main()
try 
{
  calculate();
  return 0;
}
catch (exception& e) {
  cerr << "exception: " << e.what() << endl;
  char c;
  while (cin >>c && c!=';') ;
  return 1;
}
catch (...) {
  cerr << "exception\n";
  char c;
  while (cin>>c && c!=';');
  return 2;
}

void help_command()
{

  cout << R""""(
    
  simple_calculator_v2.cpp - Simple calculator

  This program implements a basic expression calculator.
  Input from cin, output from cout.
  The gramman for input is:

  Statement:
    Declaration 
    Expression
    Function
    Update
    Const
    Print
    Quit

  Print:
    ;
    
  Quit:
    quit

  Updates:
    set Name = Expression

  Declarations:
    let Name = Expression

    **this declaration can not change value**
    const let Name = Expression


  FunctionName:
    sin(A)
    cos(A)
    tan(A)
    asin(A)
    acos(A)
    atan(A)
    exp(A)
    ln(A)
    log10(A)
    log2(A)
    pow(A, B)

  Notations of numbers:

    Integers:
      [-]*[0-9]+
    
    Floats:
      [-]*[0-9]+[.][0-9]+

  Name:
    a string of letters and numbers
      [a-zA-Z]+[ALPHANUMERIC]*
  
  \n)"""";
}