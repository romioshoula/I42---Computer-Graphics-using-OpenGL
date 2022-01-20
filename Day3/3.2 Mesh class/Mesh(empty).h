#pragma once
#include <vector>
#include "Types.h"
#include "Shader.h"
#include <gl\glew\glew.h>
#include<gl\glm\glm.hpp>
#include<gl\glm\gtc\type_ptr.hpp>
#include<gl\glm\gtx\transform.hpp>
class Mesh
{
private:
	GLuint vao;
	GLuint vbo;
	GLuint ibo;
	glm::vec3 position;
	glm::vec3 scale;
	glm::vec3 euler_angles;
	glm::mat4x4 model_mat;
	bool is_mode_mat_dirty;
	void update_model_mat();
	GLuint indices_count;
	std::shared_ptr<Shader> shader;
public:
	Mesh(std::vector<vertex> vertices,std::vector<GLuint> indices, std::shared_ptr<Shader> shader);
	static Mesh create_cube(std::shared_ptr<Shader> shader);
	static Mesh create_sphere(std::shared_ptr<Shader> shader, int iterations);
	static Mesh create_cylinder(std::shared_ptr<Shader> shader,int segments, float radius);
	void render(glm::mat4 view_mat, glm::mat4 proj_mat);
	void translate(float tx, float ty, float tz)
	{
		position = glm::vec3(position.x + tx, position.y + ty, position.z + tz);
		is_mode_mat_dirty = true;
	}
	glm::vec3 get_position() const
	{
		return position;
	}
	void set_scale(float sx, float sy, float sz)
	{
		scale = glm::vec3(scale.x*sx, scale.y*sy, scale.z*sz);
		is_mode_mat_dirty = true;
	}
	glm::vec3 get_scale()const
	{
		return scale;
	}
	void set_euler_angles(glm::vec3 _angles)
	{
		euler_angles = _angles;
		is_mode_mat_dirty = true;
	}
	glm::vec3 get_euler_angles() const
	{
		return euler_angles;
	}
	~Mesh();
};

