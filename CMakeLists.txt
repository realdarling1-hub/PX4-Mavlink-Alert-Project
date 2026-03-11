px4_add_module(
    MODULE modules__hello_mavlink
    MAIN hello_mavlink
    SRCS
        HelloMavlink.cpp
    DEPENDS
        px4_work_queue
    )
