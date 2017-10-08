#ifndef COMMON_H
#define COMMON_H
#include <base/basic.h>
#include <Buffer.h>
#include <arpa/inet.h>
#include <Log.h>

const uint32 PACKET_HEAD_LEN = 20;
struct PACKET {
    PACKET(){}
    uint32_t len; //整个包体的长度
    uint32_t cmd;
    uint64_t uid;
    uint32_t sid;
    std::string msg;
};

inline std::string Encode(struct PACKET& pkt) {
    char* msg_ = new char[pkt.len];
    char* msg = msg_;
    memset(msg_, 0, pkt.len);
    
    *reinterpret_cast<uint32_t*>(msg_) = htonl(pkt.len);
    msg_ += sizeof(uint32_t);
    *reinterpret_cast<uint32_t*>(msg_) = htonl(pkt.cmd);
    msg_ += sizeof(uint32_t);
    *reinterpret_cast<uint64_t*>(msg_) = htobe64(pkt.uid);
    msg_ += sizeof(uint64_t);
    *reinterpret_cast<uint32_t*>(msg_) = htonl(pkt.sid);
    msg_ += sizeof(uint32_t);
    pkt.msg.copy(msg_, pkt.msg.size(), 0);
    std::string smsg(msg, pkt.len);
    delete msg;
    return smsg;
}

inline struct PACKET Decode(char* src) {
    struct PACKET pkt;
    //ntohl(*reinterpret_cast<const uint32_t>(src))
    pkt.len = ntohl(*reinterpret_cast<const uint32_t*>(src));
    src += sizeof(uint32_t);
    pkt.cmd = ntohl(*reinterpret_cast<const uint32_t*>(src));
    src += sizeof(uint32_t);
    pkt.uid = be64toh(*reinterpret_cast<const uint64_t*>(src));
    src += sizeof(uint64_t);
    pkt.sid = ntohl(*reinterpret_cast<const uint32_t*>(src));
    src += sizeof(uint32_t);
    pkt.msg = std::string(src, pkt.len - PACKET_HEAD_LEN);
    return pkt;
}

inline bool checkBufValid(khaki::Buffer& buf) {
    char* src = buf.begin();
    uint32_t len = buf.size();
    uint32_t pktLen = ntohl(*reinterpret_cast<const uint32_t*>(src));
    if ( pktLen > len ) {
        return false;
    }
    return true;
}

#endif