.model small
.data
.386
.stack 100h
a db 3
b db 4
c db 5
.code
begin:
mov ax,@data
mov ds,ax
mov al,c
cbw
cwde
mov ecx,eax
mov al,b
cbw
mov bx,ax
imul b
imul bx
rol eax,16
mov ax,dx
ror eax,16
cdq
mov esi,edx
mov edi,eax
mov al,a
cbw
cwde
mov ebx,eax
imul eax
imul eax
imul ebx
sub eax,edi
sbb edx,esi
idiv ecx
mov ax,4c00h
int 21h
end