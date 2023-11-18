ORG 0
LJMP MAIN

ORG 100
MAIN:
; Set initial values for A and B
MOV A,#0FFH 
INC A 
INC A
MOV R2, #30H
MOV R3, #40H
; Call function to perform the extended Euclidean algorithm
CALL EXTEUCLID
; The result is stored in R2 (gcd) and R3 (coefficients)
; End the program
END

ORG 75h
EXTEUCLID:
; Save the values of A and B on the stack
PUSH R2
PUSH R3
; Initialize the loop counter and temp register
MOV R4, #0
MOV R5, #0

LOOP:
; Check if B is 0 (indicating gcd has been found)
CJNE R3, #0, DO_CALC
; Pop the values of A and B from the stack
POP R3
POP R2
; Return with the gcd in R2 and coefficients in R3
RET

DO_CALC:
; Calculate the quotient and remainder
DIV AB
MOV R5, A
MOV R4, B
; Replace A with B and B with the remainder
MOV A, R3
MOV R3, R4
; Increment the loop counter
INC R4
; Repeat the loop
SJMP LOOP

END
