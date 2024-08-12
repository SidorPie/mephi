.model small
.data
file_r dw 0
file_w dw 0
filename_for_read db 'a.txt',0
filename_for_write db 'b.txt',0
result db 130 dup(0)
buffer db 4096 dup(?)
buffer_for_write db 1024 dup(?)
string1 db 'Choose mode 1-from file 0-from console',13,10,'$'
string2 db 13,10,'Enter sequence for the end',13,10,'$'
.stack 256
.code
start:
      mov ax,@data
      mov ds,ax
      mov es,ax ;�����������
      mov ah,09h ;���������� ��� ������ ������
      mov dx,offset string1
      int 21h ;������� ����������� ������� ����� ������
      mov ah,1h ;���������� ��������� ���� ������
      int 21h ;al- ������, ������������ ����� ������
      cmp al,'1' ; ���� ������ 1
      jne label_1 ;���� �� 1 ������� �� ������ ��������
      call open_file ; ���� 1 �� ��������� �����
      jmp  label_2 ; ������� �� ������ �����
label_1: ;���� al �� �������
      cmp al,'0' ;���� ����� 0, ������ ���� � �������
      jne exit ; ���� al �� 0 �� �����-�� ������, �������
      mov file_r,01 ;���������� ���������� �������
      mov file_w,01 ;��� ������ ������ � ������
      mov dx,offset string2
      mov ah,09h
      int 21h;������� ����������� �� �����
label_2:      
      call read_string ;��������� � �������. �������� ��������� ��� ������� � ��� �����
      ;ax - ���������� ��������� ��������
      mov si,offset buffer ;������ ����� ������ � ������� si, �.�. ���� ������� ���������, ���������� � ���� ���������
      mov  cx,ax ;��������� ���������� ��������� ��������
loop_str: ;���� ������� �� ������� ����� ��������, ���� cx �� ������ ������ 0
      lodsb ; ��������� � al - ������, si:=si+1
      xor dx,dx
      cmp al,'$' ;���� ������� ���������
      je exit ;���� �� �����
      cmp al,13 ;���� ������� ����� ������
      je add_new_line_1
      cmp al,'0' ;��������� � 0
      jb fin ;���� ������ ����, �� ���� ������ ��� �� ��������, ������� �� �����(������� �� ��������� ������)
      cmp al,'9'; ��������� �9
      ja check_letter;���� ������ 9, ��� ����� ���� �����
      jmp add_to_mas;���� ������ 9, �� ��� ������ 0-9, ��������� ��� ��������� � ������
check_letter:;�������� �� ������� �����
      cmp al,'A' ;�� �� ����� ��� � ����, ��������� ������� � ��������� �����, ���� ��� ������ �������� � ������ ��������- ��������� +1 �� ��� ����� � ������� �����������
      jb fin
      cmp al,'Z'
      ja check_letter_2
      jmp add_to_mas
check_letter_2:;�������� �� ����� �����
      cmp al,'a'
      jb fin 
      cmp al,'z'
      ja fin
add_to_mas:
      xor ah,ah; �.�. � al- ����� �������
      mov di,offset result; � di ����� ������. ���� - ������ ���������� ������� �������� � ���������� ��������� �������� ��������� �� �������� ����� �������� � ������� ����
      add di,ax;��������� �������� � ������� � ���� ������ �������.
      mov bl,byte ptr [di]; ����� �������� ���������� ���������� �� �������
      inc bl;���������
      mov byte ptr [di],bl; ������ �������� ������� � ������
fin: ;������ ����� ��������
      dec cx; cx:=������� ������� ��������
      jnz loop_str; ���� �� ����� 0 ������� �� ����� �������� ������� �� �������
      call check_last_str;�������� ��������� �������, � ������� ��� ������� ����� ������
      cmp ax,0 ;��������� ���������� �������� ��������
      je exit
      call print_str
exit:;��������� �����, �������
        call close_files
        mov ax,4c00h
        int 21h
next_line:
      call print_str
      lodsb;10��������� ����������� ������� �������� ������
      mov ax,file_r
      cmp ax,1 ;���� ��� ������ ���������� �������, 1 - ����� ������ ������� �������
      jne l1 ;������� �� �������, ������ ������ � ������
      jmp label_2 ;������� �������, ������� �����
l1:      
      jmp loop_str;������ � ������, ������ �� ��� ������ ������� � ��������� � ��������� ������

add_new_line_1:
        dec cx;��������� ������� ������, ��� �������� ������� ��������� ��������
        call add_new_line
        nop ;��� ������
        nop ;���
        jmp next_line

open_file:
        push dx
        mov ah,3dh
        mov al,0
        mov dx,offset filename_for_read
        int 21h
        ;ax-fd or CF=1
        jc exit
        mov file_r,ax
        ;file for write
        mov ah,3ch
        mov cx,0
        mov dx,offset filename_for_write
        int 21h
        jc exit
        mov file_w,ax
        pop dx
        ret
read_string:
       mov ah,3fh ;���������� ������ �� �����
       mov bx,file_r ;������ ���������� �����
       mov dx,offset buffer ;������ ����� ������ ���� ������
       mov cx,4096 ;��������� �� 4096 ��������. ���� ����� ������ �������� - ������� ������. � �� ����� �������� ���������� ��������. ������ - ����������� ����� ��������
       int 21h ;ax:=���������� ��������
       ret
exit_2:
        jmp exit

