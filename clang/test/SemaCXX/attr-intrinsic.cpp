// RUN: %clang_cc1 -verify %s

namespace general {
[[clang::intrinsic]] void func1(); // expected-error {{'intrinsic' attribute takes one argument}}
[[clang::intrinsic("Banane", "Banane")]] void func2(); // expected-error {{'intrinsic' attribute takes no more than 1 argument}}
[[clang::intrinsic("Banane")]] void func3(int); // expected-error {{invalid intrinsic kind; use 'reference_cast' or 'trivial_bit_cast' instead}}
[[clang::intrinsic("reference_cast"), clang::intrinsic("trivial_bit_cast")]] int& func3(int&); // expected-error {{one function cannot be equivalent to multiple intrinsics at the same time}}
}

namespace reference_cast {
[[clang::intrinsic("reference_cast")]] void func1(); // expected-error {{reference_cast instrinsic takes exactly one argument}}
[[clang::intrinsic("reference_cast")]] void func2(int, int); // expected-error {{reference_cast instrinsic takes exactly one argument}}
[[clang::intrinsic("reference_cast")]] int& func3(int&);

[[clang::intrinsic("reference_cast")]] int func4(long&); // expected-error {{return type has to be a reference type}}
[[clang::intrinsic("reference_cast")]] int& func4(long); // expected-error {{parameter has to be a reference type}}
[[clang::intrinsic("reference_cast")]] int& func5(int&&); // expected-error {{cannot cast 'int &&' to 'int &'}}
[[clang::intrinsic("reference_cast")]] int& func6(int&&); // expected-error {{cannot cast 'int &&' to 'int &'}}
}

namespace trivial_bit_cast {
[[clang::intrinsic("trivial_bit_cast")]] int& func1(int); // expected-error {{return type has to be a value type}}
[[clang::intrinsic("trivial_bit_cast")]] int func2(int&); // expected-error {{parameter has to be a value type}}
[[clang::intrinsic("trivial_bit_cast")]] char func3(long long); // expected-error {{The return type and parameter do not have the same size}}

enum class E : char {};
[[clang::intrinsic("trivial_bit_cast")]] char func3(E);
}
