#pragma once
#ifndef ARTNET_COMMON_H
#define ARTNET_COMMON_H

#include <ArxTypeTraits.h>
#include <ArxContainer.h>
#include <stdint.h>
#include <stddef.h>

namespace art_net {
// Packet Summary : https://art-net.org.uk/structure/packet-summary-2/
// Packet Definition : https://art-net.org.uk/structure/streaming-packets/artdmx-packet-definition/

enum class OpCode : uint16_t {
    // Device Discovery
    Poll = 0x2000,
    PollReply = 0x2100,
    // Device Configuration
    Address = 0x6000,
    Input = 0x7000,
    IpProg = 0xF800,
    IpProgReply = 0xF900,
    Command = 0x2400,
    // Streaming Control
    Dmx = 0x5000,
    Nzs = 0x5100,
    Sync = 0x5200,
    // RDM
    TodRequest = 0x8000,
    TodData = 0x8100,
    TodControl = 0x8200,
    Rdm = 0x8300,
    RdmSub = 0x8400,
    // Time-Keeping
    TimeCode = 0x9700,
    TimeSync = 0x9800,
    // Triggering
    Trigger = 0x9900,
    // Diagnostics
    DiagData = 0x2300,
    // File Transfer
    FirmwareMaster = 0xF200,
    FirmwareReply = 0xF300,
    Directory = 0x9A00,
    DirectoryReply = 0x9B00,
    FileTnMaster = 0xF400,
    FileFnMaster = 0xF500,
    FileFnReply = 0xF600,
    // N/A
    NA = 0x0000,
};

constexpr uint16_t DEFAULT_PORT {6454};  // 0x1936
constexpr uint16_t PROTOCOL_VER {14}; // 0x000E
constexpr uint8_t ID_LENGTH {8};
constexpr char ARTNET_ID[ID_LENGTH] {"Art-Net"};
constexpr size_t NUM_POLLREPLY_PUBLIC_PORT_LIMIT {4};
constexpr float DEFAULT_FPS {40.};
constexpr uint32_t DEFAULT_INTERVAL_MS {(uint32_t)(1000. / DEFAULT_FPS)};

// ArtDmx, ArtTrigger has same structure
constexpr uint16_t HEADER_SIZE {18};
constexpr uint16_t PACKET_SIZE {530};

using CallbackAllType = std::function<void(const uint32_t universe, const uint8_t* data, const uint16_t size)>;
using CallbackType = std::function<void(const uint8_t* data, const uint16_t size)>;
using CallbackArtsync = std::function<void(void)>;

#if ARX_HAVE_LIBSTDCPLUSPLUS >= 201103L  // Have libstdc++11
template <uint16_t SIZE>
using Array = std::array<uint8_t, SIZE>;
using IntervalMap = std::map<uint32_t, uint32_t>;
using CallbackMap = std::map<uint32_t, CallbackType>;
using namespace std;
#else
template <uint16_t SIZE>
using Array = arx::vector<uint8_t, SIZE>;
using IntervalMap = arx::map<uint32_t, uint32_t>;
using CallbackMap = arx::map<uint32_t, CallbackType, NUM_POLLREPLY_PUBLIC_PORT_LIMIT>;
using namespace arx;
#endif

}  // namespace art_net

#endif  // ARTNET_COMMON_H
