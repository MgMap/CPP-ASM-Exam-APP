.386              ;Target processor.  Use instructions for Pentium class machines
.xmm		      ; enable floating point instructions
.MODEL FLAT, C  ;Use the flat memory model. Use C calling conventions
.STACK            ;Define a stack segment of 1KB (Not required for this example)
.DATA             ;Create a near data segment.  Local variables are declared after
                  ;this directive



text	      BYTE "HEY I AM INSIDE OF ASM FUNCTION ADD TWO VALUES", 50, 10, 0

.CODE             ;Indicates the start of a code segment.

;include Irvine32.inc

; call/called external "C" code



; note that argc/argv are here on the stack - I am not using them.
mainASM PROC
    

   ret 
mainASM ENDP 

addTwoValues PROC

	; Parameters a and b are accessed relative to ESP
    mov eax, [esp + 4]  ; a
    add eax, [esp + 8]  ; b
    

ret
addTwoValues ENDP

END
