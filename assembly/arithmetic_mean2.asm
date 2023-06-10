					;		arithmetic mean of numbers divisible by 3
array				dcd		1,2,3,4,5,6
					
					mov		r0, #6
					mov		r1, #array
					mov		r2, #0 ; partial sum
					mov		r3, #0 ; total elements to consider
divisibility_loop
					cmp		r0, #0
					beq		end_divisibility_loop
					ldr		r4, [r1]
					
					mov		r8,r0 ; regsiters backup
					mov		r9,r1
					mov		r10,r2
					
					mov		r1, r4
					mov		r2, #3
					bl		division
					cmp		r1,#0
					beq		divisible
					mov		r0,r8 ;restore registers
					mov		r1,r9
					mov		r2,r10
					b		not_divisible
divisible
					mov		r0,r8 ;restore registers
					mov		r1,r9
					mov		r2,r10
					add		r3,r3,#1
					add		r2,r2,r4
not_divisible
					sub		r0,r0,#1
					add		r1,r1,#4
					b		divisibility_loop
end_divisibility_loop
					mov		r1,r2 ; r1 = mean remainder
					mov		r2,r3 ; r0 = mean result
					bl		division
					end
					
division
					mov		r0, #0 ; quotient
division_loop
					cmp		r1,r2
					blt		end_division_loop
					sub		r1,r1,r2
					add		r0,r0,#1
					b		division_loop
end_division_loop
					mov		pc, lr