NUMX		DCD		0x4
NUMY		DCD		0x3
ANS		FILL		4
Start	MOV		SP,#0xFFFFFFFC		;initialise stack pointer
		MOV		R0,#0x100			;initialise memory area address
		LDR		R1,[R0]
		STR		R1,[SP,#-4]!		;store NumX to stack
		ADD		R0,R0,#4
		LDR		R1,[R0]
		STR		R1,[SP,#-4]!		;store NumY to stack
		ADD		R0,R0,#4
		STR		R0,[SP,#-4]!		;store address of Ans variable to stack
		BL		MySub
		LDR		R0,[SP,#-4]
		end
		
MySub	STMFD	SP!,{R0-R3}		;(s1) Save registers R0,R1,R2,R3
		LDR		R0,[SP,#0x18]		;(s2) Retrieve NumX from stack
		LDR		R1,[SP,#0x14]		;(s3) Retrieve NumY from stack
		;compute	value of NumX*NumY using successive addition
		MOV		R2,#0			;initialise result variable
		MOV		R3,R1			;loop counter set to NumY
Loop		ADD		R2,R2,R0			;add NumX to result
		SUBS		R3,R3,#1			;decrement loop counter
		BNE		Loop				;loop NumY times
		LDR		R3,[SP,#0x10]		;(s4a) Move the result directly to …
		STR		R2,[R3]			;(s4b) … the memory variable Ans
		LDMFD	SP!,{R0-R3}		;(s5) Restore saved registers
		
		Mov		PC,LR		; (s6) Return to calling program
