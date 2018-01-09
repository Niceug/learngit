; 编写并运行程序，按要求粘贴程序和截屏。（40分）
; 编写程序, 当Int0中断发生时，将以0结尾的字符串中的小写字母转换成大写字母，; 并在显示器居中显示输出。
; 要求：
; 1）使用条件转移指令2条以上；（10分）
; 2）使用Int0中断处理子程序实现将小写字母转换成大写字母功能；（10分）
; 3）使用emu8086 汇编工具调试并演示运行结果；（5分）
; 4）参数传递使用ds:si表示字符串的存放位置。（5分）
; 5）程序运行正确。粘贴程序和运行结果截屏粘贴一幅图。（10分）

assume cs : code, ds : data

data segment
	str db "hello WORLD!", 0, "$"
data ends

code segment
start : mov ax, data
	mov ds, ax

	call castToUpPro; 调用子函数将小写转大写
	
	;换行
	mov ah,02h
        mov dl,0ah
        int 21h
	;输出转换后的字符串
	mov  dx, offset str
	mov  ah, 09H;
	int 21H

	;退出程序
	mov ax, 4C00H
	int 21H

castToUpPro : 
	;保护现场
	push ax
	push bx
	push cx
	push si
	push di
	push bp
	push dx
	push ds
	mov si, 0

	mov  dx, offset str
	mov  ah, 09H;
	int 21H

	s:          
	mov al, ds : [si]
	mov cl, ds : [si]
	mov ch, 0
	jcxz ed; 如果检测到字符为零时，就跳到ed处，结束子程序

	cmp al, 97; 如果不是小写字母就不转换
	jb ok
	cmp al, 122
	ja ok

	sub al, 32; 如果是小写字母就转换为大写字母
	mov ds : [si], al
	mov ax, 0

	ok : 
	inc si;
	jmp s

	ed :
	;恢复现场
	pop ds
	pop dx
	pop bp
	pop di
	pop si
	pop cx
	pop bx
	pop ax
	ret;返回

	code ends
	end start