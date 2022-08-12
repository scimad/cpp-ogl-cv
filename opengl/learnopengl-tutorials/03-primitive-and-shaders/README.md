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
* Shaders are written in OpenGL Shading Language (GLSL)
* `GL_POINTS`, `GL_TRIANGLES` and `GL_LINE_STRIP` are some primitives that are given as hint to OpenGL to specify what kind of render type we want to form using a collection of vertex / color data.

### Differents of OpenGL Pipeline
* The first part is vertex shader which transforms 3D coordinates to a different 3D coordinate
* The primitive assembly takes input vertices and assemble these point(s) to form a primitive.
* Geometry shader can (in some way) manupulate to generate other primitives using output primitive from previous step. (??)
* Rasterization stage maps resulting primitive(s) to corresponding pixels and its results are 'fragments'. (A fragment is all the data required to render a single pixel.)
* Fragment shader can make use of advanced effects such as light, shadows, color of light, etc. to calculate final pixel color. (Also note, clipping is performed before running fragment shader.)
* Alpha testing and blending checks depth (and stencil) values to find occlusion and if resulting pixels should be painted or discarded and perform blending using alpha (opacity) values.

* In modern OpenGL, we are required to define at least a vertex and fragment shader of our own.

# Reference
* [Hello Triangle](https://learnopengl.com/Getting-started/Hello-Triangle)
