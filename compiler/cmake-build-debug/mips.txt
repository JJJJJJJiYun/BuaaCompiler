.data
str0: .asciiz "!@#$%%abcd114514ABCD963287~;: "
str1: .asciiz "1 hit "
str2: .asciiz "2 hit "
str3: .asciiz "3 hit "
str4: .asciiz "4 hit "
str5: .asciiz "5 hit "
str6: .asciiz "6 hit "
break: .asciiz "\n"
.text
add $fp, $sp, $zero
addi $gp, $gp, 65536
j main
nop
fact:
addi $sp, $sp, 4
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
subi $t7, $t9, 3
bgez $t7, $label0
nop
lw $t9, 0($fp)
addi $v0, $t9, 0
j fact$end
nop
j $label1
nop
$label0:
lw $t9, 0($fp)
subi $t7, $t9, 1
sw $t7, -8($fp)
lw $t7, -8($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal fact
nop
addi $t7, $v0, 0
sw $t7, -12($fp)
lw $t9, -12($fp)
lw $t8, 0($fp)
mul $v0, $t9, $t8
j fact$end
nop
$label1:
fact$end:
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
rt15:
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
li $v0, 15
j rt15$end
nop
rt15$end:
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
fun2:
addi $sp, $sp, 24
sw $t0, -32($sp)
sw $t1, -36($sp)
sw $t2, -40($sp)
sw $t3, -44($sp)
sw $t4, -48($sp)
sw $t5, -52($sp)
sw $t6, -56($sp)
sw $s0, -60($sp)
sw $s1, -64($sp)
sw $s2, -68($sp)
sw $s3, -72($sp)
sw $s4, -76($sp)
sw $s5, -80($sp)
sw $s6, -84($sp)
sw $fp, -88($sp)
sw $ra, -92($sp)
add $fp, $sp, $zero
addi $sp, $sp, -96
lw $t9, -4($fp)
lw $t8, -8($fp)
mul $t7, $t9, $t8
sw $t7, -24($fp)
lw $t9, -24($fp)
lw $t8, -12($fp)
mul $t7, $t9, $t8
sw $t7, -24($fp)
lw $t9, -24($fp)
lw $t8, -16($fp)
div $t9, $t8
mflo $t7
sw $t7, -24($fp)
lw $t9, 0($fp)
lw $t8, -24($fp)
add $t7, $t9, $t8
sw $t7, -28($fp)
lw $t9, -28($fp)
lw $t8, -20($fp)
sub $t7, $t9, $t8
sw $t7, -28($fp)
li $v0, 1
lw $t7, -28($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 65
j fun2$end
nop
fun2$end:
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
addi $sp, $sp, 96
jr $ra
nop
main:
sw $t0, -124($sp)
sw $t1, -128($sp)
sw $t2, -132($sp)
sw $t3, -136($sp)
sw $t4, -140($sp)
sw $t5, -144($sp)
sw $t6, -148($sp)
sw $s0, -152($sp)
sw $s1, -156($sp)
sw $s2, -160($sp)
sw $s3, -164($sp)
sw $s4, -168($sp)
sw $s5, -172($sp)
sw $s6, -176($sp)
sw $fp, -180($sp)
sw $ra, -184($sp)
add $fp, $sp, $zero
addi $sp, $sp, -188
li $t7, -1
sw $t7, 24($gp)
li $t7, -4
sw $t7, -24($fp)
li $t7, 6
sw $t7, -60($fp)
lw $t7, -60($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
jal fact
nop
addi $t7, $v0, 0
sw $t7, -68($fp)
li $v0, 4
la $a0, str0
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 1
lw $t7, -68($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
lw $t9, 24($gp)
lw $t8, -24($fp)
sub $t7, $t9, $t8
sw $t7, -72($fp)
lw $t7, -72($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
lw $t7, -60($fp)
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 1
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 4
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, 2
sw $t7, 0($sp)
addi $sp, $sp, -4
li $t7, -2
sw $t7, 0($sp)
addi $sp, $sp, -4
jal fun2
nop
addi $t7, $v0, 0
sw $t7, -76($fp)
addi $t7, $zero, 4
sll $t7, $t7, 2
lw $t9, -76($fp)
sub $t7, $fp, $t7
sw $t9, 0($t7)
li $t7, 4
sw $t7, 0($sp)
addi $sp, $sp, -4
jal fact
nop
div $zero, $v0
mflo $t7
sw $t7, -80($fp)
lw $t8, -80($fp)
addi $t9, $t8, 4
sll $t9, $t9, 2
sub $t9, $fp, $t9
lw $t7, 0($t9)
sw $t7, -84($fp)
li $v0, 11
lw $t7, -84($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
li $t8, 1
addi $t7, $t8, 4
sll $t7, $t7, 2
li $t9, 43
sub $t7, $fp, $t7
sw $t9, 0($t7)
li $t8, 1
addi $t9, $t8, 4
sll $t9, $t9, 2
sub $t9, $fp, $t9
lw $t7, 0($t9)
sw $t7, -88($fp)
lw $t9, -88($fp)
addi $t7, $t9, 20
sw $t7, -88($fp)
li $t9, 1
lw $t8, -88($fp)
mul $t7, $t9, $t8
sw $t7, -88($fp)
lw $t8, -88($fp)
sub $t7, $zero, $t8
sw $t7, -88($fp)
lw $t9, -88($fp)
addi $t7, $t9, -34
sw $t7, -88($fp)
lw $t9, -88($fp)
addi $t7, $t9, 218
sw $t7, -60($fp)
li $v0, 1
lw $t7, -60($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
lw $t9, -60($fp)
addi $t7, $t9, 0
sw $t7, -64($fp)
li $v0, 5
syscall
add $t7, $v0, $zero
sw $t7, -64($fp)
li $v0, 5
syscall
add $t7, $v0, $zero
sw $t7, 24($gp)
lw $t9, -64($fp)
subi $t7, $t9, 0
blez $t7, $label2
nop
li $v0, 4
la $a0, str1
syscall
li $v0, 4
la $a0, break
syscall
lw $t9, 24($gp)
subi $t7, $t9, 0
bgtz $t7, $label4
nop
lw $t9, -64($fp)
lw $t8, 24($gp)
div $t9, $t8
mflo $t7
sw $t7, -92($fp)
lw $t9, -92($fp)
lw $t8, -64($fp)
mul $t7, $t9, $t8
sw $t7, -24($fp)
li $v0, 4
la $a0, str2
syscall
li $v0, 4
la $a0, break
syscall
j $label5
nop
$label4:
$label5:
lw $t9, -24($fp)
lw $t8, -60($fp)
add $t7, $t9, $t8
sw $t7, -24($fp)
j $label3
nop
$label2:
$label3:
lw $t9, 24($gp)
beq $t9, $zero, $label6
nop
li $v0, 4
la $a0, str3
syscall
li $v0, 4
la $a0, break
syscall
lw $t9, -64($fp)
li $t8, -4
bne $t9, $t8, $label8
nop
lw $t9, -24($fp)
addi $t7, $t9, 1
sw $t7, -24($fp)
li $v0, 4
la $a0, str4
syscall
li $v0, 4
la $a0, break
syscall
j $label9
nop
$label8:
$label9:
j $label7
nop
$label6:
$label7:
lw $t9, -64($fp)
subi $t7, $t9, 0
bgez $t7, $label10
nop
li $v0, 4
la $a0, str5
syscall
li $v0, 4
la $a0, break
syscall
lw $t9, 24($gp)
subi $t7, $t9, 0
bltz $t7, $label12
nop
lw $t9, -24($fp)
lw $t8, -64($fp)
add $t7, $t9, $t8
sw $t7, -24($fp)
li $v0, 4
la $a0, str6
syscall
li $v0, 4
la $a0, break
syscall
j $label13
nop
$label12:
$label13:
j $label11
nop
$label10:
lw $t9, -24($fp)
li $t8, -1
mul $t7, $t9, $t8
sw $t7, -24($fp)
li $v0, 1
lw $t7, -24($fp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
$label11:
li $t7, -2
sw $t7, -64($fp)
$label14:
lw $t9, -64($fp)
subi $t7, $t9, 3
bgez $t7, $label15
nop
lw $t9, 24($gp)
addi $t7, $t9, 4
sw $t7, 24($gp)
lw $t9, -64($fp)
addi $t7, $t9, 1
sw $t7, -64($fp)
j $label14
nop
$label15:
$label16:
lw $t9, 24($gp)
subi $t7, $t9, 2
sw $t7, 24($gp)
lw $t9, 24($gp)
subi $t7, $t9, 0
blez $t7, $label17
nop
j $label16
nop
$label17:
li $v0, 1
lw $t7, 24($gp)
add $a0, $t7, $zero
syscall
li $v0, 4
la $a0, break
syscall
li $v0, 10
syscall
