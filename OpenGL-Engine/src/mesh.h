//#include <map>
//#include <vector>
//#include <string>
//#include <GL\glew.h>
//#include <assimp\Importer.hpp>
//#include <assimp\scene.h>
//#include <assimp\postprocess.h>
//#include <glm/glm.hpp>
//
//struct Vertex {
//	glm::vec3 m_pos;
//	glm::vec2 m_tex;
//	glm::vec3 m_normal;
//};
//
//struct Texture {
//	unsigned int id;
//	std::string type;
//};
//
//class Mesh
//{
//public:
//	std::vector<Vertex> vertices;
//	std::vector<unsigned int> indices;
//	std::vector<Texture> textures;
//
//	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
//	void Draw();
//
//private:
//	unsigned int VAO, VBO, EBO;
//
//	void setupMesh();
//};