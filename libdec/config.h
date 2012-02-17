#ifndef FFMPEG_CONFIG_H
#define FFMPEG_CONFIG_H

#ifdef __GNUC__
	#define HAVE_INLINE_ASM 1
	#define HAVE_MMX 1
	#define HAVE_MMX2 1
	#define HAVE_SSE 1
	#define HAVE_SSSE3 1
	#define HAVE_AMD3DNOW 1
	#define HAVE_AMD3DNOWEXT 1

	#define ARCH_X86 1

	#ifdef ARCH_X86_64
		#define HAVE_FAST_64BIT 1
		#define HAVE_CMOV 1
		#define HAVE_FAST_CMOV 1
		#define HAVE_STRUCT_TIMESPEC 1
	#else
		#define ARCH_X86_32 1
		#define ARCH_X86_64 0
	#endif

	#define PTW32_STATIC_LIB 1
	#define restrict restrict
#else
	#define HAVE_INLINE_ASM 0
	#define HAVE_MMX 0
	#define HAVE_MMX2 0
	#define HAVE_SSE 0
	#define HAVE_SSSE3 0
	#define HAVE_AMD3DNOW 0
	#define HAVE_AMD3DNOWEXT 0
	#define ARCH_X86 0
	#define ARCH_X86_32 0
	#define ARCH_X86_64 0
	#define HAVE_FAST_64BIT 0
	#define HAVE_CMOV 0
	#define HAVE_FAST_CMOV 0
	#define HAVE_WINSOCK2_H 1
	#define HAVE_STRUCT_SOCKADDR_STORAGE 1
	#define  HAVE_STRUCT_ADDRINFO 1
	#define restrict
	#define __asm__ __asm
	#define inline __inline
#endif

// Use DPRINTF instead of av_log. To be used for debug purpose because DPRINTF will be always called (the
// registry switch is not read)
//#define USE_DPRINTF 1

#define FFMPEG_LICENSE "GPL version 2.1 or later"
#define CC_TYPE "gcc"
#define CC_VERSION __VERSION__

#define ASMALIGN(ZEROBITS) ".align 1 << " #ZEROBITS "\n\t"

#define EXTERN_PREFIX "_"
#define EXTERN_ASM _

#define HAVE_ALTIVEC 0
#define HAVE_ALTIVEC_H 0
#define HAVE_BIGENDIAN 0
#define HAVE_BSWAP 1
#define HAVE_EBP_AVAILABLE 1
#define HAVE_EBX_AVAILABLE 1
#define HAVE_FAST_CLZ 0
#define HAVE_FAST_UNALIGNED 1
#define HAVE_LOCAL_ALIGNED_16 1
#define HAVE_LOCAL_ALIGNED_8 1
#define HAVE_MALLOC_H 1
#define HAVE_MEMALIGN 1
#define HAVE_TEN_OPERANDS 1
#define HAVE_THREADS 1
#define HAVE_W32THREADS 1
#define HAVE_YASM 1

#ifdef __GNUC__
	#define HAVE_ATTRIBUTE_PACKED 1
	#define HAVE_ATTRIBUTE_MAY_ALIAS 1
#else
	#define HAVE_ATTRIBUTE_PACKED 0
	#define HAVE_ATTRIBUTE_MAY_ALIAS 0
	#define EMULATE_FAST_INT
#endif

#ifdef __GNUC__
#define HAVE_EXP2 1
#define HAVE_EXP2F 1
#define HAVE_LLRINT 1
#define HAVE_LOG2 1
#define HAVE_LOG2F 1
#define HAVE_LRINT 1
#define HAVE_LRINTF 1
#define HAVE_ROUND 1
#define HAVE_ROUNDF 1
#define HAVE_TRUNCF 1
#else
#define HAVE_EXP2 1
#define HAVE_EXP2F 1
#define HAVE_LLRINT 0
#define HAVE_LOG2 1
#define HAVE_LOG2F 0
#define HAVE_LRINT 0
#define HAVE_LRINTF 0
#define HAVE_ROUND 0
#define HAVE_ROUNDF 1
#define HAVE_TRUNCF 1
#define rint(x) (int)(x+0.5)
#define cbrtf(x) pow((float)x, (float)1.0/3)
#endif

