/*
 * Copyright (c) 2016 CartoDB. All rights reserved.
 * Copying and using this code is allowed only according
 * to license terms, as given in https://cartodb.com/terms/
 */

#ifndef _CARTO_WATERMARKRENDERER_H_
#define _CARTO_WATERMARKRENDERER_H_

#include "graphics/utils/GLContext.h"

#include <memory>

#include <cglib/vec.h>
#include <cglib/mat.h>

namespace carto {
    class Bitmap;
    class Options;
    class ShaderManager;
    class TextureManager;
    class Shader;
    class Texture;
    class ViewState;
    
    class WatermarkRenderer {
    public:
        explicit WatermarkRenderer(const Options& options);
        virtual ~WatermarkRenderer();
    
        void onSurfaceCreated(const std::shared_ptr<ShaderManager>& shaderManager, const std::shared_ptr<TextureManager>& textureManager);
        void onSurfaceChanged(int width, int height);
        void onDrawFrame(const ViewState& viewState);
        void onSurfaceDestroyed();
    
    protected:
        void drawWatermark(const ViewState& viewState);
        
        static const int FIXED_WATERMARK_PADDING_X;
        static const int FIXED_WATERMARK_PADDING_Y;
        
        static const int WATERMARK_WIDTH_DP;

        static const std::string WATERMARK_VERTEX_SHADER;
        static const std::string WATERMARK_FRAGMENT_SHADER;
        
        float _randomAlignmentX;
        float _randomAlignmentY;
    
        std::shared_ptr<Bitmap> _watermarkBitmap;
        std::shared_ptr<Texture> _watermarkTex;

        float _watermarkCoords[12];
        float _watermarkTexCoords[8];
        
        cglib::mat4x4<float> _modelviewProjectionMat;
        
        bool _surfaceChanged;
    
        std::shared_ptr<Shader> _shader;
        GLuint _u_tex;
        GLuint _u_mvpMat;
        GLuint _a_coord;
        GLuint _a_texCoord;

        std::shared_ptr<TextureManager> _textureManager;
    
        const Options& _options;
    };
    
}

#endif
