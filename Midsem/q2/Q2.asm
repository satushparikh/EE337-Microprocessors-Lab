;// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--;//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:

MOV 71H,#0ADH; WHICH IS 160+13=173
MOV 70H,#216     ; WHICH IS 216

CALL MUL_SUB
CALL MOD_OPERATOR

CALL TAKE_INP
; CALL QUANT_ENC
; CALL DECRYPTED




; 
CALL LED_DISP
HERE: SJMP HERE
ORG 130H

MUL_SUB:
;Take inputs for subroutine from 73H, 74H for input 1 and 75H for input 2 and output need to
; be rewritten to 73H, 74H.
; Test case: Input 1 = 271H, Input 2 = 5H; Output = C35H
MOV A,74H ;
MOV B,75H ;
MUL AB ;
MOV 74H,A ;
MOV R7,B ; MORE SIGNIFICANT 8 BITS TO BE ADDED 

MOV A,73H ;
MOV B,75H ;
MUL AB ;

ADD A,R7
MOV 73H,A ;

; Return from subroutine
RET;  

TAKE_INP :
  MOV A,#0Fh
        MOV P1,A;making p1 an input port
        MOV R0,#73H   ;starting location where number will be stored
        MOV R4,#01H;to create for loop for taking 4 input numbers
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
    LCALL DELAY_5s 
    
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
    LCALL DELAY_5s 
    
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

    DJNZ R4,INPUT;INPUT ARE STORED IN 50,51,52,53;TAKING INPUT 4 TIMES
RET 
; 3 marks for mod-n operator sub-routine.
; Take inputs for subroutine from 73H, 74H and output need to be rewritten to 73H.
; Test case: Input = C35H; Output = A1H
MOD_OPERATOR:
MOV 70H,#247
MOV A,74H ;MODULUS NUMBER AT LOCATION 70H
MOV B,70H ;
DIV AB ;
MOV 74H,B;

; AB MOD C == (AMODC * BMODC)MOD C A=256
MOV A,#0255;
MOV B,70H
DIV AB ;
INC B 

;STORING A MOD C
MOV R3,B  ; R3= 256 MOD 70H
MOV A,73H
MOV B,70H
DIV AB ;
MOV R4,B  ; R4= 73 MOD 70H
MOV A,R3;
MOV B,R4;
MUL AB;
; ADD A,74H;
MOV B,70H;
DIV AB;      
MOV A,B
ADD A,74H ;
MOV 73H,A ;   
RET


  



FINDE: 
      MOV R2,#01H; THIS IS OUR ENCRYPTION COEFFICIENT
      MOV A,71H 
NEXT_ITERATION:
      MOV B,70H
    ;   MOV R6,A 
      DIV AB
      MOV A,B
    ;   MOV A,R6
      MOV R7,B ;STORES REMAINDER
      CJNE R7,#01H,REM_NOT_ONE
      ;SINCE WE HAVE GOT REMAINDER AS 1 IF ITS NOT JUMPING
      MOV 72H,R2 
      RET 
REM_NOT_ONE:
      CLR C  ;
      ADD A,71H
    ;   INC A;ADDED LATER ON
    ;   MOV C,OV; TAKING OVERFLOW FLAG INTO C AS INSTRUCTIONS LIKE JC EXIST
      
      JNC NO_OVERFLOW
      ;IF OVERFLOW ADD 255 MOD 216
      
    ;   ADD A,#40
      MOV R6,A ;
      MOV A,#0FFH ;
      MOV B,70H
	  CLR C
      SUBB A,B ;
      MOV R5,A ; THIS IS 39 HERE 
      INC R5 
      MOV A,R6
      ADD A,R5 

NO_OVERFLOW: ;NOTHING HAS TO BE DONE OTHER THAN INCREMENTING R2
      INC R2 

      LCALL NEXT_ITERATION
 RET

LED_DISP:
;UPPER 4 BITS 72H
MOV A,72H;
ANL A,#0F0H;
MOV P1,A; 
ACALL delay_5s

MOV P1,#000H
ACALL delay_1s

MOV A,72H;
ANL A,#0FH;
SWAP A
MOV P1,A; 
ACALL delay_5s

MOV P1,#000H
ACALL delay_1s

RET 
delay_5s:
	push 00h
	mov r0, #25
	hE5: acall delay_200ms   
	djnz r0, hE5
	pop 00h
ret
delay_1s:
	push 00h
	mov r0, #5
	hE55: acall delay_200ms   
	djnz r0, hE55
	pop 00h
ret
delay_200ms:
	push 00h
	mov r0, #200
	hE4: acall delay_1ms   
	djnz r0, hE4
	pop 00h
ret
delay_1ms:
	push 00h
	mov r0, #4
	hE2: acall delay_250us
	djnz r0, hE2
	pop 00h
ret

delay_250us:
push 00h
mov r0, #244
h1: djnz r0, h1
pop 00h
ret

END
; DELAY:;5s = 20 * 250ms

; push 03h
; mov r3, #20;20 BUT 2 TEMPORARILY
; h3: acall delay_250ms
; djnz r3, h3
; pop 03h
; acall delay_250us

; delay_250ms:;250ms = 250 * 1ms take care that 250 is written in decimal appropriately
; push 02h
; mov r2, #250
; h2: acall delay_1ms
; djnz r2, h2
; pop 02h
; ; ret

; delay_1ms:
; push 01h
; mov r1, #4
; h1: acall delay_250us
; djnz r1, h1
; pop 01h
; ; ret

; delay_250us:
; push 00h
; ; mov r0, #244
; mov r0, #185
; h0: djnz r0, h0
; pop 00h
; ; ret

 
 