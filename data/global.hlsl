// Global constant buffers
// Just a test for d3dcompile includes

#ifndef GLOBAL_HLSL
#define GLOBAL_HLSL

cbuffer CBModelViewProjection : register(b0)
{
	float4x4 matViewProjection;
};

#endif // GLOBAL_HLSL