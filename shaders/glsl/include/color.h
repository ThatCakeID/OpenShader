vec3 dayWorldColor = vec3(235.0/255.0, 238.0/255.0, 235.0/255.0);
vec3 nightWorldColor = vec3(0.47, 0.55, 0.76);
vec3 duskWorldColor = vec3(1.6, 1.0, 0.5);
vec3 rainDayWorldColor = vec3(0.33, 0.4, 0.26);
vec3 rainNightWorldColor = vec3(0.77, 0.67, 0.62);

vec3 leavesColor = vec3(0.74, 0.84, 0.96);
vec3 shadowColor = vec3(0.76, 0.83, 0.97);

vec3 daySkyColor = vec3(0.2, 0.42, 0.66);
vec3 nightSkyColor = vec3(0.0, 0.4, 0.67) * 0.4;
vec3 duskSkyColor = vec3(0.15, 0.35, 0.42);
vec3 rainDaySkyColor = vec3(1.0, 1.0, 1.0);
vec3 rainNightSkyColor = vec3(1.0, 1.0, 1.0);

vec3 dayCloudColor = vec3(1.2, 1.2, 1.2);
vec3 nightCloudColor = vec3(0.01, 0.012, 0.015);
vec3 duskCloudColor = vec3(1.3, 0.78, 0.33) * 2.0;
vec3 dayRainCloudColor = vec3(0.0, 0.0, 0.0);
vec3 nightRainCloudColor = vec3(0.0, 0.0, 0.0);

vec4 daySunColor = vec4(1.0, 0.7, 0.2, 1.0);
vec4 nightSunColor = vec4(1.0, 0.9, 0.8, 1.0);
vec4 duskSunColor = vec4(1.6, 0.7, -0.4, 1.0);

vec3 dayFogColor = vec3(0.9, 0.9, 0.9);
vec3 nightFogColor = vec3(0.1, 0.1, 0.1);
vec3 duskFogColor = vec3(0.4, 0.3, 0.2);

vec3 torchColor = vec3(235.0/255.0, 215.0/255.0, 185.0/255.0);
vec3 torchUnderwaterColor = vec3(76.0/255.0, 175.0/255.0, 275.0/255.0);
vec3 torchUnderwaterColor2 = vec3(43.0/255.0, 61.0/255.0, 210.0/255.0);

float distance_limit = 3.5;
float transWater = 0.3;
vec3 waterColor = vec3(1.0, 1.0, 1.4);
vec3 netherColor = vec3(1.8, 1.0, 1.0);
vec3 netherLightColor = vec3(0.25, 0.0, 0.0);

vec3 saturation(vec3 rgb, float adjustment)
{
    //Algorithm from Chapter 16 of OpenGL Shading Language
    vec3 W = vec3(0.2125, 0.7154, 0.0721);
    float gray = dot(rgb, W);
    vec3 intensity = vec3(gray, gray, gray);
    return mix(intensity, rgb, adjustment);
}

float filmic_curve(float x) {

// Shoulder strength
float A = 0.22;
// Linear strength
float B = 0.5;
// Linear angle
float C = 0.15;
// Toe strength
float D = 0.4 * 0.9;
// Toe numerator
float E = 0.01;
// Toe denominator
float F = 0.2;

return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;

}

vec3 doToneMapping(vec3 clr) {

float W = 1.0 / 1.1;

float Luma = dot(clr, vec3(0.100, 0.3, 0.3));
vec3 Chroma = clr - Luma;
clr = (Chroma * 1.0) + Luma;

  clr = vec3(filmic_curve(clr.r), filmic_curve(clr.g), filmic_curve(clr.b)) / filmic_curve(W);

return clr;
}

vec3 rgb2hsv(vec3 c) 
{
    const vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);
    vec4 p = c.g < c.b ? vec4(c.bg, K.wz) : vec4(c.gb, K.xy);
    vec4 q = c.r < p.x ? vec4(p.xyw, c.r) : vec4(c.r, p.yzx);

    float d = q.x - min(q.w, q.y);
    const float e = 1.0e-10;
    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);
}
