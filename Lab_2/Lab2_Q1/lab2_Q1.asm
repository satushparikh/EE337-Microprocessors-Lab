; ORG 0
; LJMP MAIN

; ORG 100
; MAIN:
; ; Set initial values for A and B
; MOV R2, #30H
; MOV R3, #40H
; ; Call function to perform the extended Euclidean algorithm
; CALL EXTEUCLID
; ; The result is stored in R2 (gcd) and R3 (coefficients)
; ; End the program
; END

; ORG 200
; EXTEUCLID:
; ; Save the values of A and B on the stack
; PUSH R2
; PUSH R3
; ; Initialize the loop counter and temp register
; MOV R4, #0
; MOV R5, #0

; LOOP:
; ; Check if B is 0 (indicating gcd has been found)
; CJNE R3, #0, DO_CALC
; ; Pop the values of A and B from the stack
; POP R3
; POP R2
; ; Return with the gcd in R2 and coefficients in R3
; RET

; DO_CALC:
; ; Calculate the quotient and remainder
; DIV AB
; MOV R5, A
; MOV R4, B
; ; Replace A with B and B with the remainder
; MOV A, R3
; MOV R3, R4
; ; Increment the loop counter
; INC R4
; ; Repeat the loop
; SJMP LOOP

; END






;// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
; MOV 70H, #034H
 ;MOV 71H, #05AH
 MOV A,#0FFH 
INC A 
INC A
;  MOV 70H, #001H
;  MOV 71H, #063H
 
MOV 70H, #04DH
MOV 71H, #009H
MOV R1, #61H

; M1 thought of writng MOV B,R1 here as i thought writing it 2x in MODADD and MODSUB will be redundatn
; but it turns out that B is getting modified in MODADD(remainder) and hence it became necessary to write
; again in MODSUB
; MOV B,R1
CALL MODADD
CALL MODSUB
HERE: SJMP HERE
ORG 130H
;// *****************
MODADD:
;// ADD YOUR CODE HERE
MOV A ,70H
ADD A,71H
MOV B,R1
DIV AB
MOV 72H,B

RET
MODSUB:
;// ADD YOUR CODE HERE
CLR C
MOV A ,70H
SUBB A ,71H
JNC NEXT;if carry bit is not set(no borrow) go directly to next
;taking 2's complement 
CPL A;if carry bit is set, (x)-(x+e)=-e in A; answer is (divisor - e mod divisor)
INC A; A now contains c, our target is to find -e mod divisor  in next step we are finding e mod divisor
MOV B,R1
DIV AB;B now contains contains e mod divisor
CLR C 
MOV A,#61H 
SUBB A,B 
 

NEXT : 
MOV B,R1
DIV AB
MOV 73H,B
RET
END
; x and y must stored at locations 70H and 71H
; sum = (x + y) mod 61H
; diff = (x - y) mod 61H
; • The sum should be stored in 72H and the difference should be stored in 73H.