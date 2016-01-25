.ent getMessage
.text
.global getMessage

getMessage:
la $t0,raStore
sw $ra,0($t0)
/*push variables onto stack*/
addi $sp,$sp,-40
sw $a0,0($sp)
sw $a1,4($sp)
sw $s0,8($sp)
sw $s1,12($sp)
sw $s2,16($sp)
sw $s3,20($sp)
sw $s4,24($sp)
addi $s5,$s5,235
sw $s5,28($sp)
sw $s6,32($sp)
sw $s7,36($sp)


/*print strings */
andi $s5,$s5,0
la $a0, myStr
jal puts
/*la $a0, myStr2
li $a1, 5
jal printf*/
nop

/*restore $a1 and $a0 and $ra*/
lw $a0,0($sp)
lw $a1,4($sp)
lw $s0,8($sp)
lw $s1,12($sp)
lw $s2,16($sp)
lw $s3,20($sp)
lw $s4,24($sp)
lw $s5,28($sp)
lw $s6,32($sp)
lw $s7,36($sp)
addi $sp,$sp,40
la $t0,raStore
lw $ra,0($t0)
.end getMessage
.data
myStr: .asciiz "Hello, world!\n"
myStr2: .asciiz "Hello, world! %d"
raStore: .word 0