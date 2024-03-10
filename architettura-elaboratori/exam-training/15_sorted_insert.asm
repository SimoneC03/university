; insert an element in a sorted array
size		dcd		6
array	dcd		1,2,3,4,5,7
		mov		r1, #size
		ldr		r0, [r1]
		mov		r1, #array
		mov		r2, #6 ; n to insert
		mov		r4, r0
		lsl		r4,r4,#2
		add		r1,r1,r4 ; pointing at the end of array
loop
		cmp		r0, #0
		blt		end_loop
		ldr		r3,[r1,#-4]
		cmp		r3,r2
		bgt		move_el
		str		r2, [r1]
		b		end_
move_el
		str		r3,[r1]
		sub		r1,r1,#4
		sub		r0,r0,#1
		b		loop
end_loop
		mov		r1,#array
		str		r2,[r1]
end_
		mov		r1, #size
		ldr		r0, [r1]
		add		r0,r0,#1
		str		r0, [r1]
		end
