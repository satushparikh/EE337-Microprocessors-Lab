;// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--;//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:
CALL TAKE_INP
CALL QUANT_ENC
CALL LED_DISP
HERE: SJMP HERE
ORG 130H

 
;new subroutine
DELAY:;5s = 20 * 250ms

push 03h
mov r3, #20;20 BUT 2 TEMPORARILY
h3: acall delay_250ms
djnz r3, h3
pop 03h
acall delay_250us

delay_250ms:;250ms = 250 * 1ms take care that 250 is written in decimal appropriately
push 02h
mov r2, #250
h2: acall delay_1ms
djnz r2, h2
pop 02h
; ret

delay_1ms:
push 01h
mov r1, #4
h1: acall delay_250us
djnz r1, h1
pop 01h
; ret

delay_250us:
push 00h
; mov r0, #244
mov r0, #185
h0: djnz r0, h0
pop 00h
; ret


ret

;new subroutine
TAKE_INP:
        MOV A,#0Fh
        MOV P1,A;making p1 an input port
        MOV R0,#60H   ;starting location where number will be stored
        MOV R4,#04H;to create for loop for taking 4 input numbers
        MOV R6,#01H 
INPUT:
;LED UPDATE->TIME-DELAY(AND MAKING INPUT PORT)->MSB INPUT->LED UPDATE->TIME-DELAY(INPUT PORT)-> LSB INPUT
    ;LED UPDATE
    MOV A,R6;
    SWAP A;INTERCHANGES NIBBLES 
    ; MOV P1,A;
    INC R6;
    ;TIME-DELAY;
    ADD A,#0FH;
    MOV P1,A
    LCALL DELAY
    LCALL DELAY
    ;MSB INPUT
    MOV A,P1;TAKING MSB
    ANL A,#0FH; RETAINING ONLY LAST 4 BITS WHICH CONSTITUTE MSB OF INPUT NUMBER
    MOV R2,A ; R2 STORES MSB
    ; MOV A,#0Fh
    ; MOV P1,A;MAKING P1 AN INPUT PORT AGAIN
    ;LED-UPDATE
    MOV A,R6;CHANGED MOV->ADD
    SWAP A;INTERCHANGES NIBBLES 
    INC R6;
    ;TIME-DELAY
    ADD A,#0FH;CHANGED ADD A,#0FH TO ADD A,#0FH
    MOV P1,A
    LCALL DELAY
    LCALL DELAY
    ;LSB INPUT
    MOV A,P1;TAKING LSB
    ANL A,#0FH; RETAINING ONLY LAST 4 BITS
    MOV R3,A;R3 STORES LSB
    ; MOV A,#0FH 
    ; MOV P1,A ;MAKING P1 AN INPUT PORT AGAIN
    
    
    MOV A,R2  ;TAKING 0000_4BITSofMSB merging two 4 bits of 8 bit number
    SWAP A 
    ORL A,R3  ;
    MOV @R0,A ;TAKING INPUT TO MEMORY LOCATION POINTED BY R0
    INC R0 ;

    DJNZ R4,INPUT;INPUT ARE STORED IN 60,61,62,63;TAKING INPUT 4 TIMES
RET 
;new subroutine
QUANT_ENC:
MOV R5,#05;UNIT DIGIT IS 5 FOR ALL OF 5,15,25,35
MOV R4,#04H;ENCODING 4 NUMBERS   
MOV R0 , #60H;FIRST NUMBER IS STORED AT MEMORY LOCATION 60

LOO:  
MOV A ,@R0
CLR C  
SUBB A,#30
JNC OUT35

MOV A ,@R0 
MOV B,#10
DIV AB

MOV B,#10
MUL AB 

ADD A,R5 

SJMP UPDATE

OUT35:
MOV A,#35

UPDATE:
MOV @R0,A 
INC R0 
DJNZ R4, LOO

MOV R0,#60H 
MOV R1,#70H ; STORING THE ENCODED NUMBERS AT MEMORY LOCATIONS STARTING FROM 70
MOV R6,#04H ; ENCODING 4 NUMBERS

ANSWER:
MOV A,@R0                
MOV @R1,A    
      
INC R0
INC R1    
DJNZ R6, ANSWER

RET

;NEW SUBROUTINE
LED_DISP:

AGAIN:
     MOV R4,#04H ;
     MOV R0,#70H;
NEXT:;TURN OF ALL LEDs
     CLR P1.4;
     CLR P1.5;
     CLR P1.6;
     CLR P1.7;
    
     MOV B,#10;IN DECIMAL
     MOV A,@R0;
     DIV AB;A CONTAINS EITHER 0,1,2,3
     JZ SET_P1_4;CHECKS IF A IS 0
     DEC A;
     JZ SET_P1_5;CHECKS IF A IS 1
     DEC A;
     JZ SET_P1_6;CHECKS IF A IS 2
     ; SINCE A WAS NOT ONE OF 0,1,2 IT WOULD BE 2
     SETB P1.7;
     LJMP WAIT; *****************

SET_P1_4:
     SETB P1.4;
     LJMP WAIT;

SET_P1_5:
     SETB P1.5;
     LJMP WAIT;

SET_P1_6:
     SETB P1.6;
    ;  LJMP WAIT;

WAIT: 
    INC R0;FOR CHECKING NEXT ENCODED BIT IN NEXT ITERATION INC R0 BY 1
    LCALL DELAY;
DJNZ R4,NEXT;
LCALL AGAIN;


RET
END


; delay_250ms:;250ms = 250 * 1ms take care that 250 is written in decimal appropriately
; push 00h
; mov r0, #250
; h2: acall delay_1ms
; djnz r0, h2
; pop 00h
; ret

; delay_1ms:
; push 00h
; mov r0, #4
; h2: acall delay_250us
; djnz r0, h2
; pop 00h
; ret

; delay_250us:
; push 00h
; mov r0, #244
; h1: djnz r0, h1
; pop 00h
; ret

 