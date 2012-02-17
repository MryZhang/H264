/*
 * IFF PBM/ILBM bitmap decoder
 * Copyright (c) 2010 Peter Ross <pross@xvid.org>
 * Copyright (c) 2010 Sebastian Vater <cdgs.basty@googlemail.com>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/**
 * @file
 * IFF PBM/ILBM bitmap decoder
 */

#include "bytestream.h"
#include "avcodec.h"
#include "get_bits.h"
#include "iff.h"

typedef struct {
    AVFrame frame;
    int planesize;
    uint8_t * planebuf;
} IffContext;

#define LUT8_PART(plane, v)                             \
    AV_LE2ME64C(UINT64_C(0x0000000)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1000000)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x0010000)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1010000)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x0000100)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1000100)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x0010100)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1010100)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x0000001)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1000001)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x0010001)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1010001)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x0000101)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1000101)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x0010101)<<32 | v) << plane,  \
    AV_LE2ME64C(UINT64_C(0x1010101)<<32 | v) << plane

#define LUT8(plane) {                           \
    LUT8_PART(plane, 0x0000000),                \
    LUT8_PART(plane, 0x1000000),                \
    LUT8_PART(plane, 0x0010000),                \
    LUT8_PART(plane, 0x1010000),                \
    LUT8_PART(plane, 0x0000100),                \
    LUT8_PART(plane, 0x1000100),                \
    LUT8_PART(plane, 0x0010100),                \
    LUT8_PART(plane, 0x1010100),                \
    LUT8_PART(plane, 0x0000001),                \
    LUT8_PART(plane, 0x1000001),                \
    LUT8_PART(plane, 0x0010001),                \
    LUT8_PART(plane, 0x1010001),                \
    LUT8_PART(plane, 0x0000101),                \
    LUT8_PART(plane, 0x1000101),                \
    LUT8_PART(plane, 0x0010101),                \
    LUT8_PART(plane, 0x1010101),                \
}

// 8 planes * 8-bit mask
static const uint64_t plane8_lut[8][256] = {
    LUT8(0), LUT8(1), LUT8(2), LUT8(3),
    LUT8(4), LUT8(5), LUT8(6), LUT8(7),
};

#define LUT32(plane) {                                \
             0,          0,          0,          0,   \
             0,          0,          0, 1 << plane,   \
             0,          0, 1 << plane,          0,   \
             0,          0, 1 << plane, 1 << plane,   \
             0, 1 << plane,          0,          0,   \
             0, 1 << plane,          0, 1 << plane,   \
             0, 1 << plane, 1 << plane,          0,   \
             0, 1 << plane, 1 << plane, 1 << plane,   \
    1 << plane,          0,          0,          0,   \
    1 << plane,          0,          0, 1 << plane,   \
    1 << plane,          0, 1 << plane,          0,   \
    1 << plane,          0, 1 << plane, 1 << plane,   \
    1 << plane, 1 << plane,          0,          0,   \
    1 << plane, 1 << plane,          0, 1 << plane,   \
    1 << plane, 1 << plane, 1 << plane,          0,   \
    1 << plane, 1 << plane, 1 << plane, 1 << plane,   \
}

// 32 planes * 4-bit mask * 4 lookup tables each
static const uint32_t plane32_lut[32][16*4] = {
    LUT32( 0), LUT32( 1), LUT32( 2), LUT32( 3),
    LUT32( 4), LUT32( 5), LUT32( 6), LUT32( 7),
    LUT32( 8), LUT32( 9), LUT32(10), LUT32(11),
    LUT32(12), LUT32(13), LUT32(14), LUT32(15),
    LUT32(16), LUT32(17), LUT32(18), LUT32(19),
    LUT32(20), LUT32(21), LUT32(22), LUT32(23),
    LUT32(24), LUT32(25), LUT32(26), LUT32(27),
    LUT32(28), LUT32(29), LUT32(30), LUT32(31),
};

/**
 * Convert CMAP buffer (stored in extradata) to lavc palette format
 */
