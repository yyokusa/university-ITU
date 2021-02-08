;########################;
;Yasin Yokus	150190739;
;########################;
index		EQU	0x06		               ;   index = 0 to index = 6  , array has 7 elements 
ArraySize	EQU	(index + 1) << 2               ;   ArraySize = 28 bytes    , 7 words x 4 bytes  
		AREA     My_Array, DATA, READWRITE     ;   Defined area will be placed to the readwrite memory
		ALIGN	                               ;   Make sure to execute next line 
y_array SPACE    ArraySize		               ;   Allocate space from memory for y
y_end
	
	AREA facto, code, readonly                 ;   Defined area will be placed to the readonly memory
	ALIGN                                      ;   Make sure to execute next line 
	THUMB
factor	FUNCTION
        ;; f_array[0] = 1
        MOVS    r2,#0               ; array traversing register for next avaliable array space arr[0]
        MOVS    r6, #1              ; r6 = 1,     here r6 used to hold temp value
        STR     r6, [r0, r2]        ; r0[0] = 1,    y_array[0] = 1
        ;; 
        ;; for i = 1 to index
        MOVS    r6,#1               ; i = 1,  for loop             , from 1 to index
_LOOP   CMP     r6, r1              ; loop condition,         r1 is index
        BGT     _stop               ; if (r6 > r1) { stop },  index is inclusive
        ;;
        ;;      f_array[i] = i * f_array[i - 1]
        ;;
        LDR     r7, [r0, r2]        ; get the y_array[i - 1] into r7
        MULS    r7, r6, r7          ; r7 = r7 * r6,     r7 = y_array[i - 1] * i
        ADDS    r2, #4              ; r2 += 4, increase array index for storing
        STR     r7, [r0, r2]        ; y_array[i] = r7,  (r7 = y_array[i - 1] * i) 
        ADDS    r6, #1              ; i += 1,         i from 1 to index
        B       _LOOP		    ; Branch Loop
        ;; return
_stop	BX      LR		    ; return
        ENDFUNC			    ; end of the function
;; function end

        AREA main, code, readonly
        ENTRY
        ALIGN
__main
        EXPORT	__main
        LDR      r0,=y_array       ; r0 holds array starting address (constraints)
        MOVS     r1,#index         ; r1 = index
        BL        factor           ; factorial(y_array, index), r0, r1
stop	B	  stop		   ; Branch stop, While(1)
    	NOP			   ; No operation
        END 			   ; End of the program