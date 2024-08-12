; 9 вар
; Дана матрица M*N. 
; Выделить в ней наиболее подходящую квадратную матрицу 
;и вычислить сумму элементов ее главной диагонали

.model small
.data
.386
.stack 100h

;размер матрицы
rows    equ 4
columns equ 3
    
a   db  1,2,3,4
    db  5,6,7,8
    db  9,10,11,12

b   db  1,2,3
    db  4,5,6
    db  7,8,9
    db 10,11,12
 
sum dw  ?

.code
begin:
xor eax,eax
xor ebx,ebx
xor ecx,ecx
xor edx,edx
xor esi,esi
xor edi,edi

mov ax, @data
mov ds, ax
;В bx номер строки, в di номер столбца.
;Вся нумерация начинается с нуля
xor bx, bx
xor di, di
xor ax, ax      ; Накопитель результата
mov cx, rows    ;внешний цикл перебираеть строки
 
;начало расчета
c_external:
    push    cx      ;запоминаем текущее значение параметра внешнего цикла в стеке
    mov cx, columns ;внутренний цикл
    xor si, si      ;обнуляем номер столбца

    c_internal: 
        cmp di, si  ; если индекс строки = индекс столбца,
        je summ     ; то прибавляем к сумме
        jne next    ; иначе просматриваем дальше
    summ:
        add al, byte ptr b[bx][si] ; базовая индексная адресация со смещением 
        adc ah, 0        
    next:
        inc si      ;переход к следующему столбцу
        loop c_internal
    pop cx
    add bx,columns    ;переходим к следующей строке
    inc di
loop c_external

mov sum, ax

mov ax,4c00h
int 21h

end        
end