int ff_cmap_read_palette(AVCodecContext *avctx, uint32_t *pal)
{
    int count, i;

    if (avctx->bits_per_coded_sample > 8) {
        av_log(avctx, AV_LOG_ERROR, "bit_per_coded_sample > 8 not supported\n");
        return AVERROR_INVALIDDATA;
    }

    count = 1 << avctx->bits_per_coded_sample;
    if (avctx->extradata_size < count * 3) {
        av_log(avctx, AV_LOG_ERROR, "palette data underflow\n");
        return AVERROR_INVALIDDATA;
    }
    for (i=0; i < count; i++) {
        pal[i] = 0xFF000000 | AV_RB24( avctx->extradata + i*3 );
    }
    return 0;
}

static av_cold int decode_init(AVCodecContext *avctx)
{
    IffContext *s = avctx->priv_data;
    int err;

    if (avctx->bits_per_coded_sample <= 8) {
        avctx->pix_fmt = PIX_FMT_PAL8;
    } else if (avctx->bits_per_coded_sample <= 32) {
        avctx->pix_fmt = PIX_FMT_BGR32;
    } else {
        return AVERROR_INVALIDDATA;
    }

    if ((err = avcodec_check_dimensions(avctx, avctx->width, avctx->height)))
        return err;
    s->planesize = FFALIGN(avctx->width, 16) >> 3; // Align plane size in bits to word-boundary
    s->planebuf = av_malloc(s->planesize + FF_INPUT_BUFFER_PADDING_SIZE);
    if (!s->planebuf)
        return AVERROR(ENOMEM);

    s->frame.reference = 1;
    if ((err = avctx->get_buffer(avctx, &s->frame) < 0)) {
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return err;
    }

    return avctx->bits_per_coded_sample <= 8 ?
       ff_cmap_read_palette(avctx, (uint32_t*)s->frame.data[1]) : 0;
}

/**
 * Decode interleaved plane buffer up to 8bpp
 * @param dst Destination buffer
 * @param buf Source buffer
 * @param buf_size
 * @param plane plane number to decode as
 */
static void decodeplane8(uint8_t *dst, const uint8_t *buf, int buf_size, int plane)
{
    const uint64_t *lut = plane8_lut[plane];
    while (buf_size--) {
        uint64_t v = AV_RN64A(dst) | lut[*buf++];
        AV_WN64A(dst, v);
        dst += 8;
    }
}

/**
 * Decode interleaved plane buffer up to 24bpp
 * @param dst Destination buffer
 * @param buf Source buffer
 * @param buf_size
 * @param plane plane number to decode as
 */
static void decodeplane32(uint32_t *dst, const uint8_t *buf, int buf_size, int plane)
{
    const uint32_t *lut = plane32_lut[plane];
    do {
        unsigned mask = (*buf >> 2) & ~3;
        dst[0] |= lut[mask++];
        dst[1] |= lut[mask++];
        dst[2] |= lut[mask++];
        dst[3] |= lut[mask];
        mask = (*buf++ << 2) & 0x3F;
        dst[4] |= lut[mask++];
        dst[5] |= lut[mask++];
        dst[6] |= lut[mask++];
        dst[7] |= lut[mask];
        dst += 8;
    } while (--buf_size);
}

static int decode_frame_ilbm(AVCodecContext *avctx,
                            void *data, int *data_size,
                            AVPacket *avpkt)
{
    IffContext *s = avctx->priv_data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    const uint8_t *buf_end = buf+buf_size;
    int y, plane;

    if (avctx->reget_buffer(avctx, &s->frame) < 0){
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return -1;
    }

    if (avctx->pix_fmt == PIX_FMT_PAL8) {
        for(y = 0; y < avctx->height; y++ ) {
            uint8_t *row = &s->frame.data[0][ y*s->frame.linesize[0] ];
            memset(row, 0, avctx->width);
            for (plane = 0; plane < avctx->bits_per_coded_sample && buf < buf_end; plane++) {
                decodeplane8(row, buf, FFMIN(s->planesize, buf_end - buf), plane);
                buf += s->planesize;
            }
        }
    } else { // PIX_FMT_BGR32
        for(y = 0; y < avctx->height; y++ ) {
            uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];
            memset(row, 0, avctx->width << 2);
            for (plane = 0; plane < avctx->bits_per_coded_sample && buf < buf_end; plane++) {
                decodeplane32((uint32_t *) row, buf, FFMIN(s->planesize, buf_end - buf), plane);
                buf += s->planesize;
            }
        }
    }

    *data_size = sizeof(AVFrame);
    *(AVFrame*)data = s->frame;
    return buf_size;
}

