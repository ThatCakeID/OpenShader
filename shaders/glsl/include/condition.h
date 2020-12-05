#include "include/color.h"

bool isGrass(vec4 color) 
{
	vec3 hsv = rgb2hsv(color.rgb);
    float hue = hsv.x * 360.0;
    return (hsv.y > 0.1 && (hue < 149.0 && hue > 12.0));
}

bool getSandMask(vec2 uv0)
{
	vec2 matID = floor(vec2(uv0.x * 32., uv0.y * 32.));
	return ((matID.x>=0.&&matID.y>=12.&&
     matID.x<=3.&&matID.y<=12.)||
    (matID.x>=14.&&matID.y>=11.&&
     matID.x<=19.&&matID.y<=11.)||
    (matID.x>=28.&&matID.y>=11.&&
     matID.x<=30.&&matID.y<=11.));
}

bool getSnowMask(vec2 uv0)
{
	vec2 matID = floor(vec2(uv0.x * 32., uv0.y * 32.));
	return (matID.x == 14.0 && matID.y == 12.0);
}

bool getGrassSideSnowedMask(vec2 uv)
{
	vec2 matID = floor(vec2(uv0.x * 32.0, uv0.y * 32.0));
	return (matID.x == 26.0 && matID.y == 6.0);
}

bool isNether(vec4 fcol)
{
    return (fcol.r * 2.0 > fcol.g + fcol.b && fcol.r < 0.5 && fcol.b < 0.2);
}

bool isTheEnd(vec4 fcol) {
    return (fcol.r > fcol.g && fcol.b > fcol.g && fcol.r < 0.05 && fcol.b < 0.05 && fcol.g < 0.05);
}

bool isWater(vec4 color)
{
	vec3 hsv = rgb2hsv(color.rgb);
    float hue = hsv.x * 360.0;
    return (hsv.y > 0.1 && hue >= 149.0 && hue <= 270.0);
}

bool isWaterPlane(highp vec4 wpos) 
{
    highp float y = fract(wpos.y);
    return (y >= 0.7 && y <= 0.9);
}

bool isUnderwater(vec4 fcol)
{
	return (fcol.b >= fcol.r * 1.8 && fcol.g > fcol.r * 1.5  && fcol.b >= fcol.g * 1.1 && fcol.b > 0.15);
}

bool isPlant(vec4 col)
{
	#ifdef ALPHA_TEST
		if(col.g * 2.0 > col.r + col.b) return true;
	#endif
	return false;
}

bool isDay(vec4 fcol)
{
	return (fcol.r > .5 && fcol.b > .9);
}

bool isNight(vec4 fcol)
{
	return (fcol.r < .5 && fcol.b < .2);
}

bool isRain(vec2 fcon)
{
	return (fcon.x < .55 && fcon.x > .1);
}

float isClear(vec2 fcon) 
{
    return (smoothstep(0.8, 1.0, fcon.y));
}

bool isRenderDistanceFog(vec2 fcon)
{
    return (fcon.x > 0.6);
}

float distanceRender(float jarak) 
{
	return clamp(length(wpos) / RENDER_DISTANCE * jarak, 0.0, 1.0);
}
