;########################;
;Yasin Yokus	150190739;
;########################;
limit		EQU	0x78		                   ;   limit 120
TRUE            EQU  1                                     ; TRUE = 1
FALSE		EQU  0	                                   ; FALSE = 0

primesSize	EQU	((limit + 1) << 2)               ;   ArraySize = (limit+1) * 4 bytes    , 7 words x 4 bytes  
isPrimeSize	EQU	(limit + 1) << 2               ;   ArraySize = (limit+1) * 4 bytes    , 7 words x 4 bytes 



;;; !!!!!!!!!y_array is primeNumbers array!!!!!!!!!!!!!
		AREA     Primes, DATA, READWRITE       ;   Defined area will be placed to the readwrite memory
		ALIGN	                               ;   Make sure to execute next line 
y_array SPACE    primesSize		               ;   Allocate space from memory for y
y_end

;;; !!!!!!!!!!!!!z_array is isPrimeNumber array!!!!!!!!!
		AREA     IsPrime, DATA, READWRITE      ;   Defined area will be placed to the readwrite memory
		ALIGN	                               ;   Make sure to execute next line 
z_array SPACE    isPrimeSize		           ;   Allocate space from memory for z
z_end


        AREA SieveS, code, readonly                 ;   Defined area will be placed to the readonly memory
        ALIGN                                      ;   Make sure to execute next line 
        THUMB
sieve	FUNCTION
        ;; FIRST LOOP START
        ;  r1    limit
        ;  r2    4 8 12 array traverse
        ;  r3    TRUE
        ;  r4    i = 0 1 2...
        ;  r5    y_array
        ;  r6    z_array
        ;  r7    0 (CONSTANT)
        ;;; for i = 0 to limit(inclusive)
        MOVS    r2,#0               ; array traversing 0 4 8 12 ...
        MOVS    r4,#0               ; i = 0,  for loop        , from 1 to limit
_LOOP_BIR   CMP     r4, r1              ; loop condition          , r1 is limit
        BGT     _stop_BIR               ; if (r4 > r1) { stop }   , limit is inclusive
        LDR     r7, =0              ; r7 = 0
        LDR     r3,=TRUE          ; r3 = TRUE
        STR     r7, [r5, r2]        ;;      primeNumbers[i] = 0
        STR     r3, [r6, r2]        ;;      isPrimeNumber[i] = true
        ADDS    r2, #4              ; r2 += 4   array mem traverse
        ADDS    r4, #1              ; r4 += 1,   i += 1
        B       _LOOP_BIR		        ; Branch Loop
_stop_BIR  ;; FIRST LOOP END
        



        ;; SECOND LOOP START
        ;  r0    i = 2 ..... i*i < limit
        ;  r2    '0' * i, '1' * i ........... and for j
        ;  r3    register for FALSE
        ;  r4    outer loop index*4 ile arrayi geziyor, isPrimeNumber[i] tutuyor, '0' * i, i*i + '1' * i, i*i + '2' * i,  (0 , 1, 2, 3)
        ;  r5    y_array
        ;  r6    z_array
        ;  r7    i*i < limit
        ;; for i = 2 to as long as i * i <= limit:
        MOVS    r0, #2               ; r0 -> i = 2, 3, 4, 5, 6 ... 
	MOVS    r7, r0               ; for multiplication
        MULS    r7, r0, r7           ; use r7 = i * i as temp to compare i * i < limit also for FALSE TRUE
