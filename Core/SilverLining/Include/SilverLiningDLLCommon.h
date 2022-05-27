// Copyright (c) 2004-2010  Sundog Software, LLC All rights reserved worldwide.

/**
    \file SilverLiningDLLCommon.h
    \brief Shared header for the specific renderer DLL's, and for use by the Renderer
    class of the engine.
 */

#ifndef SILVERLININGDLLCOMMON_H
#define SILVERLININGDLLCOMMON_H

#include "SilverLiningTypes.h"
#include "Color.h"
#include "Frustum.h"
#include "Matrix4.h"
#include "Vertex.h"
#include "ResourceLoader.h"
#include <vector>

// Passes in settings from Atmosphere::Initialize, including the env pointer that you can use to pass
// along device information or pointers to your engine. This is a good point to do any required initialization.
// Return a "context" object of your choosing, that will be passed back to you via SetContext() whenever the
// current Atmosphere changes.
SILVERLININGDLL_API void *           SetEnvironment(bool rightHanded, void *env, SilverLining::ResourceLoader *resourceLoader);
typedef void *                       (*SET_ENV_PROC)(bool, void *, SilverLining::ResourceLoader *);

// Called whenever the current Atmosphere changes, generally indicated a different viewport / render context
// is now in effect. The input is the object returned by SetEnvironment for this Atmosphere.
SILVERLININGDLL_API void             SetContext(void *context);
typedef void (*SET_CONTEXT_PROC)(void *);

// Clear the color buffer to the specified color.
SILVERLININGDLL_API void             ClearScreen(const SilverLining::Color& c);
typedef void (*CLEAR_SCREEN_PROC)(const SilverLining::Color&);

// Clear the depth buffer.
SILVERLININGDLL_API void             ClearDepth(void);
typedef void (*CLEAR_DEPTH_PROC)(void);

// Return the view frustum, transformed by the view matrix into world space.
SILVERLININGDLL_API bool             GetFrustumWorldSpace(SilverLining::Frustum& f);
typedef bool (*GET_FRUSTUM_WORLD_SPACE_PROC)(SilverLining::Frustum& f);

// Return the view frustum in the usual clip space.
SILVERLININGDLL_API bool             GetFrustumClipSpace(SilverLining::Frustum& f);
typedef bool (*GET_FRUSTUM_CLIP_SPACE_PROC)(SilverLining::Frustum& f);

// Return the position and size of the current viewport.
SILVERLININGDLL_API bool             GetViewport(int& x, int& y, int& w, int& h);
typedef bool (*GET_VIEWPORT_PROC)(int&, int&, int&, int&);

// Sets the position and size of the current viewport.
SILVERLININGDLL_API bool    SetViewport(int x, int y, int w, int h);
typedef bool (*SET_VIEWPORT_PROC)(int, int, int, int);

// Return the vertical field of view in radians.
SILVERLININGDLL_API bool             GetFOV(double& fov);
typedef bool (*GET_FOV_PROC)(double&);

// Load a shader from a source file. The filename will have the suffix ".cg" - swap this out if you're using
// a different shader suffix (such as .fx). Return a handle for referring to this shader later on.
SILVERLININGDLL_API SilverLining::ShaderHandle     LoadShaderFromFile(const char *fileName, int shaderType);
typedef SilverLining::ShaderHandle (*LOAD_SHADER_FROM_FILE_PROC)(const char *, int);

// OK to stub out and return NULL; this is no longer called.
SILVERLININGDLL_API SilverLining::ShaderHandle     LoadShaderFromSource(const char *shaderSource, int shaderType);
typedef SilverLining::ShaderHandle (*LOAD_SHADER_FROM_SOURCE_PROC)(const char *, int);

// Sets a 4D vector constant for the specified shader.
SILVERLININGDLL_API bool             SetConstantVector4(SilverLining::ShaderHandle shader, const char *varName, float *data);
typedef bool (*SET_CONSTANT_VECTOR4_PROC)(SilverLining::ShaderHandle, const char *, float *);

