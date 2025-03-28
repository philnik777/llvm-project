; NOTE: Assertions have been autogenerated by utils/update_test_checks.py
; RUN: opt < %s -passes=slp-vectorizer -mtriple=riscv64 -mattr=+v \
; RUN: -riscv-v-vector-bits-min=-1 -riscv-v-slp-max-vf=0 -S | FileCheck %s --check-prefixes=CHECK
; RUN: opt < %s -passes=slp-vectorizer -mtriple=riscv64 -mattr=+v -S | FileCheck %s --check-prefixes=DEFAULT


define void @simple_copy(ptr %dest, ptr %p) {
; CHECK-LABEL: @simple_copy(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[TMP0:%.*]] = load <2 x i16>, ptr [[P:%.*]], align 4
; CHECK-NEXT:    store <2 x i16> [[TMP0]], ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @simple_copy(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    [[TMP0:%.*]] = load <2 x i16>, ptr [[P:%.*]], align 4
; DEFAULT-NEXT:    store <2 x i16> [[TMP0]], ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    ret void
;
entry:
  %e0 = load i16, ptr %p, align 4
  %inc = getelementptr inbounds i16, ptr %p, i64 1
  %e1 = load i16, ptr %inc, align 2

  store i16 %e0, ptr %dest, align 4
  %inc2 = getelementptr inbounds i16, ptr %dest, i64 1
  store i16 %e1, ptr %inc2, align 2
  ret void
}

define void @vec_add(ptr %dest, ptr %p) {
; CHECK-LABEL: @vec_add(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[TMP0:%.*]] = load <2 x i16>, ptr [[P:%.*]], align 4
; CHECK-NEXT:    [[TMP1:%.*]] = add <2 x i16> [[TMP0]], splat (i16 1)
; CHECK-NEXT:    store <2 x i16> [[TMP1]], ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @vec_add(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    [[TMP0:%.*]] = load <2 x i16>, ptr [[P:%.*]], align 4
; DEFAULT-NEXT:    [[TMP1:%.*]] = add <2 x i16> [[TMP0]], splat (i16 1)
; DEFAULT-NEXT:    store <2 x i16> [[TMP1]], ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    ret void
;
entry:
  %e0 = load i16, ptr %p, align 4
  %inc = getelementptr inbounds i16, ptr %p, i64 1
  %e1 = load i16, ptr %inc, align 2

  %a0 = add i16 %e0, 1
  %a1 = add i16 %e1, 1

  store i16 %a0, ptr %dest, align 4
  %inc2 = getelementptr inbounds i16, ptr %dest, i64 1
  store i16 %a1, ptr %inc2, align 2
  ret void
}


define void @splat_store_i16(ptr %dest, ptr %p) {
; CHECK-LABEL: @splat_store_i16(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[E0:%.*]] = load i16, ptr [[P:%.*]], align 4
; CHECK-NEXT:    store i16 [[E0]], ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    [[INC2:%.*]] = getelementptr inbounds i16, ptr [[DEST]], i64 1
; CHECK-NEXT:    store i16 [[E0]], ptr [[INC2]], align 2
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @splat_store_i16(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    [[E0:%.*]] = load i16, ptr [[P:%.*]], align 4
; DEFAULT-NEXT:    store i16 [[E0]], ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    [[INC2:%.*]] = getelementptr inbounds i16, ptr [[DEST]], i64 1
; DEFAULT-NEXT:    store i16 [[E0]], ptr [[INC2]], align 2
; DEFAULT-NEXT:    ret void
;
entry:
  %e0 = load i16, ptr %p, align 4

  store i16 %e0, ptr %dest, align 4
  %inc2 = getelementptr inbounds i16, ptr %dest, i64 1
  store i16 %e0, ptr %inc2, align 2
  ret void
}

define void @splat_store_i64(ptr %dest, ptr %p) {
; CHECK-LABEL: @splat_store_i64(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    [[E0:%.*]] = load i64, ptr [[P:%.*]], align 4
; CHECK-NEXT:    store i64 [[E0]], ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    [[INC2:%.*]] = getelementptr inbounds i64, ptr [[DEST]], i64 1
; CHECK-NEXT:    store i64 [[E0]], ptr [[INC2]], align 2
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @splat_store_i64(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    [[E0:%.*]] = load i64, ptr [[P:%.*]], align 4
; DEFAULT-NEXT:    store i64 [[E0]], ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    [[INC2:%.*]] = getelementptr inbounds i64, ptr [[DEST]], i64 1
; DEFAULT-NEXT:    store i64 [[E0]], ptr [[INC2]], align 2
; DEFAULT-NEXT:    ret void
;
entry:
  %e0 = load i64, ptr %p, align 4

  store i64 %e0, ptr %dest, align 4
  %inc2 = getelementptr inbounds i64, ptr %dest, i64 1
  store i64 %e0, ptr %inc2, align 2
  ret void
}

define void @splat_store_i64_zero(ptr %dest) {
; CHECK-LABEL: @splat_store_i64_zero(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    store i64 0, ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    [[INC2:%.*]] = getelementptr inbounds i64, ptr [[DEST]], i64 1
; CHECK-NEXT:    store i64 0, ptr [[INC2]], align 2
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @splat_store_i64_zero(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    store i64 0, ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    [[INC2:%.*]] = getelementptr inbounds i64, ptr [[DEST]], i64 1
; DEFAULT-NEXT:    store i64 0, ptr [[INC2]], align 2
; DEFAULT-NEXT:    ret void
;
entry:
  store i64 0, ptr %dest, align 4
  %inc2 = getelementptr inbounds i64, ptr %dest, i64 1
  store i64 0, ptr %inc2, align 2
  ret void
}

define void @splat_store_i64_one(ptr %dest) {
; CHECK-LABEL: @splat_store_i64_one(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    store i64 1, ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    [[INC2:%.*]] = getelementptr inbounds i64, ptr [[DEST]], i64 1
; CHECK-NEXT:    store i64 1, ptr [[INC2]], align 2
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @splat_store_i64_one(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    store i64 1, ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    [[INC2:%.*]] = getelementptr inbounds i64, ptr [[DEST]], i64 1
; DEFAULT-NEXT:    store i64 1, ptr [[INC2]], align 2
; DEFAULT-NEXT:    ret void
;
entry:
  store i64 1, ptr %dest, align 4
  %inc2 = getelementptr inbounds i64, ptr %dest, i64 1
  store i64 1, ptr %inc2, align 2
  ret void
}

define void @splat_store_i32_zero(ptr %dest) {
; CHECK-LABEL: @splat_store_i32_zero(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    store <4 x i32> zeroinitializer, ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @splat_store_i32_zero(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    store <4 x i32> zeroinitializer, ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    ret void
;
entry:
  store i32 0, ptr %dest, align 4
  %inc1 = getelementptr inbounds i32, ptr %dest, i64 1
  store i32 0, ptr %inc1, align 2
  %inc2 = getelementptr inbounds i32, ptr %dest, i64 2
  store i32 0, ptr %inc2, align 2
  %inc3 = getelementptr inbounds i32, ptr %dest, i64 3
  store i32 0, ptr %inc3, align 2
  ret void
}

define void @splat_store_i32_one(ptr %dest) {
; CHECK-LABEL: @splat_store_i32_one(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    store <4 x i32> splat (i32 1), ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @splat_store_i32_one(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    store <4 x i32> splat (i32 1), ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    ret void
;
entry:
  store i32 1, ptr %dest, align 4
  %inc1 = getelementptr inbounds i32, ptr %dest, i64 1
  store i32 1, ptr %inc1, align 2
  %inc2 = getelementptr inbounds i32, ptr %dest, i64 2
  store i32 1, ptr %inc2, align 2
  %inc3 = getelementptr inbounds i32, ptr %dest, i64 3
  store i32 1, ptr %inc3, align 2
  ret void
}

define void @store_stepvector_i32(ptr %dest) {
; CHECK-LABEL: @store_stepvector_i32(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    store i32 0, ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    [[INC1:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 1
; CHECK-NEXT:    store i32 1, ptr [[INC1]], align 2
; CHECK-NEXT:    [[INC2:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 2
; CHECK-NEXT:    store i32 2, ptr [[INC2]], align 2
; CHECK-NEXT:    [[INC3:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 3
; CHECK-NEXT:    store i32 3, ptr [[INC3]], align 2
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @store_stepvector_i32(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    store i32 0, ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    [[INC1:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 1
; DEFAULT-NEXT:    store i32 1, ptr [[INC1]], align 2
; DEFAULT-NEXT:    [[INC2:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 2
; DEFAULT-NEXT:    store i32 2, ptr [[INC2]], align 2
; DEFAULT-NEXT:    [[INC3:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 3
; DEFAULT-NEXT:    store i32 3, ptr [[INC3]], align 2
; DEFAULT-NEXT:    ret void
;
entry:
  store i32 0, ptr %dest, align 4
  %inc1 = getelementptr inbounds i32, ptr %dest, i64 1
  store i32 1, ptr %inc1, align 2
  %inc2 = getelementptr inbounds i32, ptr %dest, i64 2
  store i32 2, ptr %inc2, align 2
  %inc3 = getelementptr inbounds i32, ptr %dest, i64 3
  store i32 3, ptr %inc3, align 2
  ret void
}

define void @store_arbitrary_constant_i32(ptr %dest) {
; CHECK-LABEL: @store_arbitrary_constant_i32(
; CHECK-NEXT:  entry:
; CHECK-NEXT:    store i32 0, ptr [[DEST:%.*]], align 4
; CHECK-NEXT:    [[INC1:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 1
; CHECK-NEXT:    store i32 -33, ptr [[INC1]], align 2
; CHECK-NEXT:    [[INC2:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 2
; CHECK-NEXT:    store i32 44, ptr [[INC2]], align 2
; CHECK-NEXT:    [[INC3:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 3
; CHECK-NEXT:    store i32 77, ptr [[INC3]], align 2
; CHECK-NEXT:    ret void
;
; DEFAULT-LABEL: @store_arbitrary_constant_i32(
; DEFAULT-NEXT:  entry:
; DEFAULT-NEXT:    store i32 0, ptr [[DEST:%.*]], align 4
; DEFAULT-NEXT:    [[INC1:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 1
; DEFAULT-NEXT:    store i32 -33, ptr [[INC1]], align 2
; DEFAULT-NEXT:    [[INC2:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 2
; DEFAULT-NEXT:    store i32 44, ptr [[INC2]], align 2
; DEFAULT-NEXT:    [[INC3:%.*]] = getelementptr inbounds i32, ptr [[DEST]], i64 3
; DEFAULT-NEXT:    store i32 77, ptr [[INC3]], align 2
; DEFAULT-NEXT:    ret void
;
entry:
  store i32 0, ptr %dest, align 4
  %inc1 = getelementptr inbounds i32, ptr %dest, i64 1
  store i32 -33, ptr %inc1, align 2
  %inc2 = getelementptr inbounds i32, ptr %dest, i64 2
  store i32 44, ptr %inc2, align 2
  %inc3 = getelementptr inbounds i32, ptr %dest, i64 3
  store i32 77, ptr %inc3, align 2
  ret void
}
