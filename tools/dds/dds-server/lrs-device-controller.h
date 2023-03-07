// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2022 Intel Corporation. All Rights Reserved.

#pragma once
#include <librealsense2/rs.hpp>  // Include RealSense Cross Platform API
#include <realdds/dds-stream-sensor-bridge.h>
#include <third-party/json_fwd.hpp>

#include <unordered_map>
#include <vector>

namespace rs2 {
    class frame;
}

namespace realdds {

class dds_device_server;
class dds_stream_server;
class dds_stream_profile;
class dds_option;

} // namespace realdds


namespace tools {

// This class is in charge of handling a RS device: streaming, control..
class lrs_device_controller
{
public:
    lrs_device_controller( rs2::device dev, std::shared_ptr< realdds::dds_device_server > dds_device_server );
    ~lrs_device_controller();

    void set_option( const std::shared_ptr< realdds::dds_option > & option, float new_value );
    float query_option( const std::shared_ptr< realdds::dds_option > & option );

private:
    std::vector< std::shared_ptr< realdds::dds_stream_server > > get_supported_streams();

    void start_streaming( const nlohmann::json & msg );
    void publish_frame_metadata( const rs2::frame & f );

    rs2::device _rs_dev;
    std::map< std::string, rs2::sensor > _rs_sensors;
    std::string _device_sn;
    realdds::dds_stream_sensor_bridge _bridge;

    std::map< std::string, std::shared_ptr< realdds::dds_stream_server > > _stream_name_to_server;

    std::vector< rs2::stream_profile > get_rs2_profiles( realdds::dds_stream_profiles const & dds_profiles ) const;

    std::shared_ptr< realdds::dds_device_server > _dds_device_server;
    bool _md_enabled;
};  // class lrs_device_controller

}  // namespace tools
