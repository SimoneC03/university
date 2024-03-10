array		dcd		4,6,2,6,7,24,5
array_length	dcd		7
outer_loop
			mov		r1, #array_length
			ldr		r0, [r1]
			mov		r1, #array
			mov		r4, #1 ; 1 = sorted, 0 = not sorted
inner_loop
			cmp		r0, #1
			beq		end_inner_loop
			ldr		r2, [r1]
			ldr		r3, [r1,#4]
			cmp		r2,r3
			ble		no_swap
			str		r3, [r1]
			str		r2, [r1,#4]
			mov		r4, #0
no_swap
			add		r1,r1,#4
			sub		r0,r0,#1
			b		inner_loop
end_inner_loop
			cmp		r4, #0
			beq		outer_loop
			end
