array		dcd		3,10,9,7,3,2,1,4,20
			mov		r0, #9 ; array size
			mov		r1, #array
			mov		r2, #4 ; n to find
			mov		r3, #-1 ; found n index
scan_loop
			cmp		r0, #20
			beq		end_
			ldr		r4, [r1]
			cmp		r4, r2
			bne		c_scan_loop
			mov		r5, #array
			sub		r1,r1,r5
			lsr		r3,r1,#2
			b		end_
c_scan_loop
			add		r1,r1,#4
			sub		r0,r0,#1
			b		scan_loop
end_
			end