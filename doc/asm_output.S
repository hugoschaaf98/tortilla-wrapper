delayUsDummy(unsigned long):
        sub     sp, sp, #8
        mov     r3, #0
        str     r3, [sp, #4]
        ldr     r3, [sp, #4]
        add     r3, r3, r0
        str     r3, [sp, #4]
        add     sp, sp, #8
        bx      lr
delayMsDummy(unsigned long):
        sub     sp, sp, #8
        mov     r3, #100
        str     r3, [sp, #4]
        ldr     r3, [sp, #4]
        add     r3, r3, r0
        str     r3, [sp, #4]
        add     sp, sp, #8
        bx      lr
spiCsDummy(bool):
        push    {r4, lr}
        bl      dummyCall()
        pop     {r4, lr}
        bx      lr
spiTransfertDummy(unsigned char const*, unsigned int, unsigned char*, unsigned int):
        push    {r4, lr}
        bl      dummyCall()
        mov     r0, #0
        pop     {r4, lr}
        bx      lr
main:
        push    {r4, lr}
        sub     sp, sp, #64
        mov     r4, #1
        bl      dummyCall()
        mov     r0, #54
        bl      delayMsDummy(unsigned long)
        bl      dummyCall()
        mov     r0, r4
        bl      delayUsDummy(unsigned long)
        mov     r0, #0
        bl      spiCsDummy(bool)
        strb    r4, [sp, #48]
        mov     r3, #54
        strb    r3, [sp, #49]
        mov     r0, #0
        bl      spiCsDummy(bool)
        mov     r3, #10
        add     r2, sp, #36
        mov     r1, r3
        add     r0, sp, #48
        bl      spiTransfertDummy(unsigned char const*, unsigned int, unsigned char*, unsigned int)
        mov     r0, r4
        bl      spiCsDummy(bool)
        mov     r0, #0
        bl      spiCsDummy(bool)
        mov     r3, #10
        add     r2, sp, #36
        mov     r1, #15
        add     r0, sp, #20
        bl      spiTransfertDummy(unsigned char const*, unsigned int, unsigned char*, unsigned int)
        mov     r0, r4
        bl      spiCsDummy(bool)
        ldr     r3, .L19
        ldrh    r3, [r3]
        strh    r3, [sp, #60]   @ movhi
        mov     r0, #0
        bl      spiCsDummy(bool)
        mov     r3, #15
        add     r2, sp, #4
        mov     r1, #2
        add     r0, sp, #60
        bl      spiTransfertDummy(unsigned char const*, unsigned int, unsigned char*, unsigned int)
        mov     r0, r4
        bl      spiCsDummy(bool)
        mov     r0, #0
        bl      spiCsDummy(bool)
        mov     r3, #0
        mov     r2, r3
        mov     r1, #15
        add     r0, sp, #20
        bl      spiTransfertDummy(unsigned char const*, unsigned int, unsigned char*, unsigned int)
        mov     r0, r4
        bl      spiCsDummy(bool)
        mov     r0, r4
        bl      spiCsDummy(bool)
        mov     r0, #0
        add     sp, sp, #64
        pop     {r4, lr}
        bx      lr
.L19:
        .word   .LANCHOR0