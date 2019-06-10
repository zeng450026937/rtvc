#ifndef YEALINK_API_PEERCONNECTION_INTERFACE_H_
#define YEALINK_API_PEERCONNECTION_INTERFACE_H_

#include "api/peer_connection_interface.h"

namespace yealink {

class PeerConnectionInterface : public webrtc::PeerConnectionInterface {
 protected:
  ~PeerConnectionInterface() override = default;
};

class PeerConnectionFactoryInterface
    : public webrtc::PeerConnectionFactoryInterface {
 protected:
  ~PeerConnectionFactoryInterface() override = default;
};

}  // namespace yealink

#endif  // YEALINK_API_PEERCONNECTION_INTERFACE_H_
