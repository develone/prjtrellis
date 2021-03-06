#ifndef LIBTRELLIS_CHIP_HPP
#define LIBTRELLIS_CHIP_HPP

#include <string>
#include <memory>
#include <vector>
#include <cstdint>
#include <map>

#include "CRAM.hpp"

using namespace std;
namespace Trellis {

// Basic information about a chip that may be needed elsewhere
struct ChipInfo {
    string name;
    string family;
    uint32_t idcode;
    int num_frames;
    int bits_per_frame;
    int pad_bits_before_frame;
    int pad_bits_after_frame;
};

class Tile;

class Chip {
public:
    // Construct a chip by looking up part name
    explicit Chip(string name);

    // Construct a chip by looking up device ID
    explicit Chip(uint32_t idcode);

    // Construct a chip from a ChipInfo
    explicit Chip(const ChipInfo &info);

    // Basic information about a chip
    ChipInfo info;

    // The chip's configuration memory
    CRAM cram;

    // Tile access
    shared_ptr<Tile> get_tile_by_name(string name);

    vector<shared_ptr<Tile>> get_tiles_by_position(int row, int col);

    vector<shared_ptr<Tile>> get_tiles_by_type(string type);

    // Map tile name to a tile reference
    map<string, shared_ptr<Tile>> tiles;

    // Miscellaneous information
    uint32_t usercode = 0x0;
    vector<string> metadata;
};
}

#endif //LIBTRELLIS_CHIP_HPP
