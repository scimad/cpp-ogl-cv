# Notes for Abstraction Example:
glfwTerminate();
According to the "Abstracting OpenGL into Classes" video, glfwTerminate() destroys the GLFW context
and so all OpenGL destructors (called by default at the end of prorgram) must be called for destruction before glfwTerminate(),
otherwise glfwTerminate() would created an invalid context and the destructors while doing that GLCALL() would give errors because
of that invalid context.

(Though that behavoir is expected (which can be avoided by calling destructors before glfwTerminate() or as done [in the video right here](//https://youtu.be/bTHqmzjm2UI?list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&t=1327), the behavoir is not seen in my implementation.))
