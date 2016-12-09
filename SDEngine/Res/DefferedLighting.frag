#version 400
                                                                        
in vec2 texCoord0;                                                                  

uniform vec3 cameraPos;

uniform sampler2D worldPosition;
uniform sampler2D albedo;
uniform sampler2D emissive;
uniform sampler2D RMAO;
uniform sampler2D normal;
uniform sampler2D texCoord;

const int NUM_LIGHTS = 100;
struct LightInfo {
	float Intensity;
	vec3 Color;
	float Attenuation;
	vec3 Position;
	vec3 Direction;
};
uniform	LightInfo lights[NUM_LIGHTS];
	 	
out vec4 fragColor;

vec3 PointLight(vec3 P, vec3 N, vec3 lightCentre, float lightRadius, vec3 lightColour, float lightIntensity, float cutoff);
vec3 Luminance();	
					
void main()	{	
    fragColor = texture(albedo, texCoord0) * vec4(Luminance(), 1.0);// * texture(RMAO, texCoord0).b;
}
vec3 Luminance() {
	vec3 finalLightIntensity = vec3(0.05f,0.05f,0.05f);
	for(int i=0; i<NUM_LIGHTS; i++) {
		finalLightIntensity += PointLight(texture(worldPosition, texCoord0).xyz, texture(normal, texCoord0).xyz, lights[i].Position, lights[i].Attenuation, lights[i].Color, lights[i].Intensity, 0.02f);	
	}
	return finalLightIntensity;
}
vec3 PointLight(vec3 fragmentPosition, vec3 N, vec3 lightCentre, float lightRadius, vec3 lightColour, float lightIntensity, float cutoff) {
    // calculate normalized light vector and distance to sphere light surface
    float r = lightRadius;
    vec3 L = lightCentre - fragmentPosition;
    float dist = length(L);
    float d = max(dist - r, 0);
    L /= dist;
    //N.y = -N.y;
    // calculate basic attenuation
    float denom = d/r + 1;
    float attenuation = 1 / (denom*denom);
     
    // scale and bias attenuation such that:
    //   attenuation == 0 at extent of max influence
    //   attenuation == 1 when d == 0
    attenuation = (attenuation - cutoff) / (1 - cutoff);
    attenuation = max(attenuation, 0);

    // Specular
    float LdotN = max(dot(-L, N), 0.0);

	float roughness = (texture(RMAO, texCoord0).r);
	vec3 eyeDir = cameraPos - texture(worldPosition, texCoord0).xyz;


	float specularIntensity = 0.0f;
    vec3 halfDir = normalize(L + eyeDir);
    float specAngle = max(dot(halfDir, N), 0.0);
    specularIntensity = pow(specAngle, 32.0);

    return ((lightColour * lightIntensity) + specularIntensity) * LdotN * attenuation;
}
