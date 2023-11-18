
ORG 0H
LJMP MAIN

; Jump to main program

ORG 100H
MAIN:
; Start of main program
CALL QUANT
; Call the quantization subroutine

HERE: SJMP HERE
; Infinite loop, program will stay here

ORG 130H
; *****************
QUANT:
; Start of quantization subroutine
MOV A,#0FFH;
INC A ;
INC A ;
; ADD YOUR CODE HERE
MOV R5,#05
; Move the value 5 to register R5
MOV R4,#08H   
; Move the value 8 to register R4
MOV R0 , #60H
; Move the value 60 to register R0, this is the starting address of the input data

LOO:  
MOV A ,@R0
; Move the value at the address stored in R0 to the A register
CLR C  
; Clear the carry flag
SUBB A,#30
; Subtract 30 from the value in A
JNC OUT35
; If the carry flag is not set, jump to OUT35

MOV A ,@R0 
MOV B,#10
DIV AB
; Divide the value in A by 10, store the result in A and the remainder in B

MOV B,#10
MUL AB 
; Multiply the value in A by 10, store the result in A

ADD A,R5 
; Add the value in R5 to the value in A

SJMP UPDATE
; Jump to the update section

OUT35:
MOV A,#35
; If the carry flag was set, move the value 35 to A

UPDATE:
MOV @R0,A 
; Move the value in A to the memory location stored in R0
INC R0 
; Increment the value in R0
DJNZ R4, LOO
; Decrement the value in R4 and jump to LOO if it is not zero

; MOV A ,@R0 
; MOV B,#10
; DIV AB
; MOV B,#10
; MUL AB 
; ADD A,R5 
; MOV @R0,A 
; INC R0 
; DJNZ R4, LOO

MOV R0,#60H 
MOV R1,#70H 
MOV R6,#08H

ANSWER:
; MOV @R1,@R0             invalid    
MOV A,@R0                ;try to work with R0 and R1
MOV @R1,A    ;THIS TYPE OF SYNTAX IS ONLY VALID FOR R0 AND R1            
; MOV A,@R4                ;GIVING SYNTAX ERROR
; MOV @R5,A    THIS TYPE OF SYNTAX IS ONLY VALID FOR R0 AND R1            
INC R0
INC R1    
DJNZ R6, ANSWER
; Copy the quantized data from memory location 60h to 70h, 8 times

; E char I:60h = 11h,2Ah,01h,3Fh,18h,1Ch,0Eh,06h
; E char I:60h = 00h,09h,0Ah,13h,14h,1Dh,1Eh,0FFh

RET
; Return from subroutine
END

; ORG 0H
; LJMP MAIN
; ORG 100H
; MAIN:
; CALL QUANT
; HERE: SJMP HERE
; ORG 130H
; ; *****************
; QUANT:
; ; ADD YOUR CODE HERE
; MOV R5,#05
; MOV R4,#08H   
; MOV R0 , #60H
; LOO :  
; MOV A ,@R0
; CLR C  
; SUBB A,#30
; JNC OUT35
; MOV A ,@R0 
; MOV B,#10
; DIV AB
; MOV B,#10
; MUL AB 
; ADD A,R5 
; SJMP UPDATE


; OUT35:
; MOV A,#35

; UPDATE:
; MOV @R0,A 
; INC R0 
; DJNZ R4, LOO
; ; MOV A ,@R0 
; ; MOV B,#10
; ; DIV AB
; ; MOV B,#10
; ; MUL AB 
; ; ADD A,R5 
; ; MOV @R0,A 
; ; INC R0 
; ; DJNZ R4, LOO

; MOV R0,#60H 
; MOV R1,#70H 
; MOV R6,#08H

; ANSWER:
; ; MOV @R1,@R0             invalid    
; MOV A,@R0                ;try to work with R0 and R1
; MOV @R1,A    ;THIS TYPE OF SYNTAX IS ONLY VALID FOR R0 AND R1            
; ; MOV A,@R4                ;GIVING SYNTAX ERROR
; ; MOV @R5,A    THIS TYPE OF SYNTAX IS ONLY VALID FOR R0 AND R1            
; INC R0
; INC R1    
; DJNZ R6, ANSWER

; ; E char I:60h = 11h,2Ah,01h,3Fh,18h,1Ch,0Eh,06h
; ; E char I:60h = 00h,09h,0Ah,13h,14h,1Dh,1Eh,0FFh
; RET
; END
  
 