#include <cstdint>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <string>

static void packRaw10(const std::vector<uint16_t>& in, std::vector<uint8_t>& out) {
    size_t pixelCount = in.size();
    if (pixelCount % 4 != 0) {
        fprintf(stderr, "Pixel count must be multiple of 4.\n");
        exit(1);
    }

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

int main(int argc, char* argv[]) {
    if (argc != 6) {
        printf("Usage: %s input.raw output.bin pixel_bit_depth width height\n", argv[0]);
        return 1;
    }

    const char* inputPath  = argv[1];
    const char* outputPath = argv[2];
    int bitDepth            = atoi(argv[3]);
    int width               = atoi(argv[4]);
    int height              = atoi(argv[5]);

    size_t pixelCount = size_t(width) * size_t(height);

    // Read input raw file
    FILE* f = fopen(inputPath, "rb");
    if (!f) { perror("Failed to open input"); return 1; }

    std::vector<uint16_t> raw(pixelCount);
    if (fread(raw.data(), sizeof(uint16_t), pixelCount, f) != pixelCount) {
        perror("Failed to read input"); fclose(f); return 1;
    }
    fclose(f);

    // Truncate to 10-bit
    int shift = (bitDepth - 10);
    for (size_t i = 0; i < pixelCount; i++) {
        raw[i] >>= shift; // drop LSBs
    }

    // Pack to RAW10
    std::vector<uint8_t> packed;
    packRaw10(raw, packed);

    // Save packed file
    FILE* out = fopen(outputPath, "wb");
    if (!out) { perror("Failed to open output"); return 1; }
    if (fwrite(packed.data(), 1, packed.size(), out) != packed.size()) {
        perror("Failed to write output"); fclose(out); return 1;
    }
    fclose(out);

    printf("Packed %zu pixels to %zu bytes\n", pixelCount, packed.size());
    return 0;
}
