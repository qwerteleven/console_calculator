# PP Console Calculator

A progressive C++ console-based expression calculator built as a series of exercises, evolving from a basic arithmetic evaluator to a full-featured calculator with variables, mathematical functions, and a templated matrix library.

---

## Overview

This project is structured as incremental exercises (`exercice_1` through `exercice_9`), each adding new capabilities on top of the previous. It is designed as a learning progression through core C++ concepts such as [recursive descent parsing](https://en.wikipedia.org/wiki/Recursive_descent_parser), [tokenization](https://en.wikipedia.org/wiki/Lexical_analysis), [template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming), and [object-oriented design](https://en.wikipedia.org/wiki/Object-oriented_programming).

---

## Project Structure

```
qwerteleven-console_calculator/
├── calculator_1-7/       # Incremental calculator exercises
│   ├── exercice_1.cpp    # Basic arithmetic + variables
│   ├── exercice_2.cpp    # Adds modulo operator (%)
│   ├── exercice_3.cpp    # Adds math functions (sin, cos, pow, ...)
│   ├── exercice_4.cpp    # Adds help command
│   ├── exercice_5.cpp    # Adds const variables
│   ├── exercice_6.cpp    # Refactors keywords to enum
│   └── exercice_7.cpp    # Switches variable store to std::map
├── calculator_8-9/
│   ├── ejercicio_8.hpp   # Templated 2D matrix class (mat_lib)
│   └── ejercicio_9.cpp   # Matrix file generator using program_options
├── mat_lib_v2/
│   ├── matrix.hpp        # Refined matrix library header
│   ├── testing_mat_lib.cpp
│   └── CMakeLists.txt
├── simple_calculator_v2.cpp  # Final consolidated calculator
├── file_writing.cpp          # Utility: writes function values to file
└── regex_example.cpp         # Utility: regex matching demo
```

---

## Features

### Expression Calculator (`calculator_1-7`, `simple_calculator_v2.cpp`)

The calculator implements a [grammar](https://en.wikipedia.org/wiki/Formal_grammar)-driven expression evaluator using a hand-written [lexer](https://en.wikipedia.org/wiki/Lexical_analysis) (`Token_stream`) and a [recursive descent parser](https://en.wikipedia.org/wiki/Recursive_descent_parser).

#### Supported Operations

| Syntax         | Description                        |
|----------------|------------------------------------|
| `A + B`        | Addition                           |
| `A - B`        | Subtraction                        |
| `A * B`        | Multiplication                     |
| `A / B`        | Division (error on divide-by-zero) |
| `A % B`        | [Modulo](https://en.wikipedia.org/wiki/Modular_arithmetic) (B > 1) |
| `(expr)`       | Grouping / precedence              |
| `-A`           | Negation                           |

#### Variables

```
let x = 42
set x = x + 1
const let pi = 3.14159
```

- `let` — declares a new variable  
- `set` — updates an existing variable  
- `const let` — declares an [immutable](https://en.wikipedia.org/wiki/Immutable_object) variable

#### Mathematical Functions

Implemented using C's [`<cmath>`](https://en.wikipedia.org/wiki/C_mathematical_functions) library:

| Function     | Description                        |
|--------------|------------------------------------|
| `sin(A)`     | [Sine](https://en.wikipedia.org/wiki/Sine_and_cosine)                   |
| `cos(A)`     | [Cosine](https://en.wikipedia.org/wiki/Sine_and_cosine)                 |
| `tan(A)`     | [Tangent](https://en.wikipedia.org/wiki/Trigonometric_functions)        |
| `asin(A)`    | [Arc sine](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions) |
| `acos(A)`    | [Arc cosine](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions) |
| `atan(A)`    | [Arc tangent](https://en.wikipedia.org/wiki/Inverse_trigonometric_functions) |
| `exp(A)`     | [Exponential](https://en.wikipedia.org/wiki/Exponential_function) (eˣ) |
| `ln(A)`      | [Natural logarithm](https://en.wikipedia.org/wiki/Natural_logarithm)   |
| `log10(A)`   | [Logarithm base 10](https://en.wikipedia.org/wiki/Common_logarithm)    |
| `log2(A)`    | [Logarithm base 2](https://en.wikipedia.org/wiki/Binary_logarithm)     |
| `pow(A, B)`  | [Exponentiation](https://en.wikipedia.org/wiki/Exponentiation) (Aᴮ)   |

Functions are composable: e.g. `sin(cos(x))`.

#### Special Commands

| Command | Description               |
|---------|---------------------------|
| `;`     | Print / evaluate           |
| `quit`  | Exit the calculator        |
| `help`  | Display usage instructions |

#### Variable Storage Evolution

| Exercise | Storage Method |
|----------|---------------|
| 1–6      | [`std::vector`](https://en.wikipedia.org/wiki/Dynamic_array) of `Variable` structs |
| 7+       | [`std::map`](https://en.wikipedia.org/wiki/Associative_array) for O(log n) lookup |

---

### Matrix Library (`mat_lib`, `mat_lib_v2`)

A generic [2D matrix](https://en.wikipedia.org/wiki/Matrix_(mathematics)) class implemented as a [C++ template](https://en.wikipedia.org/wiki/Generic_programming):

```cpp
mat_lib::matrix<double> a {
  {1, 2, 3},
  {4, 5, 6}
};
```

#### Supported Types

Enforced via [`static_assert`](https://en.wikipedia.org/wiki/Assertion_(software_development)):
- All integral and floating-point primitives
- `std::complex<float>`, `std::complex<double>`, `std::complex<long double>`

#### Supported Operations

| Operation     | Description                          |
|---------------|--------------------------------------|
| `A + B`       | Element-wise addition                |
| `A - B`       | Element-wise subtraction             |
| `A * B`       | [Matrix multiplication](https://en.wikipedia.org/wiki/Matrix_multiplication) |
| `A * scalar`  | Scalar multiplication                |
| `A / scalar`  | Scalar division                      |
| `~A`          | [Transpose](https://en.wikipedia.org/wiki/Transpose) |
| `-A`          | Element-wise negation                |
| `A == B`      | Equality comparison                  |
| `a.save_as("file")` | Persist matrix to file         |
| `matrix("file")`    | Load matrix from file (uses [regex](https://en.wikipedia.org/wiki/Regular_expression)) |

---

### Utilities

#### `file_writing.cpp`

A command-line tool that evaluates a mathematical function (default: `sin`) over an interval `[a, b]` with `n` points and writes the results to a file.

```bash
./file_writing output.txt 0 6.28 100
```

Uses [`<iomanip>`](https://en.wikipedia.org/wiki/C%2B%2B_Standard_Library) for formatted output.

#### `regex_example.cpp`

Demonstrates [regular expression](https://en.wikipedia.org/wiki/Regular_expression) matching using C++11's [`<regex>`](https://en.cppreference.com/w/cpp/regex) library. Matches patterns of the form `12345abc` (5 digits followed by letters).

---

## Key C++ Concepts Demonstrated

- [Recursive descent parsing](https://en.wikipedia.org/wiki/Recursive_descent_parser) — hand-rolled grammar evaluation
- [Exception handling](https://en.wikipedia.org/wiki/Exception_handling) — `try/catch` throughout for robust error recovery
- [Template metaprogramming](https://en.wikipedia.org/wiki/Template_metaprogramming) — generic `matrix<T>` with `static_assert` type constraints
- [Move semantics](https://en.wikipedia.org/wiki/Move_semantics) — move constructor and move assignment in matrix
- [RAII](https://en.wikipedia.org/wiki/Resource_acquisition_is_initialization) — manual memory management with `new`/`delete[]`
- [Operator overloading](https://en.wikipedia.org/wiki/Operator_overloading) — arithmetic, comparison, and stream operators for matrix
- [Regular expressions](https://en.wikipedia.org/wiki/Regular_expression) — used for matrix file parsing and standalone demo
- [Enumerations](https://en.wikipedia.org/wiki/Enumerated_type) — keyword token types organized with `enum`

---

## Build

Individual calculator files can be compiled directly:

```bash
g++ -std=c++14 -o calculator simple_calculator_v2.cpp
./calculator
```

The matrix library uses [CMake](https://en.wikipedia.org/wiki/CMake):

```bash
cd mat_lib_v2
mkdir build && cd build
cmake ..
make
./testing_mat_lib
```