add_new_line:
        push cx ;������� ��������� ��������
        push si ;����� ������, ������� ����� ���������
        mov dx,0 ;������� ���������� ��������� � ������ a=0=>dx=3
        mov cx,0 ;������������ ������, � ���� ������ � �������
        mov si,offset result ;������
add_line_loop:        
        lodsb;������� ������ ;al-������� �������, ������� ����� �����, ������� ��� ����������� ������.
        cmp cx,'0' ;�������� ���������� �������� ��� ����
        jb next_step  ; ���� ������ ������ '0', ������� � next_step
        cmp cx,'9'
        ja label_1_str ; ���� ������ ������ '9', ������� � label_1_str
        jmp add_new_symbol ; ���� ������ - �����, ������� � add_new_symbol
label_1_str:        
        cmp cx,'A'
        jb next_step ; ���� ������ ������ 'A', ������� � next_step
        cmp cx,'Z'
        ja label_2_str ; ���� ������ ������ 'Z', ������� � label_2_str
        jmp add_new_symbol ; ���� ������ - ��������� �����, ������� � add_new_symbol
label_2_str:
        cmp cx,'a' 
        jb next_step ; ���� ������ ������ 'a', ������� � next_step
        cmp cx,'z'
        ja next_step ; ���� ������ ������ 'z', ������� � next_step
add_new_symbol:;al -����������, ������� ��� ���������� ������ dx-�������� ������������ ������ ������ cx- �������('a')
        mov di,offset buffer_for_write;�������, � ������� ����� ������, ������� ����� ��������
        add di,dx;��������� ��������, �� ������� ������ ���������
        push ax;��������� �� ��-�� stosb, ����� �� ��������, ����� ���� ���������� ��������� � �������
        mov al,cl;������������ � ���� �������
        stosb;����� ���. �������� � di
        inc dx;����� ������, ������� ���������
        mov al,'=';����� �����
        stosb;����� ������ �����
        inc dx;������� ��������
        pop ax;������� ��, ������ � al ��������� ���������� ��������
        ;byte to str ������� ����� � ������
        ;�������������� ����� �� �� � ���������� ������ � ����� �� �����
        ;ax - �����
        push bx
        push cx
        push dx
        xor cx,cx ;� �� ����� ���������� ���� � ���������� �����
        mov bx,10 ;��������� �������
        xor ah,ah
to_str_loop:
        xor dx,dx ;�������� ������� ����� ��������
        div bx;ax =dx:ax%bl
        add dl,'0' ;��������������� ����� � ASCII ������
        push dx;��������� ������� �� �������(������������ ��� ��������) � ����
        jmp goto
exit_3:        
        jmp exit_2
goto:
        inc cx ;����������� ���������� ���������� ���� �����
        test ax,ax ;����� ������� ������� 0?
        jnz to_str_loop ;���� ���, ����������
        mov ax,cx
to_str_loop_2:
        pop dx ;����� �� ����� ����� �����
        mov [di],dl ; ���������� � �����
        inc di
        loop to_str_loop_2; ������
        pop dx;���������� ��� �����
        pop cx
        pop bx
        ;end byte to str
        add dx,ax;��������� ������� ��������� ���������� � ������
        mov al,' '
        stosb
        inc dx;��������� ����������
        ;����� ����� ���������� ������ �������� � ������
next_step:;���� �� ��������, ���� ������ ��� �� ���������� � ��� �� ����� ������� � ������       
        inc cx ;��������� � ���������� �������� �������
        cmp cx,130 ;���������� �� ��� ��-�� ����� 130 �������� ��������� �������
        jne add_line_loop;���� �� ����� 130 ������� �� ����� ��������
        
        mov al,13
        stosb
        mov al,10
        stosb ;���������� � ������ ������� ������
        add dx,2;������ ������� ��������
        mov cx,130;��� ��������� �������
        mov di,offset result;
        mov al,0;
null_for_mas:
        stosb
        loop null_for_mas;�������� ������
        mov ax,dx;���������� � �� ���������� ���������, ������� ����� ����� ����������
        pop si;
        pop cx;���������� �������� � �������� ���������
        ret;������������ �� ������ 93
print_str:
        push cx
        mov cx,ax ;Cx - ���������� ���������, ������� � ������ ����
        mov ah,40h
        mov bx,file_w;���� �� ������
        mov dx,offset buffer_for_write;����� ������� ���� ��������
        int 21h ; ������ ����������� � ���� ��� ����� � �������
        jc exit_3 ; ���� ������ ������, ������� � exit_3
        cmp ax,cx
        jne exit_3 ; ���� �������� ������ ��������, ��� ���������, ������� � exit_3
        pop cx
        ret
close_files:
        mov bx,file_r
        cmp bx,1
        je end_close_files ; ���� ���� ��� ������ �� ������, ������� � end_close_files
        mov ah,3eh
        int 21h ; �������� ����� ��� ������
        mov bx,file_w
        cmp bx,1
        je  end_close_files; ���� ���� ��� ������ �� ������, ������� � end_close_files
        mov ah,3eh
        int 21h ; �������� ����� ��� ������
end_close_files:
        ret

check_last_str:
        mov si,offset result
        mov cx,130
check_loop: 
        lodsb
        cmp al,0
        jne end_check_last_str ; ���� ������ ��������� ������, ������� � end_check_last_str
        loop check_loop ; �������� ���������� �������
        mov ax,0
        ret ; ���� ��� ������� �������, ������� 0
end_check_last_str:
        call add_new_line  ; ���������� ����� ������
        ret

end start
