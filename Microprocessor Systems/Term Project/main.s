;*******************************************************************************
;@file				 Main.s
;@project		     Microprocessor Systems Term Project
;@date				 31.01.2021
;
;@PROJECT GROUP
;@groupno 42
;@member1 Yasin Abdülkadir Yokus 150190739
;@member2 Oben Özgür 			 150190719
;@member3 Faruk Orak 	         150180058
;@member4 Yasin Enes Polat       150200733
;@member5 Ziya Kagan Zeydan      150200732
;*******************************************************************************
;*******************************************************************************
;@section 		INPUT_DATASET
;*******************************************************************************

;@brief 	This data will be used for insertion and deletion operation.
;@note		The input dataset will be changed at the grading. 
;			Therefore, you shouldn't use the constant number size for this dataset in your code. 
				AREA     IN_DATA_AREA, DATA, READONLY
IN_DATA			DCD		 0x10, 0x20, 0x15, 0x65, 0x25, 0x01, 0x01, 0x12, 0x65, 0x25, 0x85, 0x46, 0x10, 0x00
END_IN_DATA

;@brief 	This data contains operation flags of input dataset. 
;@note		0 -> Deletion operation, 1 -> Insertion 
				AREA     IN_DATA_FLAG_AREA, DATA, READONLY
IN_DATA_FLAG	DCD		 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x02
END_IN_DATA_FLAG


;*******************************************************************************
;@endsection 	INPUT_DATASET
;*******************************************************************************

;*******************************************************************************
;@section 		DATA_DECLARATION
;*******************************************************************************

;@brief 	This part will be used for constant numbers definition.
NUMBER_OF_AT	EQU		20									; Number of Allocation Table
AT_SIZE			EQU		NUMBER_OF_AT*4						; Allocation Table Size


DATA_AREA_SIZE	EQU		AT_SIZE*32*2						; Allocable data area
															; Each allocation table has 32 Cell
															; Each Cell Has 2 word (Value + Address)
															; Each word has 4 byte
ARRAY_SIZE		EQU		AT_SIZE*32							; Allocable data area
															; Each allocation table has 32 Cell
															; Each Cell Has 1 word (Value)
															; Each word has 4 byte
LOG_ARRAY_SIZE	EQU     AT_SIZE*32*3						; Log Array Size
															; Each log contains 3 word
															; 16 bit for index
															; 8 bit for error_code
															; 8 bit for operation
															; 32 bit for data
															; 32 bit for timestamp in us

;//-------- <<< USER CODE BEGIN Constant Numbers Definitions >>> ----------------------															
							


;//-------- <<< USER CODE END Constant Numbers Definitions >>> ------------------------	

;*******************************************************************************
;@brief 	This area will be used for global variables.
				AREA     GLOBAL_VARIABLES, DATA, READWRITE		
				ALIGN	
TICK_COUNT		SPACE	 4									; Allocate #4 byte area to store tick count of the system tick timer.
FIRST_ELEMENT  	SPACE    4									; Allocate #4 byte area to store the first element pointer of the linked list.
INDEX_INPUT_DS  SPACE    4									; Allocate #4 byte area to store the index of input dataset.
INDEX_ERROR_LOG SPACE	 4									; Allocate #4 byte aret to store the index of the error log array.
PROGRAM_STATUS  SPACE    4									; Allocate #4 byte to store program status.
															; 0-> Program started, 1->Timer started, 2-> All data operation finished.
;//-------- <<< USER CODE BEGIN Global Variables >>> ----------------------															
							
MAL_firstemptyoffset	SPACE 4							; Holds the offset value for the frist entry in AT with a 0 (unallocated space) in it.

;//-------- <<< USER CODE END Global Variables >>> ------------------------															

;*******************************************************************************

;@brief 	This area will be used for the allocation table
				AREA     ALLOCATION_TABLE, DATA, READWRITE		
				ALIGN	
__AT_Start
AT_MEM       	SPACE    AT_SIZE							; Allocate #AT_SIZE byte area from memory.
__AT_END

;@brief 	This area will be used for the linked list.
				AREA     DATA_AREA, DATA, READWRITE		
				ALIGN	
__DATA_Start
DATA_MEM        SPACE    DATA_AREA_SIZE						; Allocate #DATA_AREA_SIZE byte area from memory.
__DATA_END

;@brief 	This area will be used for the array. 
;			Array will be used at the end of the program to transform linked list to array.
				AREA     ARRAY_AREA, DATA, READWRITE		
				ALIGN	
__ARRAY_Start
ARRAY_MEM       SPACE    ARRAY_SIZE						; Allocate #ARRAY_SIZE byte area from memory.
__ARRAY_END

