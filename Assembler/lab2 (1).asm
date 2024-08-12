;; 9. Задан байт. Представить его в обратном коде

.model small
.data
.386
.stack 100h
a db 10111101b
b db ?
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
xor ax, ax
mov al, a
 
shl al, 1 ; Логический сдвиг влево, старший разряд попадает в регистр флагов
jc minus ; если CF = 1 переход на minus
rcr al, 1 ; циклический сдвиг вправо через перенос
mov b, al ; кладем положительное число в ОК
jmp exit
    
minus:
    not al ;не меняет флаги процессора
    rcr al, 1
    mov b, al
exit:
    mov ax,4c00h
    int 21h
end