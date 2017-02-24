/*
   Copyright (C) 2016 Italian Institute of Technology

   Developer:
       Luca Muratore (2016-, luca.muratore@iit.it)
       
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

/**
 *
 * @author Luca Muratore (2016-, luca.muratore@iit.it)
*/


#ifndef __X_BOT_CORE_H__
#define __X_BOT_CORE_H__

#include <iit/advr/ec_boards_base.h>
#include <iit/ecat/advr/esc.h>

#include <iit/ecat/advr/pipes.h>

#include <XBotCore/XBotEcat.h>

#include <XBotCore-interfaces/IXBotJoint.h>
#include <XBotCore-interfaces/IXBotChain.h>
#include <XBotCore-interfaces/IXBotRobot.h>
#include <XBotCore-interfaces/IXBotFT.h>

#include <XBotCoreModel.h>

namespace XBot
{
    class XBotCore;
}


/**
 * @brief XBotCore: RT EtherCAT thread and RT (shared-memory) XBotCore interfaces implementation.
 * 
 */
class XBot::XBotCore : public   XBot::XBotEcat,
                       public   XBot::IXBotJoint,
                       public   XBot::IXBotChain,
                       public   XBot::IXBotRobot,
                       public   XBot::IXBotFT
                        
{
public:
    
    XBotCore(const char * config_yaml);
    virtual ~XBotCore();
    
    /**
     * @brief initialization function called before the control_loop
     * 
     * @param  void
     * @return void
     */
    virtual void control_init(void) final;
     
    /**
     * @brief Simply call the plugin handler loop function that will be implemented by the derived class: overridden from Ec_Thread_Boards_base
     * 
     * @param  void
     * @return 1 on plugin_handler_loop() success. 0 otherwise
     */
    virtual int control_loop(void) final;
    
    /**
     * @brief Plugin handler initialization: load the plugins, call the init() function of each plugin loaded
     * 
     * @param  void
     * @return true if all the plugin init() functions were successful, false otherwise
     */
    virtual bool plugin_handler_init(void) = 0;
    
    /**
     * @brief Plugin handler loop: call the run() function of each plugin loaded
     * 
     * @param  void
     * @return true if all the plugin run() functions were successful, false otherwise
     */
    virtual bool plugin_handler_loop(void) = 0;
    
    /**
     * @brief Plugin handler loop: call the close() function of each plugin loaded
     * 
     * @param  void
     * @return true if all the plugin close() functions were successful, false otherwise
     */
    virtual bool plugin_handler_close(void) = 0;
    
    /**
     * @brief Getter for the robot model
     * 
     * @param  void
     * @return XBotCoreModel the model of the robot loaded in XBotCore
     */
    XBot::XBotCoreModel get_robot_model(void);
    
    /**
     * @brief Getter for the URDF path
     * 
     * @param  void
     * @return std::string the URDF path to load
     */
    std::string get_urdf_path(void);
    
    /**
     * @brief Getter for the SRDF path
     * 
     * @param  void
     * @return std::string the SRDF path to load
     */
    std::string get_srdf_path(void);
    
    /**
     * @brief Getter for the chain names vector
     * 
     * @return std::vector< std::string> the chain names vector
     */
    std::vector<std::string> get_chain_names();
    
    // NOTE IXBotRobot getters
    virtual bool get_robot_link_pos(std::map<std::string, float>& link_pos) final;
    virtual bool get_robot_link_pos(std::map<int, float>& link_pos) final;
    
    virtual bool get_robot_motor_pos(std::map<std::string, float>& motor_pos) final;
    virtual bool get_robot_motor_pos(std::map<int, float>& motor_pos) final;
    
    virtual bool get_robot_link_vel(std::map<std::string, int16_t>& link_vel) final;
    virtual bool get_robot_link_vel(std::map<int, int16_t>& link_vel) final;
    
    virtual bool get_robot_motor_vel(std::map<std::string, int16_t>& motor_vel) final;
    virtual bool get_robot_motor_vel(std::map<int, int16_t>& motor_vel) final;
    
    virtual bool get_robot_torque(std::map<std::string, float>& torque) final;
    virtual bool get_robot_torque(std::map<int, float>& torque) final;
    
    virtual bool get_robot_temperature(std::map<int, uint16_t>& temperature) final;    
    virtual bool get_robot_temperature(std::map<std::string, uint16_t>& temperature) final;
    
    virtual bool get_robot_fault(std::map<int, uint16_t>& fault) final;    
    virtual bool get_robot_fault(std::map<std::string, uint16_t>& fault) final;

    virtual bool get_robot_rtt(std::map<int, uint16_t>& rtt) final;    
    virtual bool get_robot_rtt(std::map<std::string, uint16_t>& rtt) final;
    
    virtual bool get_robot_op_idx_ack(std::map<int, uint16_t>& op_idx_ack) final;    
    virtual bool get_robot_op_idx_ack(std::map<std::string, uint16_t>& op_idx_ack) final;
    
    virtual bool get_robot_aux(std::map<std::string, float>& aux) final;
    virtual bool get_robot_aux(std::map<int, float>& aux) final;

    // NOTE IXBotRobot setters
    virtual bool set_robot_pos_ref(const std::map<std::string, float>& pos_ref) final;
    virtual bool set_robot_pos_ref(const std::map<int, float>& pos_ref) final;
    
    virtual bool set_robot_vel_ref(const std::map<std::string, int16_t>& vel_ref) final;
    virtual bool set_robot_vel_ref(const std::map<int, int16_t>& vel_ref) final;
    
    virtual bool set_robot_tor_ref(const std::map<std::string, int16_t>& tor_ref) final;
    virtual bool set_robot_tor_ref(const std::map<int, int16_t>& tor_ref) final;
    
    virtual bool set_robot_gains(const std::map<std::string, std::vector<uint16_t> >& gains) final;
    virtual bool set_robot_gains(const std::map<int, std::vector<uint16_t> >& gains) final;
    
    virtual bool set_robot_fault_ack(const std::map<std::string, int16_t>& fault_ack) final;
    virtual bool set_robot_fault_ack(const std::map<int, int16_t>& fault_ack) final;
    
    virtual bool set_robot_ts(const std::map<int, uint16_t>& ts) final;    
    virtual bool set_robot_ts(const std::map<std::string, uint16_t>& ts) final;
    
    virtual bool set_robot_op_idx_aux(const std::map<int, uint16_t>& op_idx_aux) final;    
    virtual bool set_robot_op_idx_aux(const std::map<std::string, uint16_t>& op_idx_aux) final;
    
    virtual bool set_robot_aux(const std::map<std::string, float>& aux) final;
    virtual bool set_robot_aux(const std::map<int, float>& aux) final;

    // NOTE IXBotChain getters
    virtual bool get_chain_link_pos(std::string chain_name, std::map<std::string, float>& link_pos) final;
    virtual bool get_chain_link_pos(std::string chain_name, std::map<int, float>& link_pos) final;
    
    virtual bool get_chain_motor_pos(std::string chain_name, std::map<std::string, float>& motor_pos) final;
    virtual bool get_chain_motor_pos(std::string chain_name, std::map<int, float>& motor_pos) final;
    
    virtual bool get_chain_link_vel(std::string chain_name, std::map<std::string, int16_t>& link_vel) final;
    virtual bool get_chain_link_vel(std::string chain_name, std::map<int, int16_t>& link_vel) final;
    
    virtual bool get_chain_motor_vel(std::string chain_name, std::map<std::string, int16_t>& motor_vel) final;
    virtual bool get_chain_motor_vel(std::string chain_name, std::map<int, int16_t>& motor_vel) final;
    
    virtual bool get_chain_torque(std::string chain_name, std::map<std::string, float>& torque) final;
    virtual bool get_chain_torque(std::string chain_name, std::map<int, float>& torque) final;
    
    virtual bool get_chain_temperature(std::string chain_name, std::map<int, uint16_t>& temperature) final;    
    virtual bool get_chain_temperature(std::string chain_name, std::map<std::string, uint16_t>& temperature) final;
    
    virtual bool get_chain_fault(std::string chain_name, std::map<int, uint16_t>& fault) final;    
    virtual bool get_chain_fault(std::string chain_name, std::map<std::string, uint16_t>& fault) final;

    virtual bool get_chain_rtt(std::string chain_name, std::map<int, uint16_t>& rtt) final;    
    virtual bool get_chain_rtt(std::string chain_name, std::map<std::string, uint16_t>& rtt) final;
    
    virtual bool get_chain_op_idx_ack(std::string chain_name, std::map<int, uint16_t>& op_idx_ack) final;    
    virtual bool get_chain_op_idx_ack(std::string chain_name, std::map<std::string, uint16_t>& op_idx_ack) final;
    
    virtual bool get_chain_aux(std::string chain_name, std::map<std::string, float>& aux) final;
    virtual bool get_chain_aux(std::string chain_name, std::map<int, float>& aux) final;
    
    // NOTE IXBotChain setters
    virtual bool set_chain_pos_ref(std::string chain_name, const std::map<std::string, float>& pos_ref) final;
    virtual bool set_chain_pos_ref(std::string chain_name, const std::map<int, float>& pos_ref) final;
    
    virtual bool set_chain_vel_ref(std::string chain_name, const std::map<std::string, int16_t>& vel_ref) final;
    virtual bool set_chain_vel_ref(std::string chain_name, const std::map<int, int16_t>& vel_ref) final;
    
    virtual bool set_chain_tor_ref(std::string chain_name, const std::map<std::string, int16_t>& tor_ref) final;
    virtual bool set_chain_tor_ref(std::string chain_name, const std::map<int, int16_t>& tor_ref) final;
    
    virtual bool set_chain_gains(std::string chain_name, const std::map<std::string, std::vector<uint16_t> >& gains) final;
    virtual bool set_chain_gains(std::string chain_name, const std::map<int, std::vector<uint16_t> >& gains) final;
    
    virtual bool set_chain_fault_ack(std::string chain_name, const std::map<std::string, int16_t>& fault_ack) final;
    virtual bool set_chain_fault_ack(std::string chain_name, const std::map<int, int16_t>& fault_ack) final;
    
    virtual bool set_chain_ts(std::string chain_name, const std::map<int, uint16_t>& ts) final;    
    virtual bool set_chain_ts(std::string chain_name, const std::map<std::string, uint16_t>& ts) final;
    
    virtual bool set_chain_op_idx_aux(std::string chain_name, const std::map<int, uint16_t>& op_idx_aux) final;    
    virtual bool set_chain_op_idx_aux(std::string chain_name, const std::map<std::string, uint16_t>& op_idx_aux) final;
    
    virtual bool set_chain_aux(std::string chain_name, const std::map<std::string, float>& aux) final;
    virtual bool set_chain_aux(std::string chain_name, const std::map<int, float>& aux) final;
    
    // NOTE IXBotFT getters
    virtual bool get_ft(int ft_id, std::vector< float >& ft, int channels = 6) final;
    virtual bool get_ft_fault(int ft_id, uint16_t& fault) final;
    virtual bool get_ft_rtt(int ft_id, uint16_t& rtt) final;


private:
        
    /**
     * @brief Robot model loaded in XBotCore
     * 
     */
    XBotCoreModel model;
        
    /**
     * @brief The complete path the the urdf file to load
     * 
     */
    std::string urdf_path;
    
    /**
     * @brief The complete path the the srdf file to load
     * 
     */
    std::string srdf_path;
    
    /**
     * @brief Joint id to joint name map configuration file
     * 
     */
    std::string joint_map_config;

    /**
     * @brief map between the chain name and the id of the enabled joints in the chain 
     * 
     */
    std::map<std::string, std::vector<int>> robot;
    
    /**
     * @brief aux buffer for the last TX PDO
     * 
     */
    iit::ecat::advr::McEscPdoTypes::pdo_tx last_pdo_tx;
    

    
    // NOTE IXBotJoint getters
    virtual bool get_link_pos(int joint_id, float& link_pos) final;
    
    virtual bool get_motor_pos(int joint_id, float& motor_pos) final;
    
    virtual bool get_link_vel(int joint_id, int16_t& link_vel) final;
    
    virtual bool get_motor_vel(int joint_id, int16_t& motor_vel) final;
    
    virtual bool get_torque(int joint_id, float& torque) final;
    
    virtual bool get_temperature(int joint_id, uint16_t& temperature) final;
    
    virtual bool get_fault(int joint_id, uint16_t& fault) final;
    
    virtual bool get_rtt(int joint_id, uint16_t& rtt) final;
    
    virtual bool get_op_idx_ack(int joint_id, uint16_t& op_idx_ack) final;
    
    virtual bool get_aux(int joint_id, float& aux) final;
    
    virtual bool get_gains(int joint_id, std::vector< uint16_t >& gain_vector) final;
    
    // NOTE IXBotJoint setters
    virtual bool set_pos_ref(int joint_id, const float& pos_ref) final;
    
    virtual bool set_vel_ref(int joint_id, const int16_t& vel_ref) final;
    
    virtual bool set_tor_ref(int joint_id, const int16_t& tor_ref) final;
    
    virtual bool set_gains(int joint_id, const std::vector<uint16_t>& gains) final;
    
    virtual bool set_fault_ack(int joint_id, const int16_t& fault_ack) final;
    
    virtual bool set_ts(int joint_id, const uint16_t& ts) final;
    
    virtual bool set_op_idx_aux(int joint_id, const uint16_t& op_idx_aux) final;
    
    virtual bool set_aux(int joint_id, const float& aux) final;

    

};

#endif //__X_BOT_CORE_H__