// Sets a 4x4 matrix constant for the specified shader.
SILVERLININGDLL_API bool             SetConstantMatrix4(SilverLining::ShaderHandle shader, const char *varName, float *data);
typedef bool (*SET_CONSTANT_MATRIX4_PROC)(SilverLining::ShaderHandle, const char *, float *);

// Make the specified shader active.
SILVERLININGDLL_API bool             BindShader(SilverLining::ShaderHandle shader, int shaderType);
typedef bool (*BIND_SHADER_PROC)(SilverLining::ShaderHandle, int);

// Make the specified shader not active (this can be a no-op)
SILVERLININGDLL_API bool             UnbindShader(int shaderType);
typedef bool (*UNBIND_SHADER_PROC)(int);

// Called when the Atmosphere is destroyed; perform any cleanup here.
SILVERLININGDLL_API bool             ShutdownShaderSystem(void *context);
typedef bool (*SHUTDOWN_SHADER_SYSTEM_PROC)(void *);

// Allocate a vertex buffer of some sort (using the Vertex format in Vertex.h) for the given number of vertices.
SILVERLININGDLL_API void *           AllocateVertexBuffer(int nVerts);
typedef void *                       (*ALLOCATE_VERTEX_BUFFER_PROC)(int);

// Lock the given vertex buffer such that it may be directly modified by the CPU.
SILVERLININGDLL_API bool             LockVertexBuffer(void *buffer);
typedef bool (*LOCK_VERTEX_BUFFER_PROC)(void *);

// Return a pointer to the vertex data of the given locked vertex buffer, such that modifications to it will
// be reflected when unlocked.
SILVERLININGDLL_API SilverLining::Vertex * GetVertices(void *buffer);
typedef SilverLining::Vertex *       (*GET_VERTICES_PROC)(void *);

// Unlocks the given vertex buffer - it may be inaccessible to the CPU after this.
SILVERLININGDLL_API bool             UnlockVertexBuffer(void *buffer);
typedef bool (*UNLOCK_VERTEX_BUFFER_PROC)(void *);

// Return a locked pointer to the vertex data for this buffer. This may be stubbed out by just returning false, and
// SilverLining will fall back to different methods.
SILVERLININGDLL_API bool    GetVertexBuffer(void *buffer, int offset, SilverLining::Vertex *verts, int nVerts);
typedef bool (*GET_VERTEX_BUFFER_PROC)(void*, int, SilverLining::Vertex*, int);

// Update the vertex data in the given buffer with the data passed in. This may be stubbed out by just returning false,
// and SilverLining will fall back to different methods.
SILVERLININGDLL_API bool    UpdateVertexBuffer(void *buffer, int offset, SilverLining::Vertex *verts, int nVerts);
typedef bool (*UPDATE_VERTEX_BUFFER_PROC)(void*, int, SilverLining::Vertex*, int);

// Dispose of the given vertex buffer.
SILVERLININGDLL_API bool             ReleaseVertexBuffer(void *buffer);
typedef bool (*RELEASE_VERTEX_BUFFER_PROC)(void *);

// Make the specified vertex buffer active. If vertexColors is true, use the color information in the vertex data.
SILVERLININGDLL_API bool             SetVertexBuffer(void *buffer, bool vertexColors);
typedef bool (*SET_VERTEX_BUFFER_PROC)(void *, bool);

// Make the specified vertex buffer no longer active. This may be a no-op.
SILVERLININGDLL_API bool             UnsetVertexBuffer();
typedef bool (*UNSET_VERTEX_BUFFER_PROC)(void);

// Allocate an index buffer of shorts for the given number of indices.
SILVERLININGDLL_API void *           AllocateIndexBuffer(int nIndices);
typedef void *                       (*ALLOCATE_INDEX_BUFFER_PROC)(int);

// Lock the given index buffer for writing.
SILVERLININGDLL_API bool             LockIndexBuffer(void *buffer);
typedef bool (*LOCK_INDEX_BUFFER_PROC)(void *);

