#include "HelloMavlink.hpp"

HelloMavlink::HelloMavlink() : ScheduledWorkItem(MODULE_NAME, px4::wq_configurations::lp_default)
{}

HelloMavlink::~HelloMavlink()
{
	ScheduleClear();
}

void HelloMavlink::Run()
{
    if (should_exit()) {
        exit_and_cleanup();
        return;
    }

    vehicle_status_s status;
    if (_status_sub.update(&status)) {

        // 只有在狀態發生「改變」時才動作，不然 QGC 會被訊息淹沒
        if (status.arming_state != _last_arming_state) {

            if (status.arming_state == vehicle_status_s::ARMING_STATE_ARMED) {
                // 發送紅色緊急訊息
                mavlink_log_critical(&_mavlink_log_pub, "ALARM: MOTORS SPINNING!");
            }
            else {
                // 發送白色一般訊息
                mavlink_log_info(&_mavlink_log_pub, "SAFE: Motors Stopped.");
            }

            _last_arming_state = status.arming_state;
        }
    }
}

int HelloMavlink::task_spawn(int argc, char *argv[])
{
    HelloMavlink *instance = new HelloMavlink();
    if (instance) {
        _object.store(instance);
        _task_id = task_id_is_work_queue;
        instance->ScheduleOnInterval(100000); // 10Hz 檢查一次
        return PX4_OK;
    }
    return PX4_ERROR;
}

int HelloMavlink::print_usage(const char *reason) { return 0; }

extern "C" __EXPORT int hello_mavlink_main(int argc, char *argv[])
{
    return HelloMavlink::main(argc, argv);
}

int HelloMavlink::custom_command(int argc, char *argv[])
{
	return print_usage("unknown command");
}
