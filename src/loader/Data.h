#ifndef DANZUN_DATA_H_INCLUDED
#define DANZUN_DATA_H_INCLUDED

namespace dan {
    class Data {
    public:
        typedef std::shared_ptr<dan::Texture> texture_t;
        typedef std::shared_ptr<dan::Animation> animation_t;
        typedef std::shared_ptr<dan::Shader> shader_t;
        typedef std::shared_ptr<dan::Font> font_t;
        // typedef std::shared_ptr<dan::AbsRenderConf> renderconf_t;
    private:
        std::map<std::string, texture_t> textures;
        std::map<std::string, animation_t> animations;
        std::map<std::string, shader_t> shaders;
        std::map<std::string, font_t> fonts;
    public:
        Data();
        
    }
}

#endif



