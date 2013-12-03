from configGen import *
import random

n = 75
accel(0,-9.8,0)
maxbounds(n,n,n)
minbounds(0,0,0)

b1 = ball(0,0,0,1,1,1)
b2 = ball(1,1,1,1,1,1)
for i in range(0,4300):
    ball(random.randint(0,n),random.randint(0,n),random.randint(0,n),random.randint(0,10),0,0)

distcon(b1,b2,20)
light(0,0,-10,1,1,1)
light(0,10,-10,1,1,1)


writeConfig("config.txt")
