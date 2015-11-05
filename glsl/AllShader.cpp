#include "AllShader.h"
const char* glsl_curve_light_vex = 
"attribute vec2 Tex;\n"
"varying vec2 vTex;\n"
"varying vec3 vN;\n"
"varying vec3 vL;\n"
"varying vec3 vH;\n"
"uniform vec4 lightpos;\n"
"uniform vec4 eyepos;\n"
"uniform mat4 M;\n"
"uniform mat4 V;\n"
"uniform mat4 P;\n"
"uniform mat4 N;\n"
"void main()\n"
"{\n"
"    vec4 pos = curve_transform(Tex);\n"
"    vec3 aNormal = normal_curve_transform(Tex);\n"
"    gl_Position = pos*M*V*P;\n"
"    vL = vec3(lightpos/lightpos.w)-vec3(pos/pos.w);\n"
"    vN = vec3(vec4(aNormal,1.0)*N);\n"
"    vTex = Tex;\n"
"    vH = vL+vec3(lightpos/lightpos.w)-vec3(eyepos/eyepos.w);\n"
"}\n"
;
const char* glsl_function_txt_vex = 
"+ 0 x0+x1 d0+d1\n"
"- 0 x0-x1 d0-d1\n"
"* 1 x0*x1 d0*x1+x0*d1\n"
"/ 1 x0/x1 d0/x1-x0*d1/x1/x1\n"
"exp 9 exp(x0) d0*exp(x0)\n"
"cos 9 cos(x0) 0.0-d0*sin(x0)\n"
"sin 9 sin(x0) d0*cos(x0)\n"
"tan 9 tan(x0) d0*(1.0+tan(x0)*tan(x0))\n"
;
const char* glsl_light_vex = 
"attribute vec4 aPos;\n"
"attribute vec3 aNormal;\n"
"attribute vec2 aTex;\n"
"varying vec2 vTex;\n"
"varying vec3 vN;\n"
"varying vec3 vL;\n"
"varying vec3 vH;\n"
"uniform vec4 lightpos;\n"
"uniform vec4 eyepos;\n"
"uniform mat4 M;\n"
"uniform mat4 V;\n"
"uniform mat4 P;\n"
"uniform mat4 N;\n"
"void main()\n"
"{\n"
"    vec4 pos = aPos*M;\n"
"    gl_Position = aPos*M*V*P;\n"
"    vL = vec3(lightpos/lightpos.w)-vec3(pos/pos.w);\n"
"    vN = vec3(vec4(aNormal,1.0)*N);\n"
"    vTex = aTex;\n"
"    vH = vL+vec3(lightpos/lightpos.w)-vec3(eyepos/eyepos.w);\n"
"}\n"
;
const char* glsl_bicubic_fra = 
"varying vec2 vTex;\n"
"uniform sampler2D buffer;\n"
"uniform float uUnit;\n"
"uniform float vUnit;\n"
"float BiCubicPoly1(float x, float a)\n"
"{\n"
"    x = abs(x);\n"
"    float res = (a+float(2))*x*x*x - (a+float(3))*x*x + float(1);\n"
"    return res;\n"
"}\n"
"float BiCubicPoly2(float x, float a)\n"
"{\n"
"    x = abs(x);\n"
"    float res = a*x*x*x - float(5)*a*x*x + float(8)*a*x - float(4)*a;\n"
"    return res;\n"
"}\n"
"void main()\n"
"{\n"
"vec2 basic; \n"
"vec2 det; \n"
"basic = vTex*vec2(uUnit, vUnit) - vec2(0.5,0.5); \n"
"det = fract(basic); \n"
"gl_FragColor = vec4(0.0,0.0,0.0,0.0)\n"
"+BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(-1), float(-1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(-1), float(0)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(-1), float(1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly2(det.x-float(-1), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(-1), float(2)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(0), float(-1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(0), float(0)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(0), float(1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(0), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(0), float(2)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(1), float(-1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(1), float(0)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(1), float(1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly1(det.x-float(1), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(1), float(2)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly2(det.y-float(-1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(2), float(-1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly1(det.y-float(0), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(2), float(0)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly1(det.y-float(1), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(2), float(1)))/vec2(uUnit, vUnit))\n"
"+BiCubicPoly2(det.x-float(2), float(-0.5))*BiCubicPoly2(det.y-float(2), float(-0.5))*texture2D(buffer, vTex + ( - det + vec2(float(2), float(2)))/vec2(uUnit, vUnit))\n"
";\n"
"}\n"
;
const char* glsl_curve_light_fra = 
"uniform vec4 lightColor;\n"
"uniform vec4 ambientColor;\n"
"uniform float ka;\n"
"uniform float kd;\n"
"uniform float ks;\n"
"uniform float ns;\n"
"uniform sampler2D sam;\n"
"varying vec2 vTex;\n"
"varying vec3 vN;\n"
"varying vec3 vL;\n"
"varying vec3 vH;\n"
"void main()\n"
"{\n"
"    float p, d;\n"
"    vec4 diffuceColor = texture2D(sam, vTex) * lightColor;\n"
"    vec3 _vH = normalize(vH);\n"
"    vec3 _vN = normalize(vN);\n"
"    vec3 _vL = normalize(vL);\n"
"    p = ks*max(-dot(_vN, _vH), dot(_vN, _vH));\n"
"    p = pow(p, ns);\n"
"    d = kd*max(-dot(_vN, _vH), dot(_vN, _vL));\n"
"    gl_FragColor = ka*ambientColor + p*lightColor + d*diffuceColor;\n"
"}\n"
;
const char* glsl_light_fra = 
"uniform vec4 lightColor;\n"
"uniform vec4 ambientColor;\n"
"uniform float ka;\n"
"uniform float kd;\n"
"uniform float ks;\n"
"uniform float ns;\n"
"uniform sampler2D sam;\n"
"varying vec2 vTex;\n"
"varying vec3 vN;\n"
"varying vec3 vL;\n"
"varying vec3 vH;\n"
"void main()\n"
"{\n"
"    float p, d;\n"
"    vec4 diffuceColor = texture2D(sam, vTex) * lightColor;\n"
"    vec3 _vH = normalize(vH);\n"
"    vec3 _vN = normalize(vN);\n"
"    vec3 _vL = normalize(vL);\n"
"    p = ks*max(float(0.0), dot(_vN, _vH));\n"
"    p = pow(p, ns);\n"
"    d = kd*max(float(0.0), dot(_vN, _vL));\n"
"    gl_FragColor = ka*ambientColor + p*lightColor + d*diffuceColor;\n"
"}\n"
;
