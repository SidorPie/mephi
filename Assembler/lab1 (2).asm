.model small
.data
.386
.stack 100h
a db 115
b db 121
c db 114
d db 122
e db -103
n2 db 2
n4 db 4
.code
begin:
xor eax,eax
xor ebx,ebx
xor ecx,ecx
xor edx,edx
xor esi,esi
xor edi,edi
mov ax,@data
mov ds,ax
mov al,b 	
cbw 		
mov bx,ax
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
cdq
add edi,eax
adc esi,edx
mov al,d
cbw
mov bx,ax
imul bx
rol eax,16
mov ax,dx
ror eax,16
mov ebx,eax
mov al,c
imul n2
cwde
sub eax,ebx
mov ebx,eax
mov edx,esi
mov eax,edi
imul ebx
mov esi,edx
mov edi,eax
mov al,n2 
cbw
cwde
mov ecx,eax
mov edx,esi
mov eax,edi
imul ecx
mov esi,edx
mov edi,eax
mov al,e
imul n4
cwde
mov ecx,eax
mov eax,edi
mov edx,esi
idiv ecx
mov ax,4c00h
int 21h
end