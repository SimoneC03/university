FIND_START	equ		0 ; string scan flags
FIND_END		equ		1
string		dcb		0x75,0x6e,0x6f,0x20,0x20,0x64,0x75,0x65,0x20,0x74,0x72,0x65,0x20,0x71,0x75,0x61,0x74,0x74,0x72,0x6f,0x0,0x0,0x0,0x0
words		fill		20*4
			mov		r0, #string
			mov		r1, #words
			mov		r2, #FIND_START
scan_loop
			ldrb		r3, [r0]
			cmp		r3, #0
			beq		end_
			cmp		r2, #FIND_START
			bne		find_end
			cmp		r3, #0x20 ; space char
			beq		c_scan_loop
			;		string start found
			str		r0, [r1], #4
			mov		r2, #FIND_END
			b		c_scan_loop
find_end
			cmp		r3,#0x20 ; space char
			bne		c_scan_loop
			mov		r4, #0x0
			strb		r4, [r0]
			mov		r2, #FIND_START
c_scan_loop
			add		r0,r0,#1
			b		scan_loop
end_
			end
			
			
			
