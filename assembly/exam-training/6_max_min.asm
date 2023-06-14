			;		1st version of maximum and minimum of a sequence of numbers
total_numbers	dcd		7
numbers		dcd		5,32,5,1324,-3,131,33927
			mov		r7,#total_numbers
			ldr		r0,[r7]
			mov		r1,#numbers
			ldr		r2,[r1] ;		r2 = max
			mov		r3,r2		;		r3 = min
			add		r1,r1,#4
loop
			cmp		r0,#1
			beq		end_
			ldr		r4, [r1]
			cmp		r4,r2
			ble		check
			mov		r2,r4
check
			cmp		r4,r3
			bge		end_loop
			mov		r3,r4
end_loop
			add		r1,r1,#4
			sub		r0,r0,#1
			b		loop
end_
			end
