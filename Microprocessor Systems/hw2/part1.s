;########################;
;Yasin Yokus	150190739;
;########################;
index		EQU	0x06		                   ;   index = 0 to index = 6  , array has 7 elements 
ArraySize	EQU	(index + 1) << 2               ;   ArraySize = 28 bytes    , 7 words x 4 bytes  



		AREA     My_Array, DATA, READWRITE     ;   Defined area will be placed to the readwrite memory
		ALIGN	                               ;   Make sure to execute next line 
y_array SPACE    ArraySize		               ;   Allocate space from memory for y
y_end
	
	AREA facto, code, readonly                 ;   Defined area will be placed to the readonly memory
	ALIGN                                      ;   Make sure to execute next line 
	THUMB
factor	FUNCTION
		PUSH	{r4, lr}	        ; pushing r4 and lr to stack so we dont loose their value
		MOVS	r4, r1		        ; r4 = r1
		CMP     r4, #1		        ; if n <= 1 {
		BLE	    making_one		        ; return 1 }
		SUBS	r1, r1, #1	        ; r1 -= 1
		BL	factor                  ; factorial(r1),        (( factorial (x - 1) ))
		MULS	r1, r4, r1		        ; r1 = r1 * r4,         factorial(n) = x * factorial (x - 1)
ending	POP     {r4, pc}	        ;return, pop necessary registers in order to get appropriate values
making_one
		MOVS	r1, #1			    ;for returning 1,  r1 = 1(r4)
		B		ending              ; return
	
	ENDFUNC							; end function




	
	AREA main, code, readonly
	ENTRY
	ALIGN
__main
	EXPORT	__main
	
	LDR     r5,=y_array    ; r5 holds array starting address (constraints)
	MOVS    r6,#0          ; i = 0,  for loop             , from 0 to index
	MOVS    r4,#index      ; array index to find factorial, from 0 to index
	MOVS    r3,#0          ; array traversing register
_LOOP   CMP     r6, r4     ; loop condition
	BGT     _stop          ; if (r6 > r7) { stop }
	MOVS	r1, r6	       ; r1 = i
	BL	factor	           ; r1 = factorial(i), function call
	ADDS	r6, #1         ; r6 += 1,           i += 1
	STR	r1, [r5, r3]       ; r5[i] = r1,        y_array[i] = factorial(i)
	ADDS	r3, #4         ; r8 += 4,           for next memory address in array
	B       _LOOP		   ; Branch Loop
	
_stop	B	  _stop		   ; Branch stop, While(1)
    END 				   ; End of the program
