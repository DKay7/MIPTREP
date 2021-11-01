in
pop bx

push 0
pop ax
for_cycle:
call SqrFinder
push ax
push bx
jbe for_cycle
hlt

SqrFinder:
push ax
push ax
mul
out
push 1
push ax
add
pop ax
ret