DATA SEGMENT
    BUF DB 'Hello',0Dh,0Ah,'END$'
DATA ENDS
STACK SEGMENT
    DB 100 DUP (0)
STACK ENDS
CODE SEGMENT
    ASSUME CS:CODE,DS:DATA,SS:STACK
BEGIN:
    MOV AX,DATA
    MOV DS,AX
    LEA BX,BUF
LA:
    MOV DL,[BX]
    CMP DL,'$'
    JZ EXIT
    CMP DL,'a'
    JB K
    CMP DL,'z'
    JA K
    SUB DL,20H
K:
    MOV AH, 2
    INT 21H
    INC BX
    JMP LA
EXIT:
    MOV AH,4CH
    INT 21H
CODE ENDS
    END BEGIN

assume cs: codesg
codesg SEGMENT
    mov ax, 2000h
    mov ss, ax
    mov sp, 10h
    add sp, 4
    push ax
    push bx
    pop ax
    pop bx
    mov ax, 4c00h
    int 21h
codesg ends
end

MOV     AX,2000
MOV     SS,AX
MOV     SP,0010
ADD     SP,+04
PUSH    AX
PUSH    BX
POP     AX
POP     BX
MOV     AX,4C00
INT     21


mov ax, 4e20h   ;(ax)=4e20h
add ax, 1416h    ;(ax)=(ax)+1416h
mov bx, 2000h   ;(bx)=2000h
add ax, bx       ;(ax)=(ax)+(bx)
mov bx, ax       ;(bx)=(ax)
add ax, bx        ;(ax)=(ax)+(bx)
mov ax, 001ah    ;(ax)=001ah
mov bx, 0026h   ;(bx)=0026
add al, bl        ;(al)=(al)+(bl)
add ah, bl        ;(ah)=(ah)+(bl)
add bh, al        ;(bh)=(bh)+(al)
mov ah, 0      ;(ah)=0
add al, bl        ;(al)=(al)+(bl)
add al,9ch       ;(al)=(al)+9ch


assume cs: code
code segment
    mov ax, cs
    mov ds, ax          ;将代码段作为数据段
    mov ax, 0020h
    mov es, ax          ;(es)=0020h
    mov bx, 0
    mov cx, offset a
s:  mov al, [bx]
    mov es: [bx], al    ;将ds: [bx]复制到es: [bx]
    inc bx
    loop s
a:  mov ax, 4c00h
    int 21h
code ends
end

assume cs: code
code segment
    mov ax, 0020h
    mov ds, ax      ;设置数据段地址为0020h
    mov bx, 0
    mov cx, 0040h   ;循环64次
s:  mov [bx], bx
    inc bx
    loop s
    mov ax, 4c00h
    int 21h
code ends
end

STACK SEGMENT
    DB 200 DUP(0)
STACK ENDS
CODE SEGMENT
ASSUME CS: CODE, SS: STACK
BEGIN:
    MOV AH, 1
    INT 21H         ;从键盘输入一个小写字母放入AL
    SUB AL, 20H     ;小写字母转大写字母
    MOV DL, AL
    MOV AH, 2
    INT 21H         ;在屏幕上显示DL的内容
    MOV AH, 4CH
    INT 21H         ;程序返回
CODE ENDS
END BEGIN





DATA SEGMENT
    BUF DB 'Hello', 0Dh, 0Ah, 'END$'
DATA ENDS
STACK SEGMENT
    DB 100 DUP (0)
STACK ENDS
CODE SEGMENT
    ASSUME CS: CODE, DS: DATA, SS: STACK
BEGIN:
    MOV AX, DATA
    MOV DS, AX
    LEA BX, BUF
LA:
    MOV DL, [BX]    ;(DL)=([BX])
    CMP DL, '$'
    JZ EXIT         ;若DL中的字符是$则结束
    CMP DL, 'a'
    JB K
    CMP DL, 'z'
    JA K            ;若DL中的字符不是小写字母，转K
    SUB DL, 20H     ;小写转大写
K:
    MOV AH, 2
    INT 21H         ;显示字符
    INC BX
    JMP LA
EXIT:
    MOV AH, 4CH
    INT 21H
CODE ENDS
    END BEGIN


