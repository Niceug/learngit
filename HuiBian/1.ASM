; ��д�����г��򣬰�Ҫ��ճ������ͽ�������40�֣�
; ��д����, ��Int0�жϷ���ʱ������0��β���ַ����е�Сд��ĸת���ɴ�д��ĸ��; ������ʾ��������ʾ�����
; Ҫ��
; 1��ʹ������ת��ָ��2�����ϣ���10�֣�
; 2��ʹ��Int0�жϴ����ӳ���ʵ�ֽ�Сд��ĸת���ɴ�д��ĸ���ܣ���10�֣�
; 3��ʹ��emu8086 ��๤�ߵ��Բ���ʾ���н������5�֣�
; 4����������ʹ��ds:si��ʾ�ַ����Ĵ��λ�á���5�֣�
; 5������������ȷ��ճ����������н������ճ��һ��ͼ����10�֣�

assume cs : code, ds : data

data segment
	str db "hello WORLD!", 0, "$"
data ends

code segment
start : mov ax, data
	mov ds, ax

	call castToUpPro; �����Ӻ�����Сдת��д
	
	;����
	mov ah,02h
        mov dl,0ah
        int 21h
	;���ת������ַ���
	mov  dx, offset str
	mov  ah, 09H;
	int 21H

	;�˳�����
	mov ax, 4C00H
	int 21H

castToUpPro : 
	;�����ֳ�
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
	jcxz ed; �����⵽�ַ�Ϊ��ʱ��������ed���������ӳ���

	cmp al, 97; �������Сд��ĸ�Ͳ�ת��
	jb ok
	cmp al, 122
	ja ok

	sub al, 32; �����Сд��ĸ��ת��Ϊ��д��ĸ
	mov ds : [si], al
	mov ax, 0

	ok : 
	inc si;
	jmp s

	ed :
	;�ָ��ֳ�
	pop ds
	pop dx
	pop bp
	pop di
	pop si
	pop cx
	pop bx
	pop ax
	ret;����

	code ends
	end start