;@brief 	This area will be used for the error log array. 
				AREA     ARRAY_AREA, DATA, READWRITE		
				ALIGN	
__LOG_Start
LOG_MEM       	SPACE    LOG_ARRAY_SIZE						; Allocate #DATA_AREA_SIZE byte area from memory.
__LOG_END

;//-------- <<< USER CODE BEGIN Data Allocation >>> ----------------------															
							


;//-------- <<< USER CODE END Data Allocation >>> ------------------------															

;*******************************************************************************
;@endsection 	DATA_DECLARATION
;*******************************************************************************

;*******************************************************************************
;@section 		MAIN_FUNCTION
;*******************************************************************************

			
;@brief 	This area contains project codes. 
;@note		You shouldn't change the main function. 				
				AREA MAINFUNCTION, CODE, READONLY
				ENTRY
				THUMB
				ALIGN 
__main			FUNCTION
				EXPORT __main
				BL	Clear_Alloc					; Call Clear Allocation Function.
				BL  Clear_ErrorLogs				; Call Clear ErrorLogs Function.
				BL	Init_GlobVars				; Call Initiate Global Variable Function.
				BL	SysTick_Init				; Call Initialize System Tick Timer Function.
				LDR R0, =PROGRAM_STATUS			; Load Program Status Variable Addresses.
LOOP			LDR R1, [R0]					; Load Program Status Variable.
				CMP	R1, #2						; Check If Program finished.
				BNE LOOP						; Go to loop If program do not finish.
STOP			B	STOP						; Infinite loop.
				
				ENDFUNC
			
;*******************************************************************************
;@endsection 		MAIN_FUNCTION
;*******************************************************************************				

;*******************************************************************************
;@section 			USER_FUNCTIONS
;*******************************************************************************

;@brief 	This function will be used for System Tick Handler
SysTick_Handler	FUNCTION			
;//-------- <<< USER CODE BEGIN System Tick Handler >>> ----------------------															
				EXPORT SysTick_Handler	; export systick_handler
				
				PUSH {R4, LR}
				LDR r0, =IN_DATA		; start of operation input array
				LDR r1, =TICK_COUNT		; get tick count adress to r1
				LDR r2, =IN_DATA_FLAG	;
				LDR r1,[r1]				; get value of tick count to r1
				LSLS r1, #2				; r1 = r1*4 for memory manipulation
				LDR r2, [r2,r1]			; load operation flag to r2
				
				MOVS R4, #6				; Arg3 = Error Code = R4 = 6 If the incoming check fails, error code would be Invalid Operation
				CMP R2, #2				; Check if the operation flag is valid
				
				BHI STH_error			; Don't continue if opflag isn't valid, send out an error instead.
				
				; opflag is valid but its NOT vtable time, Thumb apparently cant branch to a register. (It can return to a register though)
				; LDR R0, [R0,R1]			; Load input value as Argument 1 (R0)
				; LDR R3, =STH_vtable		; R3 = STH_vtable
				; LSLS R2,#2				; R2 *= 4
				; LDR R3,[R3,R2]			; R3 = STH_vtable[R2]
				; BL R3					; Call whatever function operation code corresponds to.
				
;STH_vtable		DCD Remove, Insert, LinkedList2Arr
				
				; Do it the boring way instead
				LDR R0, [R0,R1]			; Load input value as Argument 1 (R0)
				
				PUSH {R1}				;
				CMP R2, #1				;
				BHI STH_case2			; if(1 < opflag && opflag =< 2) goto case2;
				BEQ STH_case1			; else if(opflag == 1)			goto case1;
