#include "include/color.h"
#include "include/noise_fbm.h"

// Base code from Bicubic Shader
vec3 skyc(vec4 fcol, float dayTime, float nightTime, float duskTime, float rainTime, float lPos)
{
	vec3 scol = mix(daySkyColor, duskSkyColor, duskTime);
    scol = mix(scol, nightSkyColor, nightTime);
    scol = mix(scol, rainDaySkyColor, (rainTime * dayTime));
    scol = mix(scol, rainNightSkyColor, (rainTime * nightTime));

    vec3 col = mix(scol, vec3(fcol.r, fcol.g, fcol.b * 1.2) * 0.6, clamp(lPos, 0.0, 1.0));
    col = mix(col, fcol.rgb, clamp(pow(lPos, 1.5) * 1.0, 0.0, 1.0));
	col = mix(col, fcol.rgb, clamp(pow(lPos, 4.0) * 1.2, 0.0, 1.0));
    col = mix(col, vec3(fcol.rgb * 1.3), rainTime);
    col = mix(col, vec3(fcol.rgb * 1.5), clamp(lPos * 1.5, 0.0, 1.0) * rainTime);
    col = mix(col, vec3(fcol.rgb * 1.5), clamp(pow(lPos, 4.0) * 1.5, 0.0, 1.0) * rainTime);
	return col;
}

vec3 skyCloud(vec3 skyc, vec3 posi, float dayTime, float nightTime, float duskTime, float rainTime, float lPos)
{
	vec3 cc = mix(vec3(1.0), dayCloudColor, dayTime);
    cc = mix(cc, nightCloudColor, nightTime);
    cc = mix(cc, duskCloudColor, duskTime);
    cc = mix(cc, dayRainCloudColor, (rainTime * dayTime));
    cc = mix(cc, nightRainCloudColor, (rainTime * nightTime));
	float cm = fbm(posi.zx * 1.2);
	return mix(skyc, cc, cm * 2.0 * (1.0 - clamp(lPos * 1.7, 0.0, 1.0)));
}
