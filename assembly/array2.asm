nums dcd 3,4,5,6,7,8,9
	mov r0,#7
	mov r1,#nums
	mov r2,#0 ; partial sum

loop 
	cmp r0,#0
	beq end_loop
	ldr r3,[r1] ; i-th element

	add r2,r2,r3 ;update partial sum

	add r1,r1,#4 ; increase pointer
	sub r0,r0,#1 ; decrease element counter
	b loop
end_loop
	end
;
; int nums[7] = { 3, 4, 5, 6, 7, 8, 9 }
; int r1 = nums;
; int r0 = 7;
; int r2 = 0;
; while(r0 > 0 ) {
; 	int r3 = *r1;
;	r2 = r2 + r3;
; 	r1++;
; 	r0--;
;}
;
