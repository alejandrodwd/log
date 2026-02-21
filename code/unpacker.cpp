#include <cstdint>
#include <cstdio>
#include <vector>
#include <cstdlib>

class Raw10Unpacker {
public:
    static void unpack(const uint8_t* in, uint16_t* out, size_t pixelCount) {
        if (pixelCount % 4 != 0) {
            fprintf(stderr, "Pixel count must be multiple of 4.\n");
            exit(1);
        }

        for (size_t i = 0; i < pixelCount; i += 4) {
            uint8_t b0 = *in++;
            uint8_t b1 = *in++;
            uint8_t b2 = *in++;
            uint8_t b3 = *in++;
            uint8_t b4 = *in++;

            out[0] = (uint16_t)(b0 | ((b4 & 0x03) << 8));
            out[1] = (uint16_t)(b1 | (((b4 >> 2) & 0x03) << 8));
            out[2] = (uint16_t)(b2 | (((b4 >> 4) & 0x03) << 8));
            out[3] = (uint16_t)(b3 | (((b4 >> 6) & 0x03) << 8));

            out += 4;
        }
    }
};

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Usage: %s input.bin output.raw width height\n", argv[0]);
        return 1;
    }

    const char* inputPath  = argv[1];
    const char* outputPath = argv[2];
    int width               = atoi(argv[3]);
    int height              = atoi(argv[4]);
    size_t pixelCount       = size_t(width) * size_t(height);

    // Read packed file
    FILE* f = fopen(inputPath, "rb");
    if (!f) { perror("Failed to open input"); return 1; }

    std::vector<uint8_t> packed((pixelCount / 4) * 5);
    if (fread(packed.data(), 1, packed.size(), f) != packed.size()) {
        perror("Failed to read input"); fclose(f); return 1;
    }
    fclose(f);

    // Unpack
    std::vector<uint16_t> unpacked(pixelCount);
    Raw10Unpacker::unpack(packed.data(), unpacked.data(), pixelCount);

    // Save unpacked
    FILE* out = fopen(outputPath, "wb");
    if (!out) { perror("Failed to open output"); return 1; }
    if (fwrite(unpacked.data(), sizeof(uint16_t), pixelCount, out) != pixelCount) {
        perror("Failed to write output"); fclose(out); return 1;
    }
    fclose(out);

    printf("Unpacked %zu pixels to %zu bytes\n", pixelCount, pixelCount * sizeof(uint16_t));
    return 0;
}