static int decode_frame_byterun1(AVCodecContext *avctx,
                            void *data, int *data_size,
                            AVPacket *avpkt)
{
    IffContext *s = avctx->priv_data;
    const uint8_t *buf = avpkt->data;
    int buf_size = avpkt->size;
    const uint8_t *buf_end = buf+buf_size;
    int y, plane, x;

    if (avctx->reget_buffer(avctx, &s->frame) < 0){
        av_log(avctx, AV_LOG_ERROR, "get_buffer() failed\n");
        return -1;
    }

    if (avctx->codec_tag == MKTAG('I','L','B','M')) { //interleaved
        if (avctx->pix_fmt == PIX_FMT_PAL8) {
            for(y = 0; y < avctx->height ; y++ ) {
                uint8_t *row = &s->frame.data[0][ y*s->frame.linesize[0] ];
                memset(row, 0, avctx->width);
                for (plane = 0; plane < avctx->bits_per_coded_sample; plane++) {
                    for(x = 0; x < s->planesize && buf < buf_end; ) {
                        int8_t value = *buf++;
                        unsigned length;
                        if (value >= 0) {
                            length = value + 1;
                            memcpy(s->planebuf + x, buf, FFMIN3(length, s->planesize - x, buf_end - buf));
                            buf += length;
                        } else if (value > -128) {
                            length = -value + 1;
                            memset(s->planebuf + x, *buf++, FFMIN(length, s->planesize - x));
                        } else { //noop
                            continue;
                        }
                        x += length;
                    }
                    decodeplane8(row, s->planebuf, s->planesize, plane);
                }
            }
        } else { //PIX_FMT_BGR32
            for(y = 0; y < avctx->height ; y++ ) {
                uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];
                memset(row, 0, avctx->width << 2);
                for (plane = 0; plane < avctx->bits_per_coded_sample; plane++) {
                    for(x = 0; x < s->planesize && buf < buf_end; ) {
                        int8_t value = *buf++;
                        unsigned length;
                        if (value >= 0) {
                            length = value + 1;
                            memcpy(s->planebuf + x, buf, FFMIN3(length, s->planesize - x, buf_end - buf));
                            buf += length;
                        } else if (value > -128) {
                            length = -value + 1;
                            memset(s->planebuf + x, *buf++, FFMIN(length, s->planesize - x));
                        } else { // noop
                            continue;
                        }
                        x += length;
                    }
                    decodeplane32((uint32_t *) row, s->planebuf, s->planesize, plane);
                }
            }
        }
    } else {
        for(y = 0; y < avctx->height ; y++ ) {
            uint8_t *row = &s->frame.data[0][y*s->frame.linesize[0]];
            for(x = 0; x < avctx->width && buf < buf_end; ) {
                int8_t value = *buf++;
                unsigned length;
                if (value >= 0) {
                    length = value + 1;
                    memcpy(row + x, buf, FFMIN3(length, buf_end - buf, avctx->width - x));
                    buf += length;
                } else if (value > -128) {
                    length = -value + 1;
                    memset(row + x, *buf++, FFMIN(length, avctx->width - x));
                } else { //noop
                    continue;
                }
                x += length;
            }
        }
    }

    *data_size = sizeof(AVFrame);
    *(AVFrame*)data = s->frame;
    return buf_size;
}

static av_cold int decode_end(AVCodecContext *avctx)
{
    IffContext *s = avctx->priv_data;
    if (s->frame.data[0])
        avctx->release_buffer(avctx, &s->frame);
    av_freep(&s->planebuf);
    return 0;
}

AVCodec iff_ilbm_decoder = {
    "iff_ilbm",
    AVMEDIA_TYPE_VIDEO,
    CODEC_ID_IFF_ILBM,
    sizeof(IffContext),
    decode_init,
    NULL,
    decode_end,
    decode_frame_ilbm,
    CODEC_CAP_DR1,
	0,0,0,0,
    NULL_IF_CONFIG_SMALL("IFF ILBM"),
};

AVCodec iff_byterun1_decoder = {
    "iff_byterun1",
    AVMEDIA_TYPE_VIDEO,
    CODEC_ID_IFF_BYTERUN1,
    sizeof(IffContext),
    decode_init,
    NULL,
    decode_end,
    decode_frame_byterun1,
    CODEC_CAP_DR1,
	0,0,0,0,
    NULL_IF_CONFIG_SMALL("IFF ByteRun1"),
};
