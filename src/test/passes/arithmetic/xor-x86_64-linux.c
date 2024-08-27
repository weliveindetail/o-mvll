// REQUIRES: x86-registered-target

// RUN:                                        clang -target x86_64-pc-linux-gnu                         -O1 -S %s -o - | FileCheck --check-prefix=R0 %s
// RUN: env OMVLL_CONFIG=%S/config_rounds_0.py clang -target x86_64-pc-linux-gnu -fpass-plugin=%libOMVLL -O1 -S %s -o - | FileCheck --check-prefix=R0 %s
// RUN: env OMVLL_CONFIG=%S/config_rounds_1.py clang -target x86_64-pc-linux-gnu -fpass-plugin=%libOMVLL -O1 -S %s -o - | FileCheck --check-prefix=R1 %s
// RUN: env OMVLL_CONFIG=%S/config_rounds_2.py clang -target x86_64-pc-linux-gnu -fpass-plugin=%libOMVLL -O1 -S %s -o - | FileCheck --check-prefix=R2 %s
// RUN: env OMVLL_CONFIG=%S/config_rounds_3.py clang -target x86_64-pc-linux-gnu -fpass-plugin=%libOMVLL -O1 -S %s -o - | FileCheck --check-prefix=R3 %s

// R0-LABEL: memcpy_xor:
// R0:       .LBB0_2:
// R0:           movzbl	(%rsi,%rcx), %edx
// R0:           xorb	$35, %dl
// R0:           movb	%dl, (%rdi,%rcx)
// R0:           incq	%rcx
// R0:           cmpq	%rcx, %rax
// R0:           jne	.LBB0_2

// FIXME: It seems like rounds=1 doesn't actually do anything!
// R1-LABEL: memcpy_xor:
// R1:       .LBB0_2:
// R1:           movzbl	(%rsi,%rcx), %edx
// R1:           xorb	$35, %dl
// R1:           movb	%dl, (%rdi,%rcx)
// R1:           incq %rcx
// R1:           cmpq	%rcx, %rax
// R1:           jne	.LBB0_2

// R2-LABEL: memcpy_xor:
// R2-DAG:   .LBB0_2:
// R2-DAG:       movl	%eax, %ecx
// R2-DAG:       movsbl	(%rsi,%rcx), %r8d
// R2-DAG:       movl	%r8d, %r9d
// R2-DAG:       notl	%r9d
// R2-DAG:       orl	$-36, %r9d
// R2-DAG:       addl	%r8d, %r9d
// R2-DAG:       addl	$36, %r9d
// R2-DAG:       andl	$35, %r8d
// R2-DAG:       negl	%r8d
// R2-DAG:       movl	%r9d, %r10d
// R2-DAG:       xorl	%r8d, %r10d
// R2-DAG:       andl	%r9d, %r8d
// R2-DAG:       leal	(%r10,%r8,2), %r8d
// R2-DAG:       movb	%r8b, (%rdi,%rcx)
// R2-DAG:       movl	%eax, %ecx
// R2-DAG:       notl	%ecx
// R2-DAG:       orl	$-2, %ecx
// R2-DAG:       addl	%eax, %ecx
// R2-DAG:       andl	$1, %eax
// R2-DAG:       addl	%ecx, %eax
// R2-DAG:       addl	$2, %eax
// R2-DAG:       cmpl	%edx, %eax
// R2-DAG:       jb	.LBB0_2

// R3-LABEL: memcpy_xor:
// R3-DAG:   .LBB0_2:
// R3-DAG:     movl	%eax, %ecx
// R3-DAG:     movzbl	(%rsi,%rcx), %r8d
// R3-DAG:     leal	35(%r8), %r9d
// R3-DAG:     movl	%r8d, %r10d
// R3-DAG:     notl	%r10d
// R3-DAG:     orl	$-36, %r10d
// R3-DAG:     leal	(%r10,%r8), %r11d
// R3-DAG:     addl	$36, %r11d
// R3-DAG:     addl	%r8d, %r10d
// R3-DAG:     movl	$-36, %r8d
// R3-DAG:     subl	%r10d, %r8d
// R3-DAG:     movl	%r8d, %r10d
// R3-DAG:     xorl	%r9d, %r10d
// R3-DAG:     andl	%r9d, %r8d
// R3-DAG:     leal	(%r10,%r8,2), %r8d
// R3-DAG:     negl	%r8d
// R3-DAG:     movl	%r8d, %r9d
// R3-DAG:     xorl	%r11d, %r9d
// R3-DAG:     andl	%r11d, %r8d
// R3-DAG:     leal	(%r9,%r8,2), %r8d
// R3-DAG:     movb	%r8b, (%rdi,%rcx)
// R3-DAG:     leal	1(%rax), %ecx
// R3-DAG:     movl	%eax, %r8d
// R3-DAG:     notl	%r8d
// R3-DAG:     orl	$-2, %r8d
// R3-DAG:     movl	$-2, %r10d
// R3-DAG:     subl	%eax, %r10d
// R3-DAG:     subl	%r8d, %r10d
// R3-DAG:     movl	%r10d, %r9d
// R3-DAG:     xorl	%ecx, %r9d
// R3-DAG:     andl	%ecx, %r10d
// R3-DAG:     leal	(%r9,%r10,2), %ecx
// R3-DAG:     addl	$2, %eax
// R3-DAG:     andl	%r8d, %eax
// R3-DAG:     leal	-1(%rax), %r8d
// R3-DAG:     andl	%ecx, %r8d
// R3-DAG:     addl	%ecx, %r8d
// R3-DAG:     addl	%eax, %r8d
// R3-DAG:     notl	%ecx
// R3-DAG:     negl	%eax
// R3-DAG:     orl	%ecx, %eax
// R3-DAG:     addl	%r8d, %eax
// R3-DAG:     cmpl	%edx, %eax
// R3-DAG:     jb	.LBB0_2

void memcpy_xor(char *dst, const char *src, unsigned len) {
  for (unsigned i = 0; i < len; i += 1) {
    dst[i] = src[i] ^ 35;
  }
  dst[len] = '\0';
}
