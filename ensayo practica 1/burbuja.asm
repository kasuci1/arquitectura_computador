.data
array: .word 5, 3, 4, 1, 2  # Array to sort
size: .word 5  # Size of the array

.text
.globl main

main:
    la $a0, array  # cargar direccion de array en $a0
    lw $a1, size  # cargar tamaño de array en $a1
    jal bubble_sort  # Call bubble_sort

    # Print the sorted array
    move $a2, $a0  # mover direccion array en $a2
    lw $a1, size  # cargar tamaño de array en $a1
print_loop:
    beq $a1, $zero, exit  # si se imprimen todos los elementos  exit
    lw $a0, 0($a2)  # cargar el siguiente elemento para print en $a0

    li $v0, 1  # codigo de servicio imprime enteros
    syscall  # imprimir elemento

    addiu $a2, $a2, 4  # mover al siguiente elemento
    addiu $a1, $a1, -1  # decrementar el contador
    j print_loop  # salto a print loop

exit:
    jr $ra  # retorno a sistema operativo

bubble_sort:
    addiu $sp, $sp, -4  # hacer espacio para $ra
    sw $ra, 0($sp)  # salvar $ra en el stack

    # Outer loop
outer_loop:
    addiu $a1, $a1, -1  # decrementar el contador
    blez $a1, outer_loop_exit  # si $a1 es 0, exit the outer loop

    # Inner loop
    move $a2, $a0  # mover la direccion del arreglo en $a2
    li $t0, 0  # inicializar el inner loop counter
inner_loop:
    beq $t0, $a1, inner_loop_exit  # si se procesaron todos los elementos, exit the inner loop

    lw $t1, 0($a2)  # cargar el elemento actual
    lw $t2, 4($a2)  # cargar el siguiente elemento
    ble $t1, $t2, no_swap  # si el elemento es menor o igual que el siguienten elemento no swap

    # Swap the elements
    sw $t1, 4($a2)  # guardar el actual elemento en la direccion del siguiente elemento
    sw $t2, 0($a2)  # guardar el siguiente elemento en la direccion actual

no_swap:
    addiu $a2, $a2, 4  # moverse al siguiente elemento
    addiu $t0, $t0, 1  # incrementar el inner loop contador
    j inner_loop  # saltar al inicio de  inner loop

inner_loop_exit:
    j outer_loop  # saltar al inicio de outer loop
    
outer_loop_exit:
    lw $ra, 0($sp)  # cargar $ra desde el stack
    addiu $sp, $sp, 4  # restaurar el  stack puntero
    jr $ra  # retornar al invocador