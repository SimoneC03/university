numbers		dcd		1,2,3,4,5
			
			mov		r5,#5 ; total numbers
			mov		r0,r5
			mov		r1, #numbers
			mov		r2,#0 ; partial sum
			mov		r4,#0 ; arithmetic mean
			
sum_loop
			cmp		r0,#0
			beq		calc_average
			ldr		r3,[r1]
			add		r2,r2,r3
			add		r1,r1,#4
			sub		r0,r0,#1
			b		sum_loop
			
calc_average
			mov		r0,r5
average_loop
			cmp		r2,r0
			blt		end_
			sub		r2,r2,r0
			add		r4,r4,#1
			b		average_loop
			
end_
			end
