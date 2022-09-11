#pragma once

namespace utils {
    constexpr int pack_int_2_10_10_10_rev(float x, float y, float z, float w) {
        const int xs = x < 0;
        const int ys = y < 0;
        const int zs = z < 0;
        const int ws = w < 0;
        int vi =
            ws << 31 | ((int)(w + (ws << 1)) & 1) << 30 |
            zs << 29 | ((int)(z * 511 + (zs << 9)) & 511) << 20 |
            ys << 19 | ((int)(y * 511 + (ys << 9)) & 511) << 10 |
            xs << 9  | ((int)(x * 511 + (xs << 9)) & 511);
        return vi;
    }

    constexpr int pack_int_2_10_10_10_rev(float x, float y, float z) {
        const int xs = x < 0;
        const int ys = y < 0;
        const int zs = z < 0;
        int vi =
            zs << 29 | ((int)(z * 511 + (zs << 9)) & 511) << 20 |
            ys << 19 | ((int)(y * 511 + (ys << 9)) & 511) << 10 |
            xs << 9  | ((int)(x * 511 + (xs << 9)) & 511);
        return vi;
    }
}
