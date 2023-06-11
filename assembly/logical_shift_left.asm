;  Multiply all elements of the array by 2
array     dcd     1,5,9,2,3,5,8,7
          mov     r0,#8
          mov     r1,#array
loop      
          cmp     r0,#0
          beq     end_loop
          ldr     r3,[r1]
          lsl     r3,r3,#1
          str     r3,[r1],#4
          sub     r0,r0,#1
          b       loop
end_loop 
          end