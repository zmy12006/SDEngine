#pragma once
#include <GLM\glm.hpp>
#include <GLM\gtx\transform.hpp>
#include <string>

using namespace glm;

class Transform {

public:
	/*
	@param Position
	+Y -> Right
	-Y -> Left
	+X -> Towards Camera
	-X -> Away From Camera
	+Z -> Up
	-Z -> Down
	*/
	Transform(const vec3 Position = vec3(0.0, 0.0, 0.0), const vec3 Rotation = vec3(0.0, 0.0, 0.0), const vec3 Scale = vec3(1,1,1)) :
		S_Position(Position),
		S_Rotation(Rotation),
		S_Scale(Scale) {}
	virtual ~Transform();

	vec3& GetPosition() { return S_Position; }
	vec3& GetRotation() { return S_Rotation; }
	vec3& GetScale() { return S_Scale; }

	void SetUniformScale(float Scale);

	inline mat4 GetModelMatrix() const {
		mat4 posMatrix = translate(S_Position);
		mat4 rotXMatrix = rotate(S_Rotation.x, vec3(1, 0, 0));
		mat4 rotYMatrix = rotate(S_Rotation.y, vec3(0, 1, 0));
		mat4 rotZMatrix = rotate(S_Rotation.z, vec3(0, 0, 1));
		mat4 scaleMatrix = scale (S_Scale);

		mat4 combinedRotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return posMatrix * combinedRotMatrix * scaleMatrix;
	}
	inline vec3 GetProjectedPosition() {
		mat4 posMatrix = translate(S_Position);
		return posMatrix * vec4(S_Position, 1.0);
	}
	inline vec3 GetForwardVector() { 
		mat4 rotXMatrix = rotate(S_Rotation.x, vec3(1, 0, 0));
		mat4 rotYMatrix = rotate(S_Rotation.y, vec3(0, 1, 0));
		mat4 rotZMatrix = rotate(S_Rotation.z, vec3(0, 0, 1));
		mat4 combinedRotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return  combinedRotMatrix[0];
	}
	inline vec3 GetUpVector() {
		mat4 rotXMatrix = rotate(S_Rotation.x, vec3(1, 0, 0));
		mat4 rotYMatrix = rotate(S_Rotation.y, vec3(0, 1, 0));
		mat4 rotZMatrix = rotate(S_Rotation.z, vec3(0, 0, 1));
		mat4 combinedRotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return  combinedRotMatrix[2];
	}
	inline vec3 GetRightVector() {
		mat4 rotXMatrix = rotate(S_Rotation.x, vec3(1, 0, 0));
		mat4 rotYMatrix = rotate(S_Rotation.y, vec3(0, 1, 0));
		mat4 rotZMatrix = rotate(S_Rotation.z, vec3(0, 0, 1));
		mat4 combinedRotMatrix = rotZMatrix * rotYMatrix * rotXMatrix;

		return  combinedRotMatrix[1];
	}
	inline void SetRotation(float Pitch, float Yaw, float Roll) {
		S_Rotation.x = radians(Pitch);
		S_Rotation.y = radians(Yaw);
		S_Rotation.z = radians(Roll);
	}
	inline std::string LocationToString() {return "X: " + std::to_string(S_Position.x) + "Y: " + std::to_string(S_Position.y) + "Z: " + std::to_string(S_Position.z); }
	inline std::string RotationToString() { return "P: " + std::to_string(degrees(S_Rotation.x)) + "Y: " + std::to_string(degrees(S_Rotation.y)) + "R: " + std::to_string(degrees(S_Rotation.z)); }
	inline std::string ScaleToString() { return "X: " + std::to_string(S_Scale.x) + "Y: " + std::to_string(S_Scale.y) + "Z: " + std::to_string(S_Scale.z); }
	inline std::string ForwardVectorToString() { 
		vec3 tempForward = GetForwardVector();
		return "X: " + std::to_string(tempForward.x) + "Y: " + std::to_string(tempForward.y) + "Z: " + std::to_string(tempForward.z); 
	}
	inline std::string UpVectorToString() {
		vec3 tempForward = GetUpVector();
		return "X: " + std::to_string(tempForward.x) + "Y: " + std::to_string(tempForward.y) + "Z: " + std::to_string(tempForward.z);
	}
	inline std::string RightVectorToString() {
		vec3 tempForward = GetRightVector();
		return "X: " + std::to_string(tempForward.x) + "Y: " + std::to_string(tempForward.y) + "Z: " + std::to_string(tempForward.z);
	}
private:
	vec3 S_Position;
	vec3 S_Rotation;
	vec3 S_Scale;
};

