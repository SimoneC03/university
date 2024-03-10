size		dcd		5
array	dcd		1,2,3,4,5
array_sum	fill		20
		mov		r1, #size
		ldr		r0, [r1]
		mov		r1, #array
		mov		r2, #array_sum
		mov		r4, #0 ; partial sum
loop
		cmp		r0, #0
		beq		end_
		ldr		r3, [r1]
		add		r4,r4,r3
		str		r4,[r2]
		add		r1,r1,#4
		add		r2,r2,#4
		sub		r0,r0,#1
		b		loop
end_
		end