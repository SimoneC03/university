;   array search and deletion
array	dcd		1,2,3,4,5,6,7
size		dcd		7
		mov		r1, #size
		ldr		r0, [r1]
		mov		r1, #array
		mov		r2, #7 ; n to find and remove
loop
		cmp		r0, #0
		beq		end_
		ldr		r3, [r1]
		cmp		r3,r2
		beq		found
		add		r1,r1,#4
		sub		r0,r0,#1
		b		loop
found
		cmp		r0,#1
		beq		end_found
		ldr		r3, [r1, #4]
		str		r3, [r1]
		add		r1,r1,#4
		sub		r0,r0,#1
		b		found
end_found 				; updating values total
		mov		r1,#size
		ldr		r0,[r1]
		sub		r0,r0,#1
		str		r0,[r1]
		
end_
		end
