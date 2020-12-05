#include "include/color.h"

vec4 sunAndMoon(vec4 fcol, vec3 pos, float dayTime, float nightTime, float duskTime, float rainTime)
{
	float a = 1.0 - pow(length(pos * 105.0), 1.8);
	float b = 1.0 - pow(length(pos * 48.0), nightTime * 20.0 + 0.5);
	float c = 1.0 - pow(length(pos * 2.0), 0.5 * max(pow(fcol.g + 0.1, 10.0), 0.2));

	vec4 sunAndMoonColor = mix(daySunColor, duskSunColor, duskTime);
	sunAndMoonColor = mix(sunAndMoonColor, nightSunColor, nightTime);
	//sunAndMoonColor = mix(sunAndMoonColor, duskSunColor, duskTime);

	vec4 sunMoon = vec4(sunAndMoonColor.rgb, clamp(a, 0.0, 1.0));
	sunMoon = mix(sunMoon, sunAndMoonColor, clamp(b, 0.0, 1.0));
	sunMoon = mix(sunMoon, sunAndMoonColor, clamp(c, 0.0, 1.0)) * (1.0 - rainTime);
	return sunMoon;
}
 
