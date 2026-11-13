# UNLaM — Programming Fundamentals in C and C++

Selected academic implementations by **Federico Pucci**: strings, matrices, binary/text files, linked lists and C++ operator overloading. Developed for Programación at Universidad Nacional de La Matanza.

| Exercise | Content | Retained scope |
| --- | --- | --- |
| [Bank accounts](exercises/bank-accounts) | Sorted movement list and binary account updates | Complete console example with synthetic records |
| [String replacement](exercises/string-replacement) | Case-insensitive, in-place search and replacement | Complete console example |
| [Time of day](exercises/time-of-day) | Constructors, comparisons, addition, increment and streams | Windows C++ console example using `Sleep` |
| [Text and matrices](exercises/text-and-matrices) | Word traversal, bounded copies, text processing and matrix operations | Student functions plus course interface |
| [Encoding and records](exercises/encoding-and-records) | Substitution tables, parsing grades and updating records | Student functions plus course interface |
| [Bounded doubly linked list](drafts/bounded-doubly-linked-list) | Ordered insertion, record comparison and capacity handling | Historical excerpt; original interface is missing |

## Compile

Requires Python 3 and GCC; Windows additionally needs G++/MinGW for the clock.

```sh
python scripts/build.py
```

On Linux the script builds the two portable C executables and compiles two solution objects. On Windows it also builds `build/time-of-day.exe`. The reference implementations supplied as binary libraries by the course are not published, so the two `funciones.c` submissions are compiled as objects rather than linked with the original grading driver.

Sources are UTF-8. The build uses `-fexec-charset=ISO-8859-1` to preserve the original single-byte accented character literals; these exercises do not implement general Unicode text processing.

To run the C examples on Linux:

```sh
cd build
./string-replacement
./bank-accounts
```

On Windows, run the corresponding `.exe` files from `build`. The bank example creates and overwrites `cuentas.dat` and `movimientos.txt` in the working directory using its built-in synthetic records.

## Validation and limitations

The two C executables and the two solution objects compiled on Ubuntu/WSL and Windows/MinGW. The two C console examples were also executed on Windows. The C++ clock compiled on Windows; its interactive timer was not exercised. Compiler warnings remain visible, including legacy signedness and unused-parameter warnings and Windows file-offset conversions. General correctness, malformed input and memory safety have not been exhaustively validated.

CI checks compilation of the portable C subset. The doubly linked list excerpt is excluded because its original header was not found in the personal submission; another student's implementation was not used to reconstruct it.

This is a curated academic archive. Personal identity numbers, generated files and empty duplicate helper templates were omitted. `_MIO` functions distinguish student implementations from the provided interfaces. See [source and attribution notes](SOURCES.md) and the [main portfolio](https://github.com/FedePucci1/portfolio-index).
