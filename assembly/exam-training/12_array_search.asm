total_numbers	dcd		4
numbers		dcd		1,2,3,4
			mov		r3,#7 ; n to find
			mov		r1,#total_numbers
			ldr		r0, [r1]
			mov		r1,#numbers
			mov		r5,#0 ; index of found n
loop
			cmp		r0,#-1
			beq		end_
			ldr		r2, [r1]
			cmp		r3,r2
			beq		end_
			sub		r0,r0,#1
			add		r1,r1,#4
			add		r5,r5,#1
			b		loop
end_
			end
