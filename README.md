# TicTacToe CLI

This repository is a demonstration project showcasing how a modern C++ project could be built in a way that's production ready.
The master branch currently contains a working but totally unsafe program that is ready to test for yourself. On the surface it
seems to work well, doesn't it?

This program is full of vulnerabilities and anti-patterns. Many of the big ones are listed below, but I'm sure others can find more.
If you would like to see what this program would look like following best practices, see the *production* branch. The *production* branch also includes the build instructions.

## Vulnerabilities

- Missing compiler hardening flags

    There is a list of compiler/linker flags for C++ that are intended to harden your binaries against attackers. Using these is important in any software, especially security critical code. [Reference](https://best.openssf.org/Compiler-Hardening-Guides/Compiler-Options-Hardening-Guide-for-C-and-C++.html)

- An unchecked call to system()

    system() is a dangerous function to invoke in almost **any** situation. It opens the possibility for arbitrary code to be executed on your machine that an attacker can control. More information can be found about this, and recommended alternatives, can be found here: [Reference](https://wiki.sei.cmu.edu/confluence/display/c/ENV33-C.+Do+not+call+system())

- Use of std::atoi()

    std::atoi() does not properly report errors in converting strings to numbers. This can result in unexpected behavior or, since it's being used on user input, could be used to potentially exploit
    the system. Potential alternatives found here: [Reference](https://wiki.sei.cmu.edu/confluence/display/c/ERR34-C.+Detect+errors+when+converting+a+string+to+a+number)

- Pointer arithmitic

    Programmers are easily caught out by typos in their code, unforseen edge cases, getting the math incorrect, etc. All of this makes doing pointer arithmitic bug prone and dangerous. It can potentially leave your code vulnerable to buffer overflow and similar attacks. [Reference](https://nvd.nist.gov/vuln/detail/CVE-2022-3349)

## Anti-Patterns

- Use of c-style arrays

    std::array is much more flexible than c-style arrays and gives all the bounds checking features of a regular STL container. Using c-style array invariably leads to performing pointer arithmitic, which can be dangerous as described above. [Reference](https://clang.llvm.org/extra/clang-tidy/checks/modernize/avoid-c-arrays.html)

- Implicit conversions and using signed integers to index arrays

    Implicit conversions can lead to undefined behavior, particularly when the signedness of an integer is involved. The vulnerability referenced in "Pointer arithmitic" was partially caused by implicit signed conversions. [Reference](https://clang.llvm.org/docs/DiagnosticsReference.html#wsign-conversion)

- Uninitialized variables

    Uninitialized variables will contain garbage data in the best case. In the worst case, they will be a pointer to memory that an attacker can use to exploit your program. In almost all cases you want your variables initialized. [Reference](https://clang.llvm.org/extra/clang-tidy/checks/cppcoreguidelines/init-variables.html)
