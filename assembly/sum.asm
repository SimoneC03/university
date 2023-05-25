; sum of numbers stored in memory by subsequent sums 

total_numbers	dcd		3
numbers		dcd		5,80,50
			
			mov		r0,#total_numbers
			ldr		r1,[r0]
			mov		r2,#numbers
			mov		r0,#0
loop
			cmp		r1,#0
			beq		end_loop
			ldr		r3,[r2]
			add		r0,r0,r3
			sub		r1,r1,#1
			add		r2,r2,#4
			b		loop
			
end_loop
			end
			
