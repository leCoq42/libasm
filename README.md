# libasm

The aim of this project is to become familiar with assembly language.

Overview of x86 registers. The 64 bit registers are shown in red.
<img width="974" height="605" alt="image" src="https://github.com/user-attachments/assets/c249f678-bc87-4bed-ae6f-78a0a70d5afb" />

# Usage

```bash
make # Build the library and a binary for the tests in main.c.
make fclean # Cleanup the files created with make.
make re # Calls 'make fclean' and then 'make'.
make test # Builds the test file and links it with the library, then executes the testfile.
make test_re # Calls 'make fclean' and then 'test'.
./test.out # Execute binary with testcases for the libasm library.
```

---

Resources:

- https://www.cs.uaf.edu/2017/fall/cs301/reference/x86_64.html
- https://cs.brown.edu/courses/cs033/docs/guides/x64_cheatsheet.pdf
