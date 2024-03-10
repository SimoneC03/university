; contigous array elements sum 
array		dcd		1,2,3,4,5
contigous_sum	fill		20 ; 20 byte memory location pointer
			
			mov		r0,#5
			mov		r1, #array
			mov		r2, #contigous_sum
			
loop
			cmp		r0,#1
			beq		end_loop
			ldr		r3, [r1], #4 ; r1[k]
			ldr		r4, [r1] ; r1[k + 1]
			add		r4,r4,r3
			str		r4, [r2], #4
			sub		r0,r0,#1
			b		loop
end_loop
			end
			
