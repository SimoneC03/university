				;		sort alphabetically a string and calculate the arithmetic mean of odd values
				;		r0 = mean quotient
				;		r1 = mean remainder
string			dcb		0x65,0x66,0x67,0x65,0x0,0x0,0x0,0x0
				mov		r1, #string
				mov		r0, #0 ; string length
strlen_loop
				ldrb		r2,[r1]
				cmp		r2, #0
				beq		sort_outer_loop
				add		r0,r0,#1
				add		r1,r1,#1
				b		strlen_loop
sort_outer_loop
				mov		r1, #string
				mov		r2, r0
				mov		r3, #0 ; 0 = sorted, 1 = not sorted
sort_inner_loop
				cmp		r2,#1
				beq		end_sort_inner_loop
				ldrb		r4, [r1]
				ldrb		r5, [r1, #1]
				cmp		r4,r5
				ble		no_swap
				strb		r5, [r1]
				strb		r4, [r1,#1]
				mov		r3, #1 ; swapped flag
no_swap
				add		r1,r1,#1
				sub		r2,r2,#1
				b		sort_inner_loop
end_sort_inner_loop
				cmp		r3,#0
				bne		sort_outer_loop
				mov		r1, #string
				mov		r3, #0 ; total nums to consider
				mov		r4, #0 ; partial sum
mean_loop
				cmp		r0,#0
				beq		end_
				ldrb		r2, [r1]
				and		r5,r2,#1
				cmp		r5,#1
				bne		c_mean_loop
				add		r3,r3,#1
				add		r4,r4,r2
c_mean_loop
				add		r1,r1,#1
				sub		r0,r0,#1
				b		mean_loop
end_
				mov		r1, r4
				mov		r2, r3
				bl		division
				end
				
division
				mov		r0,#0 ; quotient
div_loop
				cmp		r1,r2
				blt		end_div_loop
				sub		r1,r1,r2
				add		r0,r0,#1
				b		div_loop
end_div_loop
				mov		pc, lr
				