_LOOP_IKI   CMP     r7, r1              ; loop condition          , r1 is limit
        BGT     _stop_IKI               ; if ( i*i > limit) { stop }   , limit is inclusive
        ;; first condition
        
        ;;if isPrimeNumber[i] then:
	MOVS    r4, #4       ; for multiplication
        MULS    r4, r0, r4           ; r4 = r0 * 4 -> 4, 8, 12, ...
        LDR     r4, [r6, r4]         ; r4 = [r6 r2], isPrimeNumber[i]
        LDR     r3,=TRUE             ; r3 = TRUE
        CMP     r4, r3               ; r4 ?==? TRUE
        BNE     _stop_IKI_INNER      ; 


        ;; LOOP IKI INNER LOOP
		MOVS    r4, #0                   ; keep track of (0 , 1, 2, 3)
		MOVS    r2, r4                   ; for multiplication
        MULS    r2, r0, r2                       ; '0' * i, '1' * i ...........
        ADDS    r2, r7, r2                       ; r2 = i * i + 0' * i,      We are merging "i*i" and  and X*i to get j
_LOOP_IKI_INNER   CMP r2, r1                     ; if r4(j)(i*i + X*i) < limit {isPrimeNumber[j] = FALSE}
        BGT _stop_IKI_INNER                      ; else do not enter the inner loop
        
	MOVS    r3, #4
	MULS    r2, r3, r2                 ; for memory acces using j = 2, 3   * 4
        LDR     r3,=FALSE                  ; r3 = FALSE
        STR     r3, [r6, r2]               ; isPrimeNumber[j] = r3(FALSE)

        ;; updates inner loop
	ADDS    r4, #1                   ; incr for '0' * i, '1' * i ...........
	MOVS    r2, r4                   ; for multiplication
        MULS    r2, r0, r2               ; '0' * i, '1' * i ...........
        ADDS    r2, r7, r2               ; r2 = i * i + 0' * i,      We are merging "i*i" and  and X*i to get j
        ;; updates inner loop end
        B       _LOOP_IKI_INNER 
_stop_IKI_INNER      
        
        ;; updates for outer loop
        ADDS    r0, #1               ; i += 1
		MOVS    r7, r0               ; for multiplication
        MULS    r7, r0, r7           ; use r7 = i * i as temp to compare i * i < limit also for FALSE TRUE
        ;; updates for outer loop end

		B       _LOOP_IKI                    ; branch outer loop
_stop_IKI



            ;; THIRD LOOP
            ;  r0    index = 0 to ...
            ;  r2    i = 2 to limit
            ;  r3    i*4 for array mem traversing
            ;  r5    y_array
            ;  r6    z_array
            MOVS    r0, #0                ; index
            MOVS    r2, #2                ; i
_LOOP_UC    CMP     r2, r1               ;; for i=2 to limit
            BGE     _stop_UC              ; if r2 > r1 Branch _stop_UC

            ;;if isPrimeNumber[i] then:
            MOVS    r3, #4              ; r3 = 4
            MULS    r3, r2, r3          ; i * 4 for array traversing
            LDR     r3, [r6, r3]        ; r3 = isPrimeNumber[i]
            LDR     r4,=TRUE          ; r4 = TRUE
            CMP     r3, r4              ; r3 ?==? TRUE
            BNE     _if_false              ; if not equal goto _if_false
            ;;                            else it is TRUE
	    MOVS    r3, #4              ; r3 = 4
            MULS    r3, r0, r3          ; index * 4 for array traversing
            STR     r2, [r5, r3]        ; primeNumbers[index] = i
            ADDS    r0, #1              ; index += 1
_if_false
            ADDS    r2, #1              ; i+=1
            B       _LOOP_UC            ; Branch loop uc
_stop_UC
_stop       BX	    LR          ;return
        ENDFUNC						; end of the function
;; function end



        AREA main, code, readonly
        ENTRY
        ALIGN
__main
        EXPORT	__main
        LDR      r5,=y_array       ; r5 holds primeNumbers array starting address (constraints)
        LDR      r6,=z_array       ; r6 holds isPrimeNumber array starting address (constraints)
        MOVS     r1, #limit        ; r1 = limit
        BL        sieve            ; sieve(limit), r1
stop	B	  stop		   ; Branch stop, While(1)
        END 			   ; End of the program