#include "Plano.h"

Plano::Plano(SceneNode* m, std::string name, int anch, int alt, std::string material) : EntidadIG(m) {
	// Atributos: nombre, orientaci�n, anchura, idem altura, n�mero de segmentos del plano en direcci�n X,
	// idem Y, booleano (crea normales perpendiculares), n� de conjuntos de coordenadas 2D creadas,
	// n� de veces que se repite la textura, idem v, orientaci�n up de la textura 
	MeshManager::getSingleton().createPlane(name, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Plane(Vector3::UNIT_Y, 0), anch, alt, 100, 80, true, 1, 1.0, 1.0, Vector3::UNIT_Z);

	Entity* plane = mSM->createEntity(name);
	plane->setMaterialName(material);
	mNode->attachObject(plane);
}