0B6B:0000 8CC8          MOV     AX,CS
0B6B:0002 8ED8          MOV     DS,AX
0B6B:0004 B82000        MOV     AX,0020
0B6B:0007 8EC0          MOV     ES,AX
0B6B:0009 BB0000        MOV     BX,0000
0B6B:000C B91700        MOV     CX,0017
0B6B:000F 8A07          MOV     AL,[BX]
0B6B:0011 26            ES:
0B6B:0012 8807          MOV     [BX],AL
0B6B:0014 43            INC     BX
0B6B:0015 E2F8          LOOP    000F
0B6B:0017 B8004C        MOV     AX,4C00
0B6B:001A CD21          INT     21
0B6B:001C 8B7F04        MOV     DI,[BX+04]
0B6B:001F 2E            CS:
0B6B:0020 893E4E91      MOV     [914E],DI



CODE SEGMENT
    ASSUME CS: CODE
G1:
    MOV AH, 1
    INT 21H         ;从键盘读入字符送入AL
    CMP AL, '$'
    JZ EXIT         ;若字符为$结束输入
    MOV DL, AL
    MOV AH, 2       ;输出字符
    INT 21H
    JMP G1          ;跳转G1继续输入
EXIT:
    MOV AH, 4CH
    INT 21H
CODE ENDS
    END G1


    MOV AH, 1           ;系统调用功能号送入AH
    INT 21H


STACK SEGMENT STACK
    DW 256 DUP(?)
STACK ENDS
CODE SEGMENT
    ASSUME CS: CODE, SS: STACK
START:
    MOV AH, 1
    INT 21H             ;使用调用号1输入字符送入AL中，并显示在屏幕上
    MOV BH, AL          ;用BH存放键盘输入的保存在AL中的字符

    MOV AH, 2
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H             ;另起一行

    MOV AH, 1
    INT 21H             ;从键盘输入另一个字符送入AL中
    MOV BL, AL          ;将字符保存在BL中

    MOV AH, 2
    MOV DL, 0DH
    INT 21H
    MOV DL, 0AH
    INT 21H             ;另起一行

    MOV AH, 2
    MOV DL, BH
    INT 21H             ;使用调用号2在屏幕上输出BH的值

    CMP BH, BL          ;比较BH和BL的大小
    JG DISP2            ;若BH>BL，跳转到DISP2
    JE DISP3            ;若BH=BL，跳转到DISP3

DISP1:  
    MOV DL, '<'         ;将'<'保存在DL中
    JMP EXIT
DISP2:
    MOV DL, '>'         ;将'>'保存在DL中
    JMP EXIT
DISP3:
    MOV DL, '='         ;将'='保存在DL中

EXIT:
    INT 21H             ;使用调用号2在屏幕上输出DL的值
    MOV DL, BL
    INT 21H             ;使用调用号2在屏幕上输出BL的值

    MOV AH, 4CH
    INT 21H             ;程序返回
CODE ENDS
    END START



stack segment stack
    db 64 dup(?)
stack ends
data segment
    buff db 50, ?, 50 dup(?)
    mes1 db 0dh, 0ah
         db 'What is your name?:$'
    mes2 db 0dh, 0ah
         db 'hello!', '$'
data ends
code segment
    assume cs: code, ds: data, ss: stack
start:
    mov ax, data
    mov ds, ax

    ;print mes1
    mov dx, offset mes1
    mov ah, 9
    int 21h

    ;input->buff
    mov dx, offset buff
    mov ah, 0ah
    int 21h

    ;print mes2
    mov dx, offset mes2
    mov ah, 9
    int 21h

    lea si, buff
    add si, 1
    mov bx, [si]
	mov bh, 0
    mov byte ptr [bx+si+1], '$'

    ;print buff
    mov dx, offset buff+2
    mov ah, 9
    int 21h

    mov ah, 4ch
    int 21h
code ends
    end start


stack segment stack
    db 64 dup(?)
stack ends
data segment
    buff db 50, ?, 50 dup('$')
    mes1 db 0dh, 0ah
         db 'What is your name?:$'
    mes2 db 0dh, 0ah
         db 'hello!', '$'
data ends
code segment
    assume cs: code, ds: data, ss: stack
start:
    mov ax, data
    mov ds, ax

    ;print mes1
    mov dx, offset mes1
    mov ah, 9
    int 21h

    ;input->buff
    mov dx, offset buff
    mov ah, 0ah
    int 21h

    ;print mes2
    mov dx, offset mes2
    mov ah, 9
    int 21h

    ;print buff
    mov dx, offset buff+2
    mov ah, 9
    int 21h

    mov ah, 4ch
    int 21h
code ends
    end start