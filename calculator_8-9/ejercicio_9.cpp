#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <cstdlib>
#include <ctime>

#include "boost/program_options.hpp"

namespace po = boost::program_options;

using namespace std;

double number_generator(int type_value) {
  if(type_value == 0) return 0.;
  if(type_value == 1) return 1.;
  if(type_value == 2) return (double)rand();
}


int main(int argc,char* argv[])
{
  srand((unsigned) time(0));
  // Declare the supported options.
  po::options_description desc("Allowed options");
  desc.add_options()
    ("rows", po::value<int>(), "produce help message")
    ("columns", po::value<int>(), "produce help message")
    ("zeros", "produce help message")
    ("ones", "produce help message")
    ("random", "produce help message")
    ("type", po::value<char*>(), "produce help message")
    ("name", po::value<char*>(), "produce help message")
    ("fractional_digits", po::value<int>(), "produce help message")
   ;

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv, desc), vm);
  po::notify(vm);    
  int rows;
  int columns;
  int fractional_digits = 6;
  int type_matrix = 0;  // 0->zeros; 1->ones; 2-> random; by default 0
  char* type = "float"; // by default float;
  char* name = ".matrix";

  if (vm.count("rows")) {
    rows = vm["rows"].as<int>();
  } else {
    cout << "rows need be defined.\n";
    return -1;
  }

  if (vm.count("columns")) {
    columns = vm["columns"].as<int>();
  } else {
    cout << "columns need be defined.\n";
    return -1;
  }

  if (vm.count("ones")) type_matrix = 1;
  if (vm.count("random")) type_matrix = 2;

  
  if (vm.count("type")) {
    type = vm["type"].as<char*>();
  }

  if (vm.count("name")) {
    name = vm["name"].as<char*>() + name;
  } else {
    cout << "name need be defined.\n";
    return -1;
  }

  if (vm.count("fractional_digits")) {
    fractional_digits = vm["fractional_digits"].as<int>();
  }


  ofstream myfile;
  myfile.open(name);

  myfile << 'mat_lib::matrix[';
  myfile <<  rows;
  myfile <<  'x';
  myfile <<  columns;
  myfile <<  ']{\n';

  std::cout.precision(fractional_digits);

  for (int i = 0; i < rows; i++){
    myfile << '  ';

    for (int j = 0; j < columns; j++)
      if (columns - 1 == j ) {
        myfile << number_generator(type_value);
      } else {
        myfile << number_generator(type_value) << ', ';
      }
  }

  myfile << '}\n';

  myfile.close();

  return 0;
}

