#include "include/noise_fbm.h"

float rainPuddle(vec3 pos, vec2 uv1, float rainTime)
{
	if(fract(pos.y) == 0.0 || fract(pos.y) == 0.5)
	{
		//float area = clamp(1.0 - length(pos.xz * 2.0 - 1.0), 0.0, 1.0);
		float area = clamp(length(pos.xz / 8.0 - 1.0) * 0.8, 0.0, 1.0);
		float puddles = clamp(noise(pos.xz * 0.4), 0.0, 1.0);
	    puddles *= 0.3 * (rainTime - 0.4) * uv1.y;
	    return mix(puddles, 0.0, area);
	}
	return 0.0;
}

//Source : https://www.geeks3d.com/20110316/shader-library-simple-2d-effects-sphere-and-ripple-in-glsl/
float rWater(vec2 uv, float timer) 
{
	vec2 p = -1.0 + 2.0 * uv; 
	float len = length(p); 
	float r;
	float dist;
	if(len < 0.5)
	{
		dist = (0.5 - abs(0.5 - len * 2.0));	
		uv = (p / len) * cos(len * 25.0 - TIME * 10.0) * 0.5; 
	    r = uv.x * dist * sin(TIME * 3.0 + timer);
	    r = max(0.0, r);
		return r;
	}
	return 0.0;
}

float splash(vec2 pos)
{
	float rWs = rWater(pos + vec2(0.5, 0.5), 3.0);
    rWs = max(rWs, rWater(pos + vec2(0.5, 0.5), 3.0));
	rWs = max(rWs, rWater(pos + vec2(-0.5, 0.5), 3.0));
	rWs = max(rWs, rWater(pos + vec2(0.5, -0.5), 3.0));
	rWs = max(rWs, rWater(pos - vec2(0.5, 0.5), 4.0));
	
	rWs = max(rWs, rWater(pos + vec2(0.3, 0.2), 0.5));
	rWs = max(rWs, rWater(pos + vec2(0.2, -0.3), 2.5));
	rWs = max(rWs, rWater(pos + vec2(-0.3, 0.1), 1.5));
	rWs = max(rWs, rWater(pos - vec2(0.2, 0.1), 3.5));
	return rWs;
}

float rainSplash(vec3 pos, vec2 uv1, float rainTime)
{
    float c = 0.0;
    float eff = splash(fract(pos.xz));
    c = mix(0.0, eff, max(uv1.y - 0.85, 0.0) * 3.3);
	return c  * rainTime;
}
