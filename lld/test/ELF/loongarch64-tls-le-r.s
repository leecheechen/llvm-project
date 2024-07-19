# REQUIRES: loongarch

# RUN: llvm-mc --filetype=obj --triple=loongarch64 %s -o %t.64.o
# RUN: ld.lld %t.64.o %p/Inputs/loongarch64-tls-le-r.o -o %t.64
# RUN: llvm-objdump -d --no-show-raw-insn %t.64 | FileCheck --check-prefixes=LE64 %s

# LE64: lu12i.w $a0, 0
# LE64-NEXT: add.d   $a0, $a0, $tp
# LE64-NEXT: addi.d  $a0, $a0, 8

