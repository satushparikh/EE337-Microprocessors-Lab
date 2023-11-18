org 00h
ljmp MAIN
org 100h
MAIN:
		
		mov 73h, #02H
		mov 74h, #71H
		mov 75h, #05H
		
        CALL MULT_16x8
		
		//display on LEDs function here
		Here: SJMP Here


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

END