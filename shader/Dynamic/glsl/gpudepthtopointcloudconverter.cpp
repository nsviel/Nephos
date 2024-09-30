
k4a::image GpuDepthToPointCloudConverter::GenerateXyTable(const k4a::calibration &calibration,
                                                          k4a_calibration_type_t calibrationType)
{
    const k4a_calibration_camera_t &cameraCalibration = calibrationType == K4A_CALIBRATION_TYPE_COLOR ?
                                                            calibration.color_camera_calibration :
                                                            calibration.depth_camera_calibration;

    k4a::image xyTable = k4a::image::create(K4A_IMAGE_FORMAT_CUSTOM,
                                            cameraCalibration.resolution_width,
                                            cameraCalibration.resolution_height,
                                            cameraCalibration.resolution_width *
                                                static_cast<int>(sizeof(k4a_float2_t)));

    k4a_float2_t *tableData = reinterpret_cast<k4a_float2_t *>(xyTable.get_buffer());

    int width = cameraCalibration.resolution_width;
    int height = cameraCalibration.resolution_height;

    k4a_float2_t p;
    k4a_float3_t ray;

    for (int y = 0, idx = 0; y < height; y++)
    {
        p.xy.y = static_cast<float>(y);
        for (int x = 0; x < width; x++, idx++)
        {
            p.xy.x = static_cast<float>(x);

            if (calibration.convert_2d_to_3d(p, 1.f, calibrationType, calibrationType, &ray))
            {
                tableData[idx].xy.x = ray.xyz.x;
                tableData[idx].xy.y = ray.xyz.y;
            }
            else
            {
                // The pixel is invalid.
                //
                tableData[idx].xy.x = 0.0f;
                tableData[idx].xy.y = 0.0f;
            }
        }
    }

    return xyTable;
}
