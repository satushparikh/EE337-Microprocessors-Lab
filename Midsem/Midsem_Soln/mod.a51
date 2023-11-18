org 00h
ljmp MAIN
org 100h
MAIN:
		
		mov 73h, #0CH
		mov 74h, #35H
		mov 75h, #0F7H
		
		
        CALL BA_mod_r0
		
		//display on LEDs function here
		Here: SJMP Here
		
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
// saving original arguments inputs from 73h,74h
		mov b, 73h
		mov a, 74h
		mov r0, 75h

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
        mov 73h, a		
RET

END