
texture source0;
float glowPowerValue;
sampler sampler0 = sampler_state
{
	Texture = <source0>;
};
float4 MAIN_GLOW( float2 i : TEXCOORD0 ) : COLOR
{
	float4 o = tex2D( sampler0, i );

	return pow( o, glowPowerValue );
}
float4 MAIN_BLURX( float2 i : TEXCOORD0) : COLOR
{
	float4 o = 0.0f;

	o += ( 0.1f * ( tex2D( sampler0, ( i + float2( -0.01171875f, 0.0f ) ) ) ) );
	o += ( 0.358f * ( tex2D( sampler0, ( i + float2( -0.00781250f, 0.0f ) ) ) ) );
	o += ( 0.773f * ( tex2D( sampler0, ( i + float2( -0.00390625f, 0.0f ) ) ) ) );
	o += ( tex2D( sampler0, ( i + float2( 0.0f, 0.0f ) ) ) );
	o += ( 0.773f * ( tex2D( sampler0, ( i + float2( +0.00390625f, 0.0f ) ) ) ) );
	o += ( 0.358f * ( tex2D( sampler0, ( i + float2( +0.00781250f, 0.0f ) ) ) ) );
	o += ( 0.1f * ( tex2D( sampler0, ( i + float2( +0.01171875f, 0.0f ) ) ) ) );
	return ( o / 3.0f );
}
float4 MAIN_BLURY( float2 i : TEXCOORD0) : COLOR
{
	float4 o = 0.0f;

	o += ( 0.1f * ( tex2D( sampler0, ( i + float2( 0.0f, -0.01171875f ) ) ) ) );
	o += ( 0.358f * ( tex2D( sampler0, ( i + float2( 0.0f, -0.00781250f ) ) ) ) );
	o += ( 0.773f * ( tex2D( sampler0, ( i + float2( 0.0f, -0.00390625f ) ) ) ) );
	o += ( tex2D( sampler0, ( i + float2( 0.0f, 0.0f ) ) ) );
	o += ( 0.773f * ( tex2D( sampler0, ( i + float2( 0.0f, +0.00390625f ) ) ) ) );
	o += ( 0.358f * ( tex2D( sampler0, ( i + float2( 0.0f, +0.00781250f ) ) ) ) );
	o += ( 0.1f * ( tex2D( sampler0, ( i + float2( 0.0f, +0.01171875f ) ) ) ) );
	return ( o / 3.0f );
}
technique FILTER
{
	pass P0
	{
		PixelShader = compile ps_2_0 MAIN_GLOW();
	}
	pass P1
	{
		PixelShader = compile ps_2_0 MAIN_BLURX();
	}
	pass P2
	{
		PixelShader = compile ps_2_0 MAIN_BLURY();
	}
}
