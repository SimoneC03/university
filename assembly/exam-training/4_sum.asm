; sum of numbers stored in memory by subsequent sums 
total_numbers	dcd		3
numbers		dcd		5,80,50
			mov		r1,#total_numbers
			ldr		r0,[r1]
			mov		r1,#numbers
			mov		r2,#0 ; partial sum
loop
			cmp		r0,#0
			beq		end_loop
			ldr		r3,[r1]
			add		r2,r2,r3
			sub		r0,r0,#1
			add		r1,r1,#4
			b		loop
end_loop
			end
			