// Retrieve a pointer to the locked index data for writing.
SILVERLININGDLL_API SilverLining::Index * GetIndices(void *buffer);
typedef SilverLining::Index *       (*GET_INDICES_PROC)(void *);

// Unlock the given index buffer. Writes may no longer be possible after calling this.
SILVERLININGDLL_API bool             UnlockIndexBuffer(void *buffer);
typedef bool (*UNLOCK_INDEX_BUFFER_PROC)(void *);

// Dispose of the given index buffer.
SILVERLININGDLL_API bool             ReleaseIndexBuffer(void *buffer);
typedef bool (*RELEASE_INDEX_BUFFER_PROC)(void *);

// Make the given index buffer active.
SILVERLININGDLL_API bool             SetIndexBuffer(void *buffer);
typedef bool (*SET_INDEX_BUFFER_PROC)(void *);

// Make the given index buffer no longer active (this may be a no-op)
SILVERLININGDLL_API bool             UnsetIndexBuffer();
typedef bool (*UNSET_INDEX_BUFFER_PROC)(void);

// Draw a triangle strip using the specified index buffer and index range.
SILVERLININGDLL_API bool             DrawStrip(void *indexBuffer, int startIdx, int nIndices, int numVerts);
typedef bool (*DRAW_STRIP_PROC)(void *, int, int, int);

// Draw a series of points of the given point size using the currently active vertex buffer.
SILVERLININGDLL_API bool             DrawPoints(double pointSize, int nPoints, int start);
typedef bool (*DRAW_POINTS_PROC)(double, int, int);

// Return false unless you want to implement DrawQuads(). SilverLining will fall back to triangle strips.
SILVERLININGDLL_API bool             HasQuads();
typedef bool (*HAS_QUADS_PROC)(void);

SILVERLININGDLL_API bool             DrawQuads(int nPoints, int start);
typedef bool (*DRAW_QUADS_PROC)(int, int);

// Set whether depth writes are enabled.
SILVERLININGDLL_API bool             EnableDepthWrites(bool);
typedef bool (*ENABLE_DEPTH_WRITES_PROC)(bool);

// Set whether depth reads are enabled.
SILVERLININGDLL_API bool             EnableDepthReads(bool);
typedef bool (*ENABLE_DEPTH_READS_PROC)(bool);

// Set whether 2D texture mapping is enabled.
SILVERLININGDLL_API bool             EnableTexture2D(bool);
typedef bool (*ENABLE_TEXTURE_2D_PROC)(bool);

// Set whether backface culling is enabled.
SILVERLININGDLL_API bool             EnableBackfaceCulling(bool);
typedef bool (*ENABLE_BACKFACE_CULLING_PROC)(bool);

// Set whether exponential fog is enabled.
SILVERLININGDLL_API bool             EnableFog(bool);
typedef bool (*ENABLE_FOG_PROC)(bool);

// Configure exponential fog using the specified density and color. Start and end are currently ignored.
SILVERLININGDLL_API bool    ConfigureFog(double density, double start, double end, const SilverLining::Color& c);
typedef bool (*CONFIGURE_FOG_PROC)(double, double, double, const SilverLining::Color&);

// Set whether per-vertex lighting is enabled.
SILVERLININGDLL_API bool             EnableLighting(bool);
typedef bool (*ENABLE_LIGHTING_PROC)(bool);

// Set the current color for use when vertex colors are disabled.
SILVERLININGDLL_API bool             SetCurrentColor(const SilverLining::Color& c);
typedef bool (*SET_CURRENT_COLOR_PROC)(const SilverLining::Color&);

// Retrieve the current projection matrix.
SILVERLININGDLL_API bool             GetProjectionMatrix(SilverLining::Matrix4 *m);
typedef bool (*GET_PROJECTION_MATRIX_PROC)(SilverLining::Matrix4 *m);

// Set the current projection matrix.
SILVERLININGDLL_API bool             SetProjectionMatrix(const SilverLining::Matrix4& m);
typedef bool (*SET_PROJECTION_MATRIX_PROC)(const SilverLining::Matrix4&);

