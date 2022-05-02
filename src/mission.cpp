#include <iostream>
#include <string>

#include <arpa/inet.h> // htons, inet_addr
#include <netinet/in.h> // sockaddr_in
#include <sys/types.h> // uint16_t
#include <sys/socket.h> // socket, sendto
#include <unistd.h> // close

#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <vector>

#include "common_DerivedEntityFactory.hpp"
#include "MAVLINKSerializer.h"
#include "EntityFactory.h"

#include "CommandLong.hpp"
#include "MissionItem.hpp"
#include "MissionClearAll.hpp"
#include "MissionRequest.hpp"
#include "MissionCount.hpp"
#include "MissionRequestList.hpp"
#include "MissionAck.hpp"
#include "Heartbeat.hpp"

std::string hostname{"127.0.0.1"};
uint16_t port = 18570;

int sock = ::socket(AF_INET, SOCK_DGRAM, 0);

void heartbeat(minimal::MavType::EnumItem mavType, minimal::MavAutopilot::EnumItem mavAutopilot);
void heartbeat(minimal::MavType::EnumItem mavType, minimal::MavAutopilot::EnumItem mavAutopilot) {


    minimal::Heartbeat _heartbeat;
    _heartbeat.setMagic(254,true);
    _heartbeat.setSysid(255,true);
    _heartbeat.setMsgid(0,true);
    _heartbeat.setType(mavType);
    _heartbeat.setAutopilot(mavAutopilot);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> heartbeat_bytes;
    if (!serializer->serialize(_heartbeat, heartbeat_bytes)) {
        _exit(1);
    }
    int n_bytes = ::sendto(sock, &heartbeat_bytes[0], heartbeat_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));

    std::cout << n_bytes << " bytes sent" << std::endl;
}

