in
in
in
pop cx
pop bx
pop ax

;flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

push 0
push ax
jne a_isnt_zero
; a == 0

;flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

push 0
push bx
jne b_isnt_zero_a_zero
; a == 0, b == 0

;flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
push 0
push cx
jne c_isnt_zero_b_zero_a_zero
; a == 0, b == 0, c == 0
; inf roots
push -2
out
hlt

;flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

c_isnt_zero_b_zero_a_zero:
; a == 0, b == 0, c != 0
; no real roots
push -1
out
hlt

;flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

b_isnt_zero_a_zero:
; a == 0, b != 0
push 1
out

push cx
push bx
push -1
mul
div
out
hlt

;flexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

a_isnt_zero:
; a != 0
; counting discr
push bx
push bx
mul
push 4
push ax
push cx
mul
mul
sub

pop dx
push dx
push 0
ja diskr_above_zero
; D <= 0
push 0
push dx

je diskr_is_zero
; D < 0
push -1
out
hlt

diskr_is_zero:
push 1
out

push bx
push -1
mul
push 2
push ax
mul
div
out
hlt

diskr_above_zero:
push 2
out

push bx
push -1
mul
push dx
sqrt
add
push 2
push ax
mul
div
out

push bx
push -1
mul
push dx
sqrt
sub
push 2
push ax
mul
div
out
hlt