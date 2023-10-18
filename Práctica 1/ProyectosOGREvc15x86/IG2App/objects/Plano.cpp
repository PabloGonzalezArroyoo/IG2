#include "Plano.h"

Plano::Plano(SceneNode* m, std::string name, int anch, int alt, std::string material) : EntidadIG(m) {
	// Atributos: nombre, orientación, anchura, idem altura, número de segmentos del plano en dirección X,
	// idem Y, booleano (crea normales perpendiculares), nº de conjuntos de coordenadas 2D creadas,
	// nº de veces que se repite la textura, idem v, orientación up de la textura 
	MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), anch, alt, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	Entity* plane = mSM->createEntity(name);
	plane->setMaterialName(material);
	mNode->attachObject(plane);
}