// NOTE: Assertions have been autogenerated by utils/update_cc_test_checks.py

// RUN: %clang_cc1 -triple x86_64 -emit-llvm -o - %s | FileCheck %s
//
// Verifies that clang detects memcpy inline version and uses it instead of the builtin.
// Checks alternate version with the `artificial` attribute.

typedef unsigned long size_t;

// Clang requires these attributes for a function to be redefined.
#define AVAILABLE_EXTERNALLY extern inline __attribute__((always_inline)) __attribute__((gnu_inline))

#define AVAILABLE_EXTERNALLY_ALTERNATE extern inline __attribute__((__always_inline__)) __attribute__((__artificial__))

// Clang recognizes an inline builtin and renames it to prevent conflict with builtins.
AVAILABLE_EXTERNALLY void *memcpy(void *a, const void *b, size_t c) {
  asm("# memcpy.inline marker");
  return __builtin_memcpy(a, b, c);
}

// Clang recognizes an inline builtin and renames it to prevent conflict with builtins.
AVAILABLE_EXTERNALLY_ALTERNATE void *memmove(void *a, const void *b, size_t c) {
  asm("# memmove.inline marker");
  return __builtin_memmove(a, b, c);
}

// CHECK-LABEL: @foo(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR_I:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR_I:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[C_ADDR_I:%.*]] = alloca i64, align 8
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[C_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    store ptr [[A:%.*]], ptr [[A_ADDR]], align 8
// CHECK-NEXT:    store ptr [[B:%.*]], ptr [[B_ADDR]], align 8
// CHECK-NEXT:    store i64 [[C:%.*]], ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[A_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[B_ADDR]], align 8
// CHECK-NEXT:    [[TMP2:%.*]] = load i64, ptr [[C_ADDR]], align 8
// CHECK-NEXT:    store ptr [[TMP0]], ptr [[A_ADDR_I]], align 8
// CHECK-NEXT:    store ptr [[TMP1]], ptr [[B_ADDR_I]], align 8
// CHECK-NEXT:    store i64 [[TMP2]], ptr [[C_ADDR_I]], align 8
// CHECK-NEXT:    call void asm sideeffect "# memcpy.inline marker", "~{dirflag},~{fpsr},~{flags}"() #[[ATTR3:[0-9]+]], !srcloc !2
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[A_ADDR_I]], align 8
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[B_ADDR_I]], align 8
// CHECK-NEXT:    [[TMP5:%.*]] = load i64, ptr [[C_ADDR_I]], align 8
// CHECK-NEXT:    call void @llvm.memcpy.p0.p0.i64(ptr align 1 [[TMP3]], ptr align 1 [[TMP4]], i64 [[TMP5]], i1 false)
// CHECK-NEXT:    ret ptr [[TMP3]]
//
void *foo(void *a, const void *b, size_t c) {
  return memcpy(a, b, c);
}

// CHECK-LABEL: @foo_alt(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR_I:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR_I:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[C_ADDR_I:%.*]] = alloca i64, align 8
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[C_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    store ptr [[A:%.*]], ptr [[A_ADDR]], align 8
// CHECK-NEXT:    store ptr [[B:%.*]], ptr [[B_ADDR]], align 8
// CHECK-NEXT:    store i64 [[C:%.*]], ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load ptr, ptr [[A_ADDR]], align 8
// CHECK-NEXT:    [[TMP1:%.*]] = load ptr, ptr [[B_ADDR]], align 8
// CHECK-NEXT:    [[TMP2:%.*]] = load i64, ptr [[C_ADDR]], align 8
// CHECK-NEXT:    store ptr [[TMP0]], ptr [[A_ADDR_I]], align 8
// CHECK-NEXT:    store ptr [[TMP1]], ptr [[B_ADDR_I]], align 8
// CHECK-NEXT:    store i64 [[TMP2]], ptr [[C_ADDR_I]], align 8
// CHECK-NEXT:    call void asm sideeffect "# memmove.inline marker", "~{dirflag},~{fpsr},~{flags}"() #[[ATTR3]], !srcloc !3
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[A_ADDR_I]], align 8
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[B_ADDR_I]], align 8
// CHECK-NEXT:    [[TMP5:%.*]] = load i64, ptr [[C_ADDR_I]], align 8
// CHECK-NEXT:    call void @llvm.memmove.p0.p0.i64(ptr align 1 [[TMP3]], ptr align 1 [[TMP4]], i64 [[TMP5]], i1 false)
// CHECK-NEXT:    ret ptr [[TMP3]]
//
void *foo_alt(void *a, const void *b, size_t c) {
  return memmove(a, b, c);
}

