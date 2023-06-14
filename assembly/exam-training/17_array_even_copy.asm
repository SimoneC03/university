; copy even numbers into array2
size		dcd		5
array	dcd		1,2,3,4,5
array2	fill		20 ; 20 bytes allocated
		mov		r1,#size
		ldr		r0,[r1]
		mov		r1,#array
		mov		r2,#array2
		mov		r5,#0 ; total even nums
loop
		cmp		r0,#0
		beq		end_
		ldr		r3, [r1]
		and		r4,r3,#1
		cmp		r4, #0
		bne		odd
		str		r3, [r2]
		add		r2,r2,#4
		add		r5,r5,#1
odd
		add		r1,r1,#4
		sub		r0,r0,#1
		b		loop
end_
		end
		
