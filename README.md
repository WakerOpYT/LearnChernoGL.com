## \# 🎮 Smoc Engine - OpenGL Abstraction Layers

## 

## This project contains a set of C++ wrappers for OpenGL to simplify the management of Buffers, Vertex Arrays, and Shaders. 

## 

## \## 🛠 Modules Overview

## 

## \### 1. Shader Manager (Shader.h)

## Handles the reading, compilation, and linking of GLSL shaders.

## \- ParseShaderFromFiles(vert, frag): Loads vertex and fragment source from separate files.

## \- CreateShader(vertSrc, fragSrc): Compiles and links shaders into a program.

## 

## Usage:

## &nbsp;   auto source = ParseShaderFromFiles("res/shaders/v.shader", "res/shaders/f.shader");

## &nbsp;   unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);

## &nbsp;   glUseProgram(shader);

## 

## ---

## 

## \### 2. Vertex Buffer (VertexBuffer.h)

## Manages the GL\_ARRAY\_BUFFER (VBO). Holds the raw vertex data.

## 

## Usage:

## &nbsp;   VertexBuffer vbo(vertices, sizeof(vertices));

## 

## ---

## 

## \### 3. Vertex Buffer Layout (VertexBufferLayout.h)

## The "Interpreter" for your raw data. Defines the attributes (position, texture coords, etc.).

## \- Note: Stride is calculated automatically as you push elements.

## 

## Usage:

## &nbsp;   VertexBufferLayout layout;

## &nbsp;   layout.Push<float>(3); // Position (x, y, z)

## &nbsp;   layout.Push<float>(2); // Texture Coords (u, v)

## 

## ---

## 

## \### 4. Vertex Array (VertexArray.h)

## The "Master State." Links a VertexBuffer with a VertexBufferLayout.

## \- Note: You must call AddBuffer to define the layout and enable attributes.

## 

## Usage:

## &nbsp;   VertexArray vao;

## &nbsp;   vao.AddBuffer(vbo, layout);

## &nbsp;   vao.Bind();

## 

## ---

## 

## \### 5. Index Buffer (IndexBuffer.h)

## Manages the GL\_ELEMENT\_ARRAY\_BUFFER (IBO/EBO). Defines the drawing order.

## 

## Usage:

## &nbsp;   IndexBuffer ibo(indices, 6); // 6 is the count of indices

## 

## ---

## 

## \## 🚀 Drawing Workflow (The Smoc Way)

## 

## To render an object, follow this state-binding order to avoid 1282 errors:

## 

## 1\. Prepare State:

## &nbsp;   glUseProgram(shader);

## &nbsp;   vao.Bind();

## &nbsp;   ibo.Bind();

## 

## 2\. Draw:

## &nbsp;   glDrawElements(GL\_TRIANGLES, ibo.GetCount(), GL\_UNSIGNED\_INT, nullptr);

## 

## \## ⚠️ Common Gotchas

## \- Core Profile: You MUST bind a VAO before calling glDrawElements or glVertexAttribPointer.

## \- Stride Bug: If the geometry looks "exploded," check that VertexBufferLayout is multiplying count \* size.

## \- IBO Unbinding: Do not unbind the GL\_ELEMENT\_ARRAY\_BUFFER while a VAO is active, or the VAO will forget its index buffer.

