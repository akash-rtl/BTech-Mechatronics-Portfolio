ORG 0000H
	
	mov scon, #40h
	mov tmod, #10h
	mov th1, #0fdh
	setb tr1
	loop:
	mov a,#'A'
	acall Trans
	mov a,#'d'
	acall Trans
	sjmp loop
	
	Trans: mov sbuf, a
	again: jnb t1, again
	clr t1
END