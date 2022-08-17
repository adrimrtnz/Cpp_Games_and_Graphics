Parms   struc
                dw  ?   ;pushed BP
                dw  ?   ;return address
handle          dw  ?
checksum        dw  ?
Parms   ends
;
                .model small
                .data
TempWord label  word
TempByte        db  ?   ;each byte read will be stored here
                db  0
            
                .code
                public      _ChecksumFile
_ChecksumFile   proc    near
                push    bp 
                mov     bp,sp
                push    si      ;save Cs register variable

                mov     bx,[bp+handle]
                sub     si, si

                mov     cx,1

                mov     dx,offset TempByte

ChecksumLoop:
                mov     ah,3fh
                int     21h
                jc      ErrorEnd
                and     ax,ax
                jz      Success
                add     si,[TempWord]

                jmp     ChecksumLoop

ErrorEnd:       
                sub     ax,ax
                jmp     short Done

Success:
                mov     bx,[bp+cheksum]
                mov     [bx],si
                mov     ax,1

;
Done:
                pop     si
                pop     bp
                ret

_ChecksumFile   endp
                end