#define CONFIG_DWT 0
#define CONFIG_HARDCODED_TABLES 0
#define CONFIG_GPL 1
#define CONFIG_GRAY 1
#define CONFIG_H264DSP 1
#define CONFIG_LIBAMR_NB 1
#define CONFIG_LIBXVID 0
#define CONFIG_LPC 0
#define CONFIG_MDCT 1
#define CONFIG_MPEGAUDIO_HP 1
#define CONFIG_SMALL 0
#define CONFIG_ZLIB 1

#define CONFIG_DECODERS 1
#define CONFIG_ENCODERS 0 /*1*/ //zyl
#define CONFIG_SWSCALE 0 /*1*/ //zyl
#define CONFIG_SWSCALE_ALPHA 0 /*1*/ //zyl
#define CONFIG_POSTPROC 1
#define CONFIG_RUNTIME_CPUDETECT 1

/* 
Note: when adding a new codec, you have to:
1)	Add a
		#define CONFIG_<codec suffix>_<ENCODER|DECODER|PARSER>
		depending on the type of codec you are adding
2)	Add a
		REGISTER_<ENCODER|DECODER|PARSER> (<codec suffix>, <codec suffix lowercase>);
		line to libavcodec/allcodecs.c
3)	Define the codec into ffcodecs.h :
		CODEC_OP(CODEC_ID_<codec suffix>, <unique id>, "<codec description">)
*/

#define CONFIG_AASC_DECODER 1
#define CONFIG_AMV_DECODER 1
#define CONFIG_ASV1_DECODER 1
#define CONFIG_ASV2_DECODER 1
#define CONFIG_AVS_DECODER 1
#define CONFIG_CAVS_DECODER 0 /*1*/ //zyl
#define CONFIG_CINEPAK_DECODER 1
#define CONFIG_COREPNG_DECODER 1
#define CONFIG_CSCD_DECODER 1
#define CONFIG_CYUV_DECODER 1
#define CONFIG_EIGHTBPS_DECODER 1
#define CONFIG_FFV1_DECODER 1
#define CONFIG_FFVHUFF_DECODER 1
#define CONFIG_FLV_DECODER 1
#define CONFIG_FRAPS_DECODER 1
#define CONFIG_H261_DECODER 0 /*1*/ //zyl
#define CONFIG_H263_DECODER 0 /*1*/ //zyl
#define CONFIG_H263I_DECODER 1
#define CONFIG_H264_DECODER 1
#define CONFIG_HUFFYUV_DECODER 1
#define CONFIG_INDEO2_DECODER 1
#define CONFIG_INDEO3_DECODER 1
#define CONFIG_JPEGLS_DECODER 1
#define CONFIG_LOCO_DECODER 1
#define CONFIG_MJPEG_DECODER 1
#define CONFIG_MJPEGB_DECODER 1
#define CONFIG_MPEG1VIDEO_DECODER 1
#define CONFIG_MPEG2VIDEO_DECODER 1
#define CONFIG_MPEG4_DECODER 1
#define CONFIG_MPEGVIDEO_DECODER 1
#define CONFIG_MSMPEG4V1_DECODER 1
#define CONFIG_MSMPEG4V2_DECODER 1
#define CONFIG_MSMPEG4V3_DECODER 1
#define CONFIG_MSRLE_DECODER 1
#define CONFIG_MSVIDEO1_DECODER 1
#define CONFIG_MSZH_DECODER 1
#define CONFIG_PNG_DECODER 0 /*1*/ //zyl
#define CONFIG_QPEG_DECODER 1
#define CONFIG_QTRLE_DECODER 1
#define CONFIG_RPZA_DECODER 1
#define CONFIG_RV10_DECODER 1
#define CONFIG_RV20_DECODER 1
#define CONFIG_RV30_DECODER 0 /*1*/ // zyl
#define CONFIG_RV40_DECODER 0 /*1*/ // zyl
#define CONFIG_SNOW_DECODER 0
#define CONFIG_SP5X_DECODER 1
#define CONFIG_SVQ1_DECODER 1
#define CONFIG_SVQ3_DECODER 1
#define CONFIG_THEORA_DECODER 1
#define CONFIG_TRUEMOTION1_DECODER 1
#define CONFIG_TRUEMOTION2_DECODER 1
#define CONFIG_TSCC_DECODER 1
#define CONFIG_ULTI_DECODER 1
#define CONFIG_VC1_DECODER 0 /*1*/ // zyl
#define CONFIG_VCR1_DECODER 1
#define CONFIG_VP3_DECODER 0 /*1*/ // zyl
#define CONFIG_VP5_DECODER 1
#define CONFIG_VP6_DECODER 0 /*1*/ // zyl
#define CONFIG_VP6A_DECODER 1
#define CONFIG_VP6F_DECODER 1
#define CONFIG_WMV1_DECODER 1
#define CONFIG_WMV2_DECODER 0 /*1*/ //! zyl
#define CONFIG_WMV3_DECODER 1
#define CONFIG_WNV1_DECODER 1
#define CONFIG_XL_DECODER 1
#define CONFIG_ZLIB_DECODER 1
#define CONFIG_ZMBV_DECODER 1