STH_case0		BL Remove				; else { Remove(IN_DATA[*TICK_COUNT])
				POP {R1}				;
				B STH_checkerror		; Check for errors & Return
STH_case1		BL Insert				; case1: Insert(IN_DATA[*TICK_COUNT])
				POP {R1}				;
				B STH_checkerror		; Log any errors & Return
STH_case2		BL LinkedList2Arr		; case2: LinkedList2Array(IN_DATA[*TICK_COUNT])
				POP {R1}				;
				B STH_checkerror		; Log any errors & Return
				
STH_checkerror	CMP R0,#0				; 
				BEQ STH_return			; if(Return Value != 0){
				MOV R4, R0				; 	R4 = Error Code = Return Value
				LDR R0, =IN_DATA		; 	R0 = IN_DATA
				
STH_error		MOVS R3, R0				; 	Load input data as Argument 4 (R3)
				LSRS R1, #2				; 	Index was multiplied by 4 to make indexing easier, divide by 4 to accomodate.
				MOVS R0, R1				; 	Load Index as Argument 1 (R0)
				MOVS R1, R4				; 	Load Error Code(=R4) as Argument 2 (R1)
				BL WriteErrorLog		; 	WriteErrorLog(Index,6,opflag,data)	; (opflag has been loaded as arg3 during the initial opflag validity check)
										; }
STH_return      LDR R0, =TICK_COUNT		; R0 = TICK_COUNT		//
				LDR R1, [R0]			; R1 = *TICK_COUNT		//
				ADDS R1,#1				; R1++					//
				STR R1, [R0]			; *TICK_COUNT = R1		// TICK_COUNT++
				
				LDR R0, =IN_DATA        ; R0 = IN_DATA
                LDR R2, =END_IN_DATA    ; R2 = IN_DATA_END
                SUBS R2,R2,R0           ; R2 = IN_DATA_END - IN_DATA
                LSRS R2,#2              ; R2 = (IN_DATA_END - IN_DATA) / 4 = number of data
                CMP R1, R2              ;
                BNE STH_notlasttick     ; if(R1==R2){
				
				; LDR R2, =PROGRAM_STATUS	;
                ; MOVS R1, #2				;set program status 2
                ; STR R1, [R2]				;store program status
				; This is done by SysTick_Stop, no need to do here too.
				
				BL SysTick_Stop			; 	SysTick_Stop(); }
STH_notlasttick POP {R4, PC}			; return	

;//-------- <<< USER CODE END System Tick Handler >>> ------------------------				
				ENDFUNC


;*******************************************************************************				

;@brief 	This function will be used to initiate System Tick Handler
SysTick_Init	FUNCTION			
;//-------- <<< USER CODE BEGIN System Tick Timer Initialize >>> ----------------------	
	

				LDR R0, =0xE000E010		;load systick control and status register address
				LDR R1, =11695			;load reload value to r1
				STR R1,[R0, #4]			;store reload value to reload value register	
				MOVS R1,#0				;clear r1
				STR R1,[R0, #8]			;clear current value register
				MOVS R1,#7				;set enable,control and interrupt flags
				STR R1,[R0]				;store r1 to systickCSR register
				LDR R0, =PROGRAM_STATUS ;address of PROGRAM_STATUS
				MOVS R1,#1				;set program status to start
				STR R1,[R0]				;load program status
				BX LR					;return
;//-------- <<< USER CODE END System Tick Timer Initialize >>> ------------------------				
				ENDFUNC

;*******************************************************************************				

;@brief 	This function will be used to stop the System Tick Timer
SysTick_Stop	FUNCTION			
;//-------- <<< USER CODE BEGIN System Tick Timer Stop >>> ----------------------	
				LDR R0, =0xE000E010		;load systick control and status register address
				MOVS R1,#0				;clear control and interrupt flags
				STR R1,[R0]				;store value control and status register address
				LDR R0, =PROGRAM_STATUS ;address of PROGRAM_STATUS
				MOVS R1,#2				;set program status tp finished
				STR R1,[R0]				;load program status
				BX LR					;return
;//-------- <<< USER CODE END System Tick Timer Stop >>> ------------------------				
				ENDFUNC

;*******************************************************************************				

;@brief 	This function will be used to clear allocation table
Clear_Alloc		FUNCTION			
;//-------- <<< USER CODE BEGIN Clear Allocation Table Function >>> ----------------------															
				LDR R0, =__AT_Start		;load start addres of allocation table to r0
				LDR R1, =__AT_END		;load end addres of allocation table to r1
				LDR R2, =0				;value to be loaded
				B ca_FOR_START			;branch to for_start
ca_LOOP			STR R2,[R0]				;load 0 to adress of r0
				ADDS R0,R0,#4			;r0++ for iteration
ca_FOR_START	CMP R0, R1				;cmp adrress of r0 and end adres
				BLT ca_LOOP				;if ro<end_address loop over
				BX LR					;return
;//-------- <<< USER CODE END Clear Allocation Table Function >>> ------------------------				
				ENDFUNC
				
;*******************************************************************************		

;@brief 	This function will be used to clear error log array
Clear_ErrorLogs	FUNCTION			
;//-------- <<< USER CODE BEGIN Clear Error Logs Function >>> ----------------------															
				LDR R0, =__LOG_Start	;load start addres of error log table to r0
				LDR R1, =__LOG_END		;load end addres of error log table to r1
				LDR R2, =0				;value to be loaded
				B ce_FOR_START			;branch to for_start
ce_LOOP			STR R2,[R0]				;load 0 to adress of r0
				ADDS R0,R0,#4			;r0++ for iteration
ce_FOR_START	CMP R0, R1				;cmp adrress of r0 and end adres
				BLT ce_LOOP				;if ro<end_address loop over
				BX LR					;return
;//-------- <<< USER CODE END Clear Error Logs Function >>> ------------------------				
				ENDFUNC
				
;*******************************************************************************

;@brief 	This function will be used to initialize global variables
Init_GlobVars	FUNCTION			
;//-------- <<< USER CODE BEGIN Initialize Global Variables >>> ----------------------	
				LDR R0, =TICK_COUNT		;load start addres of global variables to r0
				LDR R1, =MAL_firstemptyoffset	;load end addres of global variables to r1
				LDR R2, =0				;value to be loaded
				B ig_FOR_START			;branch to for_start
ig_LOOP			STR R2,[R0]				;load 0 to adress of r0
				ADDS R0,R0,#4			;r0++ for iteration
ig_FOR_START	CMP R0, R1				;cmp adrress of r0 and end adres
				BLE ig_LOOP				;if ro<end_address loop over
				BX LR					;return
;//-------- <<< USER CODE END Initialize Global Variables >>> ------------------------				
				ENDFUNC
				
;*******************************************************************************	

;@brief 	This function will be used to allocate the new cell 
;			from the memory using the allocation table.
;@return 	R0 <- The allocated area address
Malloc			FUNCTION			
;//-------- <<< USER CODE BEGIN System Tick Handler >>> ----------------------	
				PUSH {R4,R5,R6,R7}
				LDR R0, =AT_MEM
				LDR R2, =AT_SIZE-4				; Last valid offset for AT. There isn't a "Lower Than" condition in Thumb, so we need to use Lower or Same (aka BLS).
				LDR R1, =MAL_firstemptyoffset	; r1 = &STR_firstemptyoffset
				LDR R1, [R1]					; r1 = *r1 = STR_firstemptyoffset
				
				CMP R1, R2						; vvv
				BLS MAL_noerrors				; if(!(MAL_firstemptyoffset < AT_size )){
				MOVS R0, #0						; 	// We've got no space!
				POP {R4,R5,R6,R7}				; 	return 0;
				BX LR							; }
				
MAL_noerrors	
				; Load the block onto R3 & R6
				MOVS R5, #0						; R5 = result
				LDR R3, [R0,R1]					; R3 = AT[STR_firstemptyoffset]
				MOVS R6, R3						; Make a backup at R6 [alloc(r6)]
				MVNS R3, R3						; R3 = ~AT[STR_firstemptyoffset]
				
				; Find the first 0 bit of the block
				LDR R4, =0x0000FFFF			;
				TST R3, R4					;
				BNE MAL_skip1				; if (!(R3 & 0x0000FFFF)){ // first empty space is in the more significant half
				ADDS R5, R5, #16			;	R5 += 16;
				LSRS R3, #16				;	R3 >>= 16;	}
				
MAL_skip1		LDR R4, =0x000000FF			;
				TST R3, R4					;
				BNE MAL_skip2				; if (!(R3 & 0x000000FF)){ // first empty space is in the more significant quarter
				ADDS R5, R5, #8				;	R5 += 8;
				LSRS R3, #8					;	R3 >>= 8;	}
				
MAL_skip2		LDR R4, =0x0000000F			;
				TST R3, R4					;
				BNE MAL_skip3				; if (!(R3 & 0x0000000F)){ // first empty space is in the more significant 1/8th
				ADDS R5, R5, #4				;	R5 += 4;
				LSRS R3, #4					;	R3 >>= 4;	}
				
MAL_skip3		LDR R4, =0x00000003			;
				TST R3, R4					;
				BNE MAL_skip4				; if (!(R3 & 0x00000003)){ // first empty space is in the more significant 1/16th
				ADDS R5, R5, #2				;	R5 += 2;
				LSRS R3, #2					;	R3 >>= 2;	}
				
MAL_skip4		LDR R4, =0x00000001			;
				TST R3, R4					;
				BNE MAL_skip5				; if (!(R3 & 0x00000001)){ // first empty space is in the more significant 1/32th
				ADDS R5, R5, #1				;	R5 += 1;
				LSRS R3, #1					;	R3 >>= 1;	}
				
MAL_skip5		; R5 now holds the location of the first nonzero bit, 0-indexed obviously this isnt Lua or MATLAB
				MOVS R3, R6			; Restore R3 using the backup.
				MOVS R6,#0x1		; r6 = 0x1
				LSLS R6,R5			; R6 = (1<<r5)
				ORRS R3, R6			; R3 |= (1<<R5)		// Set the bit for the space we are allocating [DEALLOC R6]
				STR R3, [R0,R1]		; AT[STR_firstemptyoffset] = R3
				
				MOVS R7, R1				; Make a backup of R1(=MAL_firstemptyoffset) @ R7
				LSLS R1, #6				; R1=firstemptyblock*64		// every byte in AT corresponds to 64 bytes
				LSLS R5,#3				; R5=r5*2	// every bit corresponds to 8 bytes
				LDR R0, =DATA_MEM		; R0 = DATA_MEM
				ADDS R0, R5, R0			; R0 = DATA_MEM + r5*8
				ADDS R0, R1, R0			; R0 = DATA_MEM + r1*64 + r5*8
				
				; We dont need to update STR_firstemptyoffset if its still empty.
				LDR R6, =0xFFFFFFFF		;
				CMP R3, R6				; if(R3 != 0xFFFFFFFF)
				BEQ MAL_findnextblock	; {
				
				POP {R4,R5,R6,R7}		; 	return _DATA_Start + r1*64 + r5*8
				BX LR					; }
				
				
MAL_findnextblock	; Find the first block with unallocated 
				MOVS R1, R7				; Reload from backup
				LDR R7, =AT_MEM			; R7 = AT_MEM
				; r1 already has the offset of the (now filled) starting block
				B MAL_l1_start		; {
MAL_l1_loop		LDR R3, [R7,R1]		; Load AT[i] to R3
				MVNS R3, R3			; Set condition registers
				BNE MAL_found		; if(~AT[i]) goto found;
				
				ADDS R1,R1,#4		; i+=4
				
MAL_l1_start	CMP R1,R2			; if(R1<=R2) 
				BLE MAL_l1_loop		;	continue;
				
MAL_found		LDR R3, =MAL_firstemptyoffset	;
				STR R1, [R3]					; STR_firstemptyoffset = R1
				POP {R4,R5,R6,R7}				;
				BX LR							; return
;//-------- <<< USER CODE END System Tick Handler >>> ------------------------				
				ENDFUNC

				
;*******************************************************************************				

;@brief 	This function will be used for deallocate the existing area
;@param		R0 <- Address to deallocate
Free			FUNCTION			
;//-------- <<< USER CODE BEGIN Free Function >>> ----------------------
				PUSH {R4}
				
				LDR R1, =DATA_MEM		; R1 = DATA_MEM
				SUBS R0, R0, R1			; R0 = Target offset = (address - DATA_Mem)
				LSRS R0, #3				; R0 = Cell index = Address / 8 bytes per cell 
				MOVS R1, R0				; R1 = R0 (will be turned into the bit index)
				LSRS R0, #5				; R0 = AT block index = Cell index / 32 cells per AT word
				MOVS R2, #0x1F			; 
				ANDS R1, R2				; R1 = AT bit index = (Cell index) % (32 cells per word) = Cell index & 0x1F
				LSLS R0, #2				; R0 = AT block offset = AT block index * 4 bytes per word
				
				; Check and update MAL_firstemptyoffset if necessary.
				LDR R3, =MAL_firstemptyoffset	; R3 = MAL_firstemptyoffset
				LDR R2, [R3]					; R2 = *MAL_firstemptyoffset
				CMP R0, R2						; if(AT_block_offset < MAL_firstemptyoffset)	// if firstemptyoffset needs to be updated
				BGE	FRE_noupdate				; {
				
				STR R0, [R3]					;	*MAL_firstemptyoffset = AT_block_offset;
												; }
FRE_noupdate	LDR R3, =AT_MEM
				ADDS R0, R3						; R0 = AT block address = AT_MEM + AT block offset
				LDR R3, [R0]					; R3 = *(AT block address)
				
				MOVS R4, #1						; R4 = 1
				LSLS R4, R1						; R4 = (1<<R1) = (1 << AT_bit_index)
				MVNS R4, R4						; R4 = ~R4
				ANDS R3, R4						; R3 |= R4 = ~(1 << AT_bit_index)
				STR R3, [R0]					; AT[AT block index] &= ~(1 << AT_bit_index)  <=>  AT[AT block index] = R3
				
				POP {R4}						;
				BX LR							; return;
;//-------- <<< USER CODE END Free Function >>> ------------------------				
				ENDFUNC

;*******************************************************************************				

;@brief 	This function will be used to insert data to the linked list
;@param		R0 <- The data to insert
;@return    R0 <- Error Code
Insert			FUNCTION			
;//-------- <<< USER CODE BEGIN Insert Function >>> ----------------------		

				;this part is for checking if there is enough space to insert or not
				PUSH {LR}				;push lr
				PUSH {R0}				;push value to stack
				BL Malloc				;allocate memory
				LDR R1,=0				;load 0 to r1 for comparison
				CMP R0,R1				;compare r0 and r1
				BNE not_full			;if there is allocable area go to not_full
				POP	{R0}				;pop value to be inserted
				LDR R0,=1				;load r0 "0" as return value
				POP {PC}				;return with value of "0"
				
				
				;this part is for insertion to an empty list
not_full		BL Free					;free the allocated memory it wil be reallocated later
				LDR R1, =FIRST_ELEMENT	;load the adress of the first element to r1
				LDR R3,[R1]				;load head adress
				LDR R2, =0				;load 0 to r2 for comparison
				CMP R3, R2				;check if the list is empty
				BNE	not_empty			;if not empty continue
				BL Malloc 				;allocate memory
				LDR R1, =FIRST_ELEMENT	;load the adress of the first element to r1 (in case it has changed)
				STR R0,[R1]				;set first element adress as adress of allocated area
				POP {R0}				;get the value to be inserted
				LDR R2,[R1]				;load the head address to r2
				STR R0,[R2]				;store the given value as head
				LDR R0, =0				;load r0 to "0" as null pointer (ALSO AS SUCCESFULLY ADDED INDICATOR)
				STR R0, [R2,#4]			;load null address as next element
				POP {PC}				;return with value of "0"


				;this part is for insertion as head to a non empty list
not_empty		POP {R0}				;pop value to be inserted
				LDR R1, =FIRST_ELEMENT	;load the adress of the first element to r1
				LDR R3,[R1]				;load head adress
				LDR R2, [R3]			;store r2 head value of the list
				CMP R0, R2				;compare r0 and r2
				BEQ duplicate			;if equal go to duplicate
				BGT traverse			;if value to be insterted is greater than head value branch to larger than head
				PUSH {R3}				;push head adress
				PUSH {R0}				;push value to be inserted
				BL Malloc 				;allocate memory
				LDR R1, =FIRST_ELEMENT	;load the adress of the first element to r1 (in case it has changed)
				STR R0, [R1]			;store allocated adress as head adress
				POP {R2} 				;pop value to be inserted to r2
				POP {R3}				;pop previous head's adress to r3
				STR R2, [R0]			;store value to be inserted to new head
				STR R3, [R0,#4]			;store previous head adress as next adress to new head
				LDR R0, =0				;load r0 "0" as return value
				POP {PC}				;return with value of "0"
				
				
				;this part is for traversing the list for duplicate values
traverse		LDR R3, =FIRST_ELEMENT	;load the adress of the first element to r3	
				LDR R1,[R3]				;load head adress
				LDR R2,[R1,#0]			;r2 stores the current element's value
				LDR R3,[R1,#4]			;r3 stores the next adress
next_element	CMP R0, R2				;compare value to be inserted and current value
				BEQ duplicate			;if equal branch to duplicate
				CMP R3, #0				;compare r3 and 0
				BEQ end_of_list			;if equal (NULL) branch to end_of_list
				MOVS R1, R3				;get r1 current element's adress
				LDR R2,[R3,#0]			;get next address' value to r2
				LDR R3,[R3,#4]			;get next adress's next adress to r3
				B next_element			;iterate
				
				;this is for returning with duplicate error code
duplicate		LDR R0, =2				;load 2 to r0 as error code
				POP {PC}					;return with value of "2"

				;this is for checking if insertion is going to be at the end
end_of_list		CMP R0, R2				;compare the last element of the list with value to be inserted
				BGT	insert_to_end		;if greater branch to insert to end
				B insert_inside			;if not branch to inser_inside
		
		
				;this the part for insertion to end
insert_to_end	PUSH {R0}				;push value to stack
				PUSH {R1}				;push last element's adress to stack
				BL Malloc				;allocate cell
				POP {R1}				;pop last element's adress to r1
				STR R0,[R1,#4]			;load last element's next adress as to allocated area
				MOVS R1, R0				;move allocated area's adress to r1
				POP {R0}				;pop value to be inserted from stack
				STR R0,[R1,#0]			;load value to be inserted to the allocated area's value
				LDR R0, =0;				;load r0 "0" as NULL pointer
				STR R0,[R1,#4]			;load NULL adress to next adress since it is the last element
				LDR R0, =0;				;load r0 "0" as return value
				POP {PC}					;return
				
				;this is for insertion to inside
insert_inside	LDR R3, =FIRST_ELEMENT	;load the adress of the first element to r3	
				LDR R3,[R3]				;load head adress to r3
next_one		PUSH {R3}				;push current adress
				LDR R3,[R3,#4]			;get next adress's next adress to r3
				LDR R2,[R3,#0]			;get next address' value to r2
				CMP R0, R2				;compare value to be inserted and current value
				BLT insert_it 			;if equal branch to duplicate
				POP {R1}				;pop current current adress to r1, it is redundant and won't be used
				B next_one				;iterate
				
				
insert_it		POP {R3}				;pop element's adress before the inserted one
				PUSH {R0}				;push the value to be inserted to stack
				PUSH {R3}				;push element's adress before the inserted one
				BL Malloc				;allocate memory
				POP {R3}				;pop element's adress before the inserted one 
				LDR R1,[R3,#4]			;get the element's adress that comes after the inserted node to r1
				STR R0,[R3,#4]			;put current node's next adress the allocated memory's adress
				POP {R2}				;pop value to be inserted to r2
				STR R2,[R0,#0]			;put value to be inserted to allocated cell
				STR R1,[R0,#4]			;put allocated cell's next adress the correspoing adress (r1)
				LDR R0, =0;				;load r0 "0" as return value
				POP {PC}				;return
				

;//-------- <<< USER CODE END Insert Function >>> ------------------------				
				ENDFUNC
				
;*******************************************************************************				

;@brief 	This function will be used to remove data from the linked list
;@param		R0 <- the data to delete
;@return    R0 <- Error Code
Remove			FUNCTION			
;//-------- <<< USER CODE BEGIN Remove Function >>> ----------------------															
				;Error codes: 3 -> Linked list is empty, 4 -> Element is not found
				
				LDR 	r1, =FIRST_ELEMENT
				
				LDR		r1, [r1, #0]			;FIRST_ELEMENT's pointed address
				CMP		r1, #0					;empty check
				BEQ		EMPTY_LST_ERR
				LDR		r3, [r1, #0]			;load first element's value into r3
				

				;If element will be removed is first element
				CMP		r3, r0
				BEQ		DELETE_FIRST
				
				MOVS	r2, r1					;r2 = previous element's starting address
				LDR		r1, [r1, #4]			;First element's next pointer's pointed address
				LDR		r3, [r1, #0]			;load element's value into r3
				
EQUALITY_Check	CMP		r3, r0
				BEQ		DELETE_ELEMENT
				MOVS	r2, r1					;r2 = previous element's starting address
				LDR		r1, [r1, #4]			;r1 = r1's next pointer value
				CMP		r1, #0					;End of list check
				BEQ		NOT_FOUND_ERR
				LDR		r3, [r1, #0]
				B		EQUALITY_Check
				
NOT_FOUND_ERR	MOVS	r0, #4				;Returns error code for adding new element to error log table
				BX		LR
				
EMPTY_LST_ERR	MOVS	r0, #3				;Returns error code for adding new element to error log table
				BX		LR
				
DELETE_FIRST	LDR 	r4, =FIRST_ELEMENT	
				LDR		r5, [r1, #4]		;r5 = Next pointer value of element which will be removed
				STR		r5, [r4, #0]		;FIRST_ELEMENT's pointed address = r5
				MOVS	r0, r1				;r0 = removed (done) elements memory address
				PUSH {LR}					;Pushing LR to stack, prevent it to be changed after returning from Free
				BL		Free				;Calling Free function to deallocate memory area
				MOVS	r0, #0				;r0 = success code(?)
				POP {PC}					;Returning to caller funtion

DELETE_ELEMENT	LDR		r4, [r1, #4]		;r4 = removed (not yet) element's next pointer value
				STR		r4, [r2, #4]		;r2 = previous.next = r4
				MOVS	r0, r1				;r0 = removed (done) elements memory address
				PUSH {LR}					;Pushing LR to stack, prevent it to be changed after returning from Free
				BL		Free				;Calling Free function to deallocate memory area
				MOVS	r0, #0				;r0 = success code(?)
				POP {PC}					;Returning to caller funtion
;//-------- <<< USER CODE END Remove Function >>> ------------------------				
				ENDFUNC
				
;*******************************************************************************				

;@brief 	This function will be used to clear the array and copy the linked list to the array
;@return	R0 <- Error Code
					ALIGN
LinkedList2Arr		FUNCTION			
					
;//-------- <<< USER CODE BEGIN Linked List To Array >>> ----------------------		
					PUSH {LR}
					LDR r0, =FIRST_ELEMENT
					LDR r0, [r0]
					CMP r0,#0
					BEQ ERROR_LL2A
				
					LDR r0, =__ARRAY_Start	;load start addres of allocation table to r0
					LDR r1, =__ARRAY_END	;load end addres of allocation table to r1
					MOVS r2, #0				;value to be loaded
					B LL2A_CLEAR_START		;branch to for_start
CLEAR_LL2A			STR r2,[r0]				;load 0 to adress of r0
					ADDS r0,r0,#4			;r0++ for iteration
LL2A_CLEAR_START	CMP r0, r1				;cmp adrress of r0 and end adres
					BLT CLEAR_LL2A			;if ro<end_address loop over
				
					LDR r0, =FIRST_ELEMENT
					LDR r1, =__ARRAY_Start 
LOOP_LL2A			LDR r0,[r0]				;take the address of the variable
					LDR r2,[r0]				;take the data from LL
					STR r2, [r1]			;store data to array
					ADDS r0,#4				;take the address of the memory cell that keeps next variable's address
					ADDS r1,#4				;next array memory cell
					LDR r2,[r0]				;take the next address
					CMP r2,#0				;if the next address is not null
					BNE LOOP_LL2A			;Go LOOP
					MOVS r0, #0
					POP {PC}
					
ERROR_LL2A			MOVS r0, #5
					POP {PC}
;//-------- <<< USER CODE END Linked List To Array >>> ------------------------				
					
					ENDFUNC
					ALIGN
				
;*******************************************************************************				



;@brief 	This function will be used to write errors to the error log array.
;@param		R0 -> Index of Input Dataset Array
;@param     R1 -> Error Code 
;@param     R2 -> Operation (Insertion / Deletion / LinkedList2Array)
;@param     R3 -> Data
WriteErrorLog	FUNCTION			
;//-------- <<< USER CODE BEGIN Write Error Log >>> ----------------------															
				PUSH {r4, r5, lr}           ; we will use r4
				
				LDR  r4, =INDEX_ERROR_LOG    ; get address of the index of the error log array.
				LDR r4, [r4,#0]				; get value of the index of the error log array.
                LSLS r4, #2    ; get address of the index of the error log array.
				LDR R5, =3 		; r5 = 3
                MULS r4, R5, R4    ; get address of the index of the error log array.
				LDR R5, =__LOG_Start		; load start addres of log table to r5
				ADDS r4, r5;				 ; r4 = (load start addres + 323index)

				LDR r5, =__LOG_END		; load end addres of log table to r5
				CMP r4, r5				; cmp adrress of r4 and end adres
				BGE we_exit			    ; if r4 >= end_address return
				; else do writing error log
				; each word has 32 bits
				; writing Index          -> 16bit -> half word
				STRH r0, [r4]            ; halfword store the address of the index of the dataset to the index of the error log array.
				ADDS r4, #2              ; incr mem for a half word
				; writing ErrorCode      -> 8bit  -> 1/4 word
				STRB r1, [r4]            ; byte store the error code to index of the error log array.
				ADDS r4, #1              ; incr mem for a byte
				; writing Operation      -> 8bit  -> 1/4 word
				STRB r2, [r4]            ; byte store the op code to index of the error log array.
				ADDS r4, #1              ; incr mem for a byte
				; writing Data           -> 32bit -> 1 word
				STR  r3, [r4]            ; word store the data to the index of the error log array.
				ADDS r4, #4              ; incr mem for a  word
				; writing TimeStamp      -> 32bit -> 1 word
				BL    GetNow              ; call GetNow, timestamp is stored in r0
				STR  r0, [r4]            ; word store the timestamp to the index of the error log array.
				ADDS r4, #4              ; incr mem for a  word
				; index error log update for next record
				LDR r4, =INDEX_ERROR_LOG
				LDR r4, [r4,#0]
				ADDS r4, #1				; write updated value back into INDEX_ERROR_LOG
				LDR r5, =INDEX_ERROR_LOG
				STR r4, [r5,#0]
we_exit
				POP {r4, r5, pc}                ; pop vals from stack
;//-------- <<< USER CODE END Write Error Log >>> ------------------------				
				ENDFUNC
	
;@brief 	This function will be used to get working time of the System Tick timer
;@return	R0 <- Working time of the System Tick Timer (in us).			
GetNow			FUNCTION			
;//-------- <<< USER CODE BEGIN Get Now >>> ----------------------															
				LDR  r0, =TICK_COUNT		; get tick count adress to r0
				LDR  r0, [r0]			; get value of tick count to r0
				LDR  r1, =11695             ;load reload value to r1
				MULS r0, r1, r0				; TICK_COUNT * reload value
				LDR  r2, =0xE000E018     ; get the address for SYST_CVR, SysTick Current Value Register
				LDR  r2, [r2]            ; get the value for SYST_CVR, SysTick Current Value Register 
				ADDS r0, r2              ; r0 = (TICK_COUNT * reload value) + SYST_CVR, returns in microseconds (clock period and SYST_CVR)
				LSRS r0, #4				;r0 /= 16
				BX   LR						;return
;//-------- <<< USER CODE END Get Now >>> ------------------------
				ENDFUNC
				
;*******************************************************************************	

;//-------- <<< USER CODE BEGIN Functions >>> ----------------------															


;//-------- <<< USER CODE END Functions >>> ------------------------

;*******************************************************************************
;@endsection 		USER_FUNCTIONS
;*******************************************************************************
				ALIGN
				END		; Finish the assembly file
				
;*******************************************************************************
;@endfile 			main.s
;*******************************************************************************				

