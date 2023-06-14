			;		string compare
			;		r0 = 0 -> same strings
string1		dcb		65,66,67,68,0
string2		dcb		65,66,67,68,0
			mov		r1,#string1
			mov		r2,#string2
strcmp_loop
			ldrb		r3,[r1]
			ldrb		r4,[r2]
			sub		r0,r3,r4
			cmp		r0,#0
			bne		end_
			cmp		r3,#0
			bne		continue_loop
			cmp		r4, #0
			bne		continue_loop
			mov		r0,#0
			b		end_
continue_loop
			add		r1,r1,#1
			add		r2,r2,#1
			b		strcmp_loop
end_
			end
			
			
