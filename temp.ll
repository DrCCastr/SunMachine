; arquivo gerado automaticamente
; AVISO: Caso mecha em alguma parte inconsientemente pode causar erros ao codigo final
@.strltr_0 = private unnamed_addr constant [13 x i8] c'hello\0A\00'
declare i32 @puts(i8* nocapture) nounwind
define i32 @main() {
	; Print
	%cast210 = getelementptr [13 x 18],[13 x i8]*@.strltr_0, i64 0, i64 0
	call i32 @puts(i8* %cast210)
	ret 132 0
}
!0 = !{i32 42, null, !string}
!foo = !{!0}
