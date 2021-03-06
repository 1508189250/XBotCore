/*
 * Copyright (C) 2017 IIT-ADVR
 * Author: Giuseppe Rigano
 * email:  giuseppe.rigano@iit.it
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

#ifndef __LOADER_H__
#define __LOADER_H__

#include <XCM/XBotPluginHandler.h>
#include <ros/ros.h>
#include <std_srvs/SetBool.h>


class Loader {
    
public:
  
  Loader(XBot::PluginHandler::Ptr pluginH);
  
  ~Loader();
  
  void init_internal();
  void loop_internal();

  static std::string name;
  
private:
    
  XBot::PluginHandler::Ptr _pluginHandler;
    
  bool callback(std_srvs::SetBoolRequest& req, std_srvs::SetBoolResponse& res, const std::string& port_name);
  
  std::shared_ptr<ros::NodeHandle> nh;
  std::map<std::string, ros::ServiceServer> _services;
  
  
};
#endif