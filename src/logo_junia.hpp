#ifndef LOGO_JUNIA_hpp
#define LOGO_JUNIA_hpp

#include "Arduino.h"

#define logo_junia_66_32_SIZE 1246
#define logo_junia_66_32_WIDTH 66
#define logo_junia_66_32_HEIGHT 32

const char logo_junia_66_32_map[] = {
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x42, 0x00, 0x00, 0x00, 0x20, 0x08, 0x03, 0x00, 0x00, 0x00, 0x91, 0xb6, 0x5e,
    0x8b, 0x00, 0x00, 0x00, 0x01, 0x73, 0x52, 0x47, 0x42, 0x00, 0xae, 0xce, 0x1c, 0xe9, 0x00, 0x00,
    0x00, 0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1, 0x8f, 0x0b, 0xfc, 0x61, 0x05, 0x00, 0x00,
    0x01, 0x50, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff, 0xff, 0x99, 0x8e, 0xa5, 0x3f, 0x2a, 0x56, 0x9d,
    0x93, 0xa9, 0xca, 0xc4, 0xd0, 0x79, 0x6a, 0x89, 0x7d, 0x6f, 0x8d, 0xaa, 0xa0, 0xb4, 0x7a, 0x6c,
    0x8a, 0x7f, 0x71, 0x8f, 0xac, 0xa3, 0xb6, 0xba, 0xb3, 0xc2, 0x6e, 0x5e, 0x7f, 0x6f, 0x5f, 0x80,
    0xc9, 0xc3, 0xd0, 0x9e, 0x94, 0xaa, 0x83, 0x76, 0x92, 0xe0, 0xdc, 0xe4, 0x53, 0x40, 0x67, 0xd2,
    0xcd, 0xd7, 0xf3, 0xf1, 0xf4, 0x82, 0x74, 0x91, 0xb0, 0xa8, 0xba, 0xa1, 0x97, 0xac, 0xa7, 0x9e,
    0xb2, 0xd8, 0xd4, 0xdd, 0x8e, 0x82, 0x9c, 0x7c, 0x6e, 0x8c, 0x79, 0x6b, 0x89, 0x52, 0x3f, 0x67,
    0xd1, 0xcc, 0xd6, 0xef, 0xed, 0xf1, 0xc3, 0xbd, 0xca, 0xa7, 0x9d, 0xb1, 0xd2, 0xcd, 0xd8, 0x48,
    0x34, 0x5d, 0xb9, 0xb1, 0xc1, 0xf0, 0xee, 0xf2, 0xce, 0xc8, 0xd4, 0xdc, 0xd8, 0xe0, 0x47, 0x33,
    0x5d, 0xbc, 0xb5, 0xc4, 0xa6, 0x9c, 0xb0, 0x54, 0x41, 0x68, 0x73, 0x64, 0x84, 0x7b, 0x6c, 0x8b,
    0x4e, 0x3b, 0x63, 0xe8, 0xe6, 0xeb, 0xf6, 0xf5, 0xf7, 0x70, 0x60, 0x81, 0x95, 0x8a, 0xa2, 0x4f,
    0x3c, 0x64, 0x51, 0x3e, 0x66, 0xd0, 0xcb, 0xd6, 0xee, 0xec, 0xf0, 0xa0, 0x95, 0xab, 0x7c, 0x6d,
    0x8b, 0x55, 0x43, 0x69, 0x9f, 0x95, 0xab, 0xf5, 0xf4, 0xf6, 0xcb, 0xc6, 0xd2, 0xec, 0xea, 0xee,
    0x77, 0x68, 0x87, 0xcf, 0xca, 0xd5, 0xde, 0xdb, 0xe2, 0xeb, 0xe9, 0xee, 0x61, 0x50, 0x74, 0xf0,
    0xef, 0xf2, 0xed, 0xeb, 0xef, 0xf2, 0xf0, 0xf4, 0x58, 0x46, 0x6c, 0x4b, 0x37, 0x60, 0xc8, 0xc2,
    0xcf, 0x5b, 0x49, 0x6f, 0xc4, 0xbd, 0xcb, 0x8c, 0x80, 0x9a, 0xaf, 0xa6, 0xb8, 0x78, 0x69, 0x88,
    0x70, 0x61, 0x81, 0x8f, 0x83, 0x9d, 0x4b, 0x38, 0x61, 0xf3, 0xf2, 0xf5, 0x5a, 0x48, 0x6e, 0x73,
    0x63, 0x83, 0xe2, 0xdf, 0xe6, 0x8d, 0x80, 0x9b, 0x60, 0x4e, 0x73, 0xcb, 0xc5, 0xd1, 0xa4, 0x9a,
    0xaf, 0x46, 0x32, 0x5c, 0xea, 0xe7, 0xec, 0xf8, 0xf7, 0xf9, 0x57, 0x45, 0x6b, 0x88, 0x7b, 0x97,
    0xd5, 0xd0, 0xda, 0xb7, 0xaf, 0xc0, 0xe4, 0xe1, 0xe7, 0xc2, 0xbc, 0xca, 0x97, 0x8b, 0xa3, 0x4c,
    0x39, 0x61, 0xbc, 0xb4, 0xc4, 0x86, 0x79, 0x95, 0xb3, 0xab, 0xbc, 0x67, 0x57, 0x79, 0xbd, 0xb6,
    0xc5, 0x49, 0x35, 0x5f, 0x45, 0x30, 0x5b, 0xb1, 0xa9, 0xba, 0x76, 0x67, 0x86, 0xce, 0xc9, 0xd4,
    0xe9, 0xe6, 0xec, 0xa8, 0x9f, 0xb2, 0x5d, 0x7e, 0x49, 0x75, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48,
    0x59, 0x73, 0x00, 0x00, 0x0e, 0xc4, 0x00, 0x00, 0x0e, 0xc4, 0x01, 0x95, 0x2b, 0x0e, 0x1b, 0x00,
    0x00, 0x00, 0x18, 0x74, 0x45, 0x58, 0x74, 0x53, 0x6f, 0x66, 0x74, 0x77, 0x61, 0x72, 0x65, 0x00,
    0x50, 0x61, 0x69, 0x6e, 0x74, 0x2e, 0x4e, 0x45, 0x54, 0x20, 0x35, 0x2e, 0x31, 0x2e, 0x37, 0x8b,
    0xd6, 0xf7, 0x39, 0x00, 0x00, 0x00, 0xb6, 0x65, 0x58, 0x49, 0x66, 0x49, 0x49, 0x2a, 0x00, 0x08,
    0x00, 0x00, 0x00, 0x05, 0x00, 0x1a, 0x01, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00,
    0x00, 0x1b, 0x01, 0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0x52, 0x00, 0x00, 0x00, 0x28, 0x01, 0x03,
    0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x31, 0x01, 0x02, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x5a, 0x00, 0x00, 0x00, 0x69, 0x87, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x6a, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0xa8, 0x93, 0x00, 0x00, 0xe8, 0x03, 0x00, 0x00, 0xa8, 0x93, 0x00,
    0x00, 0xe8, 0x03, 0x00, 0x00, 0x50, 0x61, 0x69, 0x6e, 0x74, 0x2e, 0x4e, 0x45, 0x54, 0x20, 0x35,
    0x2e, 0x31, 0x2e, 0x37, 0x00, 0x03, 0x00, 0x00, 0x90, 0x07, 0x00, 0x04, 0x00, 0x00, 0x00, 0x30,
    0x32, 0x33, 0x30, 0x01, 0xa0, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x05,
    0xa0, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x94, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
    0x00, 0x01, 0x00, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00, 0x52, 0x39, 0x38, 0x00, 0x02, 0x00, 0x07,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x30, 0x31, 0x30, 0x30, 0x00, 0x00, 0x00, 0x00, 0xb0, 0x16, 0x20,
    0xd0, 0xfe, 0x2a, 0x41, 0x10, 0x00, 0x00, 0x02, 0x31, 0x49, 0x44, 0x41, 0x54, 0x48, 0x4b, 0xb5,
    0x95, 0x69, 0x53, 0x13, 0x41, 0x18, 0x84, 0xc7, 0x41, 0x40, 0x70, 0x25, 0x1e, 0x11, 0x14, 0x3c,
    0x40, 0x44, 0x50, 0x10, 0xa3, 0xdc, 0x82, 0x02, 0x42, 0x3c, 0x10, 0xe5, 0x88, 0x0a, 0xde, 0x0a,
    0x82, 0x8a, 0x04, 0xfe, 0xff, 0x37, 0xba, 0xdf, 0x77, 0x86, 0x64, 0xb3, 0x3b, 0x6b, 0xca, 0x2a,
    0xbb, 0x8a, 0xf4, 0x33, 0x3d, 0x53, 0x9d, 0xd9, 0x99, 0x05, 0x0c, 0x75, 0xc2, 0x5a, 0x2b, 0x90,
    0xa9, 0x06, 0xac, 0x3a, 0xe9, 0x38, 0xa1, 0xc6, 0xba, 0x2a, 0x9a, 0xb0, 0xaa, 0xd9, 0x71, 0x42,
    0xa7, 0xea, 0xaa, 0x68, 0xc1, 0xaa, 0x56, 0xc7, 0x09, 0x9d, 0x8e, 0xa2, 0x33, 0x0e, 0x33, 0xd4,
    0x96, 0x3b, 0x9b, 0x3b, 0xe7, 0xf8, 0x7f, 0xc8, 0x3f, 0xc8, 0x79, 0xf8, 0x05, 0x49, 0xf2, 0x17,
    0xdb, 0xc5, 0xa9, 0x0e, 0x37, 0xcb, 0xb3, 0xb8, 0x24, 0x89, 0x31, 0x97, 0x3b, 0x31, 0xb0, 0x5d,
    0x6e, 0x04, 0x5d, 0x71, 0x8b, 0xae, 0xc2, 0xaf, 0x49, 0x72, 0xdd, 0xda, 0x6e, 0x01, 0xc8, 0x57,
    0x74, 0xc1, 0x7b, 0x24, 0x31, 0x37, 0x80, 0x54, 0xef, 0x4d, 0x1d, 0xa7, 0xed, 0xa2, 0x0f, 0x74,
    0x4b, 0x28, 0x6d, 0x17, 0xfd, 0x03, 0x40, 0xd5, 0x6d, 0x09, 0x42, 0x15, 0xf6, 0x8e, 0x60, 0xb2,
    0xa2, 0x99, 0x93, 0x5e, 0x0c, 0xa0, 0x40, 0x45, 0xaf, 0x60, 0xb2, 0x62, 0x90, 0x93, 0x03, 0x43,
    0x77, 0x87, 0xe9, 0xf7, 0x98, 0x04, 0x2b, 0xdc, 0x37, 0x24, 0x2a, 0x38, 0xd5, 0x54, 0x00, 0xe4,
    0x00, 0x1d, 0x4c, 0xc2, 0x15, 0xf7, 0x85, 0xd3, 0x2a, 0x1e, 0xd0, 0x85, 0x46, 0x94, 0xfc, 0x0b,
    0x3e, 0x0a, 0x1f, 0x93, 0x64, 0x1c, 0x04, 0xc9, 0xad, 0x4c, 0x00, 0xe8, 0x93, 0x70, 0x39, 0x1e,
    0xb8, 0xbb, 0x09, 0xae, 0x51, 0xf2, 0x15, 0xbc, 0x54, 0xad, 0xc0, 0xa5, 0x52, 0x53, 0xe4, 0x87,
    0x00, 0x3a, 0x2f, 0xd5, 0x57, 0xb4, 0xd1, 0xb5, 0x62, 0x5a, 0x28, 0xf5, 0xbd, 0x50, 0x81, 0xf9,
    0xc4, 0xcc, 0x8e, 0xdf, 0x0b, 0xf8, 0x0c, 0x5d, 0x2b, 0x1e, 0x09, 0x05, 0x77, 0x91, 0xa8, 0xf0,
    0xbb, 0x08, 0x56, 0xd4, 0x9c, 0xc5, 0x63, 0xfc, 0xcc, 0x56, 0x2a, 0xaa, 0xcf, 0x42, 0x2b, 0xe6,
    0x40, 0x76, 0x5e, 0x30, 0x70, 0x23, 0x5c, 0xf1, 0xa4, 0x52, 0x51, 0x7d, 0x23, 0xac, 0x58, 0x90,
    0xdf, 0x13, 0xbb, 0xc8, 0x28, 0xe5, 0x2c, 0x8a, 0x9c, 0x2c, 0x3e, 0xc5, 0xc7, 0xb3, 0x3e, 0xfe,
    0xb5, 0x62, 0x16, 0x3f, 0x8b, 0xe7, 0x2f, 0x60, 0x94, 0x3e, 0x48, 0x72, 0x17, 0x79, 0x4e, 0xe6,
    0x97, 0xf8, 0xf9, 0x32, 0x6d, 0x17, 0xcb, 0xaf, 0x38, 0x25, 0xd2, 0x5d, 0x04, 0x2a, 0x0a, 0xe6,
    0x35, 0xcd, 0x9f, 0x54, 0xec, 0xed, 0xac, 0x28, 0xf3, 0x41, 0xf2, 0xc6, 0xac, 0xd0, 0x21, 0x66,
    0xd5, 0x0f, 0x42, 0xad, 0x2e, 0x0b, 0xe9, 0x83, 0x54, 0x57, 0xe8, 0x8d, 0x48, 0xc5, 0x9a, 0x73,
    0x88, 0x59, 0x6d, 0x05, 0xbe, 0x81, 0x16, 0xaf, 0x58, 0x87, 0xeb, 0x75, 0xcd, 0x73, 0x92, 0x40,
    0x77, 0x18, 0xaf, 0x28, 0xbd, 0x71, 0x14, 0x3f, 0x4e, 0x2e, 0x7a, 0x2b, 0x49, 0x2b, 0xe8, 0x1d,
    0x61, 0x83, 0xab, 0x74, 0xb6, 0xf6, 0x52, 0x95, 0x6a, 0x8e, 0x73, 0x13, 0xfe, 0xfe, 0x03, 0xe0,
    0xe3, 0x27, 0xd0, 0x67, 0x46, 0xf2, 0xda, 0xd5, 0x51, 0xe1, 0xcf, 0xfc, 0x0b, 0x23, 0xbc, 0x4c,
    0xa6, 0x44, 0xf8, 0xca, 0xc8, 0x7c, 0x23, 0x66, 0x57, 0x7c, 0xcf, 0x6d, 0x6d, 0x93, 0x24, 0xfa,
    0x41, 0x72, 0x9a, 0x90, 0xc4, 0x98, 0xe9, 0x11, 0x0c, 0x08, 0xc1, 0x8a, 0x1d, 0x1a, 0xa4, 0xd9,
    0x90, 0x1b, 0x41, 0x1a, 0x40, 0xbb, 0x6e, 0xf0, 0xb7, 0x8a, 0x48, 0xb3, 0x82, 0x8e, 0x20, 0x39,
    0x4c, 0x15, 0x46, 0xb4, 0xec, 0x8a, 0x9f, 0x4b, 0x1a, 0x51, 0xbf, 0x7e, 0xdb, 0xbd, 0xca, 0xff,
    0x21, 0xd1, 0x9f, 0x7d, 0x7e, 0xce, 0x95, 0xcb, 0xe5, 0x03, 0x02, 0xbc, 0x48, 0x17, 0x2a, 0xe3,
    0x16, 0xa2, 0xa8, 0x74, 0xa8, 0xc1, 0x3f, 0xc9, 0x98, 0x23, 0xe0, 0x06, 0x3a, 0x06, 0x1c, 0xfa,
    0x59, 0x16, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42, 0x60, 0x82};

#endif