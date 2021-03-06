#include "Chip.hpp"
#include "Tile.hpp"
#include "Database.hpp"
#include "Util.hpp"
#include <algorithm>

using namespace std;

namespace Trellis {

Chip::Chip(string name) : Chip(get_chip_info(find_device_by_name(name))) {};

Chip::Chip(uint32_t idcode) : Chip(get_chip_info(find_device_by_idcode(idcode))) {};

Chip::Chip(const Trellis::ChipInfo &info) : info(info), cram(info.num_frames, info.bits_per_frame) {
    vector<TileInfo> allTiles = get_device_tilegrid(DeviceLocator{info.family, info.name});
    for (const auto &tile : allTiles) {
        tiles[tile.name] = make_shared<Tile>(tile, *this);
    }
}

shared_ptr<Tile> Chip::get_tile_by_name(string name) {
    return tiles.at(name);
}

vector<shared_ptr<Tile>> Chip::get_tiles_by_position(int row, int col) {
    vector<shared_ptr<Tile>> result;
    for (const auto &tile : tiles) {
        if (tile.second->info.get_row_col() == make_pair(row, col))
            result.push_back(tile.second);
    }
    return result;
}

vector<shared_ptr<Tile>> Chip::get_tiles_by_type(string type) {
    vector<shared_ptr<Tile>> result;
    for (const auto &tile : tiles) {
        if (tile.second->info.type == type)
            result.push_back(tile.second);
    }
    return result;
}

}
