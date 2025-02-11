#version 400
                                                                        
in vec2 texCoord0;                                                                       
in mat3 tbnMatrix0;                                                                 
in vec3 worldPos0;  
in vec3 normal0;

uniform vec3 Color;
uniform float Roughness;
uniform float Metalness;
uniform vec3 Normal;

uniform float NEAR_CLIP;
uniform float FAR_CLIP; 
uniform int	MAT_ID;

layout (location = 0) out vec4 WorldPosOut;   
layout (location = 1) out vec4 AlbedoOut;  
layout (location = 2) out vec4 RMAOOut;	      
layout (location = 3) out vec3 NormalOut;     
layout (location = 4) out vec3 TexCoordOut;	

float linearizeDepth(float depth);
														
void main()	{											
	WorldPosOut.rgb		= worldPos0;	
	WorldPosOut.a		= linearizeDepth(gl_FragCoord.z);	

	AlbedoOut.rgb		= Color;		
	AlbedoOut.a			= MAT_ID;			
	TexCoordOut			= vec3(texCoord0, 0.0);
	vec3 sampledNormal	= ((255.0/128.0) * Normal)-1;
	NormalOut			= normalize(tbnMatrix0 * sampledNormal);	
	RMAOOut.r			= Roughness;	
	RMAOOut.g			= Metalness;									
	RMAOOut.b			= 1.0f;	
}
float linearizeDepth(float depth) {
    float z = depth * 2.0 - 1.0;
    return (2.0 * NEAR_CLIP * FAR_CLIP) / (FAR_CLIP + NEAR_CLIP - z * (FAR_CLIP - NEAR_CLIP));	
}
