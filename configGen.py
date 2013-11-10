_vardict = {}
_balls = []
_lights = []
_distcons = []

def _listToString(l):
    s = ""
    for i in xrange(0, len(l)-1):
        s = s+str(l[i])+" "
    s = s + str(l[-1])
    return s

def writeConfig(filename):
    f = open(filename, 'w')
    def println(s):
        f.write(str(s)+"\n")

    println("numballs "+str(len(_balls)))
    println("numlights "+str(len(_lights)))
    for name in _vardict:
        v = _vardict[name]
        if type(v) is list:
            println(name+" "+_listToString(v))
        else:
            println(name+" "+str(v))

    for b in _balls:
        println("ball "+_listToString(b))

    for d in _distcons:
        println("distcon "+_listToString(d))

    for l in _lights:
        println("light "+_listToString(l))

    f.close()

 

def accel(x,y,z):
    _vardict["accel"] = [x,y,z]

def sensitivity(x):
    _vardict["sensitivity"] = x

def ball(x,y,z,vx,vy,vz):
    i = len(_balls)
    _balls.append( [x,y,z,vx,vy,vz] )
    return i

def distcon(b1,b2,d):
    _distcons.append( [b1,b2,d])

def light(x,y,z,r,g,b):
    _lights.append( [x,y,z,r,g,b] )

def camera( cx,cy,cz,vx,vy,vz,ux,uy,uz):
    _vardict["camera"] = [cx,cy,cz,vx,vy,vz,ux,uy,uz]

def maxbounds(x,y,z):
    _vardict["maxbounds"] = [x,y,z]

def minbounds(x,y,z):
    _vardict["minbounds"] = [x,y,z]

def enable2d():
    _vardict["2d"] = "true"

def disable2d():
    _vardict["2d"] = "false"

def enableShading():
    _vardict["shading"] = "true"

def disableShading():
    _vardict["shading"] = "false"

def __init_defaults():
    disable2d()
    enableShading()
    camera( 0,0,0,0,0,1,0,1,0)
    sensitivity(0.5)

__init_defaults()
