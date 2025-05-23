# REQUIRES: loongarch
# RUN: rm -rf %t && split-file %s %t

# RUN: llvm-mc --filetype=obj --triple=loongarch32 %t/32.s -o %t/32.o
# RUN: llvm-mc --filetype=obj --triple=loongarch64 %t/64.s -o %t/64.o

## LA32 IE
# RUN: ld.lld -shared %t/32.o -o %t/32.so
# RUN: llvm-readobj -r -d %t/32.so | FileCheck --check-prefix=IE32-REL %s
# RUN: llvm-objdump -d --no-show-raw-insn %t/32.so | FileCheck --check-prefixes=IE32 %s

## LA32 IE -> LE
# RUN: ld.lld %t/32.o -o %t/32
# RUN: llvm-readelf -r %t/32 | FileCheck --check-prefix=NOREL %s
# RUN: llvm-readelf -x .got %t/32 2>&1 | FileCheck --check-prefix=LE32-GOT %s
# RUN: llvm-objdump -d --no-show-raw-insn %t/32 | FileCheck --check-prefixes=LE32 %s

## LA64 IE
# RUN: ld.lld -shared %t/64.o -o %t/64.so
# RUN: llvm-readobj -r -d %t/64.so | FileCheck --check-prefix=IE64-REL %s
# RUN: llvm-objdump -d --no-show-raw-insn %t/64.so | FileCheck --check-prefixes=IE64 %s

## LA64 IE -> LE
# RUN: ld.lld %t/64.o -o %t/64
# RUN: llvm-readelf -r %t/64 | FileCheck --check-prefix=NOREL %s
# RUN: llvm-readelf -x .got %t/64 2>&1 | FileCheck --check-prefix=LE64-GOT %s
# RUN: llvm-objdump -d --no-show-raw-insn %t/64 | FileCheck --check-prefixes=LE64 %s

# IE32-REL:      FLAGS STATIC_TLS
# IE32-REL:      .rela.dyn {
# IE32-REL-NEXT:   0x20218 R_LARCH_TLS_TPREL32 - 0xC
# IE32-REL-NEXT:   0x20214 R_LARCH_TLS_TPREL32 a 0x0
# IE32-REL-NEXT: }

# IE64-REL:      FLAGS STATIC_TLS
# IE64-REL:      .rela.dyn {
# IE64-REL-NEXT:   0x20370 R_LARCH_TLS_TPREL64 - 0xC
# IE64-REL-NEXT:   0x20368 R_LARCH_TLS_TPREL64 a 0x0
# IE64-REL-NEXT: }

## LA32:
## &.got[0] - . = 0x20214 - 0x101a4: 0x10 pages, page offset 0x214
## &.got[1] - . = 0x20218 - 0x101b0: 0x10 pages, page offset 0x218
# IE32:      101a4: pcalau12i $a4, 16
# IE32-NEXT:        ld.w $a4, $a4, 532
# IE32-NEXT:        add.w $a4, $a4, $tp
# IE32-NEXT: 101b0: pcalau12i $a5, 16
# IE32-NEXT:        ld.w $a5, $a5, 536
# IE32-NEXT:        add.w $a5, $a5, $tp

## LA64:
## &.got[0] - . = 0x20368 - 0x102a0: 0x10 pages, page offset 0x368
## &.got[1] - . = 0x20370 - 0x102ac: 0x10 pages, page offset 0x370
# IE64:      102a0: pcalau12i $a4, 16
# IE64-NEXT:        ld.d $a4, $a4, 872
# IE64-NEXT:        add.d $a4, $a4, $tp
# IE64-NEXT: 102ac: pcalau12i $a5, 16
# IE64-NEXT:        ld.d $a5, $a5, 880
# IE64-NEXT:        add.d $a5, $a5, $tp

# NOREL: no relocations

# a@tprel = st_value(a) = 0x8
# b@tprel = st_value(a) = 0xc
# LE32-GOT: could not find section '.got'
# LE64-GOT: could not find section '.got'

## LA32:
# LE32:      200d4: nop
# LE32-NEXT:        ori $a4, $zero, 8
# LE32-NEXT:        add.w $a4, $a4, $tp
# LE32-NEXT: 200e0: nop
# LE32-NEXT:        ori $a5, $zero, 12
# LE32-NEXT:        add.w $a5, $a5, $tp

## LA64:
# LE64:      20158: nop
# LE64-NEXT:        ori $a4, $zero, 8
# LE64-NEXT:        add.d $a4, $a4, $tp
# LE64-NEXT: 20164: nop
# LE64-NEXT:        ori $a5, $zero, 12
# LE64-NEXT:        add.d $a5, $a5, $tp

#--- 32.s
la.tls.ie $a4, a
add.w $a4, $a4, $tp
la.tls.ie $a5, b
add.w $a5, $a5, $tp

.section .tbss,"awT",@nobits
.globl a
.zero 8
a:
.zero 4
b:

#--- 64.s
la.tls.ie $a4, a
add.d $a4, $a4, $tp
la.tls.ie $a5, b
add.d $a5, $a5, $tp

.section .tbss,"awT",@nobits
.globl a
.zero 8
a:
.zero 4
b:
