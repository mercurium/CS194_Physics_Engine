#pragma once

class Sphere {
    public:
        Sphere();
        virtual ~Sphere ();
        void draw(); //draw sphere in OpenGL/whatever we are going to use.

    private:
        /* data */
        int x,y,z; //Position
        int r; //radius
};