// Set the projection matrix to the given orthographic matrix.
SILVERLININGDLL_API bool             SetOrthoMatrix(double left, double right, double bottom, double top, double pnear, double pfar);
typedef bool (*SET_ORTHO_MATRIX_PROC)(double, double, double, double, double, double);

// Set the projection matrix to the given 2D orthographic matrix.
SILVERLININGDLL_API bool             Set2DOrthoMatrix(double w, double h);
typedef bool (*SET_2D_ORTHO_MATRIX_PROC)(double, double);

// Get the currently active texture matrix.
SILVERLININGDLL_API bool    GetTextureMatrix(SilverLining::Matrix4 *m);
typedef bool (*GET_TEXTURE_MATRIX_PROC)(SilverLining::Matrix4 *m);

// Set the currently active texture matrix.
SILVERLININGDLL_API bool    SetTextureMatrix(const SilverLining::Matrix4& m);
typedef bool (*SET_TEXTURE_MATRIX_PROC)(const SilverLining::Matrix4&);

// Get the current view matrix.
SILVERLININGDLL_API bool             GetModelviewMatrix(SilverLining::Matrix4 *m);
typedef bool (*GET_MODELVIEW_MATRIX_PROC)(SilverLining::Matrix4 *m);

// Set the current view matrix.
SILVERLININGDLL_API bool             SetModelviewMatrix(const SilverLining::Matrix4& m);
typedef bool (*SET_MODELVIEW_MATRIX_PROC)(const SilverLining::Matrix4&);

// Multiply the current view matrix by the given matrix.
SILVERLININGDLL_API bool             MultiplyModelviewMatrix(const SilverLining::Matrix4& m);
typedef bool (*MULTIPLY_MODELVIEW_MATRIX_PROC)(const SilverLining::Matrix4&);

// Push all view and projection transforms onto the stack.
SILVERLININGDLL_API bool             PushTransforms(void);
typedef bool (*PUSH_TRANSFORMS_PROC)(void);

// Restore the view and projection matrices from the stack.
SILVERLININGDLL_API bool             PopTransforms(void);
typedef bool (*POP_TRANSFORMS_PROC)(void);

// Push all rendering state onto the stack.
SILVERLININGDLL_API bool             PushAllState(void);
typedef bool (*PUSH_ALL_STATE_PROC)(void);

// Restore all rendering state from the stack.
SILVERLININGDLL_API bool             PopAllState(void);
typedef bool (*POP_ALL_STATE_PROC)(void);

// Set default rendering state.
SILVERLININGDLL_API bool    SetDefaultState(void);
typedef bool (*SET_DEFAULT_STATE_PROC)(void);

// Enable the given blending mode.
SILVERLININGDLL_API bool             EnableBlending(int srcFactor, int dstFactor);
typedef bool (*ENABLE_BLENDING_PROC)(int, int);

// Disable blending.
SILVERLININGDLL_API bool             DisableBlending(void);
typedef bool (*DISABLE_BLENDING_PROC)(void);

// Load a 2D texture from the given filename. Return a handle to the texture in texHandle.
// u,v wrapping is specified in the boolean parameters.
SILVERLININGDLL_API bool             LoadTextureFromFile(const char *imgPath, SilverLining::TextureHandle *texHandle, bool wrapU, bool wrapV);
typedef bool (*LOAD_TEXTURE_FROM_FILE_PROC)(const char *, SilverLining::TextureHandle *, bool, bool);

// Returns whether floating point textures are supported. This is only needed for glare effects, which are disabled
// by default, so you can return false and be done with it and with implmenting LoadFloatTextureRGB / LoadFloatTexture.
SILVERLININGDLL_API bool             HasFloatTextures();
typedef bool (*HAS_FLOAT_TEXTURES_PROC)(void);

SILVERLININGDLL_API bool             LoadFloatTextureRGB(float *data, int width, int height, SilverLining::TextureHandle *texHandle);
typedef bool (*LOAD_FLOAT_TEXTURE_RGB_PROC)(float *, int, int, SilverLining::TextureHandle *);

