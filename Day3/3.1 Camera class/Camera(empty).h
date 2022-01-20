#pragma once
#include <gl\glm\glm.hpp>
#include<gl\glm\gtx\transform.hpp>
#include "Mesh.h"
enum class PROJECTION_TYPE
{
	ORTHOGRAPHIC,
	PERSPECTIVE
};
class Camera
{
protected:
	float width;
	//view
	glm::vec3 position;
	glm::vec3 up;
	glm::vec3 look;
	glm::mat4 view_mat;
	//proj
	float z_near;
	float z_far;
	float aspect_ratio;
	//orthographic
	float height;
	//perspectvie
	float fov;
	glm::mat4 proj_mat;
	PROJECTION_TYPE projection_type;
public:
	Camera(PROJECTION_TYPE _projection_type, float _width,float _height);
	~Camera();
	glm::mat4 virtual get_view();
	glm::mat4 virtual get_PerspectiveProj();
	glm::mat4 virtual get_ORTHOGRAPHICProj();
	void set_lookAt(glm::vec3 pos, glm::vec3 up, glm::vec3 _up);
	void SetPerspectiveProjection(float fov, float w, float h, float Zn, float Zf);
	void SetORTHOGRAPHICProjection(float left, float right, float top,float bottom, float Zn, float Zf);
};

