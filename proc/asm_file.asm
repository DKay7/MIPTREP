in              ; вводим a
;dump

pop     ax      ; записываем в регистр ax

;dump


in              ; вводим b
pop     bx      ; записываем в регистр bx
;dump


in              ; вводим c
pop     cx      ; записываем в регистр cx

dump


push    cx      ; возвращаем из регистра сх

push    ax      ; возвращаем из регистра aх
push    4       ; для 4*a*c
dump

mul             ; получаем 4*a
mul             ; получаем 4*a*c

dump


push    bx      ; возвращаем из регистра bх
push    bx      ; возвращаем из регистра bх

;dump

mul             ; b^2

sub             ; b^2 - 4*a*c


out             ; выводим результат
;dump
hlt             ; термнируем программу
