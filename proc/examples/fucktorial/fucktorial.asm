in                            	
pop ax

push 1
pop bx
call factorial

push bx
out      


factorial:
    push ax
    push 1
    jbe basic_case

    push ax
    push bx
    mul                   	
    pop bx

    push ax
    push 1
    sub
    pop ax

    call factorial       
    ret             
    
    basic_case:
        ret