// CHECK-LABEL: @bar(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[C_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    [[CPY:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    store ptr [[A:%.*]], ptr [[A_ADDR]], align 8
// CHECK-NEXT:    store ptr [[B:%.*]], ptr [[B_ADDR]], align 8
// CHECK-NEXT:    store i64 [[C:%.*]], ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[CMP:%.*]] = icmp ugt i64 [[TMP0]], 10
// CHECK-NEXT:    [[TMP1:%.*]] = zext i1 [[CMP]] to i64
// CHECK-NEXT:    [[COND:%.*]] = select i1 [[CMP]], ptr @memcpy, ptr @foo
// CHECK-NEXT:    store ptr [[COND]], ptr [[CPY]], align 8
// CHECK-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[CPY]], align 8
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[A_ADDR]], align 8
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[B_ADDR]], align 8
// CHECK-NEXT:    [[TMP5:%.*]] = load i64, ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call ptr [[TMP2]](ptr noundef [[TMP3]], ptr noundef [[TMP4]], i64 noundef [[TMP5]])
// CHECK-NEXT:    ret void
//
void bar(void *a, const void *b, size_t c) {
  void *(*cpy)(void *, const void *, size_t) = c > 10 ? memcpy : foo;
  cpy(a, b, c);
}

// CHECK-LABEL: @bar_alt(
// CHECK-NEXT:  entry:
// CHECK-NEXT:    [[A_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[B_ADDR:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    [[C_ADDR:%.*]] = alloca i64, align 8
// CHECK-NEXT:    [[CPY:%.*]] = alloca ptr, align 8
// CHECK-NEXT:    store ptr [[A:%.*]], ptr [[A_ADDR]], align 8
// CHECK-NEXT:    store ptr [[B:%.*]], ptr [[B_ADDR]], align 8
// CHECK-NEXT:    store i64 [[C:%.*]], ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[TMP0:%.*]] = load i64, ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[CMP:%.*]] = icmp ugt i64 [[TMP0]], 10
// CHECK-NEXT:    [[TMP1:%.*]] = zext i1 [[CMP]] to i64
// CHECK-NEXT:    [[COND:%.*]] = select i1 [[CMP]], ptr @memmove, ptr @foo_alt
// CHECK-NEXT:    store ptr [[COND]], ptr [[CPY]], align 8
// CHECK-NEXT:    [[TMP2:%.*]] = load ptr, ptr [[CPY]], align 8
// CHECK-NEXT:    [[TMP3:%.*]] = load ptr, ptr [[A_ADDR]], align 8
// CHECK-NEXT:    [[TMP4:%.*]] = load ptr, ptr [[B_ADDR]], align 8
// CHECK-NEXT:    [[TMP5:%.*]] = load i64, ptr [[C_ADDR]], align 8
// CHECK-NEXT:    [[CALL:%.*]] = call ptr [[TMP2]](ptr noundef [[TMP3]], ptr noundef [[TMP4]], i64 noundef [[TMP5]])
// CHECK-NEXT:    ret void
//
void bar_alt(void *a, const void *b, size_t c) {
  void *(*cpy)(void *, const void *, size_t) = c > 10 ? memmove : foo_alt;
  cpy(a, b, c);
}
