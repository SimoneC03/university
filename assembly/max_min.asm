		;
array	dcd		5,9,10,34,8,2,7,4,9,11
		
		mov		r0,#10
		mov		r1,#array
		
		ldr		r2,[r1]
		mov		r3,r2
		
		add		r1,r1,#4
		
loop
		cmp		r0,#1
		beq		end_loop
		
		ldr		r4,[r1]
		
		cmp		r4,r2
		ble		cont
		mov		r2,r4
cont
		cmp		r4,r3
		bge		cont2
		mov		r3,r4
cont2
		sub		r0,r0,#1
		add		r1,r1,#4
		b		loop
		
end_loop
		end