#define CONFIG_AAC_DECODER 0
#define CONFIG_AC3_DECODER 0 /*1*/ //! zyl
#define CONFIG_ATRAC3_DECODER 1
#define CONFIG_COOK_DECODER 1
#define CONFIG_DCA_DECODER 1
#define CONFIG_EAC3_DECODER 1
#define CONFIG_FLAC_DECODER 1
#define CONFIG_IMC_DECODER 1
#define CONFIG_MACE3_DECODER 1
#define CONFIG_MACE6_DECODER 1
#define CONFIG_MLP_DECODER 0 /*1*/ //! zyl
#define CONFIG_MP1_DECODER 1
#define CONFIG_MP1FLOAT_DECODER 0
#define CONFIG_MP2_DECODER 1
#define CONFIG_MP2FLOAT_DECODER 0
#define CONFIG_MP3_DECODER 1
#define CONFIG_MP3_ENCODER 1
#define CONFIG_MP3FLOAT_DECODER 0
#define CONFIG_MSGSM_DECODER 1
#define CONFIG_NELLYMOSER_DECODER 1
#define CONFIG_QDM2_DECODER 1
#define CONFIG_RA_144_DECODER 1
#define CONFIG_RA_288_DECODER 1
#define CONFIG_TRUEHD_DECODER 0 /*1*/ //! zyl
#define CONFIG_TRUESPEECH_DECODER 1
#define CONFIG_TTA_DECODER 1
#define CONFIG_VORBIS_DECODER 0 /*1*/ // zyl
#define CONFIG_WAVPACK_DECODER 1
#define CONFIG_WMAV1_DECODER 1
#define CONFIG_WMAV2_DECODER 1
#define CONFIG_PCM_ALAW_DECODER 1
#define CONFIG_PCM_MULAW_DECODER 1
#define CONFIG_ADPCM_4XM_DECODER 1
#define CONFIG_ADPCM_ADX_DECODER 1
#define CONFIG_ADPCM_CT_DECODER 1
#define CONFIG_ADPCM_EA_DECODER 1
#define CONFIG_ADPCM_G726_DECODER 1
#define CONFIG_ADPCM_IMA_AMV_DECODER 1
#define CONFIG_ADPCM_IMA_DK3_DECODER 1
#define CONFIG_ADPCM_IMA_DK4_DECODER 1
#define CONFIG_ADPCM_IMA_QT_DECODER 1
#define CONFIG_ADPCM_IMA_SMJPEG_DECODER 1
#define CONFIG_ADPCM_IMA_WAV_DECODER 1
#define CONFIG_ADPCM_IMA_WS_DECODER 1
#define CONFIG_ADPCM_MS_DECODER 1
#define CONFIG_ADPCM_SBPRO_2_DECODER 1
#define CONFIG_ADPCM_SBPRO_3_DECODER 1
#define CONFIG_ADPCM_SBPRO_4_DECODER 1
#define CONFIG_ADPCM_SWF_DECODER 1
#define CONFIG_ADPCM_XA_DECODER 1
#define CONFIG_ADPCM_YAMAHA_DECODER 1

