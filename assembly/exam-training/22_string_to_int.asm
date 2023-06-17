string			dcb		0x34, 0x35, 0x31, 0x31, 0 ; "4511\0"
				mov		r1, #string
				mov		r0, #0 ; final converted num
loop
				ldrb		r2, [r1]
				cmp		r2, #0
				beq		end_
				mov		r3, #10
				mov		r4, #0
				;		r4 = r0 * 10
multiply_loop
				cmp		r3, #0
				beq		end_multiply_loop
				add		r4,r4,r0
				sub		r3,r3,#1
				b		multiply_loop
end_multiply_loop
				sub		r2,r2,#0x30
				add		r0,r4,r2
				add		r1,r1,#1
				b		loop
end_
				end