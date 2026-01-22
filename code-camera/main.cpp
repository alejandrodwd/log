#include <cstdint>
#include <cstddef>
#include <vector>
#include <cstdlib>
#include <cstdio>

class Raw10Unpacker {
public:
    // in: packed RAW10 buffer
    // out: unpacked 16-bit pixels
    // pixelCount: number of pixels (must be multiple of 4)
    static void unpack(const uint8_t* in, uint16_t* out, size_t pixelCount) {
        for (size_t i = 0; i < pixelCount; i += 4) {
            uint8_t b0 = *in++;
            uint8_t b1 = *in++;
            uint8_t b2 = *in++;
            uint8_t b3 = *in++;
            uint8_t b4 = *in++;

            out[0] = (uint16_t)(b0 | ((b4 & 0x03) << 8));
            out[1] = (uint16_t)(b1 | ((b4 & 0x0C) << 6));
            out[2] = (uint16_t)(b2 | ((b4 & 0x30) << 4));
            out[3] = (uint16_t)(b3 | ((b4 & 0xC0) << 2));

            out += 4;
        }
    }
};


static void generateTestImage(std::vector<uint16_t>& img, int w, int h) {
    img.resize(w * h);
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            uint16_t val = (uint16_t)((x * 1023) / w);
            val ^= (rand() & 0x3FF);
            img[y * w + x] = val & 0x3FF;
        }
    }
}

static void packRaw10(const std::vector<uint16_t>& in, std::vector<uint8_t>& out) {
    size_t pixelCount = in.size();
    out.resize((pixelCount / 4) * 5);

    const uint16_t* pin = in.data();
    uint8_t* pout = out.data();

    for (size_t i = 0; i < pixelCount; i += 4) {
        uint16_t p0 = pin[i + 0] & 0x3FF;
        uint16_t p1 = pin[i + 1] & 0x3FF;
        uint16_t p2 = pin[i + 2] & 0x3FF;
        uint16_t p3 = pin[i + 3] & 0x3FF;

        pout[0] = p0 & 0xFF;
        pout[1] = p1 & 0xFF;
        pout[2] = p2 & 0xFF;
        pout[3] = p3 & 0xFF;
        pout[4] = ((p0 >> 8) & 0x03) |
                 ((p1 >> 6) & 0x0C) |
                 ((p2 >> 4) & 0x30) |
                 ((p3 >> 2) & 0xC0);

        pout += 5;
    }
}

int main() {
    const int w = 1600;
    const int h = 900;

    std::vector<uint16_t> original;
    generateTestImage(original, w, h);

    std::vector<uint8_t> packed;
    packRaw10(original, packed);

    std::vector<uint16_t> unpacked(w * h);
    Raw10Unpacker::unpack(packed.data(), unpacked.data(), w * h);

    // Verify
    for (size_t i = 0; i < original.size(); i++) {
        if (original[i] != unpacked[i]) {
            printf("Mismatch at %zu\n", i);
            return 1;
        }
    }

    printf("Unpack success\n");
    return 0;
}