void mission_item_takeoff(float lat, float lon, float alt, common::MavFrame::EnumItem mavFrame, common::MavCmd::MavCmdChoice mavCmd, int seq);
void mission_item_takeoff(float lat, float lon, float alt, common::MavFrame::EnumItem mavFrame, common::MavCmd::MavCmdChoice mavCmd, int seq) {
    

    common::MissionItem _mission_item;
    _mission_item.setMagic(254,true);
    _mission_item.setSysid(255,true);
    _mission_item.setMsgid(27,true);
    _mission_item.setTargetComponent(1);
    _mission_item.setTargetSystem(1);
    _mission_item.setFrame(mavFrame);
    _mission_item.getCommand()->setMavCmdChoiceType(mavCmd);
    _mission_item.getCommand()->getMavCmdNavTakeoff()->setPitch(1);
    _mission_item.getCommand()->getMavCmdNavTakeoff()->setParam2(0);
    _mission_item.getCommand()->getMavCmdNavTakeoff()->setParam3(0);
    _mission_item.getCommand()->getMavCmdNavTakeoff()->setYaw(0);
    _mission_item.getCommand()->getMavCmdNavTakeoff()->setLatitude(lat);
    _mission_item.getCommand()->getMavCmdNavTakeoff()->setLongitude(lon);
    _mission_item.getCommand()->getMavCmdNavTakeoff()->setAltitude(alt);
    _mission_item.setSeq(seq);
    _mission_item.setAutocontinue(1);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> mission_item_bytes;
    if (!serializer->serialize(_mission_item, mission_item_bytes)) {
        _exit(1);
    }

    int n_bytes = ::sendto(sock, &mission_item_bytes[0], mission_item_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
    
    std::cout << n_bytes << " bytes sent" << std::endl;

}

void mission_item_land(float lat, float lon, float alt, common::MavFrame::EnumItem mavFrame, common::MavCmd::MavCmdChoice mavCmd, int seq);
void mission_item_land(float lat, float lon, float alt, common::MavFrame::EnumItem mavFrame, common::MavCmd::MavCmdChoice mavCmd, int seq) {
    

    common::MissionItem _mission_item;
    _mission_item.setMagic(254,true);
    _mission_item.setSysid(255,true);
    _mission_item.setMsgid(27,true);
    _mission_item.setTargetComponent(1);
    _mission_item.setTargetSystem(1);
    _mission_item.setFrame(mavFrame);
    _mission_item.getCommand()->setMavCmdChoiceType(mavCmd);
    _mission_item.getCommand()->getMavCmdNavLand()->setLatitude(lat);
    _mission_item.getCommand()->getMavCmdNavLand()->setLongitude(lon);
    _mission_item.getCommand()->getMavCmdNavLand()->setAltitude(alt);
    _mission_item.setSeq(seq);
    _mission_item.setAutocontinue(1);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> mission_item_bytes;
    if (!serializer->serialize(_mission_item, mission_item_bytes)) {
        _exit(1);
    }

    int n_bytes = ::sendto(sock, &mission_item_bytes[0], mission_item_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
    
    std::cout << n_bytes << " bytes sent" << std::endl;

}

void mission_item_waypoint(float lat, float lon, float alt, common::MavFrame::EnumItem mavFrame, common::MavCmd::MavCmdChoice mavCmd, int seq);
void mission_item_waypoint(float lat, float lon, float alt, common::MavFrame::EnumItem mavFrame, common::MavCmd::MavCmdChoice mavCmd, int seq) {
    

    common::MissionItem _mission_item;
    _mission_item.setMagic(254,true);
    _mission_item.setSysid(255,true);
    _mission_item.setMsgid(27,true);
    _mission_item.setTargetComponent(1);
    _mission_item.setTargetSystem(1);
    _mission_item.setFrame(mavFrame);
    _mission_item.getCommand()->setMavCmdChoiceType(mavCmd);
    _mission_item.getCommand()->getMavCmdNavWaypoint()->setLatitude(lat);
    _mission_item.getCommand()->getMavCmdNavWaypoint()->setLongitude(lon);
    _mission_item.getCommand()->getMavCmdNavWaypoint()->setAltitude(alt);
    _mission_item.setSeq(seq);
    _mission_item.setAutocontinue(1);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> mission_item_bytes;
    if (!serializer->serialize(_mission_item, mission_item_bytes)) {
        _exit(1);
    }

    int n_bytes = ::sendto(sock, &mission_item_bytes[0], mission_item_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
    
    std::cout << n_bytes << " bytes sent" << std::endl;

}

void mission_start();
void mission_start(){

    common::CommandLong _mission_start;
    _mission_start.setMagic(254,true);
    _mission_start.setSysid(255,true);
    _mission_start.setMsgid(76,true);
    _mission_start.setSeq(1,true);
    _mission_start.setTargetComponent(1);
    _mission_start.setTargetSystem(1);
    _mission_start.setConfirmation(1,true);
    _mission_start.getCommand()->setMavCmdChoiceType(common::MavCmd::MAVCMD_CHOICE_MAVCMDMISSIONSTART);
    _mission_start.getCommand()->getMavCmdMissionStart()->setFirstItem(0);
    _mission_start.getCommand()->getMavCmdMissionStart()->setLastItem(1);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> mission_start_bytes;
    if (!serializer->serialize(_mission_start, mission_start_bytes)) {
        _exit(1);
    }

    int n_bytes = ::sendto(sock, &mission_start_bytes[0], mission_start_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
    
    std::cout << n_bytes << " bytes sent" << std::endl;

}

void clear_all();
void clear_all(){
    
    common::MissionClearAll _clear_all;
    _clear_all.setMagic(254,true);
    _clear_all.setSysid(255,true);
    _clear_all.setMsgid(45,true);
    _clear_all.setTargetComponent(1);
    _clear_all.setTargetSystem(1);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> clear_all_bytes;
    if (!serializer->serialize(_clear_all, clear_all_bytes)) {
        _exit(1);
    }

    int n_bytes = ::sendto(sock, &clear_all_bytes[0], clear_all_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
    
    std::cout << n_bytes << " bytes sent" << std::endl;
}

void set_mode(common::MavMode::EnumItem mavMode);
void set_mode(common::MavMode::EnumItem mavMode) {

    common::CommandLong _set_mode;
    _set_mode.setMagic(254,true);
    _set_mode.setSysid(255,true);
    _set_mode.setMsgid(76,true);
    _set_mode.setSeq(1,true);
    _set_mode.setTargetComponent(1);
    _set_mode.setTargetSystem(1);
    _set_mode.setConfirmation(1,true);
    _set_mode.getCommand()->setMavCmdChoiceType(common::MavCmd::MAVCMD_CHOICE_MAVCMDDOSETMODE);
    _set_mode.getCommand()->getMavCmdDoSetMode()->setMode(common::MavMode::MavModeManualArmed);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> set_mode_bytes;
    if (!serializer->serialize(_set_mode, set_mode_bytes)) {
        _exit(1);
    }

    int n_bytes = ::sendto(sock, &set_mode_bytes[0], set_mode_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
    
    std::cout << n_bytes << " bytes sent" << std::endl;

}

void mission_count(int count);
void mission_count(int count) {
    common::MissionCount _mission_count;
    _mission_count.setMagic(254,true);
    _mission_count.setSysid(255,true);
    _mission_count.setMsgid(44,true);
    _mission_count.setCount(count);
    _mission_count.setTargetComponent(1);
    _mission_count.setTargetSystem(1);

    sockaddr_in destination;
    destination.sin_family = AF_INET;
    destination.sin_port = htons(port);
    destination.sin_addr.s_addr = inet_addr(hostname.c_str());

    tangram::serializers::Serializer *serializer;
    common::DerivedEntityFactory derivedEntityFactory;
    tangram::serializers::MAVLINKSerializer mavlinkSerializer(&derivedEntityFactory);
    serializer = &mavlinkSerializer;

    std::vector<uint8_t> _mission_count_bytes;
    if (!serializer->serialize(_mission_count, _mission_count_bytes)) {
        _exit(1);
    }

    int n_bytes = ::sendto(sock, &_mission_count_bytes[0], _mission_count_bytes.size(), 0, reinterpret_cast<sockaddr*>(&destination), sizeof(destination));
    
    std::cout << n_bytes << " bytes sent" << std::endl;

}

int main(int argc, char const *argv[])
{
    
    set_mode(common::MavMode::MavModeManualArmed);

    heartbeat(minimal::MavType::MavTypeGcs, minimal::MavAutopilot::MavAutopilotInvalid);

    clear_all();

    mission_count(5);

    mission_item_takeoff(47.3977494, 8.5456072, 5, common::MavFrame::MavFrameGlobalRelativeAlt, common::MavCmd::MAVCMD_CHOICE_MAVCMDNAVTAKEOFF,0);
    
    mission_item_waypoint(47.3977456, 8.54556802, 5, common::MavFrame::MavFrameGlobalRelativeAlt, common::MavCmd::MAVCMD_CHOICE_MAVCMDNAVWAYPOINT,1);

    mission_item_waypoint(47.3977814, 8.545696512, 5, common::MavFrame::MavFrameGlobalRelativeAlt, common::MavCmd::MAVCMD_CHOICE_MAVCMDNAVWAYPOINT,2);

    mission_item_waypoint(47.3977957, 8.54556802, 5, common::MavFrame::MavFrameGlobalRelativeAlt, common::MavCmd::MAVCMD_CHOICE_MAVCMDNAVWAYPOINT,3);

    mission_item_land(47.3977, 8.5457, 5, common::MavFrame::MavFrameGlobalRelativeAlt, common::MavCmd::MAVCMD_CHOICE_MAVCMDNAVLAND, 4);

    sleep(1);

    mission_start();
    for (int i = 0; i < 30; i++){
        heartbeat(minimal::MavType::MavTypeGcs, minimal::MavAutopilot::MavAutopilotInvalid);
        sleep(1);
    }

    ::close(sock);

    return 0;
}