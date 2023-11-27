.text
.globl main

main:
    li $a0, 3         # Define el valor de n
    li $a1, 0         # Inicializa el acumulador a 0
    jal sum           # Llama a la función sum
    move $a0, $v0     # Mueve el resultado a $a0 para imprimirlo

    li $v0, 1         # Código de servicio del sistema para imprimir un entero
    syscall           # Imprime el resultado
    bne $a0,1,exit
    jr $ra            # Retorna al sistema operativo

sum:
    slti $t0, $a0, 1  # Comprueba si n <= 0
    bne $t0, $zero, sum_exit  # Salta a sum_exit si n <= 0

    add $a1, $a1, $a0  # Suma n a acc
    addi $a0, $a0, -1  # Decrementa n
    j sum              # Salta a sum

sum_exit:
    add $v0, $a1, $zero  # Devuelve el valor acc
    jr $ra              # Retorno de rutina
 exit:
   