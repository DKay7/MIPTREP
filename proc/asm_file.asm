push 16
pop bx

push 0
pop ax
lol:
    push ax
    push ax
    mul
    out
    push 1
    push ax
    add
    pop ax

    push ax
    push bx
jbe lol

hlt