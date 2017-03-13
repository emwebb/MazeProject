attribute vec4 pos;
uniform mat4 trans;
attribute vec4 col;
varying vec4 colv;
void main(){
    gl_Position = trans*pos;
    colv = col;
}
