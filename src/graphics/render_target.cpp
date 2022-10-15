#include "render_target.h"

#include <glad/glad.h>

#include "../global.h"

constexpr static float quad_vertices[] = {
     -1.0f,  1.0f, 0.0f, 1.0f,
     -1.0f, -1.0f, 0.0f, 0.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
     -1.0f,  1.0f, 0.0f, 1.0f,
      1.0f, -1.0f, 1.0f, 0.0f,
      1.0f,  1.0f, 1.0f, 1.0f
 };

namespace graphics {
    RenderTarget::RenderTarget() {
        screen_shader.link();

        screen_vertex_buffer.add_vertex_attribute({ 2, GL_FLOAT, sizeof(float), false });
        screen_vertex_buffer.add_vertex_attribute({ 2, GL_FLOAT, sizeof(float), false });
        
        glEnable(GL_MULTISAMPLE);
        
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        
        glEnable(GL_CULL_FACE);
        
        glGenFramebuffers(1, &framebuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        
        // creationg framebuffer for multi-sample or without
        auto screen_width = global.graphic_options->size().width();
        auto screen_height = global.graphic_options->size().height();

        if (global.graphic_options->antialiasing) {
            glGenTextures(1, &texture_color_buffer_multi_sampled);
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, texture_color_buffer_multi_sampled);
            glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, screen_width, screen_height, GL_TRUE);
        
            glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, texture_color_buffer_multi_sampled, 0);
        
            glGenRenderbuffers(1, &render_buffer_object);
            glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object);
            glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, screen_width, screen_height);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer_object);
        } else {
            glGenRenderbuffers(1, &render_buffer_object);
            glBindRenderbuffer(GL_RENDERBUFFER, render_buffer_object);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screen_width, screen_height);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, render_buffer_object);
        }
        
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            printf("ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n");
        
        if (global.graphic_options->antialiasing) {
            // post-processing framebuffer object configuration
            glGenFramebuffers(1, &intermediate_fbo);
            glBindFramebuffer(GL_FRAMEBUFFER, intermediate_fbo);
        }
        
        // setup texture for framebuffer
        glGenTextures(1, &texture_color_buffer);
        glBindTexture(GL_TEXTURE_2D, texture_color_buffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, screen_width, screen_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_color_buffer, 0);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    RenderTarget::~RenderTarget() {
        glDeleteFramebuffers(1, &framebuffer);
        glDeleteRenderbuffers(1, &render_buffer_object);
        glDeleteTextures(1, &texture_color_buffer);
    }

    void RenderTarget::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
        glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)
    }

    void RenderTarget::clear() {
        glClearColor(0, 0, 0, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderTarget::unbind() {
        if (global.graphic_options->antialiasing) {
            auto src_width = global.graphic_options->size().width();
            auto src_height = global.graphic_options->size().height();
            glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
            glBindFramebuffer(GL_DRAW_FRAMEBUFFER, intermediate_fbo);
            glBlitFramebuffer(0, 0, src_width, src_height, 0, 0, src_width, src_height, GL_COLOR_BUFFER_BIT, GL_NEAREST);
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // disable depth test so screen-space quad isn't discarded due to depth test
        glDisable(GL_DEPTH_TEST);
    }

    void RenderTarget::render() {
        // clear all relevant buffers
        glClear(GL_COLOR_BUFFER_BIT);

        screen_shader.use();
        screen_array_buffer.set_data(0, sizeof(quad_vertices), &quad_vertices);
        screen_vertex_buffer.bind();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_color_buffer);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void RenderTarget::enable_depth_test() {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);
    }

    void RenderTarget::disable_depth_test() {
        glDisable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
    }
}
