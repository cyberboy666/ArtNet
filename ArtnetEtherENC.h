#pragma once
#ifndef ARTNET_ETHER_H
#define ARTNET_ETHER_H

#define ARTNET_ENABLE_ETHER
#define ARTNET_ETHER_IS_ENC28J60

#include <Arduino.h>
#include <ArxTypeTraits.h>
#include <ArxContainer.h>
#include <EthernetENC.h>
#include <EthernetUdp.h>
#include "Artnet/util/TeensyDirtySTLErrorSolution/TeensyDirtySTLErrorSolution.h"
#include "Artnet/Manager.h"

using Artnet = art_net::Manager<EthernetUDP>;
using ArtnetSender = art_net::Sender<EthernetUDP>;
using ArtnetReceiver = art_net::Receiver<EthernetUDP>;

#endif  // ARTNET_ETHER_H
