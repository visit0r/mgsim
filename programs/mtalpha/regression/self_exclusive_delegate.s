/*
 This test test exclusive delegation to the same core the delegation comes from.
 This should work properly because the delegated create should not register as an
 exclusive create on the source side.
 */
    .file "self_exclusive_delegate.s"
    
    .globl main
    .ent main
main:
    allocate (0 << 4) | (1 << 3) | (3 << 1) | 1, $2     # PID:0, Delegate, Suspend, Exclusive
    cred     $2, foo
    
    # Sync
    sync    $2, $0
    release $2
    mov     $0, $31
    end
    .end main

    .ent foo
    .registers 0 0 1 0 0 0
foo:
    print $l0, 0
    end
    .end foo

    .ascii "PLACES: 1\0"
