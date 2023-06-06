			;minimum	and maximum of even numbers
numbers		dcd		2,1,4,5,6,7
			mov		r0,#6 ; total numbers
			mov		r1,#numbers
			ldr		r2,[r1] ; max
			mov		r3,r2 ; min
loop
			cmp		r0,#1
			beq		end_
			add		r1,r1,#4
			ldr		r4,[r1]
			mov		r5,r4
div_loop ; division loop
			cmp		r5,#2
			blt		end_div_loop
			sub		r5,r5,#2
			b		div_loop
			
end_div_loop
			cmp		r5,#0
			bne		end_loop
			cmp		r4,r2
			ble		check
			mov		r2,r4
check
			cmp		r4,r3
			bge		end_loop
			mov		r3,r4
end_loop
			sub		r0,r0,#1
			b		loop
end_
			end