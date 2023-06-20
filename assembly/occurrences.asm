total_numbers	dcd		7
numbers		dcd		4,3,1,4,1,1,1
			mov		r1, #total_numbers
			ldr		r0, [r1]
			mov		r1, #numbers
			mov		r3,#1 ; r3 -> n to find
			mov		r4,#0 ; r4 -> total occurrences
loop
			cmp		r0,#0
			beq		end_
			ldr		r5,[r1]
			cmp		r3,r5
			beq		found
			b		end_loop
found
			add		r4,r4,#1
			b		end_loop
end_loop
			add		r1,r1,#4
			sub		r0,r0,#1
			b		loop
end_
			end
