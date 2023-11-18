           ; -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--           ;
           ; E char I:60h = 14h,69h,26h,5bh,7fh,1ah,00h,05h
           ; E char I:60h = 0D4h,0CCh,0C1h,0AFh,092h,054h,016h,001h

ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL SORT
HERE: SJMP HERE
ORG 130H
           ; *****************
SORT:
                      ; ADD YOUR CODE HERE
MOV R4,#07H           ;EARLIER 8 ARRAY SHIFTED 1 UNIT TOWARDS RIGHT
OUTER_LOOP :
MOV R3,#07H           ;EARLIER 8 ARRAY SHIFTED 1 UNIT TOWARDS RIGHT
MOV R0,#60H 
INNER_LOOP :
MOV A,@R0 
MOV B,A   
INC R0
MOV A ,@R0 

           ; INC R0 
           ; MOV B,@R0 
CJNE A,B,CONTINUE ; if A<B then carry set 1, A is i+1 address value and B is i address value
           ; CJNE B,A,CONTINUE GIVING SYNTAX ERROR
CONTINUE:
JNC EQUAL
MOV @R0,B
DEC R0
MOV @R0,A 
INC R0     
EQUAL :
DJNZ R3, INNER_LOOP
DJNZ R4, OUTER_LOOP

MOV R0,#60H 
MOV R1,#70H 
MOV R6,#08H

ANSWER:
           ; MOV @R1,@R0             invalid    
MOV A,@R0               
MOV @R1,A            
           
INC R0
INC R1    
DJNZ R6, ANSWER
RET
END
 
 