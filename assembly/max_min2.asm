; 2nd version of maximum and minimum of a sequence of numbers
total_numbers	dcd		7
numbers		dcd		5,32,5,1324,-3,131,33927
			mov		r1,#total_numbers
			ldr		r0,[r1]
			mov		r1,#numbers
			ldr		r2,[r1] ;min
			mov		r3,r2 	;max
loop
			cmp		r0,#1
			beq		end_
			add		r1,r1,#4
			ldr		r4,[r1] ;r4 -> n to compare
			cmp		r2,r4
			bgt		min_switch
			cmp		r3,r4
			blt		max_switch
			b		end_loop
min_switch
			mov		r2,r4
			b		end_loop
max_switch
			mov		r3,r4
			b		end_loop
end_loop
			sub		r0,r0,#1
			b		loop
end_
			end
