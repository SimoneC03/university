; converting int to string
num			dcd		4637
string		fill		4 ; final converted string
			mov		r1, #num
			ldr		r0, [r1]
			mov		r1, #string
			add		r1,r1,#4 ; pointing at the end of the string
loop
			cmp		r0, #0
			beq		end_
			mov		r3,r0
			mov		r4,#10
			bl		division
			add		r3,r3,#0x30 ; converting remainder to ascii
			strb	r3, [r1], #-1
			mov		r0,r5
			b		loop
end_
			end
			
division
			mov		r5,#0 ; quotient
div_loop
			cmp		r3,r4
			blt		end_div_loop
			sub		r3,r3,r4
			add		r5,r5,#1
			b		div_loop
end_div_loop
			mov		pc,lr
