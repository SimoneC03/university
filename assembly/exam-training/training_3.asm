			;		find the first occurrence of a string
string1		dcb		0x65,0x66,0x67,0x68,0x0,0x0,0x0,0x0
string2		dcb		0x66,0x67,0x0,0x0
			mov		r1, #string1
			mov		r2, #string2
			mov		r5, #0 ; address of found substring
scan_loop
			ldrb		r3, [r1]
			ldrb		r4, [r2]
			cmp		r3,r4
			beq		check
			cmp		r3, #0
			beq		end_
			cmp		r4, #0
			beq		end_
			add		r1,r1,#1
			;		add		r2,r2,#1
			b		scan_loop
check
			mov		r6, r1
			mov		r7, r2
			mov		r8, #1 ; keep track of scanned char index
			mov		r5, r1
check_loop
			ldrb		r3, [r6, #1]
			ldrb		r4, [r7, #1]
			cmp		r3,r4
			bne		end_check_loop
			cmp		r3,#0
			beq		end_
			cmp		r4,#0
			beq		end_
			add		r8,r8,#1
			add		r6,r6,#1
			add		r7,r7,#1
			b		check_loop
end_check_loop
			cmp		r3, #0
			bne		not_found
			cmp		r4,#0
			beq		end_ ; found
not_found
			cmp		r4,#0
			beq		end_ ; found
			mov		r5, #0
			add		r1, r1, r8 ; continue to scan since last matching occurrence
			;		add		r2,r2,r8
			b		scan_loop
end_
			end
