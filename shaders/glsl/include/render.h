#include "include/color.h"
#include "include/condition.h"

vec3 perfectWorldLight(vec3 col, vec2 uv1, float dayTime, float nightTime, float duskTime, float rainTime, float noLight)
{
	col = mix(col, col * dayWorldColor, dayTime);
	col = mix(col, col * nightWorldColor, nightTime * uv1.y * noLight);
	col = mix(col, col * duskWorldColor, duskTime);
	col = mix(col, col * rainDayWorldColor, (rainTime * dayTime) * uv1.y * noLight);
	col = mix(col, col * rainNightWorldColor, (rainTime * nightTime) * uv1.y * noLight);
	col = mix(col, saturation(col, 0.5), rainTime);
	return col;
}

vec3 perfectLight(vec3 col, vec4 color, vec4 fcol, vec2 uv1, float dayTime, float rainTime)
{
	vec3 cli = col * torchColor * 1.1;
    if(isUnderwater(fcol)) 
	{
		cli = col * torchUnderwaterColor * 2.3;
		col *= torchUnderwaterColor2;
	}
	uv1.x = uv1.x * 1.15 + abs(0.05 * sin(TIME)) * 0.8;
    col = mix(mix(col, cli, pow(uv1.x, 3.5)), col, uv1.y);
    col = mix(col, cli, pow(uv1.x, 3.5) * (min(dayTime, rainTime) + 0.2));
	return col;
}

vec3 perfectLeavesShadow(vec3 col, vec4 color, vec2 uv1, float nightTime, float rainTime, float noLight)
{
	if(isPlant(color) || color.w == 0.0) col = mix(col, col * leavesColor, min(rainTime, nightTime) + 0.2);
	return col;
}

vec3 perfectTreeShadow(vec3 col, vec4 color, vec2 uv1, float nightTime, float rainTime, float noLight)
{
	if(uv1.y == 0.0 && uv1.x == 0.0) return col;
	float shadowY = 1.0 - min(max((uv1.y - 0.89) * 100.0, 0.0), 1.0);
	if(color.w == 0.0)
	{
		shadowY = 0.0;
		col *= 1.2;
	}
	
	col = mix(col, col * shadowColor, shadowY * noLight * (min(rainTime, nightTime) + 0.2));
	return col;
}

vec3 perfectSideBlockShadow(vec3 col, vec4 color, vec2 uv1, float nightTime, float rainTime, float noLight)
{
	if(uv1.y == 0.0 && uv1.x == 0.0) return col;
	float ux = color.g + 0.35;
	if(isWater(color)) ux = color.r + color.g + color.b;
	float shadowX = 1.0 - min(max((ux - 0.89) * 20.0, 0.0), 1.0);
	float shadowY = 1.0 - min(max((uv1.y - 0.89) * 100.0, 0.0), 1.0);
	if(color.w == 0.0)
	{
		shadowY = 0.0;
		col *= 1.2;
	}
	
	col = mix(col, col * shadowColor, shadowX * noLight * (1.0 - shadowY) * uv1.y * (min(rainTime, nightTime) + 0.2));
	return col;
}




//Debug function
vec3 mix2(vec3 c1, vec3 c2, vec3 c3, float t)
{
	float alpha = clamp((t - 0.0) / (0.5 - 0.0), 0.0, 1.0);
	float beta = clamp((t - 0.5) / (1.0 - 0.5), 0.0, 1.0);
	vec3 c;
	if(t < 0.5) c = (1.0 - alpha) * c1 + alpha * c2;
	else c = (1.0 - beta) * c2 + beta * c3;
	return c;
}

float plot(vec2 st, float pct)
{
	return smoothstep(pct - 0.02, pct, st.y) - smoothstep(pct, pct + 0.02, st.y);
}
