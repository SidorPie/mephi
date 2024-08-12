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
      mov es,ax ;стандартные
      mov ah,09h ;прерывание для вывода строки
      mov dx,offset string1
      int 21h ;выводим приглашение выбрать режим работы
      mov ah,1h ;прерывание считывает один символ
      int 21h ;al- символ, обозначающий режим работы
      cmp al,'1' ; если символ 1
      jne label_1 ;если не 1 прыгаем на вторую проверку
      call open_file ; если 1 то открываем файлы
      jmp  label_2 ; прыгаем на вторую метку
label_1: ;Если al не единица
      cmp al,'0' ;Если ввели 0, значит ввод с консоли
      jne exit ; если al не 0 то какая-то ошибка, выходим
      mov file_r,01 ;запоминаем дескриптор консоли
      mov file_w,01 ;для файлов чтения и записи
      mov dx,offset string2
      mov ah,09h
      int 21h;выводим приглашение ко вводу
label_2:      
      call read_string ;переходим в функцию. Работает одинаково для консоли и для файла
      ;ax - количество считанных символов
      mov si,offset buffer ;кладем адрес буфера в регистр si, т.к. есть команды обработки, работающие с этим регистром
      mov  cx,ax ;сохраняем количество считанных символов
loop_str: ;цикл прохода по строчке будет работать, пока cx не станет равным 0
      lodsb ; считываем в al - символ, si:=si+1
      xor dx,dx
      cmp al,'$' ;если признак окончания
      je exit ;идем на выход
      cmp al,13 ;если признак новой строки
      je add_new_line_1
      cmp al,'0' ;сравнение с 0
      jb fin ;если меньше нуля, то этот символ нам не подходит, прыгаем на финал(переход на следующий символ)
      cmp al,'9'; сравнение с9
      ja check_letter;если больше 9, это может быть буква
      jmp add_to_mas;если меньше 9, то это символ 0-9, добавляем его появление в массив
check_letter:;проверка на большие буквы
      cmp al,'A' ;то же самое что и выше, проверяет большие и маленькие буквы, если наш символ попадает в нужный диапазон- добавялем +1 на его место в массиве результатов
      jb fin
      cmp al,'Z'
      ja check_letter_2
      jmp add_to_mas
check_letter_2:;проверка на малые буквы
      cmp al,'a'
      jb fin 
      cmp al,'z'
      ja fin
add_to_mas:
      xor ah,ah; т.о. в al- номер символа
      mov di,offset result; В di лежит массив. Суть - массив аналогичен таблице символов и количество повторных символов находится по индексам самих символов в таблице аски
      add di,ax;добавляем смещение к массиву в виде номера символа.
      mov bl,byte ptr [di]; берем значение количества повторений из массива
      inc bl;инкремент
      mov byte ptr [di],bl; кладем значение обратно в массив
fin: ;начало новой итерации
      dec cx; cx:=счетчик сколько символов
      jnz loop_str; Если не равен 0 прыгаем на новую итерацию прохода по строчке
      call check_last_str;проверка последней строчки, у которой нет символа конца строки
      cmp ax,0 ;сравнение колчисетва оставших символов
      je exit
      call print_str
exit:;закрываем файлы, выходим
        call close_files
        mov ax,4c00h
        int 21h
next_line:
      call print_str
      lodsb;10считываем последующую десятку перевода строки
      mov ax,file_r
      cmp ax,1 ;если был выбран дескриптор консоли, 1 - нужно заново считать строчку
      jne l1 ;выбрана не единица, значит работа с файлом
      jmp label_2 ;выбрана единица, прыгаем назад
l1:      
      jmp loop_str;Работа с файлом, значит мы все строки считали и переходим к следующей строке

add_new_line_1:
        dec cx;поскольку считали символ, тут уменьшим счетчик считанных символов
        call add_new_line
        nop ;для дебага
        nop ;для
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
       mov ah,3fh ;прерывание чтение из файла
       mov bx,file_r ;кладем дескриптор файла
       mov dx,offset buffer ;кладем адрес буфера куда читать
       mov cx,4096 ;считываем по 4096 символов. Если будет меньше символов - считает меньше. в ах будет реальное количество символов. Больше - некорректно будет работать
       int 21h ;ax:=количество символов
       ret
exit_2:
        jmp exit

add_new_line:
        push cx ;сколько элементов осталось
        push si ;адрес строки, который нужно запомнить
        mov dx,0 ;счетчик количества элементов в строке a=0=>dx=3
        mov cx,0 ;определенный символ, в виде адреса в массиве
        mov si,offset result ;массив
add_line_loop:        
        lodsb;считали символ ;al-элемент массива, который равен числу, сколько раз встречается символ.
        cmp cx,'0' ;алгоритм фильтрации символов как выше
        jb next_step  ; Если символ меньше '0', переход к next_step
        cmp cx,'9'
        ja label_1_str ; Если символ больше '9', переход к label_1_str
        jmp add_new_symbol ; Если символ - цифра, переход к add_new_symbol
