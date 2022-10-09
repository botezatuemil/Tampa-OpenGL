
# Tampa Real Terrain with OpenGL

An app that renders Mountain Tampa from Brasov with camera movement and 
terrain collider




## Screenshots

![image1](https://user-images.githubusercontent.com/74835450/194766068-8430ac9e-275c-4df1-ab71-5f348e366463.png)

![image2](https://user-images.githubusercontent.com/74835450/194766069-928b694a-9b47-4b6b-996c-855697f32ebb.png)

![image3](https://user-images.githubusercontent.com/74835450/194766064-5aad9533-c29a-4130-8bd8-dd130c1bf5d4.png)
## Features

- Skybox
- Collision with terrain
- Camera movement



## Optimizations

Because of the map size, the model has a very large data set of vertexes, more then 4 million, so a complete traversal will substantially decrease
the frame rate when the user moves the camera. So, the size of the map was reduced 15 times by calculating a new position
that will be the average of the 15 most close vertexes. The quality of the map was not reduced because the vertexes are too close to each other and the camera collider is large enough.

After that the distance between the current camera position and the terrain was calculated with hypot function with a respect to a threshold.

```c++
for (int i = 0; i < tampa.meshes.size(); ++i) {
		average = glm::vec3(0, 0, 0);
		const Mesh& mesh = tampa.meshes[i];
		int j = 0, steps = 0;

		while (j < mesh.vertices.size())
		{
			if (steps < averageSteps)
			{
				++steps;
				average += mesh.vertices[j].Position;
			}
			else
			{
				steps = 0;
				average /= averageSteps;
				meshAndVertex[i].push_back(average);
				average = glm::vec3(0, 0, 0);
			}

			++j;
		}
}
```

```c++
for (const auto& mesh : meshAndVertises) {

	for (const auto& vertex : mesh) {

		float dis = hypot(hypot(position.x - vertex.x,
			position.y - vertex.y), position.z - vertex.z);
		if (dis <= 0.3) {
			return false;
		}
	}
    return true
```

## Tech Stack

- C++
- OpenGL
- Assimp library for object loading
- Blender
- RenderDoc



