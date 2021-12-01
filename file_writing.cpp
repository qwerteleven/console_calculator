#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <string>
#include <cmath>

using namespace std;

inline void error(const string& s)
{
    throw runtime_error(s);
}

inline void error(const string& s, const string& s2) { error(s+s2); }

const int LINE_COLUMN_SPACE=5;
const int DATA_PRECISION=6;
const int DATA_COLUMN_SPACE=DATA_PRECISION+5;

const char INIT_FILE_CHAR='>';
const char FINAL_FILE_CHAR='<';

const string right_arrow="---->";

typedef double Function_Type(double);

Function_Type& the_function=sin;

int main(int argc,char* argv[])
try
{
  if(argc<5)
  {
    ostringstream ostr;
    ostr<<"not enough parameters!\n"
      <<"usage: "<<argv[0]<<" file a b n"<<endl
      <<"options:"<<endl
      <<"   file: output file"<<endl
      <<"   a: interval initial point (a<b)"<<endl
      <<"   b: interval final point (a<b)"<<endl
      <<"   n: numbers of points (n>1)"<<endl;
    error(ostr.str());
  }

  double x_a, x_b;
  x_a=atof(argv[2]);
  x_b=atof(argv[3]);
  if(x_a>=x_b) error("bad interval");

  int n=atoi(argv[4]);
  if(n<=1) error("bad number of points");

  cout<<"provided options: ";
  for(int i=1; i<argc; i++) cout<<argv[i]<<" ";
  cout<<endl;

  cout<<right_arrow<<" file name: "<<argv[1]<<endl;
  cout<<right_arrow<<" interval: ["<<argv[2]<<","<<argv[3]<<"]"<<endl;
  cout<<right_arrow<<" n: "<<argv[4]<<" points"<<endl;

  ofstream ost {argv[1]}; 
  if (!ost) error("can’t open output file ", argv[1]);

  double d=(x_b-x_a)/(n-1);
 
  cout<<setw(LINE_COLUMN_SPACE)<<setfill(INIT_FILE_CHAR)<<""<<": "<<argv[1]<<endl;
  for(int i=0;i<n;i++)
  {
    ostringstream ostr;
    ostr<<setw(DATA_COLUMN_SPACE)<<setfill(' ')
      <<fixed<<setprecision(DATA_PRECISION)
      <<(x_a+i*d)<<" "
      <<setw(DATA_COLUMN_SPACE)<<setfill(' ')
      <<fixed<<setprecision(DATA_PRECISION)
      <<the_function(x_a+i*d);
    cout<<setw(LINE_COLUMN_SPACE)<<setfill('#')<<(i+1)<<": "
      <<ostr.str()<<endl;
    ost<<ostr.str()<<endl;
  }
  cout<<setw(LINE_COLUMN_SPACE)<<setfill(FINAL_FILE_CHAR)<<""<<": "<<argv[1]<<endl;

  return 0;
}
catch (exception& e) 
{
  cerr<<"[ERROR] "<<e.what();
  return 1;
}
catch (...) 
{
  cerr<<"[ERROR] UNCAUGHT EXCEPTION!";
  return 2;
}