#define CONFIG_LIBAMR_NB_DECODER 1

#define CONFIG_FFV1_ENCODER 1
#define CONFIG_FFVHUFF_ENCODER 1
#define CONFIG_FLV_ENCODER 1
#define CONFIG_H261_ENCODER 0 /*1*/ // zyl
#define CONFIG_H263_ENCODER 0 /*1*/ // zyl
#define CONFIG_H263P_ENCODER 1
#define CONFIG_H264_ENCODER 0
#define CONFIG_HUFFYUV_ENCODER 1
#define CONFIG_LJPEG_ENCODER 1
#define CONFIG_MJPEG_ENCODER 1
#define CONFIG_MPEG1VIDEO_ENCODER 1
#define CONFIG_MPEG2VIDEO_ENCODER 1
#define CONFIG_MPEG4_ENCODER 1
#define CONFIG_MSMPEG4V1_ENCODER 1
#define CONFIG_MSMPEG4V2_ENCODER 1
#define CONFIG_MSMPEG4V3_ENCODER 1
#define CONFIG_PNG_ENCODER 1
#define CONFIG_RV10_ENCODER 0
#define CONFIG_RV20_ENCODER 0
#define CONFIG_SNOW_ENCODER 0
#define CONFIG_WMV1_ENCODER 1
#define CONFIG_WMV2_ENCODER 1
#define CONFIG_AC3_ENCODER 1

#define CONFIG_AAC_PARSER 0
#define CONFIG_AC3_PARSER 1
#define CONFIG_DCA_PARSER 1
#define CONFIG_H263_PARSER 1
#define CONFIG_H264_PARSER 1
#define CONFIG_MJPEG_PARSER 1
#define CONFIG_MPEGAUDIO_PARSER 1
#define CONFIG_MPEG4VIDEO_PARSER 1
#define CONFIG_MLP_PARSER 1

