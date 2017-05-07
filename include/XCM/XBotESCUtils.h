/*
 * Copyright (C) 2017 IIT-ADVR
 * Author: Arturo Laurenzi, Luca Muratore
 * email:  arturo.laurenzi@iit.it, luca.muratore@iit.it
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#ifndef __XBOT_ESC_UTILS_H__
#define __XBOT_ESC_UTILS_H__

#include <XBotCore-interfaces/XBotESC.h>

#include <XBotInterface/RobotInterface.h>

namespace XBot
{
class ESCUtils
{
public:
    
    typedef std::shared_ptr<ESCUtils> Ptr;
    
    explicit ESCUtils(XBot::RobotInterface::Ptr robot);
    
    bool setReferenceFromRobotStateTX( const std::map<int, XBot::RobotState::pdo_tx>& pdo_tx );
    bool setRobotStateFromRobotInterface( std::map<int, XBot::RobotState>& pdo );
    
    bool setRobotFTFromRobotInterface( std::map<int, XBot::RobotFT::pdo_rx>& ft );
    
protected:
    
private:
    
    XBot::RobotInterface::Ptr _robot;
    XBot::JointIdMap _joint_map;
    
    KDL::Wrench _wrench;
    

};
}

#endif //__XBOT_ESC_UTILS_H__