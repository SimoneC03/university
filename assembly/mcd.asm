; MCD(a,b) calculator
		mov		r0,#80 ; a
		mov		r1,#36 ; b
loop
		cmp		r0,r1
		beq		end_loop
		bgt		maggiore
		sub		r1,r1,r0
		b		loop
maggiore
		sub		r0,r0,r1
		b		loop
end_loop
		end
