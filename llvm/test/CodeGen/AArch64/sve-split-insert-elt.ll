; NOTE: Assertions have been autogenerated by utils/update_llc_test_checks.py
; RUN: llc -mtriple=aarch64-linux-gnu -mattr=+sve < %s | FileCheck %s

; INSERT VECTOR ELT

define <vscale x 8 x i8> @promote_insert_8i8(<vscale x 8 x i8> %a, i8 %elt, i64 %idx) {
; CHECK-LABEL: promote_insert_8i8:
; CHECK:       // %bb.0:
; CHECK-NEXT:    index z1.h, #0, #1
; CHECK-NEXT:    mov z2.h, w1
; CHECK-NEXT:    ptrue p0.h
; CHECK-NEXT:    cmpeq p0.h, p0/z, z1.h, z2.h
; CHECK-NEXT:    mov z0.h, p0/m, w0
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 8 x i8> %a, i8 %elt, i64 %idx
  ret <vscale x 8 x i8> %ins
}

define <vscale x 32 x i8> @split_insert_32i8_idx(<vscale x 32 x i8> %a, i8 %elt, i64 %idx) {
; CHECK-LABEL: split_insert_32i8_idx:
; CHECK:       // %bb.0:
; CHECK-NEXT:    str x29, [sp, #-16]! // 8-byte Folded Spill
; CHECK-NEXT:    addvl sp, sp, #-2
; CHECK-NEXT:    .cfi_escape 0x0f, 0x0c, 0x8f, 0x00, 0x11, 0x10, 0x22, 0x11, 0x10, 0x92, 0x2e, 0x00, 0x1e, 0x22 // sp + 16 + 16 * VG
; CHECK-NEXT:    .cfi_offset w29, -16
; CHECK-NEXT:    rdvl x8, #2
; CHECK-NEXT:    mov x9, sp
; CHECK-NEXT:    str z1, [sp, #1, mul vl]
; CHECK-NEXT:    sub x8, x8, #1
; CHECK-NEXT:    str z0, [sp]
; CHECK-NEXT:    cmp x1, x8
; CHECK-NEXT:    csel x8, x1, x8, lo
; CHECK-NEXT:    strb w0, [x9, x8]
; CHECK-NEXT:    ldr z0, [sp]
; CHECK-NEXT:    ldr z1, [sp, #1, mul vl]
; CHECK-NEXT:    addvl sp, sp, #2
; CHECK-NEXT:    ldr x29, [sp], #16 // 8-byte Folded Reload
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 32 x i8> %a, i8 %elt, i64 %idx
  ret <vscale x 32 x i8> %ins
}

define <vscale x 8 x float> @split_insert_8f32_idx(<vscale x 8 x float> %a, float %elt, i64 %idx) {
; CHECK-LABEL: split_insert_8f32_idx:
; CHECK:       // %bb.0:
; CHECK-NEXT:    str x29, [sp, #-16]! // 8-byte Folded Spill
; CHECK-NEXT:    addvl sp, sp, #-2
; CHECK-NEXT:    .cfi_escape 0x0f, 0x0c, 0x8f, 0x00, 0x11, 0x10, 0x22, 0x11, 0x10, 0x92, 0x2e, 0x00, 0x1e, 0x22 // sp + 16 + 16 * VG
; CHECK-NEXT:    .cfi_offset w29, -16
; CHECK-NEXT:    cnth x8
; CHECK-NEXT:    mov x9, sp
; CHECK-NEXT:    str z1, [sp, #1, mul vl]
; CHECK-NEXT:    sub x8, x8, #1
; CHECK-NEXT:    str z0, [sp]
; CHECK-NEXT:    cmp x0, x8
; CHECK-NEXT:    csel x8, x0, x8, lo
; CHECK-NEXT:    str s2, [x9, x8, lsl #2]
; CHECK-NEXT:    ldr z0, [sp]
; CHECK-NEXT:    ldr z1, [sp, #1, mul vl]
; CHECK-NEXT:    addvl sp, sp, #2
; CHECK-NEXT:    ldr x29, [sp], #16 // 8-byte Folded Reload
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 8 x float> %a, float %elt, i64 %idx
  ret <vscale x 8 x float> %ins
}

define <vscale x 8 x i64> @split_insert_8i64_idx(<vscale x 8 x i64> %a, i64 %elt, i64 %idx) {
; CHECK-LABEL: split_insert_8i64_idx:
; CHECK:       // %bb.0:
; CHECK-NEXT:    str x29, [sp, #-16]! // 8-byte Folded Spill
; CHECK-NEXT:    addvl sp, sp, #-4
; CHECK-NEXT:    .cfi_escape 0x0f, 0x0c, 0x8f, 0x00, 0x11, 0x10, 0x22, 0x11, 0x20, 0x92, 0x2e, 0x00, 0x1e, 0x22 // sp + 16 + 32 * VG
; CHECK-NEXT:    .cfi_offset w29, -16
; CHECK-NEXT:    cnth x8
; CHECK-NEXT:    mov x9, sp
; CHECK-NEXT:    str z3, [sp, #3, mul vl]
; CHECK-NEXT:    sub x8, x8, #1
; CHECK-NEXT:    str z2, [sp, #2, mul vl]
; CHECK-NEXT:    cmp x1, x8
; CHECK-NEXT:    str z1, [sp, #1, mul vl]
; CHECK-NEXT:    csel x8, x1, x8, lo
; CHECK-NEXT:    str z0, [sp]
; CHECK-NEXT:    str x0, [x9, x8, lsl #3]
; CHECK-NEXT:    ldr z0, [sp]
; CHECK-NEXT:    ldr z1, [sp, #1, mul vl]
; CHECK-NEXT:    ldr z2, [sp, #2, mul vl]
; CHECK-NEXT:    ldr z3, [sp, #3, mul vl]
; CHECK-NEXT:    addvl sp, sp, #4
; CHECK-NEXT:    ldr x29, [sp], #16 // 8-byte Folded Reload
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 8 x i64> %a, i64 %elt, i64 %idx
  ret <vscale x 8 x i64> %ins
}

; INSERT VECTOR ELT, CONSTANT IDX

define <vscale x 4 x i16> @promote_insert_4i16(<vscale x 4 x i16> %a, i16 %elt) {
; CHECK-LABEL: promote_insert_4i16:
; CHECK:       // %bb.0:
; CHECK-NEXT:    mov w8, #5 // =0x5
; CHECK-NEXT:    index z1.s, #0, #1
; CHECK-NEXT:    ptrue p0.s
; CHECK-NEXT:    mov z2.s, w8
; CHECK-NEXT:    cmpeq p0.s, p0/z, z1.s, z2.s
; CHECK-NEXT:    mov z0.s, p0/m, w0
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 4 x i16> %a, i16 %elt, i64 5
  ret <vscale x 4 x i16> %ins
}

; In this test, the index is small enough that we know it will be in the
; low half of the vector and there is no need to go through the stack as
; done in the remaining tests
define <vscale x 32 x i8> @split_insert_32i8(<vscale x 32 x i8> %a, i8 %elt) {
; CHECK-LABEL: split_insert_32i8:
; CHECK:       // %bb.0:
; CHECK-NEXT:    mov w8, #3 // =0x3
; CHECK-NEXT:    index z2.b, #0, #1
; CHECK-NEXT:    ptrue p0.b
; CHECK-NEXT:    mov z3.b, w8
; CHECK-NEXT:    cmpeq p0.b, p0/z, z2.b, z3.b
; CHECK-NEXT:    mov z0.b, p0/m, w0
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 32 x i8> %a, i8 %elt, i64 3
  ret <vscale x 32 x i8> %ins
}

define <vscale x 32 x i16> @split_insert_32i16(<vscale x 32 x i16> %a, i16 %elt) {
; CHECK-LABEL: split_insert_32i16:
; CHECK:       // %bb.0:
; CHECK-NEXT:    str x29, [sp, #-16]! // 8-byte Folded Spill
; CHECK-NEXT:    addvl sp, sp, #-4
; CHECK-NEXT:    .cfi_escape 0x0f, 0x0c, 0x8f, 0x00, 0x11, 0x10, 0x22, 0x11, 0x20, 0x92, 0x2e, 0x00, 0x1e, 0x22 // sp + 16 + 32 * VG
; CHECK-NEXT:    .cfi_offset w29, -16
; CHECK-NEXT:    rdvl x8, #2
; CHECK-NEXT:    mov w9, #128 // =0x80
; CHECK-NEXT:    str z3, [sp, #3, mul vl]
; CHECK-NEXT:    sub x8, x8, #1
; CHECK-NEXT:    str z2, [sp, #2, mul vl]
; CHECK-NEXT:    cmp x8, #128
; CHECK-NEXT:    str z1, [sp, #1, mul vl]
; CHECK-NEXT:    csel x8, x8, x9, lo
; CHECK-NEXT:    mov x9, sp
; CHECK-NEXT:    str z0, [sp]
; CHECK-NEXT:    strh w0, [x9, x8, lsl #1]
; CHECK-NEXT:    ldr z0, [sp]
; CHECK-NEXT:    ldr z1, [sp, #1, mul vl]
; CHECK-NEXT:    ldr z2, [sp, #2, mul vl]
; CHECK-NEXT:    ldr z3, [sp, #3, mul vl]
; CHECK-NEXT:    addvl sp, sp, #4
; CHECK-NEXT:    ldr x29, [sp], #16 // 8-byte Folded Reload
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 32 x i16> %a, i16 %elt, i64 128
  ret <vscale x 32 x i16> %ins
}

define <vscale x 8 x i32> @split_insert_8i32(<vscale x 8 x i32> %a, i32 %elt) {
; CHECK-LABEL: split_insert_8i32:
; CHECK:       // %bb.0:
; CHECK-NEXT:    str x29, [sp, #-16]! // 8-byte Folded Spill
; CHECK-NEXT:    addvl sp, sp, #-2
; CHECK-NEXT:    .cfi_escape 0x0f, 0x0c, 0x8f, 0x00, 0x11, 0x10, 0x22, 0x11, 0x10, 0x92, 0x2e, 0x00, 0x1e, 0x22 // sp + 16 + 16 * VG
; CHECK-NEXT:    .cfi_offset w29, -16
; CHECK-NEXT:    cnth x8
; CHECK-NEXT:    mov w9, #16960 // =0x4240
; CHECK-NEXT:    str z1, [sp, #1, mul vl]
; CHECK-NEXT:    movk w9, #15, lsl #16
; CHECK-NEXT:    sub x8, x8, #1
; CHECK-NEXT:    str z0, [sp]
; CHECK-NEXT:    cmp x8, x9
; CHECK-NEXT:    csel x8, x8, x9, lo
; CHECK-NEXT:    mov x9, sp
; CHECK-NEXT:    str w0, [x9, x8, lsl #2]
; CHECK-NEXT:    ldr z0, [sp]
; CHECK-NEXT:    ldr z1, [sp, #1, mul vl]
; CHECK-NEXT:    addvl sp, sp, #2
; CHECK-NEXT:    ldr x29, [sp], #16 // 8-byte Folded Reload
; CHECK-NEXT:    ret
  %ins = insertelement <vscale x 8 x i32> %a, i32 %elt, i64 1000000
  ret <vscale x 8 x i32> %ins
}
