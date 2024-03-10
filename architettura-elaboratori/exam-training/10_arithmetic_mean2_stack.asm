					;		arithmetic mean of numbers divisible by 3 using stack memory to backup registers value
array		dcd		1,2,3,4,5,6
			mov		r0,#6
			mov		r1, #array
			mov		r2, #0 ; partial sum
			mov		r3, #0 ; total elements to consider
loop
			cmp		r0, #0
			beq		end_loop
			ldr		r4, [r1]
			stmdb	r13!, {r0} ; registers backup
			stmdb	r13!, {r1}
			stmdb	r13!, {r2}
			mov		r1,r4
			mov		r2, #3
			bl		division
			cmp		r1,#0
			beq		divisible
			ldmia	r13!, {r2} ; restore registers
			ldmia	r13!, {r1}
			ldmia	r13!, {r0}
			b		not_divisible
divisible
			ldmia	r13!, {r2} ; restore registers
			ldmia	r13!, {r1}
			ldmia	r13!, {r0}
			add		r2,r2,r4
			add		r3,r3,#1
not_divisible
			add		r1,r1,#4
			sub		r0,r0,#1
			b		loop
end_loop
			mov		r1,r2 ; r1 = mean remainder
			mov		r2,r3
			bl		division
			end
			
division
			mov		r0,#0 ; quotient (final mean result)
div_loop
			cmp		r1,r2
			blt		end_div_loop
			sub		r1,r1,r2
			add		r0,r0,#1
			b		div_loop
end_div_loop
			mov		pc,lr
