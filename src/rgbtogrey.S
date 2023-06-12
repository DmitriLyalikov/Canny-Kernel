/*
 * Filename: rgbtogrey.S
 * Description: RISC-V Vector program to convert 8-bit RGB image to 8-bit greyscale
 * Author: Dmitri Lyalikov
 * Date: 6/12/2023
 */

.section .text
.align 2

.global _rgbtogrey

/* a0 = dest, a1 = src, a2 = n (WIDTH x HEIGHT) */
_rgbtogrey:

    /*
     * Main code goes here
     */
    li a4 0x3E99999A  // R Luminescence coefficient of .299
    mv f0 a4
    li a4 0x3F02F983  // G Luminescence coefficient of .587
    mv f1 a4
    li a4 0x3DC28F5C  // B Luminescence coefficient of .114
    mv f2 a4
    mv a3 a0 

loop:
    vsetvli t0, a2, e32    /* set the vector length and t0 to min(a2, maxvl) vectors that are 32 bits wide */
    vlseg3b.v  v1, (a1)    /* load the 8-bit R values to v1 starting at src (a1) and 3 byte stride         */
    vlseg3b.v  v2, (a1)1   /* load the 8-bit G values to v2 starting at src (a1) and 3 byte stride with offset 1 byte */ 
    vlseg3b.v  v3, (a1)2   /* load the 8-but B values to v3 starting at src (a1) and 3 byte stride with offset 2 bytes */

    add a1, a1, t0         /* Bump the address pointer */
    sub a2, a2, t0         /* decrement count          */ 

    vfcvt.s.i.v v1, v1
    vfcvt.s.i.v v2, v2
    vfcvt.s.i.v v3, v3 

    vfmax.s.v  v1, v1, f0   /* Multiply the R value by the Luminescence coefficient (R * .299) */
    vfmax.s.v  v2, v2, f1   /* Multiply the G value by the Luminescence coefficient (G * .587) */
    vfmax.s.v  v3, v3, f2   /* Multiply the B value by the Luminescence coefficient (B * .114) */

    /* (R * .299) + (G * .587) + (B * .114) */
    vf.add.s v1, v1, v2 
    vf.add.s v1, v1, v3      

    vfcvt.u.s v4, v4       /* This is resulting 8-bit greyscale image */

    vsw.v v1, (a3)         /* Store words starting to dest address    */
    add a3, a3, t0

    bnez a2, loop
    ret                  

