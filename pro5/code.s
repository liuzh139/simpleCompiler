 .globl _Main_main
 # Method 
 _Main_main: 
 push %ebp
 mov %esp, %ebp
 sub $12, %esp
 # Integer Literal 
 push $8
 # Integer Literal 
 push $5
 # Plus
 pop %edx
 pop %eax
 add %edx, %eax
 push %eax
 # Assignment
 pop %eax
 mov %eax, -4
 # Variable Node
 push -4 (%ebp)
 # Assignment
 pop %eax
 mov %eax, -8
 # Variable Node
 push -4 (%ebp)
 # Assignment
 pop %eax
 mov %eax, -12
 # Variable Node
 push -4 (%ebp)
 # Variable Node
 push -8 (%ebp)
 # Plus
 pop %edx
 pop %eax
 add %edx, %eax
 push %eax
 # Variable Node
 push -12 (%ebp)
 # Plus
 pop %edx
 pop %eax
 add %edx, %eax
 push %eax
 # Return Statement
 pop %eax
 mov %ebp, %esp
 pop %ebp
 ret
