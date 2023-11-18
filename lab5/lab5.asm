;// -- DO NOT CHANGE ANYTHING UNTIL THE **** LINE--;//
ORG 0H
LJMP MAIN
ORG 100H

;SA - 1960US DELAY     1/(2*frequency)
;RE - 1724US DELAY
;GA - 1538US DELAY
;MA - 1449US DELAY
MAIN:

      MOV A,#0FH                 ;
      MOV P1,A                   ;MAKING P1 AN INPUT PORT
;I WILL PUT ONE LABEL HERE
INPUT :  

  ;   MOV P0,#0                   ;MAKE OUTPUT 0
   ;  MOV P1,#0                   ;CLEAR PREVIOUS INPUT FLUSH

      ; MOV A,P1                   ; READING INTO A
      ; ANL A,#0FH                 ;RETAINING ONLY SWITCH INPUT EXCLUDING JUNK INPUT;
      
      ; MOV R2,A                   ;STORING DATA INTO R2

      ; MOV A,#0FH                 ;
      ; MOV P1,A                   ;MAKING P1 AN INPUT PORT
      ; REALISING THAT P1 CAN BE TREATED LIKE REGISTER
      MOV P1, #0FH
	
      MOV A, P1
	ANL A, #0FH
      

      CJNE A,#1,RE;


SA:   ;CJNE A,#0001H,RE          ;
      ;SINCE THIS IS SA GENERATING SQUARE WAVE OF FREQUENCY 25Hz
      CPL P0.7;MADE 1 1960=7*250+4*50
      CALL DELAY_250US
	CALL DELAY_250US
      CALL DELAY_250US
	CALL DELAY_250US
	
      CALL DELAY_250US
	CALL DELAY_250US
	CALL DELAY_250US

	CALL DELAY_50US
	CALL DELAY_50US
	CALL DELAY_50US
	CALL DELAY_50US
      
      CPL P0.7; MADE 0
      
       CALL DELAY_250US
	CALL DELAY_250US
      CALL DELAY_250US
	CALL DELAY_250US
	
      CALL DELAY_250US
	CALL DELAY_250US
	CALL DELAY_250US

	CALL DELAY_50US
	CALL DELAY_50US
	CALL DELAY_50US
	CALL DELAY_50US

      AJMP INPUT;


RE:   CJNE A,#03,GA       ;
      ;SINCE THIS IS SA GENERATING SQUARE WAVE OF FREQUENCY 25Hz
      ;69 
      CPL P0.7
      MOV R5,#034
DELAY_RE:
      CALL DELAY_50US 
      DJNZ R5,DELAY_RE   
      CALL DELAY_25US 

      CPL P0.7
      MOV R5,#034
DELAY_RE0:
      CALL DELAY_50US 
      DJNZ R5,DELAY_RE0
      CALL DELAY_25US 

      AJMP INPUT;    

 


GA:   CJNE A,#07H,MA       ;
      ;SINCE THIS IS SA GENERATING SQUARE WAVE OF FREQUENCY 25Hz
       CPL P0.7
      MOV R5,#031
DELAY_GA:
      CALL DELAY_50US 
      DJNZ R5,DELAY_GA 
       
      CPL P0.7
      MOV R5,#031
DELAY_GA0:
      CALL DELAY_50US 
      DJNZ R5,DELAY_GA0
       
      AJMP INPUT;  

MA:   CJNE A,#15,INPUT       ;
      ;SINCE THIS IS SA GENERATING SQUARE WAVE OF FREQUENCY 25Hz
      CPL P0.7
      MOV R5,#029
DELAY_MA:
      CALL DELAY_50US 
      DJNZ R5,DELAY_MA  

      CPL P0.7
      MOV R5,#029
DELAY_MA0:
      CALL DELAY_50US 
      DJNZ R5,DELAY_MA0

      AJMP INPUT;    

 


RET
;time delays 

	
	
delay_1ms:
	push 00h
	mov r0, #4
	hE2: acall delay_250us
	djnz r0, hE2
	pop 00h
ret

delay_250us:
	push 00h
	mov r0, #5
	hE1: acall delay_50us
	djnz r0, hE1
	pop 00h
ret

delay_50us:
	push 00h
	mov r0, #43
	hE3: djnz r0, hE3
	pop 00h
ret

delay_25us:
	push 00h
	mov r0, #22
	hE0: djnz r0, hE3
	pop 00h
ret

END


 
