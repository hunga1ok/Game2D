attribute vec4 a_position; 
attribute vec2 a_uv;
uniform mat4 u_MVP;
varying vec4 v_pos;
varying vec2 v_uv; 
void main() 
{      
	gl_Position = u_MVP * a_position;     
	v_uv = a_uv;
	v_pos = a_position; 
} 