# Notes for Abstraction Example:
glfwTerminate();
According to the "Abstracting OpenGL into Classes" video, glfwTerminate() destroys the GLFW context
and so all OpenGL destructors (called by default at the end of prorgram) must be called for destruction before glfwTerminate(),
otherwise glfwTerminate() would created an invalid context and the destructors while doing that GLCALL() would give errors because
of that invalid context.

(Though that behavoir is expected (which can be avoided by calling destructors before glfwTerminate() or as done [in the video right here](//https://youtu.be/bTHqmzjm2UI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=1327), the behavoir is not seen in my implementation.))


# Materials

```c++
shader.bind();
shader.setUniform4f("u_color", r, 0.2, 0.5, 0.0);
renderer.draw(va, ib, shader);
```
The way to avoid above not-so-good way of passing uniforms to shader and eventuallly to renderer by using "Materials".

Materials = Shader & Set of Data (All it's Uniforms)
uniforms can be renderer specific uniform or per object uniform. (Refer to [this](https://youtu.be/jjaTTRFXRAk?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=679))


