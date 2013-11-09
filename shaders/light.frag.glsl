# version 120 

// in vec4 color ;  
// in vec4 mynormal ; 
// in vec4 myvertex ;
// That is certainly more modern

varying vec4 color ;
varying vec3 mynormal ; 
varying vec4 myvertex ; 

const int numLights = 10 ; 
uniform bool enablelighting ; // are we lighting at all (global).
uniform vec4 lightposn[numLights] ; // positions of lights 
uniform vec4 lightcolor[numLights] ; // colors of lights
uniform int numused ;               // number of lights used

uniform vec4 ambient ; 
uniform vec4 diffuse ; 
uniform vec4 specular ; 
uniform vec4 emission ; 
uniform float shininess ; 

vec4 CalculateLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) {

        //Diffuse
        float nDotL = dot(normal, direction)  ;         
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;  

        //Specular
        float nDotH = dot(normal, halfvec) ; 
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ; 

        vec4 retval = lambert + phong ; 
        return retval ;            
}  

void main (void) 
{       
    if (enablelighting) {       

        vec4 finalcolor ; 
        int i ;
        
        //borrowed code
        const vec3 eyepos = vec3(0,0,0) ; 
        vec4 _mypos = gl_ModelViewMatrix * myvertex ; 
        vec3 mypos = _mypos.xyz / _mypos.w ; // Dehomogenize current location 
        vec3 eyedirn = normalize(eyepos - mypos) ; 
        // Compute normal, needed for shading. 
        // Simpler is vec3 normal = normalize(gl_NormalMatrix * mynormal) ; 
        vec3 _normal = (gl_ModelViewMatrixInverseTranspose*vec4(mynormal,0.0)).xyz ; 
        vec3 normal = normalize(_normal) ; 

		finalcolor = vec4(0,0,0,0);
		finalcolor += ambient;
		finalcolor += emission;
		
        for( i=0; i<numused; i++){ //loop through each light.
			if( lightposn[i].w != 0) { //point light
                vec4 lightp;
                lightp = gl_ModelViewMatrix * lightposn[i] ; 
				//vec3 position = lightposn[i].xyz/ lightposn[i].w; 
                vec3 position = lightp.xyz/ lightp.w; 
				vec3 direction = normalize(position-mypos);
				vec3 halfo = normalize (direction + eyedirn) ;  

				finalcolor += CalculateLight(direction, lightcolor[i], normal, halfo, diffuse, specular, shininess);
			}else{ //directional.
				vec3 direction = normalize(lightposn[i].xyz);
				vec3 halfo = normalize (direction + eyedirn) ;  

				finalcolor += CalculateLight(direction, lightcolor[i], normal, halfo, diffuse, specular, shininess);
			}

        }
		gl_FragColor = ( finalcolor);
        //gl_FragColor = diffuse;
        //gl_FragColor = normalize(vec4(normal.x,normal.y,normal.z,0) ); 
        }
    else gl_FragColor = color ; 

}

// vim:syntax=c
