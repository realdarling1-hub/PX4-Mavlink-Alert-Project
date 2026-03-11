#pragma once

#include <px4_platform_common/module.h>
#include <px4_platform_common/px4_work_queue/ScheduledWorkItem.hpp>
#include <uORB/Subscription.hpp>
#include <uORB/topics/vehicle_status.h>   // 核心狀態 Topic
#include <systemlib/mavlink_log.h>        // MAVLink Log 工具

class HelloMavlink : public ModuleBase<HelloMavlink>, public px4::ScheduledWorkItem
{
    public:
        HelloMavlink();
        ~HelloMavlink() override;

        static int task_spawn(int argc, char *argv[]);
        static int print_usage(const char *reason = nullptr);
        // 新增這一行：
	    static int custom_command(int argc, char *argv[]);

    private:
        void Run() override;

        // 訂閱無人機狀態
        uORB::Subscription _status_sub{ORB_ID(vehicle_status)};

        // MAVLink 日誌把手，必須初始化為 nullptr
        orb_advert_t _mavlink_log_pub{nullptr};

        // 用來記錄上一次的狀態，避免重複發送訊息
        uint8_t _last_arming_state{0};
};
