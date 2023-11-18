;// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--;//
ORG 0H
LJMP MAIN
ORG 100H
MAIN:

MOV 71H,#0ADH; WHICH IS 160+13=173
MOV 70H,#216     ; WHICH IS 216

CALL FINDE
; CALL TAKE_INP
; CALL QUANT_ENC
CALL LED_DISP
HERE: SJMP HERE
ORG 130H

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


; ret

 
; LED_DISP:

; AGAIN:
;      MOV R4,#04H ;
;      MOV R0,#70H;
; NEXT:;TURN OF ALL LEDs
;      CLR P1.4;
;      CLR P1.5;
;      CLR P1.6;
;      CLR P1.7;
    
;      MOV B,#10;IN DECIMAL
;      MOV A,@R0;
;      DIV AB;A CONTAINS EITHER 0,1,2,3
;      JZ SET_P1_4;CHECKS IF A IS 0
;      DEC A;
;      JZ SET_P1_5;CHECKS IF A IS 1
;      DEC A;
;      JZ SET_P1_6;CHECKS IF A IS 2
;      ; SINCE A WAS NOT ONE OF 0,1,2 IT WOULD BE 2
;      SETB P1.7;
;      LJMP WAIT; *****************

; SET_P1_4:
;      SETB P1.4;
;      LJMP WAIT;

; SET_P1_5:
;      SETB P1.5;
;      LJMP WAIT;

; SET_P1_6:
;      SETB P1.6;
;     ;  LJMP WAIT;

; WAIT: 
;     INC R0;FOR CHECKING NEXT ENCODED BIT IN NEXT ITERATION INC R0 BY 1
;     LCALL DELAY;
; DJNZ R4,NEXT;
; LCALL AGAIN;


; RET
 