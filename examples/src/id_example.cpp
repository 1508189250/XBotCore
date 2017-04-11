#include <id_example.h>

REGISTER_XBOT_PLUGIN(IdExample, XBot::IdExample)


XBot::IdExample::IdExample()
{

}

bool XBot::IdExample::init_control_plugin(std::string path_to_config_file, XBot::SharedMemory::Ptr shared_memory, XBot::RobotInterface::Ptr robot)
{
    _robot = robot;
    _robot->model().getJointPosition(_q0);

    _model = ModelInterface::getModel(path_to_config_file);


    Eigen::VectorXd qmin, qmax;
    _robot->model().getJointLimits(qmin, qmax);

    double dqmin, dqmax, dq;
    dqmin = (_q0-qmin).minCoeff();
    dqmax = (qmax-_q0).minCoeff();
    dq = dqmin < dqmax ? dqmin : dqmax;

    _dq.setConstant(qmin.size(), dq);
}

void XBot::IdExample::on_start(double time)
{
    damp_motion = false;

    _robot->model().getJointPosition(_q0);
    _dq.setConstant(_robot->model().getJointNum(), 0.2);

    _first_loop_time = time;
    _robot->setStiffness(Eigen::VectorXd::Zero(_robot->getJointNum()));
    _robot->setDamping(Eigen::VectorXd::Zero(_robot->getJointNum()));
    _model->syncFrom(*_robot);
}

void XBot::IdExample::control_loop(double time, double period)
{
    static double PERIOD = 1.0;
    static double OMEGA = 2.0 * 3.1415 / PERIOD;

    if(command.read(current_command)){
        damp_motion = true;
        std::cout << "Damping motion!" << std::endl;
    }

    if( damp_motion ) OMEGA *= 0.995;

    _qref = _q0 + _dq * std::sin(OMEGA*(time-_first_loop_time));
    _qdotref = _dq * std::cos(OMEGA*(time-_first_loop_time)) * OMEGA;
    _qddotref = -1.0 * _dq * std::sin(OMEGA*(time-_first_loop_time)) * OMEGA * OMEGA;

    _model->syncFrom(*_robot, Sync::Position, Sync::Velocity);
    _model->setJointAcceleration(_qddotref); // FIXME syncFrom does the update, but now we need another one!!!!
    _model->update();

    _model->computeInverseDynamics(_tau);
    _model->getInertiaMatrix(_B);

    _robot->model().getJointPosition(_q);
    _robot->model().getJointVelocity(_qdot);

    double kp = 50, kd = 5;

    _tau += _B*( kp*(_qref-_q) + kd*(_qdotref-_qdot) );

    _model->setJointEffort(_tau);
    _robot->setPositionReference(_qref);
    _robot->setReferenceFrom(*_model, Sync::Effort);

    _robot->move();

}

void XBot::IdExample::on_stop(double time)
{
}

bool XBot::IdExample::close()
{

}