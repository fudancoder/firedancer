#ifndef HEADER_fd_src_util_sandbox_run2_seccomp.h_h
#define HEADER_fd_src_util_sandbox_run2_seccomp.h_h

#include <linux/filter.h>

/* THIS FILE WAS GENERATED BY generate_filters.py. */
/* DO NOT EDIT BY HAND!                            */

static const unsigned int sock_filter_policy_run2_instr_cnt = 15;

static void populate_sock_filter_policy_run2(struct sock_filter (*out) [static 15]) {
  *out = {
    /* Check: Jump to RET_KILL_PROCESS if the script's arch != the runtime arch */
    BPF_STMT( BPF_LD | BPF_W | BPF_ABS, ( offsetof( struct seccomp_data, arch ) ) ),
    BPF_JUMP( BPF_JMP | BPF_JEQ | BPF_K, ARCH_NR, 0, /* RET_KILL_PROCESS */ 11 ),
    /* loading syscall number in accumulator */
    BPF_STMT( BPF_LD | BPF_W | BPF_ABS, ( offsetof( struct seccomp_data, nr ) ) ),
    /* simply allow write (eq (arg 0) 2) */
    BPF_JUMP( BPF_JMP | BPF_JEQ | BPF_K, __NR_write (eq (arg 0) 2), /* RET_ALLOW */ 10, 0 ),
    /* allow wait4 based on expression */
    BPF_JUMP( BPF_JMP | BPF_JEQ | BPF_K, __NR_wait4, /* check_wait4 */ 2, 0 ),
    /* simply allow exit_group */
    BPF_JUMP( BPF_JMP | BPF_JEQ | BPF_K, __NR_exit_group, /* RET_ALLOW */ 8, 0 ),
    /* none of the syscalls matched */
    { BFP_JMP | BPF_JA, 0, 0, /* RET_KILL_PROCESS */ 6 },
//  check_wait4:
    /* load syscall argument 0 in accumulator */
    BPF_STMT( BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, args[0])),
    BPF_JUMP( BPF_JMP | BPF_JEQ | BPF_K, -1, /* lbl_1 */ 0, /* RET_KILL_PROCESS */ 4 ),
//  lbl_1:
    /* load syscall argument 2 in accumulator */
    BPF_STMT( BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, args[2])),
    BPF_JUMP( BPF_JMP | BPF_JEQ | BPF_K, __WCLONE, /* lbl_2 */ 0, /* RET_KILL_PROCESS */ 2 ),
//  lbl_2:
    /* load syscall argument 3 in accumulator */
    BPF_STMT( BPF_LD | BPF_W | BPF_ABS, offsetof(struct seccomp_data, args[3])),
    BPF_JUMP( BPF_JMP | BPF_JEQ | BPF_K, 0, /* RET_ALLOW */ 1, /* RET_KILL_PROCESS */ 0 ),
//  RET_KILL_PROCESS:
    /* KILL_PROCESS is placed before ALLOW since it's the fallthrough case. */
    BPF_STMT( BPF_RET | BPF_K, SECCOMP_RET_KILL_PROCESS ),
//  RET_ALLOW:
    /* ALLOW has to be reached by jumping */
    BPF_STMT( BPF_RET | BPF_K, SECCOMP_RET_ALLOW ),
  };
}

#endif
