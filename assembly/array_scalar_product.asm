array_size	dcd		5
array1		dcd		1,2,3,4,5
array2		dcd		2,2,1,1,1
			;		r0 = array size
			;		r1 = array1 pointer
			;		r2 = array2 pointer
			;		r5 = multiply result
			;		r6 = result
			
			mov		r1,#array_size
			ldr		r0, [r1]
			mov		r1,#array1
			mov		r2,#array2
			
loop
			cmp		r0, #0
			beq		end_
			
			ldr		r3,[r1]
			ldr		r4,[r2]
			bl		multiply
			add		r6,r6,r5
			add		r1,r1,#4
			add		r2,r2,#4
			sub		r0,r0,#1
			b		loop
			
multiply
			mov		r5,#0
multiply_loop
			cmp		r4,#0
			beq		end_multiply
			add		r5,r5,r3
			sub		r4,r4,#1
			b		multiply_loop
end_multiply
			mov		pc, lr
			
			
end_
			end
