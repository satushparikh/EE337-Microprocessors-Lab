org 00h
ljmp MAIN
org 100h
MAIN:
		
		mov 71h,#173 //public key, e = 173 stored in 71h
		mov 70h, #216 //totient, x = 216 stored in 70h
		
		mov r2,#00h
above:	inc r2
		mov a, 70h
		mov b,r2
		mul ab //x*i for each value of r2 from 1 to 255
		mov 60h,b
		mov 61h,a
		mov 62h,#00h
		mov 63h,#01h
		CALL ADD_16 
		CALL BA_mod_r0
		JNZ above
		// b has the private key i.e d = 5
		mov 72h,b //d is stored in 72h
		
;For Displaying on board
;Puput 5sec and Pause 1sec
		mov a,72h
		mov P1,a
		CALL DELAY_5s
		mov P1, #0
		CALL DELAY_1s
		swap a
		mov P1,a
		CALL DELAY_5s
		mov P1, #0
		CALL DELAY_1s
		
		//display on LEDs function here
		Here: SJMP Here
	
;--------------------------------------------------------------------------------------------------------	

;--------------------------------------------------------------------------------------------------------	

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
//16 bit result will be stored at 74h(MSByte) and 73h(LSByte)
SUB_16:	
		mov r3,60h 
		mov r4,61h
		mov r5,62h 
		mov r6,63h
		mov a,r4
		clr c
		subb a,r6
		mov 73h,a  //LSB PART
		mov a,r3
		subb a,r5
		mov 74h,a //MSB PART	
RET	
;--------------------------------------------------------------------------------------------------------	
BA_mod_r0:
// b holds the quotient and a the remainder
// saving original arguments
; Take 16 bit input from 73h 74h and e value from 71h
		push 02h
		mov b,73h
		mov a,74h
		mov r0, 71h
		mov r2,#00h
		mov 60h,b
		mov 61h,a
		mov 62h,#00h
		mov 63h,r0
		
up1:	inc r2
		CALL SUB_16
		mov 60h,74h
		mov 61h,73h
		mov a,74h
		cjne a,#00h,up1
		mov a,73h
		subb a,r0
		jnc up1
		mov a,73h
		mov b,r2
		pop 02h
RET
;--------------------------------------------------------------------------------------------------------		
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

DELAY_10s: 
push 00h
mov r0,#10
back5:
	CALL DELAY_1s
	djnz r0,back5
pop 00h
RET
END