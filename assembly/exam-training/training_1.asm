; sort alphabetically a string and sum all even char numeric values
string			dcb		0x65,0x66,0x67,0x65,0x69,0x68,0 ; "ABCAED"
				mov		r1, #string
				mov		r0, #0 ;  string length
strlen_loop
				ldrb		r2, [r1]
				cmp		r2, #0
				beq		sort_outer_loop
				add		r0,r0,#1
				add		r1,r1,#1
				b		strlen_loop
sort_outer_loop
				mov		r1, #string
				mov		r2, r0
				mov		r3, #1 ; 0 = not sorted, 1 = sorted
sort_inner_loop
				cmp		r2, #1
				beq		end_sort_inner_loop
				ldrb		r4, [r1]
				ldrb		r5, [r1, #1]
				cmp		r4,r5
				ble		no_swap
				strb		r5,[r1]
				strb		r4, [r1,#1]
				mov		r3,#0
no_swap
				add		r1,r1,#1
				sub		r2,r2,#1
				b		sort_inner_loop
end_sort_inner_loop
				cmp		r3,#0
				beq		sort_outer_loop
				;		end sort
				mov		r1, #0 ; partial sum
				mov		r2, r0
				mov		r3, #string
sum_loop
				cmp		r2, #0
				beq		end_sum_loop
				ldrb		r4, [r3]
				and		r6,r4,#1
				cmp		r6,#0
				bne		not_even
				add		r1,r1,r4
not_even
				sub		r2,r2,#1
				add		r3,r3,#1
				b		sum_loop
end_sum_loop
				end