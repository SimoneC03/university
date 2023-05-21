; multiplication by successive sums 
mov	r0,#5
mov	r1,#8
mov	r2,#0
		
loop
	cmp	r1,#0
	beq	end_loop
	add	r2,r2,r0
	sub	r1,r1,#1
	b	loop
			
end_loop
	end