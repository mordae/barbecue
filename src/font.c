#include <stdint.h>

uint8_t tft_font[256][16] = {
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x42, 0x42, 0x42, 0x42, 0x42,
  0x42, 0x42, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x42,
  0x42, 0x42, 0x42, 0x42, 0x5a, 0x5a, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x18, 0x3c, 0x42, 0x42, 0x42, 0x5a, 0x5a, 0x5a, 0x5a, 0x42, 0x3c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x42, 0x5a, 0x5a, 0x5a, 0x5a,
  0x5a, 0x5a, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x3c, 0x42,
  0x4a, 0x4a, 0x5a, 0x5a, 0x52, 0x52, 0x42, 0x3c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xa1, 0x43, 0xa5, 0x09, 0x11, 0x21, 0x41, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x05, 0x09, 0x11,
  0x21, 0x41, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01,
  0x03, 0x05, 0x09, 0x19, 0x39, 0x79, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x26,
  0x27, 0x24, 0x24, 0xe4, 0x64, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x20, 0x30, 0x38, 0x3c, 0x38, 0x30, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x66, 0x66, 0x66, 0x66, 0x66,
  0x66, 0x66, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x03, 0x06, 0x0c, 0xff, 0xff, 0x30, 0x60, 0xc0, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x30, 0xff, 0xff,
  0x0c, 0x06, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0x22, 0x22, 0x44, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x12, 0x12, 0x7f, 0x24, 0x24, 0xfe, 0x48, 0x48, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x20, 0x70, 0xa8, 0xa0, 0xa0, 0x70, 0x28, 0x28, 0xa8, 0x70, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x91, 0x92, 0x64, 0x08, 0x10,
  0x26, 0x49, 0x89, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
  0x48, 0x48, 0x30, 0x50, 0x8a, 0x84, 0x8a, 0x70, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x20, 0xa8, 0x70, 0x20, 0x70, 0xa8, 0x20, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0xfe,
  0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x08,
  0x08, 0x10, 0x10, 0x20, 0x20, 0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x84, 0x84, 0x8c, 0x94, 0xa4, 0xc4, 0x84, 0x84, 0x78,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x84,
  0x84, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x84, 0x04, 0x04, 0x38, 0x04, 0x04, 0x04, 0x84, 0x78,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x18, 0x28, 0x48, 0x88, 0xfc,
  0x08, 0x08, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x80,
  0x80, 0x80, 0xf8, 0x04, 0x04, 0x04, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x84, 0x80, 0x80, 0xf8, 0x84, 0x84, 0x84, 0x84, 0x78,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x04, 0x04, 0x08, 0x08, 0x08,
  0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x84,
  0x84, 0x84, 0x78, 0x84, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x7c, 0x04, 0x04, 0x04, 0x84, 0x78,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00,
  0x00, 0xc0, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0,
  0xc0, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x08,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00,
  0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80,
  0x40, 0x20, 0x10, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x70, 0x88, 0x88, 0x08, 0x10, 0x20, 0x20, 0x20, 0x00, 0x20,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x42, 0x82, 0x9e, 0xa2, 0xa6,
  0x9a, 0x80, 0x40, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48,
  0x84, 0x84, 0x84, 0xfc, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xf8, 0x84, 0x84, 0x84, 0xf8, 0x84, 0x84, 0x84, 0x84, 0xf8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x84, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x84,
  0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0xf8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfc, 0x80, 0x80, 0x80, 0xf0, 0x80, 0x80, 0x80, 0x80, 0xfc,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x80, 0x80, 0x80, 0xf0, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x84,
  0x80, 0x80, 0x80, 0x9c, 0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0xfc, 0x84, 0x84, 0x84, 0x84, 0x84,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x40, 0x40, 0x40, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0x04,
  0x04, 0x04, 0x04, 0x04, 0x04, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x84, 0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x88, 0x84, 0x82,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0xc6,
  0xaa, 0x92, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x82, 0xc2, 0xa2, 0xa2, 0x92, 0x92, 0x8a, 0x8a, 0x86, 0x82,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84,
  0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x84,
  0x84, 0x84, 0xf8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x94, 0x88, 0x74,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x84, 0x84, 0x84, 0xf8, 0xc0,
  0xa0, 0x90, 0x88, 0x84, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x84,
  0x80, 0x80, 0x78, 0x04, 0x04, 0x04, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84,
  0x84, 0x84, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x82,
  0x82, 0x82, 0x44, 0x44, 0x44, 0x28, 0x28, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x54, 0x54, 0x54, 0x28,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x82, 0x44, 0x28, 0x10, 0x10,
  0x28, 0x44, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x82, 0x82,
  0x44, 0x44, 0x28, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x80, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x40,
  0x40, 0x20, 0x20, 0x10, 0x10, 0x08, 0x08, 0x04, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xc0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0xc0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x44, 0x82, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x40, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x08, 0x78,
  0x88, 0x88, 0x88, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80,
  0xb8, 0xc4, 0x84, 0x84, 0x84, 0x84, 0xc4, 0xb8, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x80, 0x80, 0x80, 0x88, 0x70,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x74, 0x8c, 0x84, 0x84,
  0x84, 0x84, 0x8c, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x78, 0x84, 0x84, 0xf8, 0x80, 0x80, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x38, 0x44, 0x40, 0xf0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7a, 0x84, 0x84, 0x84,
  0x84, 0x84, 0x78, 0x40, 0xb8, 0x84, 0x78, 0x00, 0x00, 0x80, 0x80, 0x80,
  0xb8, 0xc4, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x20, 0x00, 0xe0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xf0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x38, 0x08, 0x08, 0x08,
  0x08, 0x08, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
  0x88, 0x90, 0xa0, 0xe0, 0x90, 0x90, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xe0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xf8,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xec, 0x92, 0x92, 0x92,
  0x92, 0x92, 0x92, 0x92, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf0, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xb8, 0xc4, 0x84, 0x84,
  0x84, 0x84, 0xc4, 0xb8, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x74, 0x8c, 0x84, 0x84, 0x84, 0x84, 0x8c, 0x74, 0x04, 0x04, 0x04, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xb0, 0xc8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x88, 0x80, 0x70,
  0x08, 0x08, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40,
  0xf0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x8c, 0x74,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x88, 0x88,
  0x50, 0x50, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x82, 0x92, 0x92, 0x92, 0x92, 0x92, 0x92, 0x6c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x88, 0x88, 0x50, 0x20, 0x20, 0x50, 0x88, 0x88,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x84, 0x84, 0x84,
  0x84, 0x8c, 0x74, 0x04, 0x04, 0x08, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xfc, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xfc, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x60, 0x80, 0x80, 0x80, 0x40, 0x80, 0x40, 0x80, 0x80, 0x80, 0x60,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x20, 0x20,
  0x20, 0x40, 0x20, 0x40, 0x20, 0x20, 0x20, 0xc0, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x92, 0x0c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x44,
  0x82, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x40, 0x50, 0x60, 0x40, 0xc0,
  0x40, 0x40, 0x40, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5d, 0x22,
  0x41, 0x41, 0x41, 0x22, 0x5d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x30, 0x10, 0xa0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x7c, 0x82, 0x80, 0x80, 0x7c,
  0x02, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x21, 0x31,
  0x28, 0x24, 0x12, 0x09, 0x05, 0x23, 0x21, 0x1e, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x28, 0x10, 0x00, 0x7c, 0x82, 0x80, 0x80, 0x7c,
  0x02, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x82,
  0x80, 0x80, 0x7c, 0x02, 0x02, 0x02, 0x82, 0x7c, 0x10, 0x10, 0x08, 0x00,
  0x28, 0x10, 0x00, 0xfe, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0xfe, 0x02, 0x04, 0x08, 0x10,
  0x20, 0x40, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x10, 0x00, 0xfe, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xfe, 0x02, 0x04, 0x08, 0x10,
  0x20, 0x40, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x30, 0x48, 0x48, 0x30,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x02, 0x7e, 0x82, 0x82, 0x82, 0x7d,
  0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x14,
  0x18, 0x10, 0x30, 0x50, 0x10, 0x10, 0x10, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x0c, 0x04, 0x78, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00,
  0x7c, 0x82, 0x80, 0x7c, 0x02, 0x02, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x20, 0x00,
  0x70, 0x88, 0x80, 0x70, 0x08, 0x08, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x80, 0x7c, 0x02, 0x02, 0x82, 0x7c,
  0x10, 0x10, 0x08, 0x00, 0x00, 0x06, 0x42, 0x44, 0xf0, 0x40, 0x40, 0x40,
  0x40, 0x40, 0x48, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00,
  0xfe, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x10, 0x00, 0xfe, 0x04, 0x08, 0x10,
  0x20, 0x40, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
  0xfe, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x10, 0x00, 0xfc, 0x82, 0x82, 0x82, 0xfc, 0x90, 0x88, 0x84, 0x82,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x38, 0x44, 0x82, 0x82, 0xfe,
  0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x00, 0x38,
  0x44, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x10, 0x00, 0x38, 0x44, 0x82, 0x82, 0xfe, 0x82, 0x82, 0x82, 0x82,
  0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x38, 0x44, 0x82, 0x82, 0x82, 0xfe,
  0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x20, 0x40, 0x00, 0x80,
  0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x10, 0x00, 0x7c, 0x82, 0x80, 0x80, 0x80, 0x80, 0x80, 0x82, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x80, 0x80, 0x80, 0x80,
  0x80, 0x80, 0x82, 0x7c, 0x10, 0x10, 0x08, 0x00, 0x28, 0x10, 0x00, 0x7c,
  0x82, 0x80, 0x80, 0x80, 0x80, 0x80, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x08, 0x10, 0x00, 0xfe, 0x80, 0x80, 0x80, 0xf8, 0x80, 0x80, 0x80, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x80, 0x80, 0x80, 0xf8, 0x80,
  0x80, 0x80, 0x80, 0xfe, 0x10, 0x10, 0x08, 0x00, 0x00, 0x28, 0x00, 0xfe,
  0x80, 0x80, 0x80, 0xf8, 0x80, 0x80, 0x80, 0xfe, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x10, 0x00, 0xfe, 0x80, 0x80, 0x80, 0xf8, 0x80, 0x80, 0x80, 0xfe,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x38, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x00, 0x38,
  0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x38, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x10, 0x00, 0xfc, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0xfc,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x84, 0x84, 0x84, 0xe4, 0x84,
  0x84, 0x84, 0x84, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x82,
  0xc2, 0xa2, 0xa2, 0x92, 0x8a, 0x8a, 0x86, 0x82, 0x00, 0x00, 0x00, 0x00,
  0x28, 0x10, 0x00, 0x82, 0xc2, 0xa2, 0xa2, 0x92, 0x8a, 0x8a, 0x86, 0x82,
  0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82,
  0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x00, 0x7c,
  0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x14, 0x28, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82,
  0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x50, 0x20, 0x00, 0xf8, 0x84, 0x84, 0x84, 0xf8, 0xa0, 0x90, 0x88, 0x84,
  0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x10, 0x82, 0x82, 0x82, 0x82, 0x82,
  0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x82,
  0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x14, 0x28, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82,
  0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x82, 0x82,
  0x44, 0x44, 0x28, 0x10, 0x10, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0xfe, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x08, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0x82, 0xbc, 0x82,
  0x82, 0x82, 0x82, 0xbc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00,
  0xbc, 0xc2, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x20, 0x00, 0x70, 0x88, 0x08, 0x78, 0x88, 0x88, 0x88, 0x74,
  0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0x88, 0x00, 0x70, 0x88, 0x08, 0x78,
  0x88, 0x88, 0x88, 0x74, 0x00, 0x00, 0x00, 0x00, 0x88, 0x50, 0x20, 0x00,
  0x70, 0x88, 0x08, 0x78, 0x88, 0x88, 0x88, 0x74, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x50, 0x50, 0x00, 0x70, 0x88, 0x08, 0x78, 0x88, 0x88, 0x88, 0x74,
  0x00, 0x00, 0x00, 0x00, 0x28, 0x10, 0x00, 0x70, 0x10, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00,
  0x7c, 0x82, 0x80, 0x80, 0x80, 0x80, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x80, 0x80, 0x80, 0x80, 0x82, 0x7c,
  0x10, 0x10, 0x08, 0x00, 0x00, 0x50, 0x20, 0x00, 0x70, 0x88, 0x80, 0x80,
  0x80, 0x80, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x20, 0x00,
  0x78, 0x84, 0x84, 0xf8, 0x80, 0x80, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x7c, 0x82, 0x82, 0xfc, 0x80, 0x80, 0x82, 0x7c,
  0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 0x28, 0x00, 0x7c, 0x82, 0x82, 0xfc,
  0x80, 0x80, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x10, 0x00,
  0x78, 0x84, 0x84, 0xf8, 0x80, 0x80, 0x84, 0x78, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x20, 0x00, 0xe0, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0xf0,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x28, 0x00, 0x70, 0x10, 0x10, 0x10,
  0x10, 0x10, 0x10, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x03, 0x02,
  0x7a, 0x86, 0x82, 0x82, 0x82, 0x82, 0x86, 0x7a, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x02, 0x07, 0x02, 0x7a, 0x86, 0x82, 0x82, 0x82, 0x82, 0x86, 0x7a,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0xfc, 0x82, 0x82, 0x82,
  0x82, 0x82, 0x82, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x20, 0x00,
  0xf0, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x08, 0x10, 0x00, 0x78, 0x84, 0x84, 0x84, 0x84, 0x84, 0x84, 0x78,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x50, 0x00, 0x70, 0x88, 0x88, 0x88,
  0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x28, 0x00,
  0x7c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x28, 0x00, 0x7c, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x7c,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0x20, 0x00,
  0xb0, 0xc8, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x10, 0x28, 0x10, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x86, 0x7a,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x82, 0x82, 0x82, 0x82,
  0x82, 0x82, 0x86, 0x7a, 0x00, 0x00, 0x00, 0x00, 0x00, 0x14, 0x28, 0x00,
  0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x86, 0x7a, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x28, 0x00, 0x82, 0x82, 0x82, 0x82, 0x82, 0x82, 0x86, 0x7a,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x82, 0x82, 0x82, 0x82,
  0x82, 0x86, 0x7a, 0x02, 0x02, 0x04, 0x38, 0x00, 0x00, 0x00, 0x40, 0x40,
  0xf0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x42, 0x3c, 0x10, 0x10, 0x08, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