SILVERLININGDLL_API bool             LoadFloatTexture(float *data, int width, int height, SilverLining::TextureHandle *texHandle);
typedef bool (*LOAD_FLOAT_TEXTURE_PROC)(float *, int, int, SilverLining::TextureHandle *);

// Load a 2D texture from the bytes passed in explicitly.
SILVERLININGDLL_API bool             LoadTexture(unsigned char *data, int width, int height, SilverLining::TextureHandle *texHandle, bool, bool);
typedef bool (*LOAD_TEXTURE_PROC)(unsigned char *, int, int, SilverLining::TextureHandle *, bool, bool);

// Enable the given texture on the given texture layer.
SILVERLININGDLL_API bool             EnableTexture(SilverLining::TextureHandle texture, int stage);
typedef bool (*ENABLE_TEXTURE_PROC)(SilverLining::TextureHandle, int);

// Disable the current texture on the given texture layer.
SILVERLININGDLL_API bool             DisableTexture(int stage);
typedef bool (*DISABLE_TEXTURE_PROC)(int);

// Release the given texture's resources.
SILVERLININGDLL_API bool             ReleaseTexture(SilverLining::TextureHandle texture);
typedef bool (*RELEASE_TEXTURE_PROC)(SilverLining::TextureHandle);

// Create a 2D texture map that's only required to store a single byte of luminance information per texel.
// The luminance textures only need to be implemented if you want to support the automatic generation of
// shadow maps from the clouds.
SILVERLININGDLL_API bool    CreateLuminanceTexture(int w, int h, SilverLining::TextureHandle *texture);
typedef bool (*CREATE_LUMINANCE_TEXTURE_PROC)(int, int, SilverLining::TextureHandle*);

// Copy 8-bit luminance data into the given luminance texture.
SILVERLININGDLL_API bool    CopyLuminanceIntoTexture(SilverLining::TextureHandle texture, int w, int h, unsigned char *buf);
typedef bool (*COPY_LUMINANCE_INTO_TEXTURE_PROC)(SilverLining::TextureHandle, int, int, unsigned char *);

// Copy an area of the screen into the given buffer as 8-bit luminance data.
SILVERLININGDLL_API bool    CopyLuminanceFromScreen(int x, int y, int w, int h, unsigned char *buf);
typedef bool (*COPY_LUMINANCE_FROM_SCREEN_PROC)(int, int, int, int, unsigned char *);

// Returns if point sprites are supported by this renderer. You can just return false and SilverLining will draw
// billboards on its own using triangle strips.
SILVERLININGDLL_API bool             HasPointSprites();
typedef bool (*HAS_POINT_SPRITES_PROC)(void);

SILVERLININGDLL_API bool             EnablePointSprites(double pointSize);
typedef bool (*ENABLE_POINT_SPRITES_PROC)(double);

SILVERLININGDLL_API bool             DisablePointSprites(void);
typedef bool (*DISABLE_POINT_SPRITES_PROC)(void);

// You can just return false for all the render target functions - they are only used if you set
// cumulus-lighting-quick-and-dirty to false in SilverLining.config, which it isn't by default.
SILVERLININGDLL_API bool    InitRenderTarget(int w, int h, SilverLining::RenderTargetHandle *tgtHandle);
typedef bool (*INIT_RENDER_TARGET_PROC)(int, int, SilverLining::RenderTargetHandle *);

SILVERLININGDLL_API bool             InitRenderTexture(int w, int h, SilverLining::RenderTextureHandle *texHandle);
typedef bool (*INIT_RENDER_TEXTURE_PROC)(int, int, SilverLining::RenderTextureHandle *);

SILVERLININGDLL_API bool    MakeRenderTargetCurrent(SilverLining::RenderTargetHandle tgtHandle);
typedef bool (*MAKE_RENDER_TARGET_CURRENT_PROC)(SilverLining::RenderTargetHandle);

// You can just return false for all the render texture functions - they are only used if impostors are enabled
// in SilverLining.config, which they aren't by default.
SILVERLININGDLL_API bool             MakeRenderTextureCurrent(SilverLining::RenderTextureHandle texHandle);
typedef bool (*MAKE_RENDER_TEXTURE_CURRENT_PROC)(SilverLining::RenderTextureHandle);

