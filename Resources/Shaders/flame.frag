#version 330 core

out vec4 FragColor;

in vec3 color;

uniform float time;
uniform float flameIntensity;

void main()
{
    vec3 innerColor = vec3(1.0, 1.0, 0.0);
    vec3 outerColor = vec3(1.0, 0.1, 0.0);
    vec3 flameColor = mix(outerColor, innerColor, color.r);

    float pulse = 0.6 + 0.4 * sin(time * 8.0);
    float alpha = flameIntensity * pulse;

    FragColor = vec4(flameColor, alpha);
}
