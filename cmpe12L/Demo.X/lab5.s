.ent getDelay
.text
.global getDelay

getDelay:
andi $v0,$v0,0
add $v0,$v0,0x80000

.end getDelay
.data

/* any global data here */