org 00h
ljmp MAIN
org 40h
MAIN:

;-------------------------TAKING INPUT FROM P1.3 to P1.0--------------------------------------------------------------	
		mov p1,#0fh
		setb p1.4
		CALL DELAY_5s
		clr p1.4
		clr a
		mov a,p1
		mov 71h,a //input cipher text, c = 9 stored in 71h (needs to be taken from input pins)

		mov 70h, #247 //modulus, n = 247 stored in 70h, value of n = 19*13 =247
	
		mov 72h, #05h //private key, d (generated previously) stored in 72h
		
;------------------------------COMPUTATION BEGINS----------------------------------------------------------------------	
		mov A, 71h //For c^d calculation give base value c
		mov B, 72h //For c^d calculation give exponent value d
		//16 bit result will be stored at 65h(MSByte) and 66h(LSByte)
		CALL A_exp_B
		//saving the result
		mov 50h,73h
		mov 51h,74h 

		CALL BA_mod_r0
		// a has the decrypted plain-text message i.e m = 10
		mov 73h, a //m is stored in 73h
		
;--------------DISPLAYING THE RESULT ON LEDs NIBBLE by NIBBLE MSB NIBBLE FIRST(IN ENDLESS LOOP) -----------

		
Here:	mov p1,#0fh
		mov a,73h
		anl a,#0f0h
		mov p1,a
		CALL DELAY_5s
		
		mov p1,#00h
		CALL DELAY_1s

		
		mov a,73h
		anl a,#0fh
		swap a
		mov p1,#0fh
		mov p1,a
		CALL DELAY_5s
		
		mov p1,#00h
		CALL DELAY_1s

		
		
		 JMP Here
		
;--------------------------------------------------------------------------------------------------------	

A_exp_B:
		mov 73h,#00h
		mov 74h,A
		mov 75h,A
		dec B
		mov r7,B
		up:	CALL MULT_16x8
		DJNZ r7,up
RET
;--------------------------------------------------------------------------------------------------------	
// STORE 16 bit no. at 73h(MSByte) and 74h(LSByte)
// STORE  8 bit no. at 75h
//16 bit result will be stored at 73h(MSByte) and 74h(LSByte)

MULT_16x8:
		mov A,74h
		mov B,75h
		mul AB
		mov 60h,B
		mov 61h,A
		
		mov A,73h
		mov B,75h
		mul AB
		mov 62h,A   // left shifting by 8
		mov 63h,#00h
		CALL ADD_16

RET
;--------------------------------------------------------------------------------------------------------
// STORE 16 bit no. at 60h(MSByte) and 61h(LSByte)
// STORE 16 bit no. at 62h(MSByte) and 63h(LSByte)
//16 bit result will be stored at 73h(MSByte) and 74h(LSByte)
ADD_16:	mov r3,60h 
		mov r4,61h
		mov r5,62h 
		mov r6,63h
		mov a,r4
		add a,r6
		mov 74h,a  //LSB PART
		mov a,r3
		addc a,r5
		mov 73h,a //MSB PART
		
RET	


;--------------------------------------------------------------------------------------------------------
// STORE 16 bit no. at 60h(MSByte) and 61h(LSByte)
// STORE 16 bit no. at 62h(MSByte) and 63h(LSByte)
//16 bit result will be stored at 65h(MSByte) and 66h(LSByte)
SUB_16:	
		mov r3,60h 
		mov r4,61h
		mov r5,62h 
		mov r6,63h
		mov a,r4
		clr c
		subb a,r6
		mov 66h,a  //LSB PART
		mov a,r3
		subb a,r5
		mov 65h,a //MSB PART	
RET	

;--------------------------------------------------------------------------------------------------------	
BA_mod_r0:
// saving original arguments inputs from 73h,74h and n value from 70h
		mov b, 73h
		mov a, 74h
		mov r0, 70h

;Mod n operation

		mov 60h,b
		mov 61h,a
		mov 62h,#00h
		mov 63h,r0
		
up1:	CALL SUB_16
		mov 60h,65h
		mov 61h,66h
		mov a,65h
		cjne a,#00h,up1
		mov a,66h
		subb a,r0
		jnc up1
		mov a,66h
        mov 73h, a		//Save output to 73h
RET
;-----------------------------------------------------------------------------------------------------------
DELAY_250us:
push 00h
mov r0,#0fah
back1:
	djnz r0,back1
pop 00h
RET

DELAY_10ms:
push 00h
mov r0,#40
back2:
	CALL DELAY_250us
	djnz r0,back2
pop 00h
RET

DELAY_1s: 
push 00h
mov r0,#100
back3:
	CALL DELAY_10ms
	djnz r0,back3
pop 00h
RET

DELAY_5s: 
push 00h
mov r0,#5
back4:
	CALL DELAY_1s
	djnz r0,back4
pop 00h
RET

END
