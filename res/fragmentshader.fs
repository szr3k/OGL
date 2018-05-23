#version 330 core
out vec4 FragColor;
precision highp float;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

struct Material {
    
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
}; 
  
uniform Material material;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform float time;

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 emission;
};

uniform Light light;  



void main()
{    
    
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	
    /*Emission */
    vec3 emission = vec3(0.0);
    if (texture(material.specular, TexCoords).r == 0.0)   /*rough check for blackbox inside spec texture */
    {
        /*apply emission texture */
        emission = texture(material.emission, TexCoords).rgb;
        
        /*some extra fun stuff with "time uniform" */
        emission = texture(material.emission, TexCoords + vec2(0.0,time)).rgb;   /*moving */
    
    }
		
 


    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));  
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
  
    vec3 result = ambient + diffuse + specular + emission;
    FragColor = vec4(result, 1.0);
	
	
}