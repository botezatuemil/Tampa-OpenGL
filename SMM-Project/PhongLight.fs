
#version 330 core
out vec4 FragColor;

in vec3 Normal;  
in vec3 FragPos;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;


uniform float Ka;
uniform float Kd ;
uniform float n;
uniform float Ks;

void main()
{

vec3 ambient=(lightColor*Ka);

 vec3 lightDir=normalize(lightPos-FragPos);
 vec3 diffuse=lightColor*Kd*max(dot(Normal,lightDir),0.0);
 vec3 viewDir=normalize(viewPos-FragPos);
 vec3 reflectDir=reflect(-lightDir,normalize(Normal));
 float specFactor=pow(max(dot(viewDir,reflectDir),0.0),n);
 vec3 specularComponent=Ks*specFactor*lightColor;

 FragColor = vec4(ambient+diffuse+specularComponent,1.0)*vec4(objectColor, 1.0);
 
} 
