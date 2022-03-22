#include <open3d/Open3D.h>
#include <Eigen/Core>

using namespace open3d;
using namespace geometry;

int main(int argc, char** argv){
    auto icosa = open3d::geometry::TriangleMesh::CreateIcosahedron(1.0);
    icosa->ComputeVertexNormals();
    visualization::DrawGeometries({icosa});

    Eigen::Matrix4d trans;
    trans << 1.0f , 0.0f , 0.0f , 0.0f ,
        0.0f , 1.0f , 0.0f , 0.0f ,
        0.8f , 0.0f , 1.0f, 0.0f, 
        0.0f , 0.0f , 0.0f , 1.0f; 

    icosa->Transform(trans);
    open3d::visualization::DrawGeometries({icosa});


    return 0;
}
