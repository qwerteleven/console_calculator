#include <iostream>
#include <regex>

using namespace std;

int main(int argc, char const **argv)
{
  regex re(R"((\d{5})([[:alpha:]]+))");

  cmatch results;

  if (not regex_match(argv[1], results, re))
    cout << "No match\n";
  else
  {
    cout << "size: " << results.size() << "\n";
    for(auto i=0; i<results.size(); i++)
      cout << "match " << i << ": " << results.str(i) << "\n";
    cout << "Total match: " << results.str() << '\n';
  }
} 
