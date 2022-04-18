#include <string>
#include <open3d/Open3D.h>

int main(int argc, char** argv){
    std::string filepath = "../../test-data/fragment.ply";

    open3d::geometry::PointCloud cloud;
    open3d::io::ReadPointCloudFromPLY (filepath, cloud, open3d::io::ReadPointCloudOption());

    auto cloud_ptr = std::make_shared<open3d::geometry::PointCloud>(cloud);
    open3d::visualization::DrawGeometries({cloud_ptr},"ZR::Read Ply");

    return 0;
}
