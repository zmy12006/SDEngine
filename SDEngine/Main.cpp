#include <iostream>
#include <GLEW/glew.h>
#include "Display.h"
#include "Shader.h"
#include "Texture2D.h"
#include "StaticMesh.h"
#include "Transform.h"
#include "Light.h"
#include <random>
#include "Grid.h"
#include "Engine.h"
#include "RenderingEngine.h"
#include "EyeActor.h"
#include "AssetManager.h"
#include "EngineStatics.h"

#undef main
using namespace glm;

/*
Physics
Collision
AI/Pathfinding
Resource Management
Content Creation

How to implement? (IMO)
What are concerns you have about it?


*/
Engine* S_Engine;
int main(int argc, char* argv[]) {
	S_Engine = Engine::GetInstance();
	if (!S_Engine->Init()) {		
		return 0;
	}
	init_logger("SD_EngineLog.txt");
	PrintToLog("Engine Launched!");

	Transform planeTransform;
	Material* planeMat = EngineStatics::GetDefaultMaterial();
	StaticMesh* plane = new StaticMesh("Plane", planeTransform, planeMat, "./res/Plane.fbx");
	S_Engine->GetWorld()->RegisterEntity(plane);

	Transform headTransform;
	headTransform.GetPosition().z = 7;
	SAsset* headAsset = S_Engine->GetAssetManager()->GetAsset("./Res/Assets/Head.sasset");
	StaticMesh* head = headAsset->GetAsStaticMesh("Head");
	head->SetTransform(headTransform);
	S_Engine->GetWorld()->RegisterEntity(head);

	Transform gizmoTransform;
	SAsset* gizmoAsset = S_Engine->GetAssetManager()->GetAsset("./Res/Assets/Gizmo.sasset");
	StaticMesh* gizmo = gizmoAsset->GetAsStaticMesh("Gizmo");
	gizmo->SetTransform(gizmoTransform);
	S_Engine->GetWorld()->RegisterEntity(gizmo);

	//Transform innerEyetransform;
	//innerEyetransform.SetUniformScale(0.5f);
	//innerEyetransform.SetRotation(-60, 0, 0);
	//innerEyetransform.GetPosition().z = 10;

	//SAsset* eyeAsset = S_Engine->GetAssetManager()->GetAsset("./Res/Assets/Eye.sasset");
	//StaticMesh* eyeMesh = eyeAsset->GetAsStaticMesh("Eye");
	//eyeMesh->SetTransform(innerEyetransform);
	//S_Engine->GetWorld()->RegisterEntity(eyeMesh);

	//Transform outerEyeTransform;
	//outerEyeTransform.SetUniformScale(0.5f);
	//outerEyeTransform.SetRotation(-60, 0, 0);
	//outerEyeTransform.GetPosition().z = 10;

	//SAsset* eyeClearAsset = S_Engine->GetAssetManager()->GetAsset("./Res/Assets/EyeClear.sasset");
	//StaticMesh* eyeClearMesh = eyeAsset->GetAsStaticMesh("EyeClear");
	//eyeClearMesh->SetTransform(outerEyeTransform);
	//S_Engine->GetWorld()->RegisterEntity(eyeClearMesh);

	//Grid grid(40, 2);
//	S_Engine->GetWorld()->RegisterEntity(&grid);
	int count = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				float r = (float)(rand()) / (float)(RAND_MAX);
				float g = (float)(rand()) / (float)(RAND_MAX);
				float b = (float)(rand()) / (float)(RAND_MAX);
				Transform tempTransform;
				tempTransform.GetPosition().x = (float)j * 5.5f - 5.5f;
				tempTransform.GetPosition().y = (float)i * 5.5f - 5.5f;
				tempTransform.GetPosition().z = 9 + (float)k * 6.5f;
				vec3 tempColor = vec3(r, g, b);
				float atten = (((float)(rand()) / (float)(RAND_MAX))+1)*20;
				tempTransform.SetUniformScale(0.25f);
				Light* tempLight = new Light("Light " + std::to_string(count), tempTransform, POINT, 25, tempColor, atten);
				tempLight->ToggleDebug(false);
				S_Engine->GetWorld()->RegisterLight(tempLight);
				count++;
			}
		}
	}

	Transform fillLightTransform;
	fillLightTransform.SetRotation(0, 100, 0);
	fillLightTransform.GetPosition().z = 30;
	Light* fillLight = new Light("Directional Light", fillLightTransform, DIRECTIONAL, 6, vec3(0.75, 0.9, 0.8));
	fillLight->ToggleDebug(false);
	fillLight->SetCastsShadows(true);
	S_Engine->GetWorld()->RegisterLight(fillLight);

	S_Engine->StartEngine();
	return 0;
}