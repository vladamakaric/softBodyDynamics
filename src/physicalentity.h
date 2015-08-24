#ifndef PHYSICAL_ENTITY
#define PHYSICAL_ENTITY

#include "Vector.h"

class CPhysicalEntity
{
public:
	static int globalID;
	int ID;
	CVector position;

	CPhysicalEntity() {ID = globalID++;}
	bool operator==(const CPhysicalEntity &pe) { return ID == pe.ID; }

	virtual void Update(double deltaT)=0;
};
#endif
