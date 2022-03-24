# Vertex and Shapes

Based on Hello Triangle Tutorial on learnopengl.com

## Keywords
graphics pipeline, shaders, OpenGL Shading Language

## Notes
* The goal of graphics pipeline of OpenGL can be dividen into two major parts:
    * taking 3D coordinates and transforming them to 2D coordinates
    * taking 2D coordinates and transforming those to actual pixel coordinates

* The overall pipeline (output of one step serves input of other step) can be divided into several independent steps which can be run in a highly parallel fashion.
* Numerous processing 'cores' run small programs called shaders for each such step that can run in parallel.


# Reference
* [Hello Triangle](https://learnopengl.com/Getting-started/Hello-Triangle)
