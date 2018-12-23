.data
str0: .asciiz "<"
str1: .asciiz "<="
str2: .asciiz "=="
str3: .asciiz ">="
str4: .asciiz "not > 0"
str5: .asciiz " !#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}"
str6: .asciiz "%c"
str7: .asciiz "n cannot be smaller or equal than 0!"
str8: .asciiz "\\n\\\\n\\\\\\n"
break: .asciiz "\n"
.text
add $fp, $sp, $zero
addi $gp, $gp, 65536
j main
nop
funcReturnInt:
addi $sp, $sp, 8
sw $t0, -16($sp)
sw $t1, -20($sp)
sw $t2, -24($sp)
sw $t3, -28($sp)
sw $t4, -32($sp)
sw $t5, -36($sp)
sw $t6, -40($sp)
sw $s0, -44($sp)
sw $s1, -48($sp)
sw $s2, -52($sp)
sw $s3, -56($sp)
sw $s4, -60($sp)
sw $s5, -64($sp)
sw $s6, -68($sp)
sw $fp, -72($sp)
sw $ra, -76($sp)
add $fp, $sp, $zero
addi $sp, $sp, -80
lw $t8, 0($fp)
sub $t7, $zero, $t8
sw $t7, -12($fp)
lw $t9, -12($fp)
lw $t8, -4($fp)
add $t7, $t9, $t8
sw $t7, -12($fp)
lw $t9, -12($fp)
addi $t7, $t9, 2
sw $t7, -8($fp)
lw $t9, -8($fp)
addi $v0, $t9, 0
j funcReturnInt$end
nop
funcReturnInt$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 80
jr $ra
nop
funcReturnChar:
addi $sp, $sp, 4
sw $t0, -8($sp)
sw $t1, -12($sp)
sw $t2, -16($sp)
sw $t3, -20($sp)
sw $t4, -24($sp)
sw $t5, -28($sp)
sw $t6, -32($sp)
sw $s0, -36($sp)
sw $s1, -40($sp)
sw $s2, -44($sp)
sw $s3, -48($sp)
sw $s4, -52($sp)
sw $s5, -56($sp)
sw $s6, -60($sp)
sw $fp, -64($sp)
sw $ra, -68($sp)
add $fp, $sp, $zero
addi $sp, $sp, -72
lw $t9, 0($fp)
addi $t7, $t9, 0
sw $t7, -4($fp)
lw $t9, -4($fp)
addi $v0, $t9, 0
j funcReturnChar$end
nop
funcReturnChar$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 72
jr $ra
nop
funcRelation:
addi $sp, $sp, 4
sw $t0, -4($sp)
sw $t1, -8($sp)
sw $t2, -12($sp)
sw $t3, -16($sp)
sw $t4, -20($sp)
sw $t5, -24($sp)
sw $t6, -28($sp)
sw $s0, -32($sp)
sw $s1, -36($sp)
sw $s2, -40($sp)
sw $s3, -44($sp)
sw $s4, -48($sp)
sw $s5, -52($sp)
sw $s6, -56($sp)
sw $fp, -60($sp)
sw $ra, -64($sp)
add $fp, $sp, $zero
addi $sp, $sp, -68
lw $t9, 0($fp)
subi $t7, $t9, 0
blez $t7, $label0
nop
lw $t9, 0($fp)
subi $t7, $t9, 7
bgez $t7, $label2
nop
li $v0, 4
la $a0, str0
syscall
li $v0, 4
la $a0, break
syscall
j funcRelation$end
nop
j $label3
nop
$label2:
$label3:
lw $t9, 0($fp)
subi $t7, $t9, 7
bgtz $t7, $label4
nop
li $v0, 4
la $a0, str1
syscall
li $v0, 4
la $a0, break
syscall
j funcRelation$end
nop
j $label5
nop
$label4:
$label5:
lw $t9, 0($fp)
li $t8, 17
bne $t9, $t8, $label6
nop
li $v0, 4
la $a0, str2
syscall
li $v0, 4
la $a0, break
syscall
j funcRelation$end
nop
j $label7
nop
$label6:
$label7:
lw $t9, 0($fp)
subi $t7, $t9, 77
bltz $t7, $label8
nop
li $v0, 4
la $a0, str3
syscall
li $v0, 4
la $a0, break
syscall
j funcRelation$end
nop
j $label9
nop
$label8:
$label9:
j $label1
nop
$label0:
li $v0, 4
la $a0, str4
syscall
li $v0, 4
la $a0, break
syscall
$label1:
funcRelation$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 68
jr $ra
nop
funcPrint:
sw $t0, 0($sp)
sw $t1, -4($sp)
sw $t2, -8($sp)
sw $t3, -12($sp)
sw $t4, -16($sp)
sw $t5, -20($sp)
sw $t6, -24($sp)
sw $s0, -28($sp)
sw $s1, -32($sp)
sw $s2, -36($sp)
sw $s3, -40($sp)
sw $s4, -44($sp)
sw $s5, -48($sp)
sw $s6, -52($sp)
sw $fp, -56($sp)
sw $ra, -60($sp)
add $fp, $sp, $zero
addi $sp, $sp, -64
li $v0, 4
la $a0, str5
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 1
li $t7, -10
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 4
la $a0, str6
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 11
li $t7, 97
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
funcPrint$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 64
jr $ra
nop
funcDoWhileAndFor:
sw $t0, -24($sp)
sw $t1, -28($sp)
sw $t2, -32($sp)
sw $t3, -36($sp)
sw $t4, -40($sp)
sw $t5, -44($sp)
sw $t6, -48($sp)
sw $s0, -52($sp)
sw $s1, -56($sp)
sw $s2, -60($sp)
sw $s3, -64($sp)
sw $s4, -68($sp)
sw $s5, -72($sp)
sw $s6, -76($sp)
sw $fp, -80($sp)
sw $ra, -84($sp)
add $fp, $sp, $zero
addi $sp, $sp, -88
li $t7, 0
sw $t7, 0($fp)
li $t7, 0
sw $t7, -4($fp)
$label10:
lw $t8, 0($fp)
addi $t7, $t8, 8
sll $t7, $t7, 2
lw $t9, 0($fp)
addu $t7, $t7, $gp
sw $t9, 0($t7)
lw $t9, 0($fp)
addi $t7, $t9, 1
sw $t7, 0($fp)
lw $t9, 0($fp)
subi $t7, $t9, 10
bgez $t7, $label11
nop
j $label10
nop
$label11:
li $t7, 0
sw $t7, 0($fp)
$label12:
lw $t9, 0($fp)
subi $t7, $t9, 10
bgez $t7, $label13
nop
li $t7, 0
sw $t7, -4($fp)
$label14:
lw $t9, -4($fp)
lw $t8, 0($fp)
sub $t7, $t9, $t8
bgez $t7, $label15
nop
lw $t8, 0($fp)
addi $t9, $t8, 8
sll $t9, $t9, 2
addu $t9, $t9, $gp
lw $t7, 0($t9)
sw $t7, -20($fp)
li $v0, 1
lw $t7, -20($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
lw $t9, -4($fp)
addi $t7, $t9, 1
sw $t7, -4($fp)
j $label14
nop
$label15:
lw $t9, 0($fp)
addi $t7, $t9, 1
sw $t7, 0($fp)
j $label12
nop
$label13:
funcDoWhileAndFor$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 88
jr $ra
nop
funcRecursion:
addi $sp, $sp, 4
sw $t0, -20($sp)
sw $t1, -24($sp)
sw $t2, -28($sp)
sw $t3, -32($sp)
sw $t4, -36($sp)
sw $t5, -40($sp)
sw $t6, -44($sp)
sw $s0, -48($sp)
sw $s1, -52($sp)
sw $s2, -56($sp)
sw $s3, -60($sp)
sw $s4, -64($sp)
sw $s5, -68($sp)
sw $s6, -72($sp)
sw $fp, -76($sp)
sw $ra, -80($sp)
add $fp, $sp, $zero
addi $sp, $sp, -84
lw $t9, 0($fp)
subi $t7, $t9, 0
bgtz $t7, $label16
nop
li $v0, 4
la $a0, str7
syscall
li $v0, 4
la $a0, break
syscall
li $v0, -1
j funcRecursion$end
nop
j $label17
nop
$label16:
$label17:
lw $t9, 0($fp)
li $t8, 1
bne $t9, $t8, $label18
nop
li $v0, 1
j funcRecursion$end
nop
j $label19
nop
$label18:
$label19:
lw $t9, 0($fp)
li $t8, 2
bne $t9, $t8, $label20
nop
li $v0, 1
j funcRecursion$end
nop
j $label21
nop
$label20:
$label21:
lw $t9, 0($fp)
subi $t7, $t9, 1
sw $t7, -4($fp)
lw $t7, -4($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcRecursion
nop
addi $t7, $v0, 0
sw $t7, -8($fp)
lw $t9, 0($fp)
subi $t7, $t9, 2
sw $t7, -12($fp)
lw $t7, -12($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcRecursion
nop
addi $t7, $v0, 0
sw $t7, -16($fp)
lw $t9, -8($fp)
lw $t8, -16($fp)
add $v0, $t9, $t8
j funcRecursion$end
nop
funcRecursion$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 84
jr $ra
nop
multiParaFunc:
addi $sp, $sp, 24
sw $t0, -36($sp)
sw $t1, -40($sp)
sw $t2, -44($sp)
sw $t3, -48($sp)
sw $t4, -52($sp)
sw $t5, -56($sp)
sw $t6, -60($sp)
sw $s0, -64($sp)
sw $s1, -68($sp)
sw $s2, -72($sp)
sw $s3, -76($sp)
sw $s4, -80($sp)
sw $s5, -84($sp)
sw $s6, -88($sp)
sw $fp, -92($sp)
sw $ra, -96($sp)
add $fp, $sp, $zero
addi $sp, $sp, -100
lw $t9, 0($fp)
lw $t8, -4($fp)
mul $t7, $t9, $t8
sw $t7, -24($fp)
lw $t9, -8($fp)
lw $t8, -12($fp)
sub $t7, $t9, $t8
sw $t7, -28($fp)
lw $t9, -24($fp)
lw $t8, -28($fp)
add $t7, $t9, $t8
sw $t7, -24($fp)
lw $t9, -24($fp)
lw $t8, -16($fp)
sub $t7, $t9, $t8
sw $t7, -24($fp)
lw $t9, -4($fp)
lw $t8, -20($fp)
div $t9, $t8
mflo $t7
sw $t7, -32($fp)
lw $t9, -24($fp)
lw $t8, -32($fp)
add $v0, $t9, $t8
j multiParaFunc$end
nop
multiParaFunc$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 100
jr $ra
nop
MULTIpARAfUNC:
addi $sp, $sp, 8
sw $t0, -16($sp)
sw $t1, -20($sp)
sw $t2, -24($sp)
sw $t3, -28($sp)
sw $t4, -32($sp)
sw $t5, -36($sp)
sw $t6, -40($sp)
sw $s0, -44($sp)
sw $s1, -48($sp)
sw $s2, -52($sp)
sw $s3, -56($sp)
sw $s4, -60($sp)
sw $s5, -64($sp)
sw $s6, -68($sp)
sw $fp, -72($sp)
sw $ra, -76($sp)
add $fp, $sp, $zero
addi $sp, $sp, -80
lw $t9, 0($fp)
lw $t8, -4($fp)
mul $t7, $t9, $t8
sw $t7, -8($fp)
lw $t9, -8($fp)
subi $t7, $t9, 10
sw $t7, -8($fp)
lw $t9, 0($fp)
lw $t8, -4($fp)
div $t9, $t8
mflo $t7
sw $t7, -12($fp)
lw $t9, -8($fp)
lw $t8, -12($fp)
add $v0, $t9, $t8
j MULTIpARAfUNC$end
nop
MULTIpARAfUNC$end:
lw $ra, 4($sp)
lw $fp, 8($sp)
lw $s6, 12($sp)
lw $s5, 16($sp)
lw $s4, 20($sp)
lw $s3, 24($sp)
lw $s2, 28($sp)
lw $s1, 32($sp)
lw $s0, 36($sp)
lw $t6, 40($sp)
lw $t5, 44($sp)
lw $t4, 48($sp)
lw $t3, 52($sp)
lw $t2, 56($sp)
lw $t1, 60($sp)
lw $t0, 64($sp)
addi $sp, $sp, 80
jr $ra
nop
main:
sw $t0, -44($sp)
sw $t1, -48($sp)
sw $t2, -52($sp)
sw $t3, -56($sp)
sw $t4, -60($sp)
sw $t5, -64($sp)
sw $t6, -68($sp)
sw $s0, -72($sp)
sw $s1, -76($sp)
sw $s2, -80($sp)
sw $s3, -84($sp)
sw $s4, -88($sp)
sw $s5, -92($sp)
sw $s6, -96($sp)
sw $fp, -100($sp)
sw $ra, -104($sp)
add $fp, $sp, $zero
addi $sp, $sp, -108
li $t7, 7
sw $t7, -8($fp)
li $t7, 17
sw $t7, -12($fp)
lw $t7, -8($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
lw $t7, -12($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal MULTIpARAfUNC
nop
addi $t7, $v0, 0
sw $t7, -16($fp)
li $v0, 1
lw $t7, -16($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 5
syscall
add $t7, $v0, $zero
sw $t7, 24($gp)
li $v0, 5
syscall
add $t7, $v0, $zero
sw $t7, 28($gp)
li $v0, 12
syscall
add $t7, $v0, $zero
sw $t7, 72($gp)
li $t7, 7
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 1
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 104
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 106
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 7
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 121
sw $t7, 0($sp)
addi $sp, $sp, -4
jal multiParaFunc
nop
addi $t7, $v0, 0
sw $t7, -20($fp)
li $v0, 4
la $a0, str8
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 1
lw $t7, -20($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
addi $t7, $zero, 19
sll $t7, $t7, 2
li $t9, 122
addu $t7, $t7, $gp
sw $t9, 0($t7)
lw $t9, 24($gp)
lw $t8, 28($gp)
bne $t9, $t8, $label22
nop
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcReturnInt
nop
addi $t7, $v0, 0
sw $t7, 0($fp)
li $v0, 1
lw $t7, 0($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
j $label23
nop
$label22:
$label23:
lw $t9, 24($gp)
lw $t8, 28($gp)
sub $t7, $t9, $t8
blez $t7, $label24
nop
lw $t7, 72($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcReturnChar
nop
addi $t7, $v0, 0
sw $t7, -4($fp)
li $v0, 11
lw $t7, -4($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
li $t7, 100
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcReturnChar
nop
addi $t7, $v0, 0
sw $t7, -32($fp)
lw $t9, -32($fp)
addi $t7, $t9, 1
sw $t7, -32($fp)
li $v0, 1
lw $t7, -32($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
j $label25
nop
$label24:
$label25:
lw $t9, 72($gp)
li $t8, 97
bne $t9, $t8, $label26
nop
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcRelation
nop
j $label27
nop
$label26:
$label27:
lw $t9, 72($gp)
li $t8, 45
bne $t9, $t8, $label28
nop
jal funcPrint
nop
j $label29
nop
$label28:
$label29:
lw $t9, 72($gp)
li $t8, 47
bne $t9, $t8, $label30
nop
jal funcDoWhileAndFor
nop
j $label31
nop
$label30:
$label31:
addi $t9, $zero, 19
sll $t9, $t9, 2
addu $t9, $t9, $gp
lw $t7, 0($t9)
sw $t7, -36($fp)
lw $t9, 72($gp)
lw $t8, -36($fp)
bne $t9, $t8, $label32
nop
lw $t7, 24($gp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal funcRecursion
nop
addi $t7, $v0, 0
sw $t7, -40($fp)
li $v0, 1
lw $t7, -40($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
j $label33
nop
$label32:
$label33:
li $v0, 10
syscall
