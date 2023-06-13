				;		search duplicates
array			dcd		1,2,3,4,5,3,7,8,9
found_indexes	dcd		0,0,0,0,0,0,0,0,0
				mov		r0, #9
				mov		r1, #array
				mov		r2, #found_indexes
				mov		r3, #3 ; n to find
				mov		r5, #0 ; total occurrencies of n
loop
				cmp		r0,#0
				beq		end_
				ldr		r4, [r1]
				cmp		r4,r3
				bne		end_loop
				add		r5,r5,#1
				mov		r6,r1
				sub		r6,r6,#array
				lsr		r6,r6,#2
				str		r6,[r2]
				add		r2,r2,#4
end_loop
				add		r1,r1,#4
				sub		r0,r0,#1
				b		loop
end_
				end
				
				