#define CONFIG_NETWORK 1
#define CONFIG_DEMUXERS       1
#define  CONFIG_MUXERS        1
#define CONFIG_AAC_DEMUXER     1
#define CONFIG_AAC_DEMUXER     1
#define CONFIG_AAC_DEMUXER     1
#define CONFIG_AC3_MUXER     1
#define CONFIG_AC3_DEMUXER     1
#define CONFIG_ADTS_MUXER     1
#define CONFIG_AEA_DEMUXER     1
#define CONFIG_AIFF_MUXER     1
#define CONFIG_AIFF_DEMUXER     1
#define CONFIG_AMR_MUXER     1
#define CONFIG_AMR_DEMUXER     1
#define CONFIG_ANM_DEMUXER     1
#define CONFIG_APC_DEMUXER     1
#define CONFIG_APE_DEMUXER     1
#define CONFIG_ASF_MUXER     1
#define CONFIG_ASF_DEMUXER     1
#define CONFIG_ASS_MUXER     1
#define CONFIG_ASS_DEMUXER     1
#define CONFIG_ASF_STREAM_MUXER     1
#define CONFIG_AU_MUXER     1
#define CONFIG_AU_DEMUXER     1
#define CONFIG_AVI_MUXER     1
#define CONFIG_AVI_DEMUXER     1
#define CONFIG_AVISYNTH_DEMUXER     1
#define CONFIG_AVM2_MUXER     1
#define CONFIG_AVS_DEMUXER     1
#define CONFIG_BETHSOFTVID_DEMUXER     1
#define CONFIG_BFI_DEMUXER     1
#define CONFIG_BINK_DEMUXER     1
#define CONFIG_C93_DEMUXER     1
#define CONFIG_CAF_DEMUXER     1
#define CONFIG_CAVSVIDEO_DEMUXER     1
#define CONFIG_CDG_DEMUXER     1
#define CONFIG_CRC_MUXER     1
#define CONFIG_DAUD_MUXER     1
#define CONFIG_DAUD_DEMUXER     1
#define CONFIG_DIRAC_MUXER     1
#define CONFIG_DIRAC_DEMUXER     1
#define CONFIG_DNXHD_MUXER     1
#define CONFIG_DNXHD_DEMUXER     1
#define CONFIG_DSICIN_DEMUXER     1
#define CONFIG_DTS_MUXER     1
#define CONFIG_DTS_DEMUXER     1
#define CONFIG_DV_MUXER     1
#define CONFIG_DV_DEMUXER     1
#define CONFIG_DXA_DEMUXER     1
#define CONFIG_EA_DEMUXER     1
#define CONFIG_EA_CDATA_DEMUXER     1
#define CONFIG_EAC3_MUXER     1
#define CONFIG_EAC3_DEMUXER     1
#define CONFIG_FFM_MUXER     1
#define CONFIG_FFM_DEMUXER     1
#define CONFIG_FILMSTRIP_MUXER     1
#define CONFIG_FILMSTRIP_DEMUXER     1
#define CONFIG_FLAC_MUXER     1
#define CONFIG_FLAC_DEMUXER     1
#define CONFIG_FLIC_DEMUXER     1
#define CONFIG_FLV_MUXER     1
#define CONFIG_FLV_DEMUXER     1
#define CONFIG_FOURXM_DEMUXER     1
#define CONFIG_FRAMECRC_MUXER     1
#define CONFIG_GIF_MUXER     1
#define CONFIG_GSM_DEMUXER     1
#define CONFIG_GXF_MUXER     1
#define CONFIG_GXF_DEMUXER     1
#define CONFIG_H261_MUXER     1
#define CONFIG_H261_DEMUXER     1
#define CONFIG_H263_MUXER     1
#define CONFIG_H263_DEMUXER     1
#define CONFIG_H264_MUXER     1
#define CONFIG_H264_DEMUXER     1
#define CONFIG_IDCIN_DEMUXER     1
#define CONFIG_IFF_DEMUXER     1
#define CONFIG_IMAGE2_MUXER     1
#define CONFIG_IMAGE2_DEMUXER     1
#define CONFIG_IMAGE2PIPE_MUXER     1
#define CONFIG_IMAGE2PIPE_DEMUXER     1
#define CONFIG_INGENIENT_DEMUXER     1
#define CONFIG_IPMOVIE_DEMUXER     1
#define CONFIG_IPOD_MUXER     1
#define CONFIG_ISS_DEMUXER     1
#define CONFIG_IV8_DEMUXER     1
#define CONFIG_LMLM4_DEMUXER     1
#define CONFIG_M4V_MUXER     1
#define CONFIG_M4V_DEMUXER     1
#define CONFIG_MATROSKA_MUXER     1
#define CONFIG_MATROSKA_DEMUXER     1
#define CONFIG_MATROSKA_AUDIO_MUXER     1
#define CONFIG_MJPEG_MUXER     1
#define CONFIG_MJPEG_DEMUXER     1
#define CONFIG_MLP_MUXER     1
#define CONFIG_MLP_DEMUXER     1
#define CONFIG_MM_DEMUXER     1
#define CONFIG_MMF_MUXER     1
#define CONFIG_MMF_DEMUXER     1
#define CONFIG_MOV_MUXER     1
#define CONFIG_MOV_DEMUXER     1
#define CONFIG_MP2_MUXER     1
#define CONFIG_MP3_MUXER     1
#define CONFIG_MP3_DEMUXER     1
#define CONFIG_MP4_MUXER     1
#define CONFIG_MPC_DEMUXER     1
#define CONFIG_MPC8_DEMUXER     1
#define CONFIG_MPEG1SYSTEM_MUXER     1
#define CONFIG_MPEG1VCD_MUXER     1
#define CONFIG_MPEG1VIDEO_MUXER     1
#define CONFIG_MPEG2DVD_MUXER     1
#define CONFIG_MPEG2SVCD_MUXER     1
#define CONFIG_MPEG2VIDEO_MUXER     1
#define CONFIG_MPEG2VOB_MUXER     1
#define CONFIG_MPEGPS_DEMUXER     1
#define CONFIG_MPEGTS_MUXER     1
#define CONFIG_MPEGTS_DEMUXER     1
#define CONFIG_MPEGTSRAW_DEMUXER     1
#define CONFIG_MPEGVIDEO_DEMUXER     1
#define CONFIG_MPJPEG_MUXER     1
#define CONFIG_MSNWC_TCP_DEMUXER     1
#define CONFIG_MTV_DEMUXER     1
#define CONFIG_MVI_DEMUXER     1
#define CONFIG_MXF_MUXER     1
#define CONFIG_MXF_DEMUXER     1
#define CONFIG_MXF_D10_MUXER     1
#define CONFIG_NC_DEMUXER     1
#define CONFIG_NSV_DEMUXER     1
#define CONFIG_NULL_MUXER     1
#define CONFIG_NUT_MUXER     1
#define CONFIG_NUT_DEMUXER     1
#define CONFIG_NUV_DEMUXER     1
#define CONFIG_OGG_MUXER     1
#define CONFIG_OGG_DEMUXER     1
#define CONFIG_OMA_DEMUXER     1
#define CONFIG_PCM_ALAW_MUXER     1
#define CONFIG_PCM_ALAW_DEMUXER     1
#define CONFIG_PCM_MULAW_MUXER     1
#define CONFIG_PCM_MULAW_DEMUXER     1
#define CONFIG_PCM_F64BE_MUXER     1
#define CONFIG_PCM_F64BE_DEMUXER     1
#define CONFIG_PCM_F64LE_MUXER     1
#define CONFIG_PCM_F64LE_DEMUXER     1
#define CONFIG_PCM_F32BE_MUXER     1
#define CONFIG_PCM_F32BE_DEMUXER     1
#define CONFIG_PCM_F32LE_MUXER     1
#define CONFIG_PCM_F32LE_DEMUXER     1
#define CONFIG_PCM_S32BE_MUXER     1
#define CONFIG_PCM_S32BE_DEMUXER     1
#define CONFIG_PCM_S32LE_MUXER     1
#define CONFIG_PCM_S32LE_DEMUXER     1
#define CONFIG_PCM_S24BE_MUXER     1
#define CONFIG_PCM_S24BE_DEMUXER     1
#define CONFIG_PCM_S24LE_MUXER     1
#define CONFIG_PCM_S24LE_DEMUXER     1
#define CONFIG_PCM_S16BE_MUXER     1
#define CONFIG_PCM_S16BE_DEMUXER     1
#define CONFIG_PCM_S16LE_MUXER     1
#define CONFIG_PCM_S16LE_DEMUXER     1
#define CONFIG_PCM_S8_MUXER     1
#define CONFIG_PCM_S8_DEMUXER     1
#define CONFIG_PCM_U32BE_MUXER     1
#define CONFIG_PCM_U32BE_DEMUXER     1
#define CONFIG_PCM_U32LE_MUXER     1
#define CONFIG_PCM_U32LE_DEMUXER     1
#define CONFIG_PCM_U24BE_MUXER     1
#define CONFIG_PCM_U24BE_DEMUXER     1
#define CONFIG_PCM_U24LE_MUXER     1
#define CONFIG_PCM_U24LE_DEMUXER     1
#define CONFIG_PCM_U16BE_MUXER     1
#define CONFIG_PCM_U16BE_DEMUXER     1
#define CONFIG_PCM_U16LE_MUXER     1
#define CONFIG_PCM_U16LE_DEMUXER     1
#define CONFIG_PCM_U8_MUXER     1
#define CONFIG_PCM_U8_DEMUXER     1
#define CONFIG_PSP_MUXER     1
#define CONFIG_PVA_DEMUXER     1
#define CONFIG_QCP_DEMUXER     1
#define CONFIG_R3D_DEMUXER     1
#define CONFIG_RAWVIDEO_MUXER     1
#define CONFIG_RAWVIDEO_DEMUXER     1
#define CONFIG_RL2_DEMUXER     1
#define CONFIG_RM_MUXER     1
#define CONFIG_RM_DEMUXER     1
#define CONFIG_ROQ_MUXER     1
#define CONFIG_ROQ_DEMUXER     1
#define CONFIG_RPL_DEMUXER     1
#define CONFIG_RTP_MUXER     1
#define CONFIG_RTSP_MUXER     1
#define CONFIG_RTSP_DEMUXER     1
#define CONFIG_SDP_DEMUXER     1
#define CONFIG_SEGAFILM_DEMUXER     1
#define CONFIG_SHORTEN_DEMUXER     1
#define CONFIG_SIFF_DEMUXER     1
#define CONFIG_SMACKER_DEMUXER     1
#define CONFIG_SOL_DEMUXER     1
#define CONFIG_SOX_MUXER     1
#define CONFIG_SOX_DEMUXER     1
#define CONFIG_SPDIF_MUXER     1
#define CONFIG_STR_DEMUXER     1
#define CONFIG_SWF_MUXER     1
#define CONFIG_SWF_DEMUXER     1
#define CONFIG_TG2_MUXER     1
#define CONFIG_TGP_MUXER     1
#define CONFIG_THP_DEMUXER     1
#define CONFIG_TIERTEXSEQ_DEMUXER     1
#define CONFIG_TMV_DEMUXER     1
#define CONFIG_TRUEHD_MUXER     1
#define CONFIG_TRUEHD_DEMUXER     1
#define CONFIG_TTA_DEMUXER     1
#define CONFIG_TXD_DEMUXER     1
#define CONFIG_VC1_DEMUXER     1
#define CONFIG_VC1T_MUXER     1
#define CONFIG_VC1T_DEMUXER     1
#define CONFIG_VMD_DEMUXER     1
#define CONFIG_VOC_MUXER     1
#define CONFIG_VOC_DEMUXER     1
#define CONFIG_VQF_DEMUXER     1
#define CONFIG_W64_DEMUXER     1
#define CONFIG_WAV_MUXER     1
#define CONFIG_WAV_DEMUXER     1
#define CONFIG_WC3_DEMUXER     1
#define CONFIG_WSAUD_DEMUXER     1
#define CONFIG_WSVQA_DEMUXER     1
#define CONFIG_WV_DEMUXER     1
#define CONFIG_XA_DEMUXER     1
#define CONFIG_YOP_DEMUXER     1
#define CONFIG_YUV4MPEGPIPE_MUXER     1
#define CONFIG_YUV4MPEGPIPE_DEMUXER     1
#define CONFIG_LIBNUT_MUXER     1
#define CONFIG_FILE_PROTOCOL     1
#define CONFIG_GOPHER_PROTOCOL     1
#define CONFIG_HTTP_PROTOCOL     1
#define CONFIG_PIPE_PROTOCOL     1
#define CONFIG_RTMP_PROTOCOL     1
#define CONFIG_RTP_PROTOCOL     1
#define CONFIG_TCP_PROTOCOL     1
#define CONFIG_UDP_PROTOCOL     1
#define CONFIG_CONCAT_PROTOCOL     1
#define CONFIG_MPEG4_VDPAU_DECODER 0
#define CONFIG_VC1_VDPAU_DECODER 0

#endif /* FFMPEG_CONFIG_H */