SILVERLININGDLL_API bool    RestoreRenderTarget(SilverLining::RenderTargetHandle tgtHandle);
typedef bool (*RESTORE_RENDER_TARGET_PROC)(SilverLining::RenderTargetHandle);

SILVERLININGDLL_API bool             BindRenderTexture(SilverLining::RenderTextureHandle texHandle);
typedef bool (*BIND_RENDER_TEXTURE_PROC)(SilverLining::RenderTextureHandle);

SILVERLININGDLL_API bool             GetRenderTextureTextureHandle(SilverLining::RenderTextureHandle renTexHandle, SilverLining::TextureHandle *texHandle);
typedef bool (*GET_RENDER_TEXTURE_TEXTURE_HANDLE_PROC)(SilverLining::RenderTextureHandle, SilverLining::TextureHandle *);

SILVERLININGDLL_API bool    ReleaseRenderTarget(SilverLining::RenderTargetHandle tgtHandle);
typedef bool (*RELEASE_RENDER_TARGET_PROC)(SilverLining::RenderTargetHandle);

SILVERLININGDLL_API bool             ReleaseRenderTexture(SilverLining::RenderTextureHandle texHandle);
typedef bool (*RELEASE_RENDER_TEXTURE_PROC)(SilverLining::RenderTextureHandle);

// Reads back RGBA data from the current color buffer. You can just return false and leave this unimplemented
// unless you set cumulus-lighting-quick-and-dirty to false, which it isn't by default.
SILVERLININGDLL_API bool             GetPixels(int x, int y, int w, int h, void *pixels);
typedef bool (*GET_PIXELS_PROC)(int, int, int, int, void *);

// Draws the given RGBA data to the area of the current color buffer.
SILVERLININGDLL_API bool             SetPixels(int x, int y, int w, int h, void *pixels);
typedef bool (*SET_PIXELS_PROC)(int, int, int, int, void *);

// Draw a (preferably) anti-aliased line of the given color and width between two points.
SILVERLININGDLL_API bool             DrawAALine(const SilverLining::Color& c, double width, const SilverLining::Vector3& p1, const SilverLining::Vector3& p2);
typedef bool (*DRAW_AA_LINE_PROC)(const SilverLining::Color& c, double, const SilverLining::Vector3&, const SilverLining::Vector3&);

// Draw (preferably) anti-aliased lines connecting the given vector points using the given color and width.
SILVERLININGDLL_API bool             DrawAALines(const SilverLining::Color& c, double width, const std::vector<SilverLining::Vector3>& points);
typedef bool (*DRAW_AA_LINES_PROC)(const SilverLining::Color& c, double width, const std::vector<SilverLining::Vector3>&);

// Begin an occlusion query - everything drawn between StartOcclusionQuery and EndOcclusionQuery will
// count up the number of fragments that pass the depth and stencil tests. If you choose not to implement
// the occlusion query interface, it just means that the optional lens flare effect won't be disabled
// when the sun is occluded, and sun/moon occlusion data won't be passed back to the application.
SILVERLININGDLL_API bool             StartOcclusionQuery(SilverLining::QueryHandle *queryHandle);
typedef bool (*START_OCCLUSION_QUERY_PROC)(SilverLining::QueryHandle *queryHandle);

// End the occlusion query.
SILVERLININGDLL_API bool             EndOcclusionQuery(SilverLining::QueryHandle queryHandle);
typedef bool (*END_OCCLUSION_QUERY_PROC)(SilverLining::QueryHandle);

// Get the results of the occlusion query (must be called after StartOcclusionQuery and EndOcclusionQuery).
// The number of fragments that passed the depth and stencil tests during the query is returned.
SILVERLININGDLL_API unsigned int     GetOcclusionQueryResult(SilverLining::QueryHandle queryHandle);
typedef unsigned int (*GET_OCCLUSION_QUERY_RESULT_PROC)(SilverLining::QueryHandle);
#endif
