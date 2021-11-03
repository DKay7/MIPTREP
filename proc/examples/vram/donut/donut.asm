push 46
pop [3520]
push 44
pop [3521]
push 45
pop [3522]
push 126
pop [3523]
push 58
pop [3524]
push 59
pop [3525]
push 61
pop [3526]
push 33
pop [3527]
push 42
pop [3528]
push 35
pop [3529]
push 36
pop [3530]
push 64
pop [3531]


;  0 - 1759 -- z_array
;  1760 - 3519 -- screen_array

vrsetx 80
vrsety 22
vrsetstart 1760

start:
clrbuf 1759
scrclr

push 0
pop ix

push 0
pop jx


outer_cycle:
    push 0
    pop ix

    inner_cycle:
        call DrawDonutFrame
                
        push ix
        push 0.04
        add
        pop ix

        push ix
        push 6.28
        jb inner_cycle

        push jx
        push 0.14
        add
        pop jx
        
        push jx
        push 6.28
        jb outer_cycle

push ax
push 0.0704
add
pop ax

push bx
push 0.0352
add
pop bx

scrupd
jmp start

DrawDonutFrame:
    pop retx ; pop return addres to register

    push ix
    sin
    pop cx
    push    

    push jx
    cos
    pop dx

    push ax
    sin
    pop ex

    push jx
    sin
    pop fx

    push ax
    cos
    pop gx

    push dx
    push 2
    add
    pop hx

    push 1
    push cx
    push hx
    push ex
    mul
    mul
    push fx
    push gx
    mul
    push 5
    add
    add
    div
    pop qx

    push ix
    cos
    pop lx

    push bx
    cos
    pop mx

    push bx
    sin
    pop nx
    
    push cx
    push hx
    push gx
    mul
    mul
    push fx
    push ex
    mul
    sub
    pop tx

    push lx
    push hx
    push mx
    mul
    mul
    push tx
    push nx
    mul
    sub
    push qx
    push 30
    mul
    mul
    push 40
    add
    rnd
    pop xx

    push lx
    push hx
    push nx
    mul
    mul
    push tx
    push mx
    mul
    add
    push qx
    push 15
    mul
    mul
    push 12
    add
    rnd
    pop yx

    push yx
    push 80
    mul
    push xx
    add
    pop ox
    
    push fx
    push ex
    mul
    push cx
    push dx
    push gx
    mul
    mul
    push mx
    mul
    sub
    push cx
    push dx
    push ex
    mulpop
    mul
    sub
    push fx
    push gx
    mul
    sub
    push lx
    push dx
    push nx
    mul
    mul
    sub
    push 8
    mul
    rnd
    pop sx

    push 22
    push yx
    push yx
    push 0
    push xx
    push 0
    push 80
    push xx
    push qx
    push [ox]
    jb end_loop
    jb end_loop    
    jb end_loop
    jb end_loop
    jb end_loop
    
    ; in loop
    
    push sx
    push 0
    ja s_above
    ; s <= 0
    push 0
    pop sx


    s_above:
        push qx
        pop [ox]
    
        push sx
        push 3520 ; start of  ".,-~:;=!*#$@"
        add
        pop sx
        
        push 1760 ; start of screen_array
        push ox
        add
        pop ox

        push [sx]
        pop [ox]

    end_loop:
        push retx
        ret