from configGen import *
import random

accel(0,-9.8,0)
maxbounds(35,30,35)
minbounds(0,0,0)

b1 = ball(0,0,0,1,1,1)
b2 = ball(1,1,1,1,1,1)
for i in range(0,1000):
    ball(random.randint(0,30),random.randint(0,30),random.randint(0,30),random.randint(0,5),random.randint(0,5),random.randint(0,5))

distcon(b1,b2,20)
light(0,0,-10,1,1,1)
light(0,10,-10,1,1,1)


writeConfig("config.txt")
