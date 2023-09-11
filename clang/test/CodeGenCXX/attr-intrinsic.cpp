// RUN: %clang_cc1 -S -emit-llvm %s -triple x86_64-unknown-linux-gnu -o - | FileCheck %s

struct S {
  operator int();
};

template <class T>
[[clang::intrinsic("reference_cast")]] __remove_reference_t(T)&& move(T&& v) {
  return static_cast<__remove_reference_t(T)&&>(v);
}

template <class T>
[[clang::intrinsic("trivial_bit_cast")]] __underlying_type(T) to_underlying(T v) {
  return static_cast<__underlying_type(T)>(v);
}

enum class E : int {};

void take(S&&);
void take(int);

// CHECK-LABEL: define {{.*}} void @_Z4test
void test(S& v, E e) {
  // CHECK: store ptr %{{.*}}, ptr %[[T_REF:[^,]*]]
  // CHECK: %0 = load ptr, ptr %[[T_REF]]
  // CHECK: call void @_Z4takeO1S(ptr {{.*}} %0)
  take(move(v));

  // CHECK: %1 = load i32, ptr %e.addr, align 4
  // CHECK: call void @_Z4takei(i32 noundef %1)
  take(to_underlying(e));
}
