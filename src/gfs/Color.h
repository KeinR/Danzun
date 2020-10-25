#ifndef DANZUN_COLOR_H_INCLUDED
#define DANZUN_COLOR_H_INCLUDED

namespace dan {
    class Context;
}

namespace dan {
    class Color {
    public:
        typedef unsigned int hex_t;
        typedef unsigned char value_t;
        typedef float prop_t;
    private:
        prop_t color[4];
    public:
        Color();
        Color(prop_t r, prop_t g, prop_t b, prop_t a = 1.0f);
        Color(hex_t hex);

        Color &operator=(hex_t hex);

        prop_t operator[](int index) const;
        bool operator==(const Color &other) const;
        bool operator!=(const Color &other) const;

        void setHex(hex_t hex);

        void setVal(value_t red, value_t green, value_t blue);
        void setAlpha(value_t alpha);

        hex_t getHex() const;

        prop_t *get();

        // NOTE: ATM loads all 4 channels!
        void load(Context &c) const;

        Color brighten(float percent) const;
    };
}

#endif