label_1_str:        
        cmp cx,'A'
        jb next_step ; Если символ меньше 'A', переход к next_step
        cmp cx,'Z'
        ja label_2_str ; Если символ больше 'Z', переход к label_2_str
        jmp add_new_symbol ; Если символ - заглавная буква, переход к add_new_symbol
label_2_str:
        cmp cx,'a' 
        jb next_step ; Если символ меньше 'a', переход к next_step
        cmp cx,'z'
        ja next_step ; Если символ больше 'z', переход к next_step
add_new_symbol:;al -количество, сколько раз встречался символ dx-смещение относительно начала строки cx- элемент('a')
        mov di,offset buffer_for_write;строчку, в которую пишем данные, которые будем выводить
        add di,dx;Добавляем смещение, на сколько строка заполнена
        push ax;запоминаю ах из-за stosb, чтобы не потерять, какое было количество элементов в массиве
        mov al,cl;перекладываю в него элемент
        stosb;вывел его. работает с di
        inc dx;Ввели символ, счетчик увеличили
        mov al,'=';кладу равно
        stosb;ввожу символ равно
        inc dx;счетчик символов
        pop ax;забираю ах, теперь в al вернулось количество символов
        ;byte to str перевод числа в строку
        ;преобразование числа из ах в десятичную строку и вывод на экран
        ;ax - число
        push bx
        push cx
        push dx
        xor cx,cx ;в сх будет количество цифр в десятичном числе
        mov bx,10 ;основание системы
        xor ah,ah
to_str_loop:
        xor dx,dx ;очистить старшую часть делимого
        div bx;ax =dx:ax%bl
        add dl,'0' ;преобразовываем цифру в ASCII символ
        push dx;сохраняем остаток от деления(коэффициенты при степенях) в стек
        jmp goto
exit_3:        
        jmp exit_2
goto:
        inc cx ;увеличиваем количество десятичных цифр числа
        test ax,ax ;после деления остался 0?
        jnz to_str_loop ;если нет, продолжаем
        mov ax,cx
to_str_loop_2:
        pop dx ;взять из стека цифру числа
        mov [di],dl ; записываем в буфер
        inc di
        loop to_str_loop_2; циклом
        pop dx;возвращаем все нафиг
        pop cx
        pop bx
        ;end byte to str
        add dx,ax;добавляем сколько элементов напечатали в строку
        mov al,' '
        stosb
        inc dx;добавляем пробельчик
        ;Конец цикла добавление нового элемента в строку
next_step:;сюда мы попадаем, если символ нас не интересует и его не нужно вводить в строку       
        inc cx ;переходим к следующему элементу массива
        cmp cx,130 ;Сравниваем сч тек эл-та Всего 130 символов элементов массива
        jne add_line_loop;если не равно 130 прыгаем на новую итерацию
        
        mov al,13
        stosb
        mov al,10
        stosb ;записываем в строку перевод строки
        add dx,2;увелич счетчик символов
        mov cx,130;для обнуления массива
        mov di,offset result;
        mov al,0;
null_for_mas:
        stosb
        loop null_for_mas;обнуляем массив
        mov ax,dx;Возвращаем в ах количество элементов, которые нужно будет напечатать
        pop si;
        pop cx;Возвращаем регистры в исходное положение
        ret;возвращаемся на строку 93
print_str:
        push cx
        mov cx,ax ;Cx - количество элементов, сколько в строке есть
        mov ah,40h
        mov bx,file_w;файл на запись
        mov dx,offset buffer_for_write;буфер который надо записать
        int 21h ; Запись результатов в файл или вывод в консоль
        jc exit_3 ; Если ошибка записи, переход к exit_3
        cmp ax,cx
        jne exit_3 ; Если записано меньше символов, чем ожидалось, переход к exit_3
        pop cx
        ret
close_files:
        mov bx,file_r
        cmp bx,1
        je end_close_files ; Если файл для чтения не открыт, переход к end_close_files
        mov ah,3eh
        int 21h ; Закрытие файла для чтения
        mov bx,file_w
        cmp bx,1
        je  end_close_files; Если файл для записи не открыт, переход к end_close_files
        mov ah,3eh
        int 21h ; Закрытие файла для записи
end_close_files:
        ret

check_last_str:
        mov si,offset result
        mov cx,130
check_loop: 
        lodsb
        cmp al,0
        jne end_check_last_str ; Если найден ненулевой символ, переход к end_check_last_str
        loop check_loop ; Проверка следующего символа
        mov ax,0
        ret ; Если все символы нулевые, возврат 0
end_check_last_str:
        call add_new_line  ; Добавление новой строки
        